// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

// You may add data members and other member functions to this class.


#include "dungeon.h"
#include "actor.h"



class Game
{
public:
    // Constructor/destructor
    Game(int goblinSmellDistance);
    ~Game();
    
    
    
    //Mutators
    void play();
    void newLevel(int level);
    
    
    
private:
    dungeon* m_dungeon;
    player* m_player;
    int m_goblinSmellDistance;
    
    
};




#endif // GAME_INCLUDED
