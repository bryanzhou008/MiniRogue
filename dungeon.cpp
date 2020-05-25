//
//  dungeon.cpp
//  Project3
//
//  Created by Bryan Zhou on 5/15/20.
//  Copyright © 2020 Bryan Zhou. All rights reserved.
//
#include <cstdlib>
#include "dungeon.h"

//-----------------------------------Constructor + Populate Function + Destructor-----------------------------------//

dungeon::dungeon(int level, int goblinSmellDistance)
:m_level(level), m_goblinSmellDistance(goblinSmellDistance)
{
    //the player is created in the game not here
    //the monsters are created and placed in the dungeon by the populateWithMonsters() function
    
    
    //draw the map of the grid
    //fill the grid with walls
    for(int i=0; i<18; i++)
    {
        for(int j=0; j<70; j++)
        {
            m_grid[i][j] = '#';
        }
    }
    
    //initialize the rooms
    m_room1.m_number = 1;
    m_room2.m_number = 2;
    m_room3.m_number = 3;
    m_room4.m_number = 4;
    m_room5.m_number = 5;
    m_room6.m_number = 6;
    
    
    
    //I split the whole board into 6 blocks
    m_numberOfRooms = randInt(4, 6);
    
    //build room1 in the first quardrant
    m_room1.up = randInt(1, 6);
    m_room1.down = randInt(m_room1.up+2, 8);
    m_room1.left = randInt(1, 16);
    m_room1.right = randInt(m_room1.left+6, 22);
    
    //build room2 in the second quardrant
    m_room2.up = randInt(1, 6);
    m_room2.down = randInt(m_room2.up+2, 8);
    m_room2.left = randInt(24, 39);
    m_room2.right = randInt(m_room2.left+6, 45);
    
    //build room3 in the third quardrant
    m_room3.up = randInt(1, 6);
    m_room3.down = randInt(m_room3.up+2, 8);
    m_room3.left = randInt(47, 62);
    m_room3.right = randInt(m_room3.left+6, 68);
    
    //build room4 in the fourth quardrant
    m_room4.up = randInt(10, 14);
    m_room4.down = randInt(m_room4.up+2, 16);
    m_room4.left = randInt(1, 16);
    m_room4.right = randInt(m_room4.left+6, 22);
    
    //build room5 in the fifth quardrant
    m_room5.up = randInt(10, 14);
    m_room5.down = randInt(m_room5.up+2, 16);
    m_room5.left = randInt(24, 39);
    m_room5.right = randInt(m_room5.left+6, 45);
    
    //build room6 in the sixth quardrant
    m_room6.up = randInt(10, 14);
    m_room6.down = randInt(m_room6.up+2, 16);
    m_room6.left = randInt(47, 62);
    m_room6.right = randInt(m_room6.left+6, 68);
    //and then build and connect the rooms
    
    //if the number of rooms is not 6, decide which of the rooms not to build
    m_dontBuild1 = -1;
    m_dontBuild2 = -1;
    if(m_numberOfRooms == 5)
    {
        m_dontBuild1 = randInt(1, 6);
    }
    else if(m_numberOfRooms == 4)
    {
        m_dontBuild1 = randInt(1, 3);
        m_dontBuild2 = randInt(4, 6);
    }
    
    buildRooms();
    
    
    
    //draw the map of the player distance grid
    for(int i=0; i<18; i++)
    {
        for(int j=0; j<70; j++)
        {
            m_playerDistanceMap[i][j] = 99;
        }
    }
    


    

    
    //create the objects
    int r = 0;
    int c = 0;
    
    
    for(int i=0; i<randInt(2,3); i++)
    {
        int o = randInt(1, 7);
        switch(o)
        {
            case 1:
                findVacantForObject(r, c);
                Vec_objects.push_back(new S_sword(r,c));
                break;
                
            case 2:
                findVacantForObject(r, c);
                Vec_objects.push_back(new L_sword(r,c));
                break;
                
            case 3:
                findVacantForObject(r, c);
                Vec_objects.push_back(new mace(r,c));
                break;
                
                
            case 4:
                findVacantForObject(r, c);
                Vec_objects.push_back(new Iarm(r,c));
            
                break;
                
            case 5:
                findVacantForObject(r, c);
                Vec_objects.push_back(new Istr(r,c));
                break;
                
            case 6:
                findVacantForObject(r, c);
                Vec_objects.push_back(new Ihel(r,c));
                break;
                
            case 7:
                findVacantForObject(r, c);
                Vec_objects.push_back(new Idex(r,c));
                break;
        }
    }
    
    
    //if on level four, create the golden idol, else create a staircase
    switch(level)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            findVacantForObject(r, c);
            m_grid[r][c] = '>';
            m_stairRow = r;
            m_stairCol = c;
            m_goldenRow = -1;
            m_goldenCol = -1;
            
            break;
            
        case 4:
            findVacantForObject(r, c);
            m_grid[r][c] = '&';
            m_goldenRow = r;
            m_goldenCol = c;
            m_stairRow = -1;
            m_stairCol = -1;
            break;
    }
}
















