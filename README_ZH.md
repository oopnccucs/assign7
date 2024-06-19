# Programming Assignment #7

**Due:2024/6/11 23:59:59**

NCCU OOP 112 spring

author: 111703045 李奕辰 / @organic_san at 2024/5/26

---

## Topic: 建立一個控制台的RPG遊戲(Part 3)
## Objective: 使用 virtual class 建立遊戲的 MVC 架構

## Description

### 遊戲目標
使用控制台建立一個RPG的小遊戲，包含進入遊戲、移動、切換房間，以及戰鬥、收尾等流程。

在進入遊戲之後，遊戲會來到以35 * 20的格子單位所建構成的房間，也就是遊戲中的地圖。玩家可以使用WASD進行前後左右的操作，操作名為「PL」的玩家圖示進行在房間中前後左右的移動，並且會受到牆壁的阻擋。

透過來到房間的左右側進行房間的切換，其中本次作業只考慮左右之間的地圖切換，不考慮上下之間的房間切換。房間透過 `id` 彼此左右連接，最左邊為0號的房間，每往右側的房間，房間`id`會+1，往左側的房間時，房間id會-1。但是不能前往資料不存在的房間。

遊戲中會出現有自我移動方式的敵人，需要設計怪物的移動模式。在遭遇怪物之後，將會進入戰鬥模式，此時玩家可以做出從選單中選擇以下四種操作：攻擊、防禦、猛力一擊、以及回複，詳細的差異將於後續作業中說明。

如果被怪物擊倒，將進入遊戲結束狀態，而怪物可以設定成最終boss，擊倒有最終boss標記的敵人時，則將進入遊戲過關狀態。

完整版本的遊戲試玩可以執行這個程式：<br>
`./example/rpg-game-full-example`

### 本次作業目標

本次作業的目標是建立遊戲的 MVC 架構。MVC 架構是將 Model (模型)、View (顯示)、Controller (控制器) 分離的軟體架構。

在這次的作業中，我們會將 `Move`、`Battle`、`Pause` 等等的行為分開包裝成各自繼承自 `GameProcessBase Class` 的不同 Class，並且透過 `Controller Class` 控制與決定現在要執行的 Game Process。

首先我們需要將 Controller 中關於地圖上的移動處理搬遷到 gameprocess/move 中的 Move Class 中，透過回傳 `GameProcess::ProcessInfo` 中的 

- `CONTINUE`
- `MOVE_FINISH_ROOMCHANGE_LEFT`
- `MOVE_FINISH_ROOMCHANGE_RIGHT`
- `MOVE_FINISH_PAUSE`
- `MOVE_FINISH_BATTLE`

等狀態來告知 Controller 下一步需要執行的內容。

`Controller` 接收到不同的 `ProcessInfo` 後，再由 `Controller` 做出相對應的行為，例如狀態轉移，或是房間的左右移動。

接著需要完成 `Battle Class` 的設計，當遊戲進入戰鬥狀態的時候，初始的 state 為 `ACTION_SELECTING`，在戰鬥結束前，會不斷在 `ACTION_SELECTING` -> `TURN_END` -> `ACTION_SELECTING` 的 state 間循環。當其中一方的血量扣減到 0 後，遊戲進入 `ENEMY_DEAD` 或 `PLAYER_DEAD` state，展示這場戰鬥的結果，最後回傳勝負結果至 `Controller`，並由 `Controller` 負責接下來的處理。

在 `Move` Process中，玩家與敵人在同一個座標的時候，會進入 `Battle` Process。在戰鬥中，玩家可以在選單頁面上下選擇，來決定要使用的戰術，並按下確認鍵執行戰術。選單的上下切換使用 `W` 代表上，`S` 代表下，`Enter` 或空白鍵代表確認。在所有 state 的切換之間，都需要被按下確認鍵之後才能到下一個 state (即，顯示回合結果與戰鬥結果的頁面不能一幀閃過，需要等待按下確認鍵後才能跳轉頁面。)

玩家與怪物在戰鬥過程中可以選擇 

1. 攻擊 (Attack)
2. 防守 (Defend)
3. 奮力一擊 (Force Attack)

的操作，怪物會在這三種操作中隨機且平均的選擇一個。為了提升遊戲性，在戰鬥過程中，玩家還可以額外選擇

4. 回復 (Heal)

的操作。

戰鬥過程中造成的傷害計算方式如下：

1. 當使出攻擊時，造成的傷害 = 角色傷害 * `ATTACK_MULTIPLIER`
2. 當使出奮力一擊時，造成的傷害 = 角色傷害 * `FORCE_ATTACK_MULTIPLIER`
3. 當使出防禦或回復時，不造成傷害。

4. 當對方使出防禦時，造成的傷害 = 計算後的傷害 / `DEFEND_MULTIPLIER`
5. 當對方使出奮力一擊或回復時，造成的傷害 = 計算後的傷害 * `FORCE_ATTACK_MULTIPLIER`

在戰鬥結束後，如果玩家敗北，則以 `GameOver` Process 結束遊戲，如果玩家獲勝，而該怪物為 last boss，則以 `GameClear` Process 結束遊戲，若非 last boss，則回到 `Move` Process。

在預設情況下，在第二個房間的 `Slime` 都不是 last boss，而在第三個房間的 `Dragon` 則是 last boss。

以上是 `Battle Class` 的說明。

接著需要完成 `Pause Class`，只需要在 `Move` Process 時考慮是否要進入 `Pause` Process。預設的 `Pause` Key 是 esc 鍵，當按下 esc 鍵時進入 `Pause` Process，而按下任何一個按鈕回到遊戲狀態中。

