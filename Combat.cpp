#include "Combat.h"


CombatInstance::CombatInstance() { cout << "Level created" << endl; };

CombatInstance::~CombatInstance() { cout << "Level ended" << endl; };

//TODO: Move some functions to character class
void CombatInstance::setInstanceDifficulty( int Difficulty ) { InstanceDifficulty = Difficulty; };

int CombatInstance::getEnemyMove() { return ( rand() % 3 ) + 1 ; }; //return random number between 1 and 3 for now || super advanced AI algorithm

void CombatInstance::Display( Character *Player , map<int,Character *> EnemyList )
{
    cout
        << "  -PLAYER-  " << endl
        << "| Health   | " << Player->getCharacterHealth() << endl
        << "| Energy   | " << Player->getCharacterEnergy() << endl
        << "| Main     | " << Player->getCharacterWeapon( 0 )->Name << endl
        << "| OffHand  | " << Player->getCharacterWeapon( 1 )->Name << endl
        << endl 
    ;
    for ( int EnemyCount = 1 ; EnemyCount <= EnemyList.size() ; EnemyCount++ )
    {
        cout
            << "  -ENEMY" << EnemyCount << "- " << endl
            << "|  Health  | " << EnemyList[ EnemyCount ]->getCharacterHealth() << endl
            << "|  Energy  | " << EnemyList[ EnemyCount ]->getCharacterEnergy() << endl
            << "|   Main   | " << EnemyList[ EnemyCount ]->getCharacterWeapon( 0 )->Name << endl
            << "| OffHand  | " << EnemyList[ EnemyCount ]->getCharacterWeapon( 1 )->Name << endl
            << endl 
        ;
    }
};

vector<int> CombatInstance::getValidMoveAndTarget( Character *Player , map<int,bool> bEnemyAlive )
{

    string PlayerMove;
    int PlayerMoveInt;
    string PlayerTarget;
    int PlayerTargetInt;
    
    bool bMoveIsValid = false;
    bool bTargetIsValid = false;

    vector<int> ValidMove;

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
                for ( int WeaponCount = 0 ; WeaponCount < Player->getCharacterWeaponCount() ; WeaponCount++ ) 
                { cout << "Slot " << WeaponCount << " : " << Player->getCharacterWeapon( WeaponCount )->Name << endl; }

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
                cout << "Not a valid input... ";
                bMoveIsValid = false;
            break;
        }
        
    } while (!bMoveIsValid);

    //CHOOSE VALID TARGET || TODO: make check to see if Enemy chosen exists and is alive
    while ( PlayerMoveInt != 3 && !bTargetIsValid )
    {
        cout << "Enter your target..." << endl ;    
        getline( cin , PlayerTarget );
        PlayerTargetInt = stoi( PlayerTarget );

        if ( bEnemyAlive[ PlayerTargetInt ]) { bTargetIsValid = true; }
        else { cout << "Not a valid target..." << endl; }

    }

    //RETURN VALID MOVE AND TARGET || TODO: put stoi here not up where it is now
    ValidMove.push_back( PlayerMoveInt );
    ValidMove.push_back( PlayerTargetInt );

    return ValidMove;

};

