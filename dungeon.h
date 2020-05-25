//
//  dungeon.h
//  Project3
//
//  Created by Bryan Zhou on 5/15/20.
//  Copyright © 2020 Bryan Zhou. All rights reserved.
//

#ifndef dungeon_h
#define dungeon_h

#include <vector>
#include <iostream>


#include "utilities.h"
#include "actor.h"
#include "object.h"

class actor;
class player;


struct room
{
    int up;
    int down;
    int left;
    int right;
    int m_number;
};


//a dungeon must have 4 to 7 rectangular rooms connected by corridores.

class dungeon
{
public:
    // Constructor/Destructor
    dungeon(int level,int goblinSmellDistance);             //create a dungeon with rooms and corridors surrounded by a wall
    ~dungeon();
    
    
    
    // Accessors
    int getLevel()const {return m_level;}                           //return what level the player is on
    size_t getMonster() const{return Vec_monsters.size();}             //return the number of monsters
    size_t getObject() const{return Vec_objects.size();}             //return the number of objects
    
    int getMyGoldenRow() const {return m_goldenRow;}
    int getMyGoldenCol() const {return m_goldenCol;}
    int getMyStairRow() const {return m_stairRow;}
    int getMyStairCol() const {return m_stairCol;}
    int getGoblinSmellDistance() const {return m_goblinSmellDistance;}
    
    
    player* getPlayer() const {return m_player;}
    
    
    void display() const;
    void displayStats() const;
    
    char getCellStatus(int r, int c) const {return m_grid[r][c];}
    
    
    actor* findMonster(int r, int c);
    object* findObject(int r, int c);
    
    
    
    bool directlyWithin(int smelldistance, int sr, int sc, int er, int ec) const;
    
    
    
    
    
    int getPlayerDistanceFrom(int r, int c) const;
    void printPlayerDistanceMap() const;
    
    
    // Mutators
    
    void buildRooms();
    void build(room& room);
    void connectRooms(const room room1, const room room2);
    
    
    void setPlayer(player* player){m_player = player;}
    void findVacant(int& r, int& c);
    void findVacantForObject(int& r, int& c);
    
    
    void removeMonster(int r, int c);
    void removeObject(int r, int c);
    
    void insertObject(int r, int c, int kind);
    
    
    
    void clearPlayerDistanceMap();
    void refreshPlayerDistanceMap(int sr, int sc, int smellDistance, int stepsTaken); // this should be a recursive function updating
    
    
    
    void monsterTurn(std::string* monsterActions);
    
    void updateGrid();
    
    
    void populateWithMonsters();
    
    
    
    
private:
    player* m_player;               //this is up to me to initialize, the constructor does not take care of this
    
    
    
    char m_grid[18][70];
    
    int m_playerDistanceMap[18][70];
    
    
    std::vector<actor*> Vec_monsters;
    std::vector<object*> Vec_objects;


    
    
    int m_stairRow;
    int m_stairCol;
    
    int m_goldenRow;
    int m_goldenCol;
    
    
    int m_level;
    int m_goblinSmellDistance;
    
    
    
    
    room m_room1;
    room m_room2;
    room m_room3;
    room m_room4;
    room m_room5;
    room m_room6;
    int m_numberOfRooms;
    int m_dontBuild1;
    int m_dontBuild2;
   
};








#endif /* dungeon_h */