最後是 `GameClear Class` 與 `GameOver Class`，這兩個 Class 不需要調整內部設計，只需要在 `Controller` 中加入觸發這兩個 Process 的流程即可。

經過以上的程序，render的部分將由各自的 Class 的 `render()` function 處理，因此在 `Controller` 的 `render()` 中，只需要呼叫當下的 Process 的 `render()` 即可。所有的 `render()` 已經設計完成，不需處理輸出處理的排版部分。

### 需要完成的內容

- 請根據這個 git 記錄中的 `assign 6 code` 的 commit (92e17a3) 和 `assign 7 code` 的 commit (c859cfc) 的差異，更新您完成的 assign6 的完成版。
  具體而言，請根據 github 上的 [這個網址](https://github.com/oopnccucs/assign7/commit/c859cfc7337d23e81f5e8035a8f448298b700a33) 進行比較，或是使用 `$git checkout <commit-hash>` 進行commit間的切換與比較。

- 將 `Move` 相關的行為從 `Controller` 移動至 `gameprocess/move` 中
- 依據說明完成 `Battle` 的設計
- 依據說明完成 `Pause` 的設計
- 在 `controller` 中加入 Process 的流程控制邏輯
- 恭喜完成本學期的所有 assign 作業！

- 額外加分要素：可以繼續延伸本遊戲的架構，例如加入遊戲開頭、戰鬥更有趣，或是等級系統等內容。請將對於遊戲要素進行的調整描述在bonus.txt中，可以依功能內容與完成度獲得額外的加分。

## Sample Output

請參見 `./example/rpg-game-full-example` 的執行結果，若順利的話會出現以下圖片：

![pic](https://i.imgur.com/lhKgeVc.png)

其中`WW`代表草地，`██`代表牆壁，`DR`代表門，`PL`代表角色。

場地物件的名稱與種類記錄在 `./src/gameobjects/room/roomstate.h` 中。

在地圖的移動過程中按下 esc 鍵，會進入暫停模式：

![pic](https://i.imgur.com/uX8z5Kd.png)

在暫停模式時，按下任意鍵即可回到地圖的移動模式。

移動到房間的右側邊緣可以移動到第二個房間，當移動到第二個房間時，會出現如下結果：

![pic](https://i.imgur.com/9By0Wzi.png)

其中`WW`代表草地，`▲▲`代表山岩，`==`代表史萊姆，`PL`代表角色。

史萊姆會在每一幀往隨機方向前進一格，不會受到草地的阻擋，會受到山岩的阻擋。目前當玩家與史萊姆重疊的時候，進入戰鬥模式。

如果進入戰鬥模式，會看到如下結果：

![pic](https://i.imgur.com/LOVQmNc.png)

玩家可以操作W與S選擇選單，詳細流程請參見上方說明或實際執行程式確認。

移動到第三個房間時，會出現如下結果：

![pic](https://i.imgur.com/vpGXOVT.png)

其中`██`代表牆壁，`▲▲`代表山岩，`DR`代表門，`Dn`代表龍，`PL`代表角色，`~~`或`……`代表水。

龍不會移動。

當玩家戰勝/戰敗於龍的時候，進入遊戲過關/遊戲結束畫面，並結束遊戲：

![pic](https://i.imgur.com/w9sR40f.png)

玩家給予龍傷害

![pic](https://i.imgur.com/Z8ou9Wx.png)

戰鬥由玩家獲勝

![pic](https://i.imgur.com/2kxsgQK.png)

遊戲結束


## 評分標準

| 評分標準 | 分數 |
| - | - |
| 上傳檔案 | 20分 |
| 可以編譯 | 15分 |
| 人物(PL)與史萊姆或龍重疊時會進入戰鬥 | 15分 |
| 戰鬥的操作方式流程與規則相同 | 10分 |
| 於地圖移動狀態按下 esc 鍵時會進入暫停狀態 | 15分 |
| 完成 GameOver 與 GameClear 的處理 | 15分 |
| 使用 virtual class 實作 MVC 架構 | 10分 |
| **合計** | **100分** |
| 追加遊戲設計 | 10 ~ 30分 |
| **合計** | **130分** |

註：加分要素不限制內容，請將對於這個遊戲的進一步設計描述在bonus.txt中，將依新增內容與完成度給予額外加分。


## Assignment Directory
`/usr/local/class/oop/assign/assign7`
or https://github.com/oopnccucs/assign7


## 作業繳交方式
在OOP主機中，assign7資料夾下，輸入：
```
/usr/local/class/oop/bin/submit 7
```
繳交本次作業。


## Files in the Assignment Directory

src<br>
| -- gamecore: 輸入轉換處理與遊戲的流程呼叫<br>
|<br>
| -- functions<br>
|<br>
| -- controller*: 遊戲整體的流程控管<br>
|<br>
| -- gameobjects: 遊戲物件與房間的定義<br>
|<br>
| ---/_ gameprocess*: 將遊戲各個流程拆分成不同的執行個體<br>
|     | -- move*: 移動的處理<br>
|     | -- pause*: 暫停的處理<br>
|     | -- battle*: 戰鬥的處理<br>
|     | -- gameover*: 遊戲結束的處理<br>
|     | -- gameclear*: 遊戲過關的處理<br>
|<br>

*: 本次主要作業範圍

## Implementation Notes

編譯:`$make`

執行: `$make run`