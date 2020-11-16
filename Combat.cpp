#include "Combat.hpp"


CombatInstance::CombatInstance( Character *GlobalPlayer , EquipmentLibrary *GlobalLibrary , Display *GlobalGameDisplay )
{ 
    Player = GlobalPlayer;
    Library = GlobalLibrary;
    GameDisplay = GlobalGameDisplay;
    GameDisplay->setPlayerDisplay( Player );
    GameDisplay->addLineToStream( "Combat Started" ); 
};

CombatInstance::~CombatInstance() { GameDisplay->addLineToStream( "Combat Ended" );   };


int CombatInstance::getEnemyMove() { return ( rand() % 3 ) + 1 ; }; //return random number between 1 and 3 for now || super advanced AI algorithm

vector<int> CombatInstance::getValidMoveAndTarget()
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
        GameDisplay->addLineToStream( "Enter your Move..." );  
        GameDisplay->DisplayScreen();

        //GET PLAYER INPUT  
        getline( cin , PlayerMove );
        try { PlayerMoveInt = stoi( PlayerMove ); } 
        catch ( ... ) 
        {
            PlayerMoveInt = 10;
        }

        //IF MENU DISPLAY MENU validMove = false
        switch (PlayerMoveInt)  
        {
            case 3:
            PlayerTargetInt = 1;
            case 1 : case 2: case 4: case 5: case 6: case 7: case 8:
                bMoveIsValid = true;
            break;

                // case 9:

                //     int Input1;
                //     int Input2;

                //     //DISPLAY INVENTORY
                //     for ( int WeaponCount = 0 ; WeaponCount < Player->getCharacterWeaponCount() ; WeaponCount++ ) 
                //     { cout << "Slot " << WeaponCount << " : " << Player->getCharacterWeapon( WeaponCount )->Name << endl; }

                //     //GET WEAPON BEING MOVED
                //     cout << "Choose a weapon to move..." << endl;
                //     getline( cin , PlayerMove );
                //     try { Input1 = stoi( PlayerMove ); }
                //     catch ( ... ) 
                //     {
                //         cout << "Invalid Input" << endl ;
                //         PlayerMoveInt = 10;
                //     }

                //     //CHOOSE SLOT
                //     cout << "Choose a weapon to switch with..." << endl;
                //     getline( cin , PlayerMove );
                //     try { Input2 = stoi( PlayerMove ); }
                //     catch ( ... ) 
                //     {
                //         cout << "Invalid Input" << endl ;
                //         PlayerMoveInt = 10;
                //     }

                //     //SWITCH WEAPONS
                //     cout << "CANT SWITCH WEAPONS YET!" << endl ;
                //     bMoveIsValid = false;

                // break;

            case 0:

                //DISPLAY IN GAME MENU 
                //GET MENU INPUT
                bMoveIsValid = false;

            break;

            default:
                GameDisplay->addLineToStream( "That is not valid move " );
                bMoveIsValid = false;
            break;
        }
        
    } while (!bMoveIsValid);

    GameDisplay->setDisplayMove( PlayerMoveInt );

    //CHOOSE VALID TARGET || TODO: make check to see if Enemy chosen exists and is alive
    while ( PlayerMoveInt != 3 && !bTargetIsValid )
    {
        GameDisplay->addLineToStream( "Enter your target..." );
        GameDisplay->DisplayScreen();

        getline( cin , PlayerTarget );
        try { PlayerTargetInt = stoi( PlayerTarget ); }
        catch ( ... ) 
        {
            PlayerTargetInt = 4;
        }

        if ( bEnemyAlive[ PlayerTargetInt ]) { bTargetIsValid = true; }
        else { GameDisplay->addLineToStream(  "That is not a valid target" ); }

    }

    GameDisplay->setDisplayTarget( PlayerTargetInt );
    GameDisplay->DisplayScreen();

    string unused;
    getline( cin , unused );

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
        streamLine +=  " makes a light attack";
        break;

        case 2 : //heavy attack
        Multipliers[ 0 ] = 2; //damage
        Multipliers[ 1 ] = 2; //energy
        Multipliers[ 2 ] = 0; //defense
        streamLine += " makes a heavy attack";
        break;

        case 3 : //block
        Multipliers[ 0 ] = 0; //damage
        Multipliers[ 2 ] = 2; //defense
        streamLine += " blocks";
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
        streamLine += " does nothing";
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

