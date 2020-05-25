// Game.cpp

#include "Game.h"
#include "utilities.h"
#include <iostream>
using namespace std;


Game::Game(int goblinSmellDistance)
:m_goblinSmellDistance(goblinSmellDistance)
{
    //create a dungeon
    m_dungeon = new dungeon(0,m_goblinSmellDistance);
    m_dungeon->populateWithMonsters();
    
    
    //create the player
    int r;
    int c;
    m_dungeon->findVacant(r, c);
    m_player = new player(r, c, m_dungeon);

    
    
    //put the player in the dungeon
    m_dungeon->setPlayer(m_player);
    m_dungeon->updateGrid();
    
    
    
    //The following are done by the dungeon constructor:
    
    //create monsters
    //insert monsters into the dungeon
    //create objects
    //insert objects into the dungeon
}





Game::~Game()
{
    delete m_dungeon;
    delete m_player;
}





void Game::play()
{
    clearScreen();
    m_dungeon->display();
    m_dungeon->displayStats();
    cout << endl << endl << endl;
    

    std::string playerActions = "";
    std::string monsterActions = "";
    
    
    
    
    while (!m_player->isDead() && !m_player->gameWon())
    {
        playerActions = "";
        monsterActions = "";
        
        
        m_player->selfHeal();           //the player heals itself before every turn, even if he is asleep
        
        if(m_player->isAsleep())        //skip the player's round if the player is asleep
        {
            m_player->setSlpt(m_player->getslpt()-1);
            getCharacter();             //this prevents the game from fast forwarding when the player is asleep
        }
        else                          //player's round since he is awake
        {
            switch(getCharacter())
            {
                    
                case 'q':
                    return;
                    break;
                    
                
                //-------------------movement commands--------------------//
                case 'h':
                {
                    m_player->moveLeft(&playerActions);
                    break;
                }
                case 'l':
                {
                    m_player->moveRight(&playerActions);
                    break;
                }
                case 'k':
                {
                    m_player->moveUp(&playerActions);
                    break;
                }
                case 'j':
                {
                    m_player->moveDown(&playerActions);
                    break;
                }
                    
                    
                //-------------------inventory commands--------------------//
                    
                    
                case 'i':
                {
                    clearScreen();
                    m_player->showInventory();
                    getCharacter();             //this charactor doesn't do anything
                    break;
                }
                    
                    
                    
                case 'g':
                {
                    m_player->addToInventory(&playerActions); //where did I deal with the golden idol??? I will come back to this in a moment
                    break;
                }
                    
                    
                case 'w':
                {
                    clearScreen();
                    m_player->showInventory();
                    
                    
                    char temp = getCharacter();
                    int index = (int)(temp - 97); // this should convert the item charactor into its corresponding index
                    m_player->wieldWeapon(index,&playerActions);
                    
                    break;
                }
                    
                    
                    
                case 'r':
                {
                    clearScreen();
                    m_player->showInventory();
                    
                    
                    char temp = getCharacter();
                    int index = (int)(temp - 97); // this should convert the item charactor into its corresponding index
                    m_player->readScroll(index,&playerActions);
                    
                    break;
                }
                    
                //-------------------other commands--------------------//
                case '>':
                {
                    if(m_dungeon->getMyStairRow()==m_player->getRow() && m_dungeon->getMyStairCol()==m_player->getCol())  //player stands on the staircase
                    {
                        newLevel(m_dungeon->getLevel()+1);
                        m_player->setDungeon(m_dungeon);
                        int r;
                        int c;
                        m_dungeon->findVacant(r, c);
                        m_player->setRow(r);
                        m_player->setCol(c);
                        m_dungeon->setPlayer(m_player);
                        m_dungeon->updateGrid();
                    }
                    break;
                }
                    
                    
                case 'c':
                {
                    m_player->cheat();
                    break;
                }
                    
                default: ;
            };
            m_dungeon->updateGrid();                        //update the grid after every player move
        }
        
        
        
        //-------------------Prepare for and Execute Monsters' Turn--------------------//
        //update the goblin moving grid before all monster turns:
        //step 1: clear grid
        //step 2: refresh to reflect current situation
        m_dungeon->clearPlayerDistanceMap();
        m_dungeon->refreshPlayerDistanceMap(m_player->getRow(), m_player->getCol(), m_goblinSmellDistance, 0);
        m_dungeon->monsterTurn(&monsterActions);
        
        
        
        
        //-------------------Print Game Interface--------------------//
        clearScreen();
        m_dungeon->display();
        m_dungeon->displayStats();
        if (playerActions != "")
            cout << playerActions;
        if (monsterActions != "")
            cout << monsterActions;
        cout << endl << endl << endl;
    }
    
    
    cout << "Press q to exit game." << endl;            //loop until the user types q
    while(getCharacter()!='q')
    {
        if(getCharacter()=='q')
            return;
    }
}







void Game::newLevel(int level)                  //this function is called every time a new level is reached
{
    delete m_dungeon;
    m_dungeon = new dungeon(level, m_goblinSmellDistance);
    m_dungeon->populateWithMonsters();
    
}