void dungeon::buildRooms()
{
    //build the rooms
    
    if(m_numberOfRooms == 6)                    //build all the rooms
    {
        build(m_room1);
        build(m_room2);
        build(m_room3);
        build(m_room4);
        build(m_room5);
        build(m_room6);
        
    }
    else if(m_numberOfRooms == 5)
    {
        switch(m_dontBuild1)                //build all the rooms except m_dontbuild1
        {
            case 1:
                build(m_room2);
                build(m_room3);
                build(m_room4);
                build(m_room5);
                build(m_room6);
                break;
            case 2:
                build(m_room1);
                build(m_room3);
                build(m_room4);
                build(m_room5);
                build(m_room6);
                break;
            case 3:
                build(m_room1);
                build(m_room2);
                build(m_room4);
                build(m_room5);
                build(m_room6);
                break;
            case 4:
                build(m_room1);
                build(m_room2);
                build(m_room3);
                build(m_room5);
                build(m_room6);
                break;
            case 5:
                build(m_room1);
                build(m_room2);
                build(m_room3);
                build(m_room4);
                build(m_room6);
                break;
            case 6:
                build(m_room1);
                build(m_room2);
                build(m_room3);
                build(m_room4);
                build(m_room5);
                break;
                
        }
    }
    else if(m_numberOfRooms == 4)                   //build all the rooms except m_dontbuild1 and m_dontbuild2
    {
        switch(m_dontBuild1)
        {
            case 1:
                build(m_room2);
                build(m_room3);
                break;
            case 2:
                build(m_room1);
                build(m_room3);
                break;
            case 3:
                build(m_room1);
                build(m_room2);
                break;
                
        }
        switch(m_dontBuild2)
        {
            case 4:
                build(m_room5);
                build(m_room6);
                break;
            case 5:
                build(m_room4);
                build(m_room6);
                break;
            case 6:
                build(m_room4);
                build(m_room5);
                break;
        }
        
    }
    else
        
    
    //connect the rooms
    if(m_dontBuild1 != 1)           //if room1 is built, connect room1 to the other rooms
    {
        if(m_dontBuild1 != 2)       //if room2 is built, connect room1 to room2
            connectRooms(m_room1, m_room2);
        else                       //else connect room1 to room3
            connectRooms(m_room1, m_room3);
        if(m_dontBuild1 != 4 && m_dontBuild2 != 4)
            connectRooms(m_room1, m_room4);
    }
    
    
    if(m_dontBuild1 != 2)          //if room2 is built, connect room2 to the other rooms
    {
        if(m_dontBuild1 != 3)
            connectRooms(m_room2, m_room3);
        if(m_dontBuild1 != 5 && m_dontBuild2 != 5)
            connectRooms(m_room2, m_room5);
    }
    
    
    
    if(m_dontBuild1 != 1)           //if room1 is built, connect room1 to the other rooms
    {
        if(m_dontBuild1 != 2)       //if room2 is built, connect room1 to room2
            connectRooms(m_room1, m_room2);
        else                       //else connect room1 to room3
            connectRooms(m_room1, m_room3);
        if(m_dontBuild1 != 4 && m_dontBuild2 != 4)
            connectRooms(m_room1, m_room4);
    }

    
    
    
    if(m_dontBuild1 != 3)          //if room3 is built, connect room3 to the other rooms
    {
        if(m_dontBuild1 != 6 && m_dontBuild2 != 6)
            connectRooms(m_room3, m_room6);
    }

    if(m_dontBuild1 != 4 && m_dontBuild2 != 4)          //if room4 is built, connect room4 to the other rooms
    {
        if(m_dontBuild1 != 5 && m_dontBuild2 != 5)
            connectRooms(m_room4, m_room5);
        else
            connectRooms(m_room4, m_room6);
    }

    if(m_dontBuild1 != 5 && m_dontBuild2 != 5)          //if room5 is built, connect room5 to the other rooms
    {
        if(m_dontBuild1 != 6 && m_dontBuild2 != 6)
            connectRooms(m_room5, m_room6);
    }

}





