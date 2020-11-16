#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Character.hpp"
#include "Display.hpp"

using namespace std;

class CombatInstance
{
private:

    string streamLine;
    Display *GameDisplay;
    Character *Player;
    EquipmentLibrary *Library;
    map<int,Character *> EnemyList;
    map<int,bool> bEnemyAlive;
    int GameSpeed;//used for testing (for now?)
    //add more Variables here if possible

public:

    CombatInstance( Character *GlobalPlayer , EquipmentLibrary *GlobalLibrary , Display *GlobalGameDisplay );

    //TODO: Move some functions to character class

    vector<int> getValidMoveAndTarget(); //Move to character class? || seperate into two functions if yes
    vector<int> getMoveStats( Character *RelevantCharacter , int CharacterInput ); //TODO: Move to Character Class?
    int getEnemyMove(); //return random number between 1 and 3 for now || super advanced AI algorithm || Character class?
    
    void SpawnEnemies( int Difficulty ); // Has to be map cause it starts from 1 not 0
    void DeleteEnemies();

    bool PlayLevel(); // MAIN COMBAT LOOP

    ~CombatInstance();

};
