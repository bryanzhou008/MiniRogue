//
//  actor.h
//  Project3
//
//  Created by Bryan Zhou on 5/15/20.
//  Copyright © 2020 Bryan Zhou. All rights reserved.
//

#ifndef actor_h
#define actor_h

#include <string>
#include <vector>

#include "utilities.h"
#include "object.h"
#include "dungeon.h"


class dungeon;



class actor
{
public:
     // Constructor/Destructor
    actor(int hp, int arm, int str, int dex, int row, int col, dungeon* dungeon, weapon* weapon, std::string name, char icon);
    
    
    virtual ~actor();
    
    // Accessors
    int getRow() const {return m_row;}
    int getCol() const {return m_col;}
    
    int getHp() const {return m_hp;}
    int getArm() const {return m_arm;}
    int getStr() const {return m_str;}
    int getDex() const {return m_dex;}
    
    char getIcon() const{return m_icon;}
    dungeon* getDungeon() const{return m_dungeon;}
    
    
    
    std::string getName() const {return m_name;}
    
    std::string getWeaponName() const {return m_weapon->getName();}
    
    weapon* getWeapon() const {return m_weapon;}
    
    
    
    bool isDead() const;
    
    
    
    
    
    int getslpt() const {return m_slpt;}
    bool isAsleep() const;
    
   
    
    
    
      
    // Mutators
    
    void setRow(int r){m_row = r;}
    void setCol(int c){m_col = c;}
    
    void setHp(int hp){m_hp = hp;}
    void setArm(int arm){m_arm = arm;}
    void setStr(int str){m_str = str;}
    void setDex(int dex){m_dex = dex;}
    
    void setWeapon(weapon* wieldMe){m_weapon = wieldMe;}
    
    void setSlpt(int slpt){m_slpt = slpt;}
    
    void setDungeon(dungeon* dungeon){m_dungeon = dungeon;}
    
    void setDead(){m_isDead = true;}
    
    
    void attack(actor* defender, std::string* actions);
    
    
    
    void monsterTurn(std::string* monsterActions);
    
    
    virtual void die();
    
    virtual void moveTowardsPlayer();
    
    virtual void selfHeal(){}

    
    
    
    
private:
    int m_row;
    int m_col;
    
    char m_icon;
    
    weapon* m_weapon;
    dungeon* m_dungeon;

    
    int m_hp;
    int m_arm;
    int m_str;
    int m_dex;
    
    
    int m_slpt;
    
    std::string m_name;
    
    bool m_isDead;
    
    
    
    
    
};






class player: public actor
{
public:
    // Constructor/Destructor
    player(int row, int col, dungeon* dungeon)
    :actor(20, 2, 2, 2, row, col, dungeon, new S_sword(), "Player", '@')
    {
        Vec_inventory.reserve(25);
        Vec_inventory.push_back(getWeapon());
        m_maxHp = 20;
        m_gameWon = false;
    }
    virtual ~player()
    {
        std::vector<object*>::iterator it;
        it = Vec_inventory.begin();
        while(it != Vec_inventory.end())
        {
            if(*it != getWeapon())
            delete *it;
            it = Vec_inventory.erase(it);
        }
        
        
//        for (int i = 0; i < Vec_inventory.size(); i++)
//        {
//            if(Vec_inventory[i] != getWeapon())
//                delete Vec_inventory[i];
//        }
            
    }
//    for (int i = 0; i < m_monster; i++)
//    delete Vec_monsters[i];
    // Accessors
    bool gameWon() const {return m_gameWon;}
    void showInventory() const;
    int getMaxHp() const {return m_maxHp;}
    
    
    
    // Mutators
    void setMaxHp(int max) {m_maxHp = max;}
    void cheat();

    
    
    void addToInventory(std::string* playerActions);
    void removeFromInventory();
    
    void wieldWeapon(int index,std::string* playerActions);
    void readScroll(int index,std::string* playerActions);
    
    void moveUp(std::string* playerActions);
    void moveDown(std::string* playerActions);
    void moveLeft(std::string* playerActions);
    void moveRight(std::string* playerActions);
    
    
    virtual void die();
    
    
    virtual void selfHeal();
    
private:
    std::vector<object*> Vec_inventory;
    int m_maxHp;
    bool m_gameWon;
    
    
};







class bogeyman: public actor
{
public:
    bogeyman(int row, int col, dungeon* dungeon)
    :actor(randInt(5, 10), 2, randInt(2, 3), randInt(2, 3), row, col, dungeon, new S_sword(), "the Bogeyman",'B')
    {
        
    }
    virtual ~bogeyman(){}
    
    
private:
    
};

class snakewoman: public actor
{
public:
    snakewoman(int row, int col, dungeon* dungeon)
    :actor(randInt(3, 6), 3, 2, 3, row, col, dungeon, new fang(), "the Snakewoman",'S')
    {
        
    }
    virtual ~snakewoman(){}
    
private:
};

class dragon: public actor
{
public:
    dragon(int row, int col, dungeon* dungeon)
    :actor(randInt(20, 25), 4, 4, 4, row, col, dungeon, new L_sword(), "the Dragon",'D')
    {
        m_maxHp = getHp();                      //using the base class's functions before fully constructing the derived class
    }
    
    
    int getMaxHp() const {return m_maxHp;}
    
    virtual ~dragon(){}
    virtual void selfHeal();
    
private:
    int m_maxHp;
};


class goblin: public actor
{
public:
    goblin(int row, int col, dungeon* dungeon)
    :actor(randInt(15, 20), 1, 3, 1, row, col, dungeon, new S_sword(), "the Goblin",'G')
    {
        
    }
    virtual ~goblin(){}
    
    
    
    
    
    
    virtual void moveTowardsPlayer();
    
private:
};

#endif /* actor_h */
