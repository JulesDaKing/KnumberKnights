#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <map>

using namespace std;

//Pointless note but uh... i need to clean up how bad of a mess this is or my OCD will kill me ( if covid doesnt do it first )

//TODO: by the mercy of God put these in seperate files with a dedicated header file
class Equipment
{
//private: 
public: //TODO: make private and make functions to get vars || or not? not necessary but bad practice i guess
    string Name;
    int Damage;
    int Weight;
    int Defense;
    //string StatusEffect; //useful for items and enchanted or poisoned items
//public:
    Equipment( string setName , int setDamage , int setWeight , int setDefense ) 
    {
        Name = setName;
        Damage = setDamage;
        Weight = setWeight;
        Defense = setDefense;
        cout << Name << " created " << endl ;
    }
};


class Character
{
private:
    int CharacterHealth; //TODO: store into array to have currentState, currentMax, absoluteMax(for when resting is implemented)
    int CharacterEnergy; // "
    //int CharacterMana; // "
    //int CharacterArmor; // TODO: make into map and add multiple slots: map<string,Equipment> (slot, armor)
    //int CharacterMagicType;
    vector<Equipment> CharacterWeapon;//first weapon main hand, second weapon off hand ( Name, Damage, Weight, Defense )

    //TODO: create damage and defense stats that change after getValidMove
    //TODO: create more complex inventory with tabs for items, weapons, armor, magic and treasure?(for achievements or unique unlocks)
    
public:
    void setCharacterStats( int Health , int Energy ) 
    {
        CharacterHealth = Health;
        CharacterEnergy = Energy;
        //CharacterMana = Mana;
    };
    void addCharacterWeapon( Equipment NewWeapon ) { CharacterWeapon.push_back( NewWeapon ); };
    void setUsedEnergy( int EnergyUsed ) { CharacterEnergy -= EnergyUsed; };
    bool setDamageToCharacter( int IncomingDamage /*, int DefenseMultiplier */) //defense multiplier is currently applied outside of function
    {
        //SUBTRACT DEFENSE STATS from incoming DAMAGE and APPLY to CHARACTER
        //IncomingDamage -= ( CharacterWeapon[ 0 ].Defense + CharacterWeapon[ 1 ].Defense ) * DefenseMultiplier;
        CharacterHealth -= IncomingDamage;
        cout << IncomingDamage << " damage" ;
        if( CharacterHealth <= 0 ) { return false; } //check if character died
        return true;//return true if character is still alive
    };
    //int getCharacterAttack() { return 2 * ( CharacterWeapon[0].Damage + CharacterWeapon[1].Damage ); };
    int getCharacterHealth() { return CharacterHealth; };
    int getCharacterEnergy() { return CharacterEnergy; };
    Equipment getCharacterWeapon( int vectorPlace ) { return CharacterWeapon[ vectorPlace ]; };
    int getCharacterWeaponCount() { return CharacterWeapon.size(); };
};


class Session
{
private:
    int SessionDifficulty;
    int GameSpeed;//used for testing (for now?)
    //add more Variables here if possible
public:
    Session() { cout << "Level created" << endl; };

