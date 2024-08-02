#include "robot.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

// prints robot, modelnumber,team,xpos,ypos
void show(robot &r) {
    
        cout << r.getModelNumber() << " " << r.getTeam() << " " <<
            r.getXPosition() << " " << r.getYPosition() << "\n";
}

// prints robot modelnumber,distancetravelled
void travelled(robot &r){
    cout << r.getModelNumber() << " " << r.getDistanceTravelled() << "\n";
}

// used in sort statement for sorting ModelNumber in accending order
bool sortIDAscendingOrder(const robot &x, const robot &y) {
    return x.getModelNumber() < y.getModelNumber();
}

// used in sort statement for sorting Distance in accending order
bool sortDistanceAscendingOrder(const robot &x, const robot &y) {
    return x.getDistanceTravelled() < y.getDistanceTravelled();
}

// used to move the robot depending on which position its facing, and increment distance,
int move(robot &r){
    r.incrementDistanceTravelled();
        if (r.getNorth() == true) {
            //return increase y by 1
            return r.setYPosition((r.getYPosition() + 1));
        }
        else if (r.getSouth() == true) {
            //return decrease y by 1
            return r.setYPosition((r.getYPosition() - 1));
        }
        else if (r.getEast() == true) {
            //return increase x by 1
            return r.setXPosition((r.getXPosition() + 1));
        }
        else if (r.getWest() == true){
            //return decrease x by 1
            return r.setXPosition((r.getXPosition() - 1));
        }
        // testing could have used void but wanted to implement return value when i can
        else{
        return 0;
        }
    
}


// changes the boolean functions when method is called, changing the positions of the robot in the right
void turnRight(robot &r){
    if (r.getNorth() == true) {
        r.setEast(true);
        r.setNorth(false);
    }
    else if (r.getSouth() == true) {
        r.setWest(true);
        r.setSouth(false);
    }
    else if (r.getEast() == true) {
        r.setSouth(true);
        r.setEast(false);
    }
    else if (r.getWest() == true) {
        r.setNorth(true);
        r.setWest(false);
    }
}

// changes the boolean functions when method is called, changing the positions of the robot in the left
void turnLeft(robot &r){
    if (r.getNorth() == true) {
        r.setWest(true);
        r.setNorth(false);
    }
    else if (r.getSouth() == true) {
        r.setEast(true);
        r.setSouth(false);
    }
    else if (r.getEast() == true) {
        r.setNorth(true);
        r.setEast(false);
    }
    else if (r.getWest() == true) {
        r.setSouth(true);
        r.setWest(false);
    }
    
}
      



