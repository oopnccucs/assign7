#ifndef POSITION_H
#define POSITION_H

class Position {
private:
    int positionX;
    int positionY;
public:
    Position(int initialPositionX, int initialPositionY);
    Position();
    ~Position();

    int getX();
    int getY();
    
    // add functions what you need

    bool operator==(const Position &other) const;








};

#endif