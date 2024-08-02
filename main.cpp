#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "robot.hpp"


using namespace std;

int distanceWithin;  // made a int variable outside the main method for the bool countDistanceWithin to store the distance from command file.

bool countDistanceWithin(const robot &r){
    return distanceWithin >= abs(r.getXPosition()) + abs(r.getYPosition()); // used as my count_if statement to return the count
}

int main() {
    ifstream start("start.txt"); // start file [Robot: Number,Team, Xpos, Ypos]
    ifstream commands("commands2.txt");  // command file   [Commands: show, move Number(r), turnleft Number(r)]

    /* VECTOR CLASS */
    vector<robot> warGround;    // empty vector
    string stringCommand;       // string for storing and reading from command file
    int mN;                     // robots model number
    int t;                      // team number
    int xPos;                   // x position
    int yPos;                   // y position

    // pushed all robots from start file into empty vector (warGround)
    while (start >> mN >> t >> xPos >> yPos) {
        warGround.push_back(robot(mN,t,xPos,yPos));
    }
    
    // traverse through the whole list of commands, storing them wastes space so vector was not created for commands file
    while(!commands.eof()){
        commands >> stringCommand;  // all commands start with a word, string
        
        
        if(stringCommand == "show"){
            // if the loop picks up the word "show" then run this statement
            /*  cout << stringCommand << " " << endl;   Testing Purposes */
                sort(warGround.begin(), warGround.end(), sortIDAscendingOrder); // sort the vector in aceeding order by ID
                for (auto &r : warGround) {
                    show(r);    // loops through the vector and calls the method travelled which prints out all all Ints from robot class
                }
            cout << endl;
            
        }
        else if(stringCommand == "travelled"){
            // if the loop picks up the word "travelled" then run this statement
            /*  cout << stringCommand << " " << endl;    Testing Purposes */
                sort(warGround.begin(), warGround.end(), sortIDAscendingOrder); // // sort the vector in aceeding order by ID first
                sort(warGround.begin(), warGround.end(), sortDistanceAscendingOrder);  // sort the vector in accending order by distance second
                for (auto &r : warGround) {
                    travelled(r);   // loops through the vector and calls the method travelled which prints out all Robots ModelNumber & Distance                   Travelled
                }
            
        }
        else if(stringCommand == "within"){
            // if the loop picks up the word "within" then run this statement
            commands >> distanceWithin; // expecting an int after the string word "within"
            /*  cout << stringCommand << " " << distanceWithin << endl;    Testing Purposes */
            cout << count_if(warGround.begin(), warGround.end(), countDistanceWithin) << endl << endl;  // counts only the distance if distanceWithin >= the addition of both abs(x and y coordinate), abs removes negative.
        }

        else if(stringCommand == "move" || stringCommand == "turnright" || stringCommand == "turnleft"){
            // if the loop picks up the word "move" or "turnright" or "turnleft" then run this statement
            commands >> mN; // expecting an int after the string word "move" or "turnright" or "turnleft"
            /*  cout << stringCommand << " " << mN << endl;    Testing Purposes */
            if (stringCommand == "move"){
                // if the loop picks up the word "move" then run this statement
                // code is in repeat but different directions are called, will only comment getNorth()
                for (auto &r : warGround) {
                    if(mN == r.getModelNumber()){
                        // loops thought the vector, if the ModelNumber in the command file matches any in the vector then run this statement
                        if (r.getNorth() == true) {
                           // if that robot is facing north run this statement
                            bool isEnemy = false;   // if the enemy is in the position infront, will return true
                            bool isTeam = false;    // if the teammate is in the position infront, will return true
                            for (auto &r2 : warGround) {
                                // loops through vector, finding another robot in the position infront
                                if(r2.getYPosition() == r.getYPosition()+1 && r2.getXPosition() == r.getXPosition()){
                                    // check if the position of the first robot is equal to the position of the second robot +1 y axis (checks if second robot is infront of the first robot)
                                    if(r2.getTeam() != r.getTeam()){
                                        // if they are not in the same team then run this statement
                                        isEnemy = true;
                                        warGround.erase(remove_if(warGround.begin(), warGround.end(), [r2](robot enemy){return enemy.getModelNumber() == r2.getModelNumber();}),warGround.end());   // removes r2 robot
                                        move(r);    // moves the first robot by whichever direction it is facing
                                        break; // breaks out the loop because move is complete
                                    }
                                    else if(r2.getTeam() == r.getTeam()){
                                        // if they are in the same team then run this statement
                                        isTeam = true;
                                        break; // breaks out the loop, making isTeam true and not allowing him to move in the next statement
                                        
                                    }
                                }
                            }
                            if (isEnemy == false && isTeam == false) { move(r);} // if the enemy and the teamate is not infront then he will move (this is for empty space)
                            isEnemy = false;
                            isTeam = false;

                    }
                        else if (r.getSouth() == true) {
                            bool isEnemy = false;
                            bool isTeam = false;
                            for (auto &r2 : warGround) {
                                if(r2.getYPosition() == r.getYPosition()-1 && r2.getXPosition() == r.getXPosition()){
                                    if(r2.getTeam() != r.getTeam()){
                                        isEnemy = true;
                                        warGround.erase(remove_if(warGround.begin(), warGround.end(), [r2](robot enemy){return enemy.getModelNumber() == r2.getModelNumber();}),warGround.end());
                                        move(r);
                                        break;
                                    }
                                    else if(r2.getTeam() == r.getTeam()){
                                        isTeam = true;
                                        break;
                                    }
                                }
                            }
                            if (isEnemy == false && isTeam == false) { move(r);}
                            isEnemy = false;
                            isTeam = false;
                    }
                        else if (r.getEast() == true) {
                            bool isEnemy = false;
                            bool isTeam = false;
                            for (auto &r2 : warGround) {
                                if(r2.getYPosition() == r.getYPosition() && r2.getXPosition() == r.getXPosition()+1){
                                    if(r2.getTeam() != r.getTeam()){
                                        isEnemy = true;
                                        warGround.erase(remove_if(warGround.begin(), warGround.end(), [r2](robot enemy){return enemy.getModelNumber() == r2.getModelNumber();}),warGround.end());
                                        move(r);
                                        break;
                                    }
                                    else if(r2.getTeam() == r.getTeam()){
                                        isTeam = true;
                                        break;
                                    }
                                }
                            }
                            if (isEnemy == false && isTeam == false) { move(r);}
                            isEnemy = false;
                            isTeam = false;
                    }
                        else if (r.getWest() == true) {
                            bool isEnemy = false;
                            bool isTeam = false;
                            for (auto &r2 : warGround) {
                                
                                if(r2.getYPosition() == r.getYPosition() && r2.getXPosition() == r.getXPosition()-1){
                                    if(r2.getTeam() != r.getTeam()){
                                        isEnemy = true;
                                        warGround.erase(remove_if(warGround.begin(), warGround.end(), [r2](robot enemy){return enemy.getModelNumber() == r2.getModelNumber();}),warGround.end());
                                        move(r);
                                        break;
                                    }
                                    else if(r2.getTeam() == r.getTeam()){
                                        isTeam = true;
                                        break;
                                    }
                                }
                            }
                            if (isEnemy == false && isTeam == false) { move(r);}
                            isEnemy = false;
                            isTeam = false;
                    }
                }
            }
        }
            else if (stringCommand == "turnright"){
                // if the loop picks up the word "turnright" then run this statement
                for (auto &r : warGround) {
                    if(mN == r.getModelNumber()){
                        // loops through the vector and checks if the modelnumber from command file is equal to any modelnumber robot in the vector file
                        turnRight(r); //changes position of the robot, turns right
                    }
                }
            }
            
            else if (stringCommand == "turnleft"){
                // if the loop picks up the word "turnright" then run this statement
                for (auto &r : warGround) {
                    if(mN == r.getModelNumber()){
                       // loops through the vector and checks if the modelnumber from command file is equal to any modelnumber robot in the vector file{
                        turnLeft(r); //changes position of the robot, turns left
                    }
                }
            }
        }
    }
    

    
    return 0;
}

