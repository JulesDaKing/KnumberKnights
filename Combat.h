#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Character.h"

using namespace std;

class CombatInstance
{
private:

    int InstanceDifficulty;
    int GameSpeed;//used for testing (for now?)
    //add more Variables here if possible

public:

    CombatInstance();

    //TODO: Move some functions to character class
    void setInstanceDifficulty( int Difficulty );
    
    void Display( Character *Player , map<int,Character *> EnemyList );

    vector<int> getValidMoveAndTarget( Character *Player , map<int,bool> bEnemyAlive ); //Move to character class? || seperate into two functions if yes
    vector<int> getMoveStats( Character *RelevantCharacter , int CharacterInput ); //TODO: Move to Character Class?
    int getEnemyMove(); //return random number between 1 and 3 for now || super advanced AI algorithm || Character class?
    
    map<int,Character *> SpawnEnemies( int Difficulty ); // Has to be map cause it starts from 1 not 0

    bool PlayLevel( Character *Player, map<int,Character *> EnemyList ); // MAIN COMBAT LOOP

    ~CombatInstance();

};