void dungeon::build(room& room)
{
    for(int i = room.up; i <= room.down; i++)
    {
        for(int j = room.left; j<= room.right; j++)
            m_grid[i][j] = ' ';
    }
}







//when I pass in two rooms into this function, I make sure that:
//the first room is always located to the upward or leftside quardrant compared to the second room
void dungeon::connectRooms(const room room1, const room room2)
{
    if((room2.m_number - room1.m_number) == 3)//room1 is loacted right on top of room2
    {
        int midRoom1 = (room1.right+room1.left)/2;                      //take the middle of the rightside edge
        int midRoom2 = (room2.up + room2.down)/2;                      //take the middle of the up edge
        {
            if(midRoom1 >= room2.left && midRoom1 <= room2.right)       //if the rooms can be connected here with adirect line
            {
                for(int i = room1.down+1; i < room2.up; i++)
                    m_grid[i][midRoom1] = ' ';
            }
            
            else if(midRoom1 < room2.left)                              //if the second maze is located to much to the right
            {
                for(int i = room1.down+1; i < midRoom2; i++)
                    m_grid[i][midRoom1] = ' ';
                for(int j = midRoom1 ; j < room2.left; j++)
                    m_grid[midRoom2][j] = ' ';
            }
            else if(midRoom1 > room2.right)                              //if the second maze is located to much to the left
            {
                for(int i = room1.down+1; i < midRoom2; i++)             
                    m_grid[i][midRoom1] = ' ';
                for(int j = room2.right+1 ; j <= midRoom1; j++)
                    m_grid[midRoom2][j] = ' ';
            }
        }
    }
    
    else if((room2.m_number - room1.m_number) == 1 || (room2.m_number - room1.m_number) == 2)//room1 is located to the left side of room2
    {
        int midRoom1 = (room1.down+room1.up)/2;
        int midRoom2 = (room2.right+room2.left)/2;
        if(midRoom1 >= room2.up && midRoom1 <= room2.down)       //if the rooms can be connected here with a direct line
        {
            for(int j = room1.right+1; j < room2.left; j++)
                m_grid[midRoom1][j] = ' ';
        }
        
        else if(midRoom1 < room2.up)                            //if the second room is located too low
        {
            for(int j = room1.right+1; j < midRoom2; j++)
                m_grid[midRoom1][j] = ' ';
            for(int i = midRoom1 ; i < room2.up; i++)
                m_grid[i][midRoom2] = ' ';
        }
        else if(midRoom1 > room2.down)                          //if the second maze is located too high
        {
            for(int j = room1.right+1; j < midRoom2; j++)
                m_grid[midRoom1][j] = ' ';
            for(int i = room2.down+1 ; i <= midRoom1; i++)
                m_grid[i][midRoom2] = ' ';
        }
    }
}



































