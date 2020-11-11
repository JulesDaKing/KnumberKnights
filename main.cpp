#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <map>

#include "Equipment.h"
#include "Character.h"
#include "Combat.h"

using namespace std;

//Pointless note but uh... i need to clean up how bad of a mess this is or my OCD will kill me ( if covid doesnt do it first )

int main()
{
    
    //TODO: this is all going to go in a class called Dungeon and the session class will be renamed CombatInstance
    //Future plans may involve another overarching class called WorldSession if world exlporation is implemented

    //SPAWN the star of the game aka the PLAYER
    Character *Player = new Character;

    //SPAWN starting EQUIPMENT || TODO: create library of equipment map<string,string,int,Equipment> ("class",type,quality,Object)
    //library can be initilized when world/dungeon created
    Equipment *Sword = new Equipment( "Sword " , 4 , 2 , 1 );
    Equipment *Shield = new Equipment( "Shield" , 0 , 2 , 2 );
    Equipment *Dagger = new Equipment( "Dagger" , 4 , 1 , 0 );

    //ADD WEAPONS to INVENTORY || TODO: add item and armor inventory
    Player->addCharacterWeapon( Sword );
    Player->addCharacterWeapon( Shield );
    Player->addCharacterWeapon( Dagger );

    //INITIALIZE SESSION VARIABLES
    int LevelDifficulty = 0;
    int CurrentRound = 0;
    int MaxRounds = 3;

    bool bPlayerAlive = true;
    //vector<bool> bLevelsWon; //keep track if all enemies were killed or someone ran away

    //LOOP through MULTIPLE LEVELS (To be redesigned with dungeon implimitation)
    do {
        CurrentRound++;
        LevelDifficulty++;

        //SET starting STATS
        Player->setCharacterStats( 200 , 200 );

        //GENERATE SEED || should work here rite? || add to constructor of dungeon class when applicable
        srand( time( NULL ) );

        //NEW COMBAT object by the name LEVEL || TODO: rename
        CombatInstance *Level = new CombatInstance ;
        Level->setInstanceDifficulty( LevelDifficulty );

        //SPAWN and STORE ENEMIES || would pointers be easier? || i feel like there will alot be problems later if pointers arent used
        map<int,Character *> ListOfEnemies = Level->SpawnEnemies( LevelDifficulty ) ;

        //PLAY LEVEL and then GET if PLAYER ALIVE
        bPlayerAlive = Level->PlayLevel( Player , ListOfEnemies );

        //TODO: delete enemies for that level
        delete Level;

    } while( CurrentRound < MaxRounds && bPlayerAlive );

    if( bPlayerAlive )
    {
        cout
            << endl 
            << endl 
            << "Congrats You Survived!" << endl
        ;
    }

    cout 
        << endl
        << endl
        << endl
    ;

    return 0;

}