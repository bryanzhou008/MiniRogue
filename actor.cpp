//
//  actor.cpp
//  Project3
//
//  Created by Bryan Zhou on 5/15/20.
//  Copyright © 2020 Bryan Zhou. All rights reserved.
//

#include "actor.h"
#include <cstdlib>              //this in included only to perform a simple absolute value calculation


//-----------------------------------Functions for all Actors-----------------------------------//

actor::actor(int hp, int arm, int str, int dex, int row, int col, dungeon* dungeon, weapon* weapon, std::string name, char icon)
: m_hp(hp),m_arm(arm), m_str(str), m_dex(dex), m_row(row), m_col(col), m_weapon(weapon), m_dungeon(dungeon), m_name(name),m_icon(icon),  m_isDead(false), m_slpt(0)
{
    
}

actor::~actor()
{
    delete m_weapon;
}


bool actor::isDead() const
{
    if(m_hp <= 0)
        return true;
    else
        return false;
}



void actor::attack(actor* defender, std::string* actions)
{
    bool hit = false;
    bool die = false;
    bool sleep = false;
    
    
    
    
    
    int ap = getDex() + getWeapon()->getBonus();
    int dp = defender->getDex() + defender->getWeapon()->getBonus();
    if(randInt(1, ap) >= randInt(1, dp))                                //this means the attacker hits the defender
    {
        hit = true;
        int da = randInt(0, getStr() + getWeapon()->getDamage() - 1);
        defender->setHp(defender->getHp()-da);                          //defender loses da amount of health
    }
    
    
    
    if(defender->isDead())
    {
        die = true;
    }
    
    
    //    using the following formula:
    //        attackerPoints = attackerDexterity + weaponDexterityBonus;
    //        defenderPoints = defenderDexterity + defenderArmorPoints;
    //        if (randInt(1, attackerPoints) >= randInt(1, defenderPoints))
    //            attacker has hit defender
    //    A damage amount, an integer used in determining how much damage is done to a defender who is hit (i.e., how much the defender's hit points decrease), using the following formula:
    //        damagePoints = randInt(0, attackerStrength + weaponDamageAmount - 1);
    
    
    else if(m_weapon->getName() == "magic fangs of sleep")
    {
        sleep = trueWithProbability(0.2);
        if(sleep && !isDead())
        {
            int slpt = randInt(2, 6);
            if(slpt > defender->getslpt())
                defender->setSlpt(slpt);
        }
    }
    
    
    
    //   there is a 1 in 5 chance that the magic fangs of sleep will put the defender to sleep. The number of moves the sleep will last (the sleep time) is a random integer from 2 to 6, call it X. If the defender is already asleep, with sleep time Y, then the defender's sleep time becomes the maximum of X and Y (and not, say, Y+X).
    
    
    
    
    
    std::string attackResult = "";
    if(!hit)
        attackResult = " and misses.\n";
    else
    {
        if(die)
            attackResult =" dealing a final blow.\n";
        else if(sleep)
            attackResult =" and hits, putting "+defender->getName()+" to sleep.\n";
        else
            attackResult =" and hits.\n";
    }
    
    
    
    
    std::string outPut = getName()+" "+getWeapon()->getAction()+" "+defender->getName()+attackResult;
    *actions+=outPut;
    
    
    
    
    if(defender->isDead())
    {
        defender->die();
    }
}








//-----------------------------------Functions for Monsters-----------------------------------//


