
#ifndef robot_hpp
#define robot_hpp

#include <stdio.h>
#include <string>
#include <algorithm>

class robot {
     int _modelNumber;                  // ID
     int _team;                         // Team
     int _xPosition;                    // X position
     int _yPosition;                    // Y position
    /* N/A */     bool _north = true;                //Set North to True
    /* N/A */     bool _south;                       // bool south
    /* N/A */     bool _east;                        // bool east
    /* N/A */     bool _west;                        // bool west
    int _travelled;                // Distance Travelled set to 0
     std:: string _direction; //
    
    
public:
    
    // Accessors
    robot(int mN, int t, int xPos, int yPos) :
    _direction("north"),_modelNumber(mN), _team(t), _xPosition(xPos), _yPosition(yPos) {}
    
    // ModelNumber, Team, X Position, Y Position setters and getters
    int getModelNumber() const { return _modelNumber; }
    int getTeam() const { return _team; }
    int getXPosition()  const { return _xPosition; }
    int setXPosition(int x) { return _xPosition = x;}
    int getYPosition() const { return _yPosition; }
    int setYPosition(int y) { return _yPosition = y;}
    
    // North, South, West, East setters and getters
    std::string getDirection() { return _direction; }
    bool getNorth()  { return _north; }
    void setNorth(bool isFacingNorth)  {  _north = isFacingNorth; }
    bool getSouth()  { return _south; }
    void setSouth(bool isFacingSouth)  {  _south = isFacingSouth;  }
    bool getEast() { return _east; }
    void setEast(bool isFacingEast)  {  _east = isFacingEast; }
    bool getWest()  { return _west; }
    void setWest(bool isFacingWest)  {  _west = isFacingWest; }
    
    // Travelled setters and getters
    int getDistanceTravelled() const { return _travelled; }
    void incrementDistanceTravelled() { ++_travelled; }
    
    
    
    
};
// methods used in robot.cpp file
bool sortIDAscendingOrder(const robot &x,const robot &y);

bool sortDistanceAscendingOrder(const robot &x, const robot &y);

void show(robot &r);

int move(robot &r);

void turnRight(robot &r);

void turnLeft(robot &r);

void travelled(robot &r);






#endif /* robot_hpp */