void CombatInstance::SpawnEnemies( int Difficulty) // Has to be map cause it starts from 1 not 0
{

    //INITIALIZE ENEMIES ACCORDING TO DIFFICULTY || future proofed
    map<int,Character *> SpawnedEnemies;

    int EnemySeed1 = rand() % 10;
    int EnemySpawnAmount;

    //DETERMINE ENEMY AMOUNT
    if( EnemySeed1 > 5 ) { EnemySpawnAmount = 2; } // 40% chance of 1 enemy
    else if ( EnemySeed1 < 3) { EnemySpawnAmount = 3; } // 30% chance of 2 enemies
    else { EnemySpawnAmount = 4; } // 30% of 3 enemies

    for ( int EnemyCount = 1 ; EnemyCount <= EnemySpawnAmount ; EnemyCount++ )
    {   

        int EnemySeed2 = rand() % 10;

        //SPAWN ENEMY
        Character *Enemy = new Character;

        //ADD WEAPONS TO INVENTORY
        Enemy->addCharacterWeapon( Library->Weapons[ "Sword" ] );

        //ADD offhand weapon randomly
        if( EnemySeed2 < 4 ) { Enemy->addCharacterWeapon( Library->Weapons[ "Shield" ] ); } // 40% of shield offhand
        else if ( EnemySeed2 > 5 ) { Enemy->addCharacterWeapon( Library->Weapons[ "Dagger" ] ); } //40% of dagger offhand
        else { Enemy->addCharacterWeapon( Library->Weapons[ "Sword" ] ); } //20% dual wield swords

        //SET STATS according to DIFFICULTY
        int EnemyHealth = ( Difficulty * 10 ) + 10;
        int EnemyEnergy = ( Difficulty * 10 ) + 10;
        int EnemyMana = ( Difficulty * 10 ) + 10;
        int EnemyFocus = ( Difficulty * 10 ) + 10;

        Enemy->setCharacterStats( EnemyHealth , EnemyEnergy , EnemyMana , EnemyFocus );

        //ADD TO ENEMY LIST
        SpawnedEnemies[ EnemyCount ] = Enemy;

    }

    EnemyList = SpawnedEnemies;

    GameDisplay->setEnemiesDisplay( EnemyList );

};

void CombatInstance::DeleteEnemies()
{
    int EnemyCount = EnemyList.size();
    while( !( EnemyCount == 0 ) ) 
    { 
        delete EnemyList[ EnemyCount ];
        EnemyCount--; 
    }

};

bool CombatInstance::PlayLevel()
{
    
    GameSpeed = 1;//i just put it here because of warning

    GameDisplay->setCombatScreen();

    //----------------------------------------------------------------------------------------------------------
    //                                          - -------------- -
    //                                         - MAIN COMBAT LOOP -
    //                                          - -------------- -
    //----------------------------------------------------------------------------------------------------------
    

    //INITILIAZE LIFE STATES
    bool bPlayerAlive = true;
    bool bAnyEnemiesAlive = true;
    //map<int,bool> bEnemyAlive;

    //SET all ENEMIES as ALIVE
    for( int EnemyCount = 1 ; EnemyCount <= EnemyList.size() ;  EnemyCount++ )
    { bEnemyAlive[ EnemyCount ] = true; }


    int Turn = 0;

    //LOOP WHILE any ENEMIES are ALIVE
    while( bAnyEnemiesAlive )
    {   
        Turn++;
        //DISPLAY
        cout<< " Turn " << Turn << endl;
        GameDisplay->resetDisplayMoveAndTarget();\
        GameDisplay->setLeftHandBar();
        GameDisplay->setRightHandBar();
        //GameDisplay->DisplayScreen();

        //----------------------------------------------------------------------------------------------------------
        //  PLAYER MOVE:
        //----------------------------------------------------------------------------------------------------------

        vector<int> PlayerInputAndTarget = getValidMoveAndTarget();

        int PlayerInput = PlayerInputAndTarget[ 0 ];
        int EnemyTargeted = PlayerInputAndTarget[ 1 ];// EnemyTarget = 0 for non target moves ( such as area attacks ) || TODO: implement EnemyTargeted

        //Set Player Move Stats
        streamLine =  "Player ";
        vector<int> PlayerStats = getMoveStats( Player , PlayerInput );

        GameDisplay->addLineToStream( streamLine );

        int PlayerDamage = PlayerStats[ 0 ];
        int PlayerEnergyUse = PlayerStats[ 1 ];
        int PlayerDefense = PlayerStats[ 2 ];
        int PlayerManaUse = PlayerStats[ 3 ];

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

                streamLine = "Enemy " + to_string( EnemyCount );
                vector<int> EnemyStats = getMoveStats( EnemyList[ EnemyCount ] , EnemyMove );

                GameDisplay->addLineToStream( streamLine );

                EnemyDamage[ EnemyCount ] = EnemyStats[ 0 ];
                EnemyEnergyUsed[ EnemyCount ] = EnemyStats[ 1 ];
                EnemyDefense[ EnemyCount ] = EnemyStats[ 2 ];
                EnemyManaUsed[ EnemyCount ] = EnemyStats[ 3 ];
            }

        }

        //GameDisplay->DisplayScreen();

        //----------------------------------------------------------------------------------------------------------
        //  APPLY MOVES: || TODO: label everthing properly when im not lazy ( or sick with covid-19 :D )
        //----------------------------------------------------------------------------------------------------------

        //Subtract Enemy Defense from Player attack
        PlayerDamage -= EnemyDefense[ EnemyTargeted ];
        if ( PlayerDamage < 0 ) { PlayerDamage = 0; }
            
        //CHECK if the PLAYER has enough ENERGY
        if( Player->getCharacterEnergy( 0 ) > PlayerEnergyUse )
        {
            //USE PLAYER ENERGY
            Player->setUsedEnergy( PlayerEnergyUse );
            //APPLY DAMAGE
            streamLine = "You do " + to_string( PlayerDamage ) + " to Enemy " + to_string( EnemyTargeted );
            bEnemyAlive[ EnemyTargeted ] = EnemyList[ EnemyTargeted ]->setDamageToCharacter( PlayerDamage );

            GameDisplay->addLineToStream( streamLine );

            //CHECK if ENEMY is ALIVE
            if (!bEnemyAlive[ EnemyTargeted ]) 
            { 
                GameDisplay->addLineToStream( "The Target died" );
                EnemyList[ EnemyTargeted ]->setCharacterStats( 0 , 0 , 0 , 0);
            }
        }
        else { GameDisplay->addLineToStream( "You are too tired" ); }

        //Subtract Player Defense from Enemy attacks
        for( int EnemyCount2 = 1 ; EnemyCount2 <= EnemyList.size() ; EnemyCount2++ ) //has to be have a 2 cause of weirdness
        { 

            if( bEnemyAlive[ EnemyCount2 ] )
            {
                EnemyDamage[ EnemyCount2 ] -= PlayerDefense; 
                if ( EnemyDamage[ EnemyCount2 ] < 0 ) { EnemyDamage[ EnemyCount2 ] = 0; }
            
                //CHECK that PLAYER has enough ENERGY
                if ( EnemyList[ EnemyCount2 ]->getCharacterEnergy( 0 ) > EnemyEnergyUsed[ EnemyCount2 ] )
                {
                    //...use enemy's energy...
                    EnemyList[ EnemyCount2 ]->setUsedEnergy( EnemyEnergyUsed[ EnemyCount2 ] ) ;
                    //and Damage player
                    streamLine =  "Enemy " + to_string( EnemyCount2 ) + " does " + to_string( EnemyDamage[ EnemyCount2 ] ) + " to you";
                    bPlayerAlive = Player->setDamageToCharacter( EnemyDamage[ EnemyCount2 ] ) ;

                }
                else { streamLine =  "Enemy " + to_string( EnemyCount2 ) + " is too tired"; }

                GameDisplay->addLineToStream( streamLine );

                //If Player is dead return false ( END GAME )
                if( !bPlayerAlive ) 
                { 
                    GameDisplay->addLineToStream(  "...You died" );
                    return false;
                }

            }
            
        }

        GameDisplay->setLeftHandBar();
        GameDisplay->setRightHandBar();
        //GameDisplay->DisplayScreen();

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
        { 
            if( bEnemyAlive[ EnemyCount4 ] )
            { EnemyList[ EnemyCount4 ]->setRecoveredStats();} 
        }

    }

    GameDisplay->addLineToStream( "all enemies are dead" );

    return true;

};