void actor::die()           //this function works for all monsters, the player has a different die function
{
    
    
    int drop = 0;
    int dropWhat = 0;
    //drop objects
    //the objects are numbered in the following way for simplicity
    //1.axe, 2.fang, 3.tele, 4.iarm, 5.istr 6.ihel, 7.idex
    
    switch(m_icon)                                                          //1.axe, 2.fang, 3.tele, 4.iarm, 5.istr 6.ihel, 7.idex
    {
        case 'B':
            drop = randInt(1, 10);
            if(drop == 1 && m_dungeon->findObject(m_row, m_col)==nullptr)
                m_dungeon->insertObject(m_row, m_col, 1);
            
            break;
            
        case 'S':
            drop = randInt(1, 3);
            if(drop == 1&& m_dungeon->findObject(m_row, m_col)==nullptr)
                m_dungeon->insertObject(m_row, m_col, 2);
                
            
            break;
            
        case 'D':
            dropWhat = randInt(3, 7);
            if(m_dungeon->findObject(m_row, m_col)==nullptr)
                m_dungeon->insertObject(m_row, m_col, dropWhat);
            
            break;
        
        case 'G':
            drop = randInt(1, 3);
            dropWhat = randInt(1, 2);
            if(drop == 1 && m_dungeon->findObject(m_row, m_col)==nullptr)
                m_dungeon->insertObject(m_row, m_col, dropWhat);
            
            break;
    }
    
    //get removed
    m_dungeon->removeMonster(m_row, m_col);
    
}



void actor::monsterTurn(std::string* monsterActions)
{
    if(isAsleep())                          // if the monster is sleeping, then do nothing and return
    {
        m_slpt--;
        return;
    }
    
    
    //since the monster is not sleeping, it is awake and takes a turn
    
    
    player* player = getDungeon()->getPlayer();
    int p_row = getDungeon()->getPlayer()->getRow();
    int p_col = getDungeon()->getPlayer()->getCol();
    
    
    bool nextTo = false;
    
    if(m_row+1 == p_row && m_col == p_col)
        nextTo= true;
    if(m_row-1 == p_row && m_col == p_col)
        nextTo= true;
    if(m_row == p_row && m_col+1 == p_col)
        nextTo= true;
    if(m_row == p_row && m_col-1 == p_col)
        nextTo= true;
    
    
    int smellDistance = 0;
    bool canSmellPlayer = false;
    
    
    
    
    switch(m_icon)
    {
        case 'B':
            smellDistance = 5;
            canSmellPlayer = m_dungeon->directlyWithin(smellDistance, m_row, m_col, p_row, p_col);
            
            if(nextTo)
                attack(player, monsterActions);
            else if(canSmellPlayer)
                moveTowardsPlayer();
            
            
            break;
            
        case 'S':
            smellDistance = 3;
            canSmellPlayer = m_dungeon->directlyWithin(smellDistance, m_row, m_col, p_row, p_col);
            
            if(nextTo)
                attack(player,monsterActions);
            else if(canSmellPlayer)
                moveTowardsPlayer();
            
            
            break;
            
        case 'D':
            selfHeal();                         //only dragons can heal itself
            if(nextTo)
                attack(player,monsterActions);
            
            
            
            break;
            
        case 'G':
            //When a goblin is able to smell the player, it must be at most 15 steps away
            //in the myPlayerDistanceGrid, the spot that the monster stands on will always be denoted 99, since it is block by the monster itself
            //however we can observe that one of the surrounding spots must have a value that is less than goblinSmellDistance by at least one
            //since it could not have gotten there without traversing through the grid
            smellDistance = m_dungeon->getGoblinSmellDistance();
            canSmellPlayer = (m_dungeon->getPlayerDistanceFrom(m_row, m_col) <= smellDistance);
            canSmellPlayer = (m_dungeon->getPlayerDistanceFrom(m_row+1, m_col) < smellDistance||m_dungeon->getPlayerDistanceFrom(m_row-1, m_col) < smellDistance||m_dungeon->getPlayerDistanceFrom(m_row, m_col+1) < smellDistance||m_dungeon->getPlayerDistanceFrom(m_row, m_col-1) < smellDistance);
            
            if(nextTo)
                attack(player,monsterActions);
            else if(canSmellPlayer)
                moveTowardsPlayer();
            
            
            break;
            
    }
    getDungeon()->updateGrid();                   //update the grid after every monster move
}





