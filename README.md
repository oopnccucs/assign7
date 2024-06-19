# Programming Assignment #7

**Due:2024/6/11 23:59:59**

NCCU OOP 112 spring

author: 111703045 李奕辰 / @organic_san at 2024/5/26

---

## Topic: Building a Console RPG Game (Part 3)
## Objective: Use virtual class to establish the MVC architecture for the game

## Description

### Game Objective

Create a small RPG game using the console, including processes such as entering the game, moving, switching rooms, battling, and ending.

Upon entering the game, the player will enter a room constructed of grid units of 35 * 20, which represents the map in the game. The player can use WASD keys for up, down, left, and right movements respectively. The player icon, labeled as "PL," will move within the room accordingly and will be obstructed by walls.

Rooms can be switched by moving to the left or right side of the current room. For this assignment, only horizontal room switching is considered, and vertical room switching is not. Rooms are connected horizontally via an id parameter. The room with the id of 0 is the leftmost room, and as you move right, the id increases by 1. Conversely, as you move left, the id decreases by 1. However, it's not possible to move to a room that does not exist.

Enemies with self-moving capabilities will appear in the game, requiring the design of monster movement patterns. Upon encountering a monster, the game will enter battle process. At this point, the player can choose from four options in a menu: Attack, Defend, Force Attack, and Heal. Detailed differences will be explained in subsequent assignments.

If the player is defeated by a monster, the game enters a game over state. Monsters can be set as final boss, and defeating an enemy marked as the final boss will lead to a game clear state.

A full version of the game can be played by executing this program:<br>
`./example/rpg-game-full-example`

### Objectives for this Assignment

The goal of this assignment is to establish the MVC architecture for the game. The MVC architecture separates the Model, View, and Controller components.

In this assignment, we will package behaviors such as `Move`, `Battle`, and `Pause` into different classes that inherit from the `GameProcessBase Class`, and control them through the `Controller Class`.

First, we need to move the movement handling on the map from the Controller to the Move Class in `gameprocess/move`, and use the returned status in `GameProcess::ProcessInfo` to inform the Controller of the next steps:

- `CONTINUE`
- `MOVE_FINISH_ROOMCHANGE_LEFT`
- `MOVE_FINISH_ROOMCHANGE_RIGHT`
- `MOVE_FINISH_PAUSE`
- `MOVE_FINISH_BATTLE`

The `Controller` will receive different `ProcessInfo` and perform corresponding actions, such as state transitions or room changing.

Next, design the `Battle Class`. When the game enters battle mode, the initial state is `ACTION_SELECTING`, and it will cycle between `ACTION_SELECTING` -> `TURN_END` -> `ACTION_SELECTING` until one side's health reaches 0. The game then enters the `ENEMY_DEAD` or `PLAYER_DEAD` state to show the battle results, returning the outcome to the `Controller`, which handles the next steps.

In the `Move` Process, when the player and the enemy are at the same coordinates, it will enter the `Battle` Process. During the battle, player can navigate the menu using W and S to choose tactics and press the confirm key to execute them. Switching the menu up and down uses `W` for up and `S` for down, with `Enter` or space bar for confirmation. All state transitions need to wait for the confirmation key before moving to the next state (i.e., pages displaying turn results and battle results cannot flash in one frame and need to wait for the confirmation key before switching).

During battle, player and enemy can choose from:

1. Attack
2. Defend
3. Force Attack

Enemy will randomly and evenly choose from these three actions. To enhance gameplay, player can also choose:

4. Heal

The damage calculation during battle is as follows:

1. When using Attack, damage dealt = character damage * `ATTACK_MULTIPLIER`
2. When using Force Attack, damage dealt = character damage * `FORCE_ATTACK_MULTIPLIER`
3. No damage is dealt when using Defend or Heal.

4. When the opponent uses Defend, damage dealt = calculated damage / `DEFEND_MULTIPLIER`
5. When the opponent uses Force Attack or Heal, damage dealt = calculated damage * `FORCE_ATTACK_MULTIPLIER`

After the battle, if the player loses, the game ends with the `GameOver` Process. If the player wins and the enemy is the "last boss", the game ends with the `GameClear` Process. If not, it returns to the `Move` Process.

By default, the `Slime`s in the second room is not the "last boss", while the `Dragon` in the third room is the "last boss".

The `Battle Class` description is above.

Next, complete the `Pause Class`. Only consider entering the `Pause` Process during the `Move` Process. The default `Pause` key is the esc key. Pressing esc enters the `Pause` Process, and pressing any key returns to the game state.