void dungeon::populateWithMonsters()
{
    // populate with monsters
    
    int r;
    int c;
    
    int m_monster = randInt(2, 5*(getLevel()+1)+1);
    
    switch(getLevel())
    {
        case 0:
        case 1:
        {
            for(int i=0; i<m_monster; i++)
            {
                int m = randInt(1, 2);
                if(m==1)
                {
                    findVacant(r, c);
                    Vec_monsters.push_back(new snakewoman(r,c,this));
                }
                if(m==2)
                {
                    findVacant(r, c);
                    Vec_monsters.push_back(new goblin(r,c,this));
                }
            }
        }
            break;
        case 2:
        {
            for(int i=0; i<m_monster; i++)
                {
                    int m = randInt(1, 3);
                    if(m==1)
                    {
                        findVacant(r, c);
                        Vec_monsters.push_back(new snakewoman(r,c,this));
                    }
                    if(m==2)
                    {
                        findVacant(r, c);
                        Vec_monsters.push_back(new goblin(r,c,this));
                    }
                    if(m==3)
                    {
                        findVacant(r, c);
                        Vec_monsters.push_back(new bogeyman(r,c,this));
                    }
            
                }
        }
            break;
            
        case 3:
        case 4:
        {
            for(int i=0; i<m_monster; i++)
                {
                    int m = randInt(1, 4);
                    if(m==1)
                    {
                        findVacant(r, c);
                        Vec_monsters.push_back(new snakewoman(r,c,this));
                    }
                    if(m==2)
                    {
                        findVacant(r, c);
                        Vec_monsters.push_back(new goblin(r,c,this));
                    }
                    if(m==3)
                    {
                        findVacant(r, c);
                        Vec_monsters.push_back(new bogeyman(r,c,this));
                    }
                    if(m==4)
                    {
                        findVacant(r, c);
                        Vec_monsters.push_back(new dragon(r,c,this));
                    }
            
                }
        }
    }
}




dungeon::~dungeon()
{
    while(Vec_monsters.size()!=0)
    {
        std::vector<actor*>::iterator itm;
        itm = Vec_monsters.begin();
        while(itm != Vec_monsters.end())
        {
            delete *itm;
            itm = Vec_monsters.erase(itm);
        }
    }
    
    while(Vec_objects.size() != 0)
    {
        std::vector<object*>::iterator ito;
        ito = Vec_objects.begin();
        while(ito != Vec_objects.end())
        {
            delete *ito;
            ito = Vec_objects.erase(ito);
        }
    }
}







































//-----------------------------------Display + Grid Update Function-----------------------------------//


void dungeon::display() const
{
    for(int i=0; i<18; i++)
    {
        for(int j=0; j<70; j++)
        {
            std::cout << m_grid[i][j];
        }
        std::cout << std::endl;
    }
}



void dungeon::displayStats() const
{
    std::cout << "Dungeon Level: " << m_level << ", Hit points: " << getPlayer()->getHp() << ", Armor: " << m_player->getArm() << ", Strength: " << m_player->getStr() << ", Dexterity: " << m_player->getDex() << std::endl << std::endl;
}






void dungeon::updateGrid()          //I should only have to update the grid after a player move or a monster move
{
    for(int i=0; i<18; i++)
    {
        for(int j=0; j<70; j++)
        {
            m_grid[i][j] = '#';
//            m_grid[i][j] = ' ';
//            if(i == 0 || i== 17 || j==0 || j==69)
//                m_grid[i][j] = '#';
        }
    }
    
    
    buildRooms();
    //will replace the up part with functions like fill_grid_with_wall, build_room, connect_room

    
    if (m_level != 4)
        m_grid[m_stairRow][m_stairCol] = '>';
    else
        m_grid[m_goldenRow][m_goldenCol] = '&';
    // update all objects
    for (int i = 0; i < Vec_objects.size(); i++)
    {
        int r = Vec_objects[i]->getRow();
        int c = Vec_objects[i]->getCol();
        m_grid[r][c] = Vec_objects[i]->getIcon();
    }
    // update all monsters
    for (int i = 0; i < Vec_monsters.size(); i++)
    {
        int r = Vec_monsters[i]->getRow();
        int c = Vec_monsters[i]->getCol();
        m_grid[r][c] = Vec_monsters[i]->getIcon();
    }
    // update the player
    m_grid[m_player->getRow()][m_player->getCol()] = '@';
    
}











































































//-----------------------------------Helper Functions-----------------------------------//