    void setSessionDifficulty( int Difficulty ) { SessionDifficulty = Difficulty; };
    void Display( Character Player , map<int,Character> EnemyList )
    {
        cout
            << "  -PLAYER-  " << endl
            << "| Health   | " << Player.getCharacterHealth() << endl
            << "| Energy   | " << Player.getCharacterEnergy() << endl
            << "| Main     | " << Player.getCharacterWeapon( 0 ).Name << endl
            << "| OffHand  | " << Player.getCharacterWeapon( 1 ).Name << endl
            << endl 
        ;
        for ( int EnemyCount = 1 ; EnemyCount <= EnemyList.size() ; EnemyCount++ )
        {
            cout
                << "  -ENEMY" << EnemyCount << "- " << endl
                << "|  Health  | " << EnemyList[ 1 ].getCharacterHealth() << endl
                << "|  Energy  | " << EnemyList[ 1 ].getCharacterEnergy() << endl
                << "|   Main   | " << EnemyList[ 1 ].getCharacterWeapon( 0 ).Name << endl
                << "| OffHand  | " << EnemyList[ 1 ].getCharacterWeapon( 1 ).Name << endl
                << endl 
            ;
        }
    };
    vector<int> getValidMoveAndTarget( Character Player )
    {
        string PlayerMove;
        int PlayerMoveInt;
        vector<int> ValidMove;
        bool bMoveIsValid = true;
        //LOOP till VALID move: not a menu option
        do 
        {
            //DISPLAY OPTIONS
            cout 
                << endl
                << "| 1 : light attack |" << "| 2 : heavy attack |" << "| 3 : block        |" << endl
                << endl
                << "| 4 :              |" << "| 5 :              |" << "| 6 :              |" << endl
                << endl
                << "| 7 :              |" << "| 8 :              |" << "| 9 : Inventory    |" << endl
                << endl
                << "| 0 : MENU(unused) |" << endl
                << endl
            ;
            //GET PLAYER INPUT
            cout << "Enter your move..." << endl ;    
            getline( cin , PlayerMove );
            PlayerMoveInt = stoi( PlayerMove );
            //IF MENU DISPLAY MENU validMove = false
            switch (PlayerMoveInt)  
            {
                case 1 : case 2: case 3: case 4: case 5: case 6: case 7: case 8:
                    bMoveIsValid = true;
                break;
                case 9:
                    int Input1;
                    int Input2;
                    //DISPLAY INVENTORY
                    for ( int WeaponCount = 0 ; WeaponCount < Player.getCharacterWeaponCount() ; WeaponCount++ ) 
                    { cout << "Slot " << WeaponCount << " : " << Player.getCharacterWeapon( WeaponCount ).Name << endl; }
                    //GET WEAPON BEING MOVED
                    cout << "Choose a weapon to move..." << endl;
                    getline( cin , PlayerMove );
                    Input1 = stoi( PlayerMove );
                    //CHOOSE SLOT
                    cout << "Choose a weapon to switch with..." << endl;
                    getline( cin , PlayerMove );
                    Input2 = stoi( PlayerMove );
                    //SWITCH WEAPONS
                    cout << "CANT SWITCH WEAPONS YET!" << endl ;
                    bMoveIsValid = false;
                break;
                case 0:
                    //DISPLAY IN GAME MENU 
                    //GET MENU INPUT
                    bMoveIsValid = false;
                break;
                default:
                    bMoveIsValid = false;
                break;
            }
            
        } while (!bMoveIsValid);
        //CHOOSE VALID TARGET

        //RETURN VALID MOVE AND TARGET
        ValidMove.push_back( PlayerMoveInt );
        ValidMove.push_back( 1 );
        return ValidMove;
    };
    int getEnemyMove() { return ( rand() % 3 ) + 1 ; }; //return random number between 1 and 3 for now || super advanced AI algorithm
    vector<int> getMoveStats( Character RelevantCharacter , int CharacterInput ) //TODO: Move switch functions to here (currently unused)
    {
        int Multipliers[] = { 1 , 1 , 1 , 0 }; //Damage, Energy, Defense, Mana(unused)
        vector<int> AppliedStats; //Damage, Energy, Defense, Mana(unused)

        //Switch ( CharacterInput )
        //if RelevantCharacter.getCharacterWeaponCount() < 2
        //Set AppliedStats

        return AppliedStats;
    };
    map<int,Character> SpawnEnemies( int Difficulty ) // Has to be map cause it starts from 1 not 0
    {
        //INITIALIZE ENEMIES ACCORDING TO DIFFICULTY || TODO: add null in first slot or start from 1 (i dunno)
        map<int,Character> SpawnedEnemies;

        //SPAWN ONE ENEMY for now... || TODO: add a loop (starting with 1 not 0)
        Character Enemy;

        //SPAWN WEAPONS
        Equipment Sword( "Sword " , 4 , 4 , 1 );
        //TODO: generate weapons according to difficulty
        //Equipment Shield( "Shield" , 0 , 4 , 2 );
        //Equipment Dagger( "Dagger" , 4 , 2 , 0 );

        //ADD WEAPONS TO INVENTORY || TODO: put next appropriate weapon
        Enemy.addCharacterWeapon( Sword );
        //Enemy.addCharacterWeapon( Shield );
        //Enemy.addCharacterWeapon( Dagger );

        //SET STATS according to DIFFICULTY
        int EnemyHealth = Difficulty * 50;
        int EnemyEnergy = Difficulty * 50;

        Enemy.setCharacterStats( EnemyHealth , EnemyEnergy );

        //ADD TO ENEMY LIST future proofed
        SpawnedEnemies[ 1 ] = Enemy;

        return SpawnedEnemies;
    };
    bool PlayLevel( Character Player, map<int,Character> EnemyList )
    {
        
        GameSpeed = 2;//i just put it here because of warning

        //----------------------------------------------------------------------------------------------------------
        //                                          - -------------- -
        //                                         - MAIN COMBAT LOOP -
        //                                          - -------------- -
        //----------------------------------------------------------------------------------------------------------
        
        //DISPLAY LEVL START MESSAGE
        cout 
            << endl 
            << "Level Started : Difficulty : " << SessionDifficulty << endl 
            << endl
        ;

        //INITILIAZE LIFE STATES
        bool bPlayerAlive = true;
        bool bAnyEnemiesAlive = true;
        map<int,bool> bEnemyAlive;
        //SET all ENEMIES as ALIVE
        for( int EnemyCount = 1 ; EnemyCount <= EnemyList.size() ;  EnemyCount++ ){ bEnemyAlive[ EnemyCount ] = true; }

        int Turn = 0;

        //LOOP WHILE any ENEMIES are ALIVE
        while( bAnyEnemiesAlive )
        {   
            Turn++;
            //DISPLAY
            cout << endl << endl << endl << endl << " Turn " << Turn << endl << endl;
            Display( Player , EnemyList );

            //----------------------------------------------------------------------------------------------------------
            //  PLAYER MOVE:
            //----------------------------------------------------------------------------------------------------------

            vector<int> PlayerInputAndTarget = getValidMoveAndTarget( Player );

            int PlayerInput = PlayerInputAndTarget[ 0 ];
            int EnemyTargeted = PlayerInputAndTarget[ 1 ];// EnemyTarget = 0 for non target moves ( such as area attacks ) || TODO: implement EnemyTargeted

            //TODO: Make into function to reduce code repetition || getMoveMultipliers( Player , )

            //Set player offensive and defensive stats
            int PlayerDamageMultiplier = 1;
            int PlayerEnergyMultiplier = 1;
            int PlayerDefenseMultiplier = 1;
            //int ManaMultiplier = 0;

            switch( PlayerInput )
            {
                case 1 : //light attack
                cout << "You make a light attack... " << endl;
                break;

                case 2 : //heavy attack
                PlayerDamageMultiplier = 3;
                PlayerEnergyMultiplier = 2;
                PlayerDefenseMultiplier = 0;
                cout << "You make a heavy attack... " << endl;
                break;

                case 3 : //block
                PlayerDamageMultiplier = 0;
                PlayerDefenseMultiplier = 2;
                cout << "You block... " << endl;
                break;

                // case 4: //light magic
                // PlayerDamageMultiplier = 1;
                // PlayerEnergyMultiplier = 0;
                // //ManaMultiplier = 1;
                // cout << " you make a light magic attack... " << endl;
                // break;

                // case 5: //heavy magic
                // PlayerDamageMultiplier = 3;
                // PlayerEnergyMultiplier = 0;
                // //ManaMultiplier = 2;
                // cout << " you make a heavy magic attack... " << endl;
                // break;

                // case 6: //Special magic ability
                // PlayerDamageMultiplier = 8;
                // PlayerEnergyMultiplier = 3;
                // //ManaMultiplier = 3;
                // cout << " you use your special ability... " << endl;
                // break;

                // case 7: //use item
                // PlayerDamageMultiplier = 0;
                // cout << " you use your item... " << endl;
                // break;

                // case 8: //escape
                // PlayerDamageMultiplier = 0;
                // PlayerEnergyMultiplier = 2;
                // PlayerDefenseMultiplier = 0;
                // break;

                default :
                PlayerDamageMultiplier = 0;
                PlayerEnergyMultiplier = 0;
                cout << " you do nothing... " << endl;
                break;
            }

            //int PlayerMagicType = Player.getCharacterMagicType();

            //switch( PlayerMagicType ) {}
            
            //TODO: initialize before switch (to set up when migrating to a function)
            //(main weapon damage + offhand weapon damage) * PlayerDamageMultiplier * Game speed multiplier (to speed things up)
            int PlayerDamage = ( Player.getCharacterWeapon( 0 ).Damage + Player.getCharacterWeapon( 1 ).Damage ) * PlayerDamageMultiplier * GameSpeed;
            //(main weapon weight + offhand weapon weight) * PlayerEnergyMultiplier * 2 (same as above)
            int PlayerEnergyUsed = ( Player.getCharacterWeapon( 0 ).Weight + Player.getCharacterWeapon( 1 ).Weight ) * PlayerEnergyMultiplier * GameSpeed;

            int PlayerDefense = ( Player.getCharacterWeapon( 0 ).Defense + Player.getCharacterWeapon( 1 ).Defense ) * PlayerDefenseMultiplier * GameSpeed;

            //----------------------------------------------------------------------------------------------------------
            //  ENEMY MOVES:
            //----------------------------------------------------------------------------------------------------------

            //Set player offensive and defensive stats || has to be map cause it starts from 1 not 0
            map<int,int> EnemyDamageMultiplier;
            map<int,int> EnemyEnergyMultiplier;
            map<int,int> EnemyDefenseMultiplier;
            //map<int,int> ManaMultiplier;

            map<int,int> EnemyDamage;
            map<int,int> EnemyEnergyUsed;
            map<int,int> EnemyDefense;

            for( int EnemyNumber = 1; EnemyNumber <= EnemyList.size() ; EnemyNumber++ )
            {
                
                int EnemyMove = getEnemyMove(); 

                EnemyDamageMultiplier[ EnemyNumber ] = 1;
                EnemyEnergyMultiplier[ EnemyNumber ] = 1;
                EnemyDefenseMultiplier[ EnemyNumber ] = 1;

                switch( EnemyMove )
                {
                    case 1 : //light attack
                    cout << "Enemy " << EnemyNumber << " makes a light attack... " << endl;
                    break;

                    case 2 : //heavy attack
                    EnemyDamageMultiplier[ EnemyNumber ] = 3;
                    EnemyEnergyMultiplier[ EnemyNumber ] = 2;
                    EnemyDefenseMultiplier[ EnemyNumber ] = 0;
                    cout << "Enemy " << EnemyNumber << " makes a heavy attack... " << endl;
                    break;

                    case 3 : //block
                    EnemyDamageMultiplier[ EnemyNumber ] = 0;
                    EnemyDefenseMultiplier[ EnemyNumber ] = 2;
                    cout << "Enemy " << EnemyNumber << " blocks... " << endl;
                    break;

                    // case 4: //light magic
                    // EnemyDamageMultiplier[ EnemyNumber ] = 1;
                    // EnemyEnergyMultiplier[ EnemyNumber ] = 0;
                    // //ManaMultiplier[ EnemyNumber ] = 1;
                    // cout << " you make a light magic attack... " << endl;
                    // break;

                    // case 5: //heavy magic
                    // EnemyDamageMultiplier[ EnemyNumber ] = 3;
                    // EnemyEnergyMultiplier[ EnemyNumber ] = 0;
                    // //ManaMultiplier[ EnemyNumber ] = 2;
                    // cout << " you make a heavy magic attack... " << endl;
                    // break;

                    // case 6: //Special magic ability
                    // EnemyDamageMultiplier[ EnemyNumber ] = 8;
                    // EnemyEnergyMultiplier[ EnemyNumber ] = 3;
                    // //ManaMultiplier[ EnemyNumber ] = 3;
                    // cout << " you use your special ability... " << endl;
                    // break;

                    // case 7: //use item
                    // EnemyDamageMultiplier[ EnemyNumber ] = 0;
                    // cout << " you use your item... " << endl;
                    // break;

                    // case 8: //escape
                    // EnemyDamageMultiplier[ EnemyNumber ] = 0;
                    // EnemyEnergyMultiplier[ EnemyNumber ] = 2;
                    // EnemyDefenseMultiplier[ EnemyNumber ] = 0;
                    // break;

                    default :
                    EnemyDamageMultiplier[ EnemyNumber ] = 0;
                    EnemyEnergyMultiplier[ EnemyNumber ] = 0;
                    cout << "Enemy " << EnemyNumber << " does nothing... " << endl;
                    break;
                }

                //int EnemyMagicType = Enemy.getCharacterMagicType();

                //switch( EnemyMagicType ) {}
                
                //CHECK if ENEMY has MULTIPLE WEAPONS equiped
                if( EnemyList[ EnemyNumber ].getCharacterWeaponCount() < 2 )// if enemy only has 1 weapon || same set up as how player stats is multiplied
                {
                    EnemyDamage[ EnemyNumber ] = ( EnemyList[ EnemyNumber ].getCharacterWeapon( 0 ).Damage ) * EnemyDamageMultiplier[ EnemyNumber] * GameSpeed;
                    EnemyEnergyUsed[ EnemyNumber ] = ( EnemyList[ EnemyNumber ].getCharacterWeapon( 0 ).Weight ) * EnemyEnergyMultiplier[ EnemyNumber] * GameSpeed;
                    EnemyDefense[ EnemyNumber ] = ( EnemyList[ EnemyNumber ].getCharacterWeapon( 0 ).Defense ) * EnemyDefenseMultiplier[ EnemyNumber] * GameSpeed;
                } 
                else //assume enemy has at least a single weapon
                {
                    EnemyDamage[ EnemyNumber ] = ( EnemyList[ EnemyNumber ].getCharacterWeapon( 0 ).Damage + EnemyList[ EnemyNumber ].getCharacterWeapon( 1 ).Damage ) * EnemyDamageMultiplier[ EnemyNumber] * GameSpeed;
                    EnemyEnergyUsed[ EnemyNumber ] = ( EnemyList[ EnemyNumber ].getCharacterWeapon( 0 ).Weight + EnemyList[ EnemyNumber ].getCharacterWeapon( 1 ).Weight ) * EnemyEnergyMultiplier[ EnemyNumber] * GameSpeed;
                    EnemyDefense[ EnemyNumber ] = ( EnemyList[ EnemyNumber ].getCharacterWeapon( 0 ).Defense + EnemyList[ EnemyNumber ].getCharacterWeapon( 1 ).Defense ) * EnemyDefenseMultiplier[ EnemyNumber] * GameSpeed;
                }

            }

            //----------------------------------------------------------------------------------------------------------
            //  APPLY MOVES: || TODO: label everthing properly when im not lazy ( or sick with covid-19 :D )
            //----------------------------------------------------------------------------------------------------------

            //int EnemyTargeted = 1; //TODO: add a targeting option

            cout << PlayerDamage << endl;
            cout << PlayerDefense << endl;
            cout << EnemyDamage[ EnemyTargeted ] << endl;
            cout << EnemyDefense[ EnemyTargeted ] << endl;

            //Subtract Enemy Defense from Player attack
            PlayerDamage -= EnemyDefense[ EnemyTargeted ];
            if ( PlayerDamage < 0 ) { PlayerDamage = 0; }
            //Subtract Player Defense from Enemy attacks
            for( int EnemyNumber2 = 1 ; EnemyNumber2 <= EnemyList.size() ; EnemyNumber2++ ) //has to be have a 2 cause of weirdness
            { 
                EnemyDamage[ EnemyNumber2 ] -= PlayerDefense; 
                if ( EnemyDamage[ EnemyNumber2 ] < 0 ) { EnemyDamage[ EnemyNumber2 ] = 0; }
            }
            //TODO: add to same loop as above
            //Apply damage to player first (if player dies then theres no reason to keep going) bPlayerAlive || If enemy has energy
            for ( int EnemyNumber3 = 1 ; EnemyNumber3 <= EnemyList.size() ; EnemyNumber3++ ) 
            {
                //If Enemy has enough energy to move then...
                if ( EnemyList[ EnemyNumber3 ].getCharacterEnergy() > EnemyEnergyUsed[ EnemyNumber3 ] )
                {
                    //...use enemy's energy...
                    EnemyList[ EnemyNumber3 ].setUsedEnergy( EnemyEnergyUsed[ EnemyNumber3 ] ) ;
                    //and Damage player
                    cout << "Enemy " << EnemyNumber3 << " does ";
                    bPlayerAlive = Player.setDamageToCharacter( EnemyDamage[ EnemyNumber3 ] ) ;
                    cout << " to you..." << endl;
                }
                else
                {
                    cout << "Enemy " << EnemyNumber3 << " is too tired..." << endl;
                }
                //If Player is dead return false ( END GAME )
                if( !bPlayerAlive ) 
                { 
                    cout << "...You died" << endl;
                    return false; 
                }
                
            }
                
            //Apply damage to targeted Enemy || bEnemyAlive[ EnemyTargeted ] || EnemyTargeted = 1; (for now)
            if( Player.getCharacterEnergy() > PlayerEnergyUsed )
            {
                Player.setUsedEnergy( PlayerEnergyUsed );
                cout << "You do ";
                bEnemyAlive[ EnemyTargeted ] = EnemyList[ EnemyTargeted ].setDamageToCharacter( PlayerDamage );
                cout << " to Enemy " << EnemyTargeted << "..." << endl;
                if (!bEnemyAlive[ EnemyTargeted ]){ cout << "The Target died..." << endl; }
            }

            bool bEnemyCheck = false;

            int EnemyNumber4 = 1;
            //while bEnemyCheck = false or EnemyNumber <= EnemyList.size() ||  bEnemyCheck = bEnemyAlive[ EnemyNumber ];
            while( bEnemyCheck == false && EnemyNumber4 <= EnemyList.size() )
            {
                bEnemyCheck = bEnemyAlive[ EnemyNumber4 ];//will be false until a live enemy is found
                EnemyNumber4++;
            }
            bAnyEnemiesAlive = bEnemyCheck;

        }

        cout << "all enemies are dead" << endl;

        return true;

        //DISPLAY || This part is redundant and never runs, but im leaving it here for now
        cout 
            << endl 
            << "Level Started : Difficulty : " << SessionDifficulty << endl 
            << endl
            << "  -PLAYER-  " << endl
            << "| Health   | " << Player.getCharacterHealth() << endl
            << "| Energy   | " << Player.getCharacterEnergy() << endl
            << "| Main     | " << Player.getCharacterWeapon( 0 ).Name << endl
            << "| OffHand  | " << Player.getCharacterWeapon( 1 ).Name << endl
            << endl 
            << "  -ENEMY1- " << endl
            << "|  Health  | " << EnemyList[0].getCharacterHealth() << endl
            << "|  Energy  | " << EnemyList[0].getCharacterEnergy() << endl
            << "|   Main   | " << EnemyList[0].getCharacterWeapon( 0 ).Name << endl
            << "| OffHand  | " << EnemyList[0].getCharacterWeapon( 1 ).Name << endl
            << endl 
        ;

        return true;

    };