Finally, for the `GameClear Class` and `GameOver Class`, no internal design adjustments are needed. Simply add the processes to the `Controller`.

After these steps, the rendering part will be handled by the `render()` function of each class. In the `Controller`'s `render()`, just call the current Process's `render()`. All `render()` functions are designed and do not require output formatting adjustments.

### Tasks to Complete

- Based on the differences between the `assign 6 code` commit (92e17a3) and the `assign 7 code` commit (c859cfc) in the git log, update your completed version of assign6.
  Specifically, compare based on [this URL](https://github.com/oopnccucs/assign7/commit/c859cfc7337d23e81f5e8035a8f448298b700a33) on GitHub, or use `$git checkout <commit-hash>` to switch and compare commits.

- Move the `Move` related behavior from the `Controller` to `gameprocess/move`.
- Complete the design of `Battle` as described.
- Complete the design of `Pause` as described.
- Add Process flow control logic to the `controller`.
- Congratulations on completing all assignments for this semester!

- Extra Bonus Factors: You can extend the game's structure, for example, by adding an opening scene, making battles more interesting, or incorporating a level system. Please describe any adjustments made to the game elements in the bonus.txt file. Additional points can be earned based on the functionality and completeness of the content.

## Sample Output

Refer to the execution result of `./example/rpg-game-full-example`. If successful, the following image will appear:

![pic](https://i.imgur.com/lhKgeVc.png)

`WW` represents grass, `██` represents walls, `DR` represents doors, and `PL` represents the player.

The names and types of field objects are recorded in `./src/gameobjects/room/roomstate.h`.

During map movement, pressing the esc key will enter pause mode:

![pic](https://i.imgur.com/uX8z5Kd.png)

In pause mode, pressing any key will return to map movement mode.

Moving to the right edge of the room will move to the second room. When moving to the second room, the following result will appear:

![pic](https://i.imgur.com/9By0Wzi.png)

`WW` represents grass, `▲▲` represents rocks, `==` represents slimes, and `PL` represents the player.

Slimes move one square in a random direction every frame, not blocked by grass but blocked by rocks. When the player and the slime overlap, combat mode starts.

In battle mode, the following result will appear:

![pic](https://i.imgur.com/LOVQmNc.png)

Players can use W and S to navigate the menu. Refer to the above description or run the program to confirm the detailed process.

Moving to the third room will result in:

![pic](https://i.imgur.com/vpGXOVT.png)

`██` represents walls, `▲▲` represents rocks, `DR` represents doors, `Dn` represents the dragon, `PL` represents the player, and `~~` or `……` represents water.

The dragon does not move.

When the player wins/loses against the dragon, the game ends with a Game Clear/Game Over screen:

![pic](https://i.imgur.com/w9sR40f.png)

Player dealing damage to the dragon

![pic](https://i.imgur.com/Z8ou9Wx.png)

Player wins the battle

![pic](https://i.imgur.com/2kxsgQK.png)

Game Clear


## Grading Criteria

| Grading Criteria | Score |
| - | - |
| File Upload | 20 pt |
| Compilation Successful | 15 pt |
| Enter battle when the player (PL) overlaps with slime or dragon | 15 pt |
| Battle process and rules match the specification | 10 pt |
| Enter pause state when esc key is pressed in map movement state | 15 pt |
| Complete GameOver and GameClear processes | 15 pt |
| Implement MVC architecture using virtual class | 10 pt |
| **Total** | **100 pt** |
| Additional Game Design |	10 ~ 30 pt |
| **Total** |	**130 pt** |

Note: There are no restrictions on the bonus elements. Please describe further design for this game in the bonus.txt file. Extra points will be awarded based on the added content and its completeness.


## Assignment Directory
`/usr/local/class/oop/assign/assign7`
or https://github.com/oopnccucs/assign7


## Submission Method
In the OOP server, under the assign7 folder, input:

/usr/local/class/oop/bin/submit 7

to submit the assignment.


## Files in the Assignment Directory

src<br>
| -- gamecore: input conversion processing and game process calls<br>
|<br>
| -- functions<br>
|<br>
| -- controller*: Overall game flow control<br>
|<br>
| -- gameobjects: game objects and room definitions<br>
|<br>
| ---/_ gameprocess*: split game processes into different instances<br>
|     | -- move*: handling movement<br>
|     | -- pause*: handling <br>
|     | -- battle*: handling battles<br>
|     | -- gameover*: handling game over<br>
|     | -- gameclear*: handling game clear<br>
|<br>

*: Main focus of this assignment

## Implementation Notes

Compile: `$make`

Run: `$make run`