void dungeon::findVacant(int& r, int& c)                        //finds a spot to place a new player or monster
{
    r = 0;
    c = 0;
    
    do
    {
        r = randInt(1, 16);
        c = randInt(1, 68);
    }while(getCellStatus(r, c) == '#' ||getCellStatus(r, c) == 'B' || getCellStatus(r, c) == 'S' ||getCellStatus(r, c) == 'G' ||getCellStatus(r, c) == 'D');
}



void dungeon::findVacantForObject(int& r, int& c)                        //finds a spot to place an new object
{
    r = 0;
    c = 0;
    
    do
    {
        r = randInt(1, 16);
        c = randInt(1, 68);
    }while(getCellStatus(r, c) == '#' ||getCellStatus(r, c) == ')' || getCellStatus(r, c) == '?' ||getCellStatus(r, c) == '>'||getCellStatus(r, c) == '&');
}





actor* dungeon::findMonster(int r, int c)                               //locates a monster based on coordinates
{
    std::vector<actor*>::iterator it;
    it = Vec_monsters.begin();
    while(it != Vec_monsters.end())
    {
        if((*it)->getRow() == r && (*it)->getCol() == c)
            return (*it);
        it++;
    }
    return nullptr;
    
}


object* dungeon::findObject(int r, int c)                               //locates an object based on coordinates
{
    std::vector<object*>::iterator it;
    it = Vec_objects.begin();
    while(it != Vec_objects.end())
    {
        if((*it)->getRow() == r && (*it)->getCol() == c)
            return (*it);
        it++;
    }
    return nullptr;
    
}








void dungeon::removeMonster(int r, int c)                              //removes a monster given its coordinates
{
    std::vector<actor*>::iterator it;
    it = Vec_monsters.begin();
    while(it != Vec_monsters.end())
    {
        if((*it)->getRow() == r && (*it)->getCol() == c)
        {
            delete *it;
            it = Vec_monsters.erase(it);
        }
        else
            it++;
    }
}



void dungeon::removeObject(int r, int c)                              //removes an object given its coordinates
{
    std::vector<object*>::iterator it;
    it = Vec_objects.begin();
    while(it != Vec_objects.end())
    {
        if((*it)->getRow() == r && (*it)->getCol() == c)
            it = Vec_objects.erase(it);
        else
            it++;
    }
}







void dungeon::insertObject(int r, int c, int kind)                  //inserts an object given selected coordinates and alias for its type
{
    switch (kind)
    {
        case 1://axe
            Vec_objects.push_back(new axe(r,c));
            
            
            break;
        case 2://fang
            Vec_objects.push_back(new fang(r,c));
            
            
            break;
        case 3://tele
            Vec_objects.push_back(new Tele(r,c));
            
        
        break;
         
        case 4://iarm
            Vec_objects.push_back(new Iarm(r,c));
           
        
        break;
        case 5://istr
            Vec_objects.push_back(new Istr(r,c));
            
        
        break;
        case 6://ihel
            Vec_objects.push_back(new Ihel(r,c));
            
        
        break;
        case 7://idex
            Vec_objects.push_back(new Idex(r,c));
           
        
        break;
    }
}














//-----------------------------------Monster Movement Functions-----------------------------------//


void dungeon::monsterTurn(std::string* monsterActions)                              //call on all the monsters to move one by one
{
    for (int i = 0; i < Vec_monsters.size(); i++)
    {
        //update the goblin moving grid before every monster turn
        clearPlayerDistanceMap();
        refreshPlayerDistanceMap(m_player->getRow(), m_player->getCol(), m_goblinSmellDistance, 0);
        Vec_monsters[i]->monsterTurn(monsterActions);
    }
}






bool dungeon::directlyWithin(int smelldistance, int sr, int sc, int er, int ec) const   //determains whether a non-goblin monster can smell the player
{
    int dis = abs(sr-er) + abs(sc-ec);
    if(dis > smelldistance)
        return false;
    else
        return true;
}














//-----------------------------------Goblin Trace Related Functions-----------------------------------//