void actor::moveTowardsPlayer()                         //works for all mosters except goblins
{
    int p_row = getDungeon()->getPlayer()->getRow();
    int p_col = getDungeon()->getPlayer()->getCol();
    int dis = abs(m_row-p_row)+abs(m_col-p_col);
    
    //move up to get closer to the player
    if(m_dungeon->getCellStatus(m_row-1, m_col) != '#' && m_dungeon->getCellStatus(m_row-1, m_col) != 'B' && m_dungeon->getCellStatus(m_row-1, m_col) != 'S' && m_dungeon->getCellStatus(m_row-1, m_col) != 'D' && m_dungeon->getCellStatus(m_row-1, m_col) != 'G' && m_dungeon->getCellStatus(m_row-1, m_col) != '@')
    {
        int newDis = abs((m_row-1)-p_row)+abs(m_col-p_col);
        if(newDis < dis)
        {
            setRow(m_row-1);
            return;
        }
    }
    //move down to get closer to the player
    if(m_dungeon->getCellStatus(m_row+1, m_col) != '#' && m_dungeon->getCellStatus(m_row+1, m_col) != 'B' && m_dungeon->getCellStatus(m_row+1, m_col) != 'S' && m_dungeon->getCellStatus(m_row+1, m_col) != 'D' && m_dungeon->getCellStatus(m_row+1, m_col) != 'G' && m_dungeon->getCellStatus(m_row+1, m_col) != '@')
    {
        int newDis = abs((m_row+1)-p_row)+abs(m_col-p_col);
        if(newDis < dis)
        {
            setRow(m_row+1);
            return;
        }
    }
    //move left to get closer to the player
    if(m_dungeon->getCellStatus(m_row, m_col-1) != '#' && m_dungeon->getCellStatus(m_row, m_col-1) != 'B' && m_dungeon->getCellStatus(m_row, m_col-1) != 'S' && m_dungeon->getCellStatus(m_row, m_col-1) != 'D' && m_dungeon->getCellStatus(m_row, m_col-1) != 'G' && m_dungeon->getCellStatus(m_row, m_col-1) != '@')
    {
        int newDis = abs(m_row-p_row)+abs((m_col-1)-p_col);
        if(newDis < dis)
        {
            setCol(m_col-1);
            return;
        }
    }
    //move right to get closer to the player
    if(m_dungeon->getCellStatus(m_row, m_col+1) != '#' && m_dungeon->getCellStatus(m_row, m_col+1) != 'B' && m_dungeon->getCellStatus(m_row, m_col+1) != 'S' && m_dungeon->getCellStatus(m_row, m_col+1) != 'D' && m_dungeon->getCellStatus(m_row, m_col+1) != 'G' && m_dungeon->getCellStatus(m_row, m_col+1) != '@')
    {
        int newDis = abs(m_row-p_row)+abs((m_col+1)-p_col);
        if(newDis < dis)
        {
            setCol(m_col+1);
            return;
        }
    }
    
}





void goblin::moveTowardsPlayer()                            //works for goblins
{
    
    int up = getDungeon()->getPlayerDistanceFrom(getRow()-1, getCol());
    int down = getDungeon()->getPlayerDistanceFrom(getRow()+1, getCol());
    int left = getDungeon()->getPlayerDistanceFrom(getRow(), getCol()-1);
    int right = getDungeon()->getPlayerDistanceFrom(getRow(), getCol()+1);
    
    if(up <= down && up <= left && up <= right)             //if moving up is one of the best options for the goblin
    {
        setRow(getRow()-1);
        return;
    }
    
    if(down <= up && down <= left && down <= right)            //if moving down is one of the best options for the goblin
    {
        setRow(getRow()+1);
        return;
    }
    
    if(left <= up && left <= down && left <= right)            //if moving left is one of the best options for the goblin
    {
        setCol(getCol()-1);
        return;
    }
    
    if(right <= up && right <= down && right <= left)            //if moving right is one of the best options for the goblin
    {
        setCol(getCol()+1);
        return;
    }
    
}