    ~Session() { cout << "Level ended" << endl; };
};





int main()
{
    
    //TODO: this is all going to go in a class called Dungeon and the session class will be renamed CombatInstance
    //Future plans may involve another overarching class called WorldSession if world exlporation is implemented

    //SPAWN the star of the game aka the PLAYER
    Character Player;

    //SPAWN starting EQUIPMENT || TODO: create library of equipment map<string,string,int,Equipment> ("class",type,quality,Object)
    Equipment Sword( "Sword " , 4 , 4 , 1 );
    Equipment Shield( "Shield" , 0 , 4 , 2 );
    Equipment Dagger( "Dagger" , 4 , 2 , 0 );

    //ADD WEAPONS to INVENTORY || TODO: add item and armor inventory
    Player.addCharacterWeapon( Sword );
    Player.addCharacterWeapon( Shield );
    Player.addCharacterWeapon( Dagger );

    //SET starting STATS
    Player.setCharacterStats( 200 , 200 );

    //INITIALIZE SESSION VARIABLES
    int LevelDifficulty = 1;
    int CurrentRound = 0;
    int MaxRounds = 1;

    bool bPlayerAlive = true;
    //vector<bool> bLevelsWon; //keep track if all enemies were killed or someone ran away

    //LOOP through MULTIPLE LEVELS (To be redesigned with dungeon implimitation)
    do {
        CurrentRound++;

        //GENERATE SEED || should work here rite? || add to constrcutor of dungeon
        srand( time( NULL ) );

        //NEW SESSION object by the name LEVEL
        Session *Level = new Session ;
        Level->setSessionDifficulty( LevelDifficulty );

        //SPAWN and STORE ENEMIES || would pointers be easier? || i feel like there will alot be problems later if pointers arent used
        map<int,Character> ListOfEnemies = Level->SpawnEnemies( LevelDifficulty ) ;

        //PLAY LEVEL and then GET if PLAYER ALIVE
        bPlayerAlive = Level->PlayLevel( Player , ListOfEnemies );

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