//My function refreshPlayerDistanceMap keeps updating a grid that has the same size and shape as the dungeon grid. This grid holds integers instead of characters. The entries centered around the player represents the minimal number of steps you need to take to reach the player from the entry. If that number is <= 15, a goblin standing at that position will be able to smell the player. When it's that goblin's turn. It will try to move to a neighboring cell whose entry is less than the current cell by exactly one. Meaning that location will be closer to the player by exactly one step.


//when i use this function, I pass in playerRow, playerColumn, and goblinSmellDistance, the function updates the grid accordingly
// the goblin will move to a position with a smaller number
//must update the grid everytime before deciding if a goblin should move or where to move


//should pass in (m_player->getRow, m_player->getCol, goblinSmellDistance, 0)
 void dungeon::refreshPlayerDistanceMap(int sr, int sc, int smellDistance, int stepsTaken)
{
    if(smellDistance == 0)
        return;
    else
    {
        if(stepsTaken==0)
        {
            m_playerDistanceMap[sr][sc] = 0;
        }
        
        int mark = stepsTaken + 1;                      //mark the spots that are one step further with this number
        
        //these values tell if any of the surrounding spots are blocked
        char up = m_grid[sr-1][sc];
        char down = m_grid[sr+1][sc];
        char left = m_grid[sr][sc-1];
        char right = m_grid[sr][sc+1];
        
        //these are the current numbers associated with surrounding spots
        int nUp = m_playerDistanceMap[sr-1][sc];
        int nDown = m_playerDistanceMap[sr+1][sc];
        int nLeft = m_playerDistanceMap[sr][sc-1];
        int nRight = m_playerDistanceMap[sr][sc+1];
        
        //nDirection > mark means that the previous method for reaching this spot takes more steps than the current one
        //therefore, update the spot marking to current best method (takes least amount of steps)
        
        //also, if this spot is never reached before, nDirection should have the value 99, which is greater than the goblin smell distance
        //therefore it will also be updated to mark value
        if(up != '#' && up != 'B' && up != 'S' && up != 'D' && up != 'G' && up != '@' && nUp > mark)
            m_playerDistanceMap[sr-1][sc] = mark;
        if(down != '#' && down != 'B' && down != 'S' && down != 'D' && down != 'G' && down != '@' && nDown > mark)
            m_playerDistanceMap[sr+1][sc] = mark;
        if(left != '#' && left != 'B' && left != 'S' && left != 'D' && left != 'G' && left != '@' && nLeft > mark)
            m_playerDistanceMap[sr][sc-1] = mark;
        if(right != '#' && right != 'B' && right != 'S' && right != 'D' && right != 'G' && right != '@' && nRight > mark)
            m_playerDistanceMap[sr][sc+1] = mark;
        
        
        //if the surrounding spots have been updated, we have found a better route, follow this route and keep exploring its surrounding spots
        //this process will continue until we can't smell any further
        //up
        if(m_playerDistanceMap[sr-1][sc] == mark)
            refreshPlayerDistanceMap(sr-1, sc, smellDistance-1, stepsTaken+1);
        //down
        if(m_playerDistanceMap[sr+1][sc] == mark)
            refreshPlayerDistanceMap(sr+1, sc, smellDistance-1, stepsTaken+1);
        //left
        if(m_playerDistanceMap[sr][sc-1] == mark)
            refreshPlayerDistanceMap(sr, sc-1, smellDistance-1, stepsTaken+1);
        //right
        if(m_playerDistanceMap[sr][sc+1] == mark)
            refreshPlayerDistanceMap(sr, sc+1, smellDistance-1, stepsTaken+1);
    }
}






void dungeon::printPlayerDistanceMap() const                //this function is only used for debugging purposes
{
    for(int i=0; i<18; i++)
    {
        for(int j=0; j<70; j++)
        {
            std::cout << m_playerDistanceMap[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}





void dungeon::clearPlayerDistanceMap()                          // this resets the playerDistanceMap to full of 99s
{
    for(int i=0; i<18; i++)
    {
        for(int j=0; j<70; j++)
        {
            m_playerDistanceMap[i][j] = 99;
        }
    }
}





int dungeon::getPlayerDistanceFrom(int r, int c) const          // this returns how far the monster is away from the player
{
    return m_playerDistanceMap[r][c];
    
};