void dragon::selfHeal()
{
    bool heal = trueWithProbability(0.1);
    if(heal && getHp() < getMaxHp())
        setHp(getHp()+1);
}



























//--------------------------------------------------Functions for The Player--------------------------------------------------//





//-----------------Player Inventory Commands------------------//

void player::addToInventory(std::string* playerActions)
{
    std::string addResult = "";
    if(getRow()== getDungeon()->getMyGoldenRow() && getCol()== getDungeon()->getMyGoldenCol())
    {
        m_gameWon = true;
        
        addResult = "You pick up the golden idol\nCongratulations, you won!\n";
        
    }
    else
    {
        //find the object
        object* addMe = getDungeon()->findObject(getRow(), getCol());
        
        
        
        if(addMe!=nullptr)
        {
            //add the object to inventory
            if(Vec_inventory.size() < 25)
            {
                
                //add this object to the player's inventory vector
                Vec_inventory.push_back(addMe);
                
                
                //remove this object in the dungeon objects vector
                getDungeon()->removeObject(getRow(), getCol());
                
                
                //change the coordinates of this object
                addMe->moveToInventory();
            }
            
            
            
            
            // form the addResult string
            if(addMe->getIcon() == ')'||addMe->getIcon() == '?')
            {
                if(Vec_inventory.size() >= 25)
                    addResult = "Your knapsack is full; you can't pick that up.\n";
                
                else if(addMe->getIcon() == ')' && Vec_inventory.size() < 25)
                    addResult = "You pick up " + addMe->getName() +"\n";
                
                else if(addMe->getIcon() == '?' && Vec_inventory.size() < 25)
                    addResult = "You pick up a scroll called " + addMe->getName()+ "\n";
            }
        }
        
    }
    
    *playerActions += addResult;                        //inventory results are part of player messages
}



void player::showInventory() const
{
    std::cout << "Inventory:" << std::endl;
    
    for(int i=0; i < Vec_inventory.size(); i++)
    {
        char ch = ('a'+ i);
        std::cout << ch << ". " << Vec_inventory[i]->getName() << std::endl;
    }
}




void player::wieldWeapon(int index,std::string* playerActions)
{
    std::string wieldResult = "";
    if(index >= Vec_inventory.size())
        return;
    object* o = Vec_inventory[index];
    weapon* w = dynamic_cast<weapon*>(o);              //use dynamic cast to differentiate a weapon from a scroll
    
    if(w != nullptr)                                //a scroll will result in null
    {
        setWeapon(w);
        wieldResult ="You are wielding " + w->getName() + "\n";
    }
    else
    {
        wieldResult ="You can't wield " + o->getName() + "\n";
    }
    
    *playerActions += wieldResult;
        
}



void player::readScroll(int index,std::string* playerActions)
{
    std::string readResult = "";
    
    
    if(index >= Vec_inventory.size())
        return;
    
    object* o = Vec_inventory[index];
    scroll* s = dynamic_cast<scroll*>(o);              //use dynamic cast to differentiate a weapon from a scroll

    
    if(s != nullptr)                                //a weapon will result in null
    {
        readResult = "You read the scroll called " + s->getName() + "\n" + s->getActionString()+ "\n";
        int amount = 0;
        int r = -1;
        int c = -1;
        switch(s->getMyId())
        {
            case 1: //tele
                getDungeon()->findVacant(r, c);
                setRow(r);
                setCol(c);
                
                break;
            case 2: //iarm
                amount = randInt(1, 3);
                if(getArm()+amount < 100)
                    setArm(getArm()+amount);
                
                break;
            case 3: //istr
                amount = randInt(1, 3);
                if(getStr()+amount < 100)
                    setStr(getStr()+amount);
                
                break;
            case 4: //ihel
                amount = randInt(3, 8);
                if(getHp()+amount < 100)
                    setMaxHp(getMaxHp()+amount);
                
                break;
            case 5: //idex
                if(getDex()+1 < 100)
                    setDex(getDex()+1);
                
                break;
        }
        //this part erases the scroll used from my inventory
        s->setRow(-2);
        s->setCol(-2);
        
        std::vector<object*>::iterator it;
        it = Vec_inventory.begin();
        while(it != Vec_inventory.end())
        {
            if((*it)->getRow() == -2 && (*it)->getCol() == -2)      //having the coordinates of (-2,-2) instead of (-1,-1) symblifies that the scroll has been used
            {
                delete *it;
                it = Vec_inventory.erase(it);
            }
            else
                it++;
        }
    }
    else
    {
        readResult = "You can't read a " + o->getName()+ "\n";
    }
    *playerActions += readResult;
}


