vector<int> CombatInstance::getMoveStats( Character *RelevantCharacter , int CharacterInput ) //TODO: Move to Character Class?
{

    int Multipliers[] = { 1 , 1 , 1 , 0 }; //0 Damage, 1 Energy, 2 Defense, 3 Mana(unused)
    vector<int> AppliedStats; //Damage, Energy, Defense, Mana(unused)
    //int MagicType = RelevantCharacter.getCharacterMagicType();

    switch( CharacterInput )
    {
        case 1 : //light attack
        cout << " makes a light attack... " << endl;
        break;

        case 2 : //heavy attack
        Multipliers[ 0 ] = 2; //damage
        Multipliers[ 1 ] = 2; //energy
        Multipliers[ 2 ] = 0; //defense
        cout << " makes a heavy attack... " << endl;
        break;

        case 3 : //block
        Multipliers[ 0 ] = 0; //damage
        Multipliers[ 2 ] = 2; //defense
        cout << " blocks... " << endl;
        break;

        // case 4: //light magic
        // Multipliers[ 0 ] = 1; //damage
        // Multipliers[ 1 ] = 0; //energy
        // //Multipliers[ 3 ] = 1; //mana
        // cout << " makes a light magic attack... " << endl;
        // break;

        // case 5: //heavy magic
        // Multipliers[ 0 ] = 3; //damage
        // Multipliers[ 1 ] = 0; //energy
        // //Multipliers[ 3 ] = 2; //mana
        // cout << " makes a heavy magic attack... " << endl;
        // break;

        // case 6: //Special magic ability
        // Multipliers[ 0 ] = 8; //damage
        // Multipliers[ 1 ] = 3; //energy
        // //Multipliers[ 3 ] = 3; //mana
        // cout << " uses a special ability... " << endl;
        // break;

        // case 7: //use item
        // Multipliers[ 0 ] = 0; //damage
        // cout << " uses an item... " << endl;
        // break;

        // case 8: //escape
        // Multipliers[ 0 ] = 0; //damage
        // Multipliers[ 1 ] = 2; //energy
        // Multipliers[ 3 ] = 0; //defense
        // cout << " attempts to escape..." << endl; 
        // break;

        default :
        Multipliers[ 0 ] = 0; //damage
        Multipliers[ 1 ] = 0; //energy
        cout << " does nothing... " << endl;
        break;

    }

    //switch ( MagicType ) {}

    //Set AppliedStats
    if ( RelevantCharacter->getCharacterWeaponCount() < 2 )//If only one weapon || does this actually matter?(requires experimenting)
    {
        //(main weapon stat) * Player Multiplier * Game speed multiplier (to speed things up)
        AppliedStats.push_back( ( RelevantCharacter->getCharacterWeapon( 0 )->Damage ) * Multipliers[ 0 ] * GameSpeed ); // damage
        AppliedStats.push_back( ( RelevantCharacter->getCharacterWeapon( 0 )->Weight ) * Multipliers[ 1 ] * GameSpeed ); // energy
        AppliedStats.push_back( ( RelevantCharacter->getCharacterWeapon( 0 )->Defense ) * Multipliers[ 2 ] * GameSpeed ); // defense
    } 
    else //assume has at least a single weapon
    {
        //(main weapon stat + offhand weapon stat) * Player Multiplier * Game speed multiplier (to speed things up)
        AppliedStats.push_back( ( RelevantCharacter->getCharacterWeapon( 0 )->Damage + RelevantCharacter->getCharacterWeapon( 1 )->Damage ) * Multipliers[ 0 ] * GameSpeed ); // damage
        AppliedStats.push_back( ( RelevantCharacter->getCharacterWeapon( 0 )->Weight + RelevantCharacter->getCharacterWeapon( 1 )->Weight ) * Multipliers[ 1 ] * GameSpeed ); // energy
        AppliedStats.push_back( ( RelevantCharacter->getCharacterWeapon( 0 )->Defense + RelevantCharacter->getCharacterWeapon( 1 )->Defense ) * Multipliers[ 2 ] * GameSpeed ); // defense
    }

    return AppliedStats;

};

