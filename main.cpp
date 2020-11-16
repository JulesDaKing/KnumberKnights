#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <map>

//#include "Equipment.hpp"
//#include "Character.hpp"
#include "Combat.hpp"

using namespace std;

//Pointless note but uh... i need to clean up how bad of a mess this is or my OCD will kill me ( if covid doesnt do it first )

int main()
{
    
    //TODO: this is all going to go in a class called Dungeon and the session class will be renamed CombatInstance
    //Future plans may involve another overarching class called WorldSession if world exlporation is implemented

    Display *GameDisplay = new Display;

    //SPAWN the star of the game aka the PLAYER
    Character *Player = new Character;
    GameDisplay->setMagicColumn( 1 ); // assuming PLayer has "FIRE" equipped

    //SPAWN EQUIPMENT
    EquipmentLibrary *Library = new EquipmentLibrary;

    //ADD WEAPONS to INVENTORY || TODO: add armor inventory
    Player->addCharacterWeapon( Library->Weapons[ "Sword" ] );
    Player->addCharacterWeapon( Library->Weapons[ "Shield" ] );
    Player->addCharacterWeapon( Library->Weapons[ "Dagger" ] );

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
        Player->setCharacterStats( 250 , 250 , 250 , 250 );

        //GENERATE SEED || should work here rite? || add to constructor of dungeon class when applicable
        srand( time( NULL ) );

        //NEW COMBAT object by the name LEVEL || Player and Library Pointer is stored in Combat Instance 
        CombatInstance *Level = new CombatInstance( Player , Library , GameDisplay ) ;

        //SPAWN and STORE ENEMIES
        Level->SpawnEnemies( LevelDifficulty ) ;

        //PLAY LEVEL and then GET if PLAYER ALIVE
        bPlayerAlive = Level->PlayLevel();

        GameDisplay->DisplayScreen();

        //CLEAR SPACE by deleting STORED CLASSES
        Level->DeleteEnemies();
        delete Level;

    } while( CurrentRound < MaxRounds && bPlayerAlive );

    if( bPlayerAlive )
    {
        cout
            << endl 
            << "Congrats You Survived!" << endl
        ;

    }

    cout 
        << endl
        << endl
    ;

    return 0;

}