//----------------------Player Movement Commands-----------------------//


void player:: moveUp(std::string* playerActions)
{
    //the player is blocked by a wall
    getDungeon()->updateGrid();
    char c = getDungeon()->getCellStatus(getRow()-1, getCol());
    if(c=='#')
        return;
    
    
    
    //the player walks onto that spot
    else if(c != '#' && c!= 'B' && c !='S' && c!='D' && c!= 'G')
    {
        setRow(getRow()-1);
    }
    
    
    //the player attacks the monster at that spot
    
    else if(c== 'B' || c =='S' || c=='D' || c== 'G')
    {
        actor* attackMe = getDungeon()->findMonster(getRow()-1, getCol());
        attack(attackMe,playerActions);
    }
}


void player:: moveDown(std::string* playerActions)
{
    //the player is blocked by a wall
    getDungeon()->updateGrid();
    char c = getDungeon()->getCellStatus(getRow()+1, getCol());
    if(c=='#')
        return;
    
    
    
    //the player walks onto that spot
    else if(c != '#' && c!= 'B' && c !='S' && c!='D' && c!= 'G')
    {
        setRow(getRow()+1);
    }
    
    
    //the player attacks the monster at that spot
    
    else if(c== 'B' || c =='S' || c=='D' || c== 'G')
    {
        actor* attackMe = getDungeon()->findMonster(getRow()+1, getCol());
        attack(attackMe,playerActions);
    }
}

void player:: moveLeft(std::string* playerActions)
{
    //the player is blocked by a wall
    getDungeon()->updateGrid();
    char c = getDungeon()->getCellStatus(getRow(), getCol()-1);
    if(c=='#')
        return;
    
    
    
    //the player walks onto that spot
    else if(c != '#' && c!= 'B' && c !='S' && c!='D' && c!= 'G')
    {
        setCol(getCol()-1);
    }
    
    
    //the player attacks the monster at that spot
    
    else if(c== 'B' || c =='S' || c=='D' || c== 'G')
    {
        actor* attackMe = getDungeon()->findMonster(getRow(), getCol()-1);
        attack(attackMe,playerActions);
    }
}

void player:: moveRight(std::string* playerActions)
{
    //the player is blocked by a wall
    getDungeon()->updateGrid();
    char c = getDungeon()->getCellStatus(getRow(), getCol()+1);
    if(c=='#')
        return;
    
    
    
    //the player walks onto that spot
    else if(c != '#' && c!= 'B' && c !='S' && c!='D' && c!= 'G')
    {
        setCol(getCol()+1);
    }
    
    
    //the player attacks the monster at that spot
    
    else if(c== 'B' || c =='S' || c=='D' || c== 'G')
    {
        actor* attackMe = getDungeon()->findMonster(getRow(), getCol()+1);
        attack(attackMe,playerActions);
    }
}

















//----------------------Other Mini Commands-----------------------//



void player::selfHeal()
{
    bool heal = trueWithProbability(0.1);
    if(heal && getHp() < getMaxHp())
        setHp(getHp()+1);
}





bool actor::isAsleep() const
{
    if(m_slpt > 0)
        return true;
    else
        return false;
}



void player::cheat()
{
    setHp(50);
    setStr(9);
}



void player::die()
{
    setDead();
}