map<int,Character *> CombatInstance::SpawnEnemies( int Difficulty ) // Has to be map cause it starts from 1 not 0
{

    //INITIALIZE ENEMIES ACCORDING TO DIFFICULTY || future proofed
    map<int,Character *> SpawnedEnemies;

    //SPAWN WEAPONS || TODO: move this to a library map in session class
    Equipment *Sword = new Equipment( "Sword " , 4 , 2 , 1 ); 
    Equipment *Shield = new Equipment( "Shield" , 0 , 2 , 2 );
    Equipment *Dagger = new Equipment( "Dagger" , 2 , 1 , 0 );

    int EnemySeed1 = rand() % 10;
    int EnemySpawnAmount;

    if( EnemySeed1 > 5 ) { EnemySpawnAmount = 1; } // 40% chance of 1 enemy
    else if ( EnemySeed1 < 3) { EnemySpawnAmount = 2; } // 30% chance of 2 enemies
    else { EnemySpawnAmount = 3; } // 30% of 3 enemies

    for ( int EnemyCount = 1 ; EnemyCount <= EnemySpawnAmount ; EnemyCount++ )
    {   
        int EnemySeed2 = rand() % 10;

        //SPAWN ENEMY
        Character *Enemy = new Character;

        //TODO: generate weapons according to difficulty
        //ADD WEAPONS TO INVENTORY
        Enemy->addCharacterWeapon( Sword );
        //ADD offhand weapon randomly
        if( EnemySeed2 < 4 ) { Enemy->addCharacterWeapon( Shield ); } // 40% of shield offhand
        else if ( EnemySeed2 > 5 ) { Enemy->addCharacterWeapon( Dagger ); } //40% of dagger offhand
        else { Enemy->addCharacterWeapon( Sword ); } //20% dual wield swords

        //SET STATS according to DIFFICULTY
        int EnemyHealth = ( Difficulty * 10 ) + 50;
        int EnemyEnergy = ( Difficulty * 10 ) + 50;

        Enemy->setCharacterStats( EnemyHealth , EnemyEnergy );

        //ADD TO ENEMY LIST
        SpawnedEnemies[ EnemyCount ] = Enemy;

    }

    return SpawnedEnemies;

};

bool CombatInstance::PlayLevel( Character *Player, map<int,Character *> EnemyList )
{
    
    GameSpeed = 1;//i just put it here because of warning

    //----------------------------------------------------------------------------------------------------------
    //                                          - -------------- -
    //                                         - MAIN COMBAT LOOP -
    //                                          - -------------- -
    //----------------------------------------------------------------------------------------------------------
    
    //DISPLAY LEVL START MESSAGE
    cout 
        << endl 
        << "Combat Started : Difficulty : " << InstanceDifficulty << endl 
        << endl
    ;

    //INITILIAZE LIFE STATES
    bool bPlayerAlive = true;
    bool bAnyEnemiesAlive = true;
    map<int,bool> bEnemyAlive;

    //SET all ENEMIES as ALIVE
    for( int EnemyCount = 1 ; EnemyCount <= EnemyList.size() ;  EnemyCount++ )
    { bEnemyAlive[ EnemyCount ] = true; }


    int Turn = 0;

    //LOOP WHILE any ENEMIES are ALIVE
    while( bAnyEnemiesAlive )
    {   
        Turn++;
        //DISPLAY
        cout << endl << endl << " Turn " << Turn << endl << endl;
        Display( Player , EnemyList );

        //----------------------------------------------------------------------------------------------------------
        //  PLAYER MOVE:
        //----------------------------------------------------------------------------------------------------------

        vector<int> PlayerInputAndTarget = getValidMoveAndTarget( Player , bEnemyAlive );

        cout << endl << endl << endl << endl << endl;

        int PlayerInput = PlayerInputAndTarget[ 0 ];
        int EnemyTargeted = PlayerInputAndTarget[ 1 ];// EnemyTarget = 0 for non target moves ( such as area attacks ) || TODO: implement EnemyTargeted

        //Set Player Move Stats
        vector<int> PlayerStats = getMoveStats( Player , PlayerInput );

        int PlayerDamage = PlayerStats[ 0 ];
        int PlayerEnergyUse = PlayerStats[ 1 ];
        int PlayerDefense = PlayerStats[ 2 ];
        int PlayerManaUse = PlayerStats[ 3 ]; //currently unused

        //----------------------------------------------------------------------------------------------------------
        //  ENEMY MOVES:
        //----------------------------------------------------------------------------------------------------------

        map<int,int> EnemyDamage;
        map<int,int> EnemyEnergyUsed;
        map<int,int> EnemyDefense;
        map<int,int> EnemyManaUsed;

        for( int EnemyCount = 1; EnemyCount <= EnemyList.size() ; EnemyCount++ )
        {
            
            if ( bEnemyAlive[ EnemyCount ] ) 
            { 
                int EnemyMove = getEnemyMove();

                vector<int> EnemyStats = getMoveStats( EnemyList[ EnemyCount ] , EnemyMove );

                EnemyDamage[ EnemyCount ] = EnemyStats[ 0 ];
                EnemyEnergyUsed[ EnemyCount ] = EnemyStats[ 1 ];
                EnemyDefense[ EnemyCount ] = EnemyStats[ 2 ];
                EnemyManaUsed[ EnemyCount ] = EnemyStats[ 3 ];
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

        //Subtract Player Defense from Enemy attacks
        for( int EnemyCount2 = 1 ; EnemyCount2 <= EnemyList.size() ; EnemyCount2++ ) //has to be have a 2 cause of weirdness
        { 
            EnemyDamage[ EnemyCount2 ] -= PlayerDefense; 
            if ( EnemyDamage[ EnemyCount2 ] < 0 ) { EnemyDamage[ EnemyCount2 ] = 0; }
        
            //Apply damage to player first (if player dies then theres no reason to keep going) bPlayerAlive || If enemy has energy
            //If Enemy has enough energy to move then...
            if ( EnemyList[ EnemyCount2 ]->getCharacterEnergy() > EnemyEnergyUsed[ EnemyCount2 ] )
            {
                //...use enemy's energy...
                EnemyList[ EnemyCount2 ]->setUsedEnergy( EnemyEnergyUsed[ EnemyCount2 ] ) ;
                //and Damage player
                cout << "Enemy " << EnemyCount2 << " does ";
                bPlayerAlive = Player->setDamageToCharacter( EnemyDamage[ EnemyCount2 ] ) ;
                cout << " to you..." << endl;
            }
            else { cout << "Enemy " << EnemyCount2 << " is too tired..." << endl; }

            //If Player is dead return false ( END GAME )
            if( !bPlayerAlive ) 
            { 
                cout << "...You died" << endl;
                return false; 
            }
            
        }

        //Subtract Enemy Defense from Player attack
        PlayerDamage -= EnemyDefense[ EnemyTargeted ];
        if ( PlayerDamage < 0 ) { PlayerDamage = 0; }
            
        //Apply damage to targeted Enemy || bEnemyAlive[ EnemyTargeted ] || EnemyTargeted = 1; (for now)
        if( Player->getCharacterEnergy() > PlayerEnergyUse )
        {
            Player->setUsedEnergy( PlayerEnergyUse );
            cout << "You do ";
            bEnemyAlive[ EnemyTargeted ] = EnemyList[ EnemyTargeted ]->setDamageToCharacter( PlayerDamage );
            cout << " to Enemy " << EnemyTargeted << "..." << endl;
            if (!bEnemyAlive[ EnemyTargeted ]) { cout << "The Target died..." << endl; }
        }
        else { cout << "You are to tired..." << endl; }

        bool bEnemyCheck = false;
        int EnemyCount3 = 1;
        //while bEnemyCheck = false or EnemyCount <= EnemyList.size() ||  bEnemyCheck = bEnemyAlive[ EnemyCount ];
        while( bEnemyCheck == false && EnemyCount3 <= EnemyList.size() )
        {
            bEnemyCheck = bEnemyAlive[ EnemyCount3 ];//will be false until a live enemy is found
            EnemyCount3++;
        }
        bAnyEnemiesAlive = bEnemyCheck;

        //TODO: add stat recovery and implement max value for stat
        Player->setRecoveredStats();

        for ( int EnemyCount4 = 1 ; EnemyCount4 <= EnemyList.size() ; EnemyCount4++ ) 
        { EnemyList[ EnemyCount4 ]->setRecoveredStats(); }

    }

    cout << "all enemies are dead" << endl;

    return true;

};
