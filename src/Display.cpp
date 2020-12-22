#include <iostream>
#include <string>
#include <map>

#include "Character.hpp"
#include "Display.hpp"

using namespace std;


void Display::DisplayScreen() 
{
    
    cout
        << endl
        << endl
        << endl
        << endl
        << endl
        << "=================================================================================================================================================" << endl
        << "| =  _______________  =  _______________________________________________________________________________________________  =  _______________  = |" << endl
    ;
    for ( int DisplayCount = 0 ; DisplayCount < 34 ; DisplayCount++ )
    {
        cout << LeftHandBar[ DisplayCount ] << CombatDisplay[ DisplayCount ] << RightHandBar[ DisplayCount ] << endl;
    }
    cout
        << "||_____________________| = |_________________________________________________________________________________________| = |_____________________||" << endl
        << "=================================================================================================================================================" << endl
    ;
    for ( int DisplayCount2 = 0 ; DisplayCount2 < 17 ; DisplayCount2++ )
    {
        cout << StreamBar[ DisplayCount2 ] << MidColumn[ DisplayCount2 ] << NumberPad[ DisplayCount2 ] << endl;
    }
    cout
        << "||    _____________________________________    ||   ________________   ||    ______________    ||    ______________    ||                      ||" << endl
        << "=================================================================================================================================================" << endl
    ;

    // string unused;
    // getline( cin , unused );

}

void Display::setPlayerDisplay( Character *PassedPlayer ) { Player = PassedPlayer; }
void Display::setEnemiesDisplay( map<int,Character *> PassedEnemyList ) { EnemyList = PassedEnemyList; }

string Display::getStatBar( vector<int> Stat )
{

    if( Stat[ 0 ] == 0 ) { return "[[]===========]"; }
    string StatBar;
    int StatMultiple = Stat[ 2 ] / 10;
    int StatBarPlace = Stat[ 0 ] / StatMultiple;
    switch ( StatBarPlace )
    {
        case 0: StatBar = "[=[]==========]";
        break;
        case 1: StatBar = "[==[]=========]";
        break;
        case 2: StatBar = "[===[]========]";
        break;
        case 3: StatBar = "[====[]=======]";
        break;
        case 4: StatBar = "[=====[]======]";
        break;
        case 5: StatBar = "[======[]=====]";
        break;
        case 6: StatBar = "[=======[]====]";
        break;
        case 7: StatBar = "[========[]===]";
        break;
        case 8: StatBar = "[=========[]==]";
        break;
        case 9: StatBar = "[==========[]=]";
        break;
        case 10: StatBar = "[===========[]]";
        break;
    }

    return StatBar;
}

void Display::setMagicColumn( int Magic )
{
    MidColumn[ 0 ] = "||______________________" ;
    MidColumn[ 1 ] = "||                      " ;
    MidColumn[ 2 ] = "||   __==--====--==__   " ;
    MidColumn[ 3 ] = "||       0. MENU        " ;
    MidColumn[ 4 ] = "||    -=-=-____-=-=-    " ;
    MidColumn[ 5 ] = "||                      " ;
    MidColumn[ 6 ] = "||======================" ;
    MidColumn[ 7 ] = "||  _-==  MAGIC : ==-_  " ;
    MidColumn[ 8 ] = "||                      " ;


    switch ( Magic )
    {
        case 1:
        MidColumn[ 9 ] =  "|| >> FIRE --------- << ";
        MidColumn[ 10 ] = "||    ICE               ";
        MidColumn[ 11 ] = "||    NATURE            ";
        MidColumn[ 12 ] = "||    LIFE              ";
        MidColumn[ 13 ] = "||    HOLY              ";
        MidColumn[ 14 ] = "||    ILLUSION          ";
        MidColumn[ 15 ] = "||    RADIANT           ";
        break;
        
        case 2:
        MidColumn[ 9 ] =  "||    FIRE              ";
        MidColumn[ 10 ] = "|| >> ICE ---------- << ";
        MidColumn[ 11 ] = "||    NATURE            ";
        MidColumn[ 12 ] = "||    LIFE              ";
        MidColumn[ 13 ] = "||    HOLY              ";
        MidColumn[ 14 ] = "||    ILLUSION          ";
        MidColumn[ 15 ] = "||    RADIANT           ";
        break;

        case 3:
        MidColumn[ 9 ] =  "||    FIRE              ";
        MidColumn[ 10 ] = "||    ICE               ";
        MidColumn[ 11 ] = "|| >> NATURE ------- << ";
        MidColumn[ 12 ] = "||    LIFE              ";
        MidColumn[ 13 ] = "||    HOLY              ";
        MidColumn[ 14 ] = "||    ILLUSION          ";
        MidColumn[ 15 ] = "||    RADIANT           ";
        break;

        case 4:
        MidColumn[ 9 ] =  "||    FIRE              ";
        MidColumn[ 10 ] = "||    ICE               ";
        MidColumn[ 11 ] = "||    NATURE            ";
        MidColumn[ 12 ] = "|| >> LIFE --------- << ";
        MidColumn[ 13 ] = "||    HOLY              ";
        MidColumn[ 14 ] = "||    ILLUSION          ";
        MidColumn[ 15 ] = "||    RADIANT           ";
        break;

        case 5:
        MidColumn[ 9 ] =  "||    FIRE              ";
        MidColumn[ 10 ] = "||    ICE               ";
        MidColumn[ 11 ] = "||    NATURE            ";
        MidColumn[ 12 ] = "||    LIFE              ";
        MidColumn[ 13 ] = "|| >> HOLY --------- << ";
        MidColumn[ 14 ] = "||    ILLUSION          ";
        MidColumn[ 15 ] = "||    RADIANT           ";
        break;

        case 6:
        MidColumn[ 9 ] =  "||    FIRE              ";
        MidColumn[ 10 ] = "||    ICE               ";
        MidColumn[ 11 ] = "||    NATURE            ";
        MidColumn[ 12 ] = "||    LIFE              ";
        MidColumn[ 13 ] = "||    HOLY              ";
        MidColumn[ 14 ] = "|| >> ILLUSION ----- << ";
        MidColumn[ 15 ] = "||    RADIANT           ";
        break;

        case 7:
        MidColumn[ 9 ] =  "||    FIRE              ";
        MidColumn[ 10 ] = "||    ICE               ";
        MidColumn[ 11 ] = "||    NATURE            ";
        MidColumn[ 12 ] = "||    LIFE              ";
        MidColumn[ 13 ] = "||    HOLY              ";
        MidColumn[ 14 ] = "||    ILLUSION          ";
        MidColumn[ 15 ] = "|| >> RADIANT ------ << ";
        break;
    }

    MidColumn[ 16 ] = "||                      " ;

}

void Display::setRightHandBar() 
{
    int EnemyCount = 1;
    
    RightHandBar[ 0 ] =  "| __|   -=--_--=-   |__ |";
    RightHandBar[ 1 ] =  "||                     ||";

    while( EnemyCount <= EnemyList.size() )
    {
        RightHandBar[ 0 + ( 2 * EnemyCount ) ] =  "||   ENEMY " + to_string( EnemyCount ) + " :         ||";
        RightHandBar[ 1 + ( 2 * EnemyCount ) ] =  "||   " + getStatBar( EnemyList[ EnemyCount ]->CharacterHealth ) + "   ||";
        EnemyCount++;
    }
    while ( EnemyCount <= 4 )
    {
        RightHandBar[ 0 + ( 2 * EnemyCount ) ] = "||                     ||"; 
        RightHandBar[ 1 + ( 2 * EnemyCount ) ] = "||                     ||";
        EnemyCount++; 
    }
   

    RightHandBar[ 10 ] = "||   __==--===--==__   ||";
    RightHandBar[ 11 ] = "||_____________________||";
    RightHandBar[ 12 ] = "||  _________________  ||";
    RightHandBar[ 13 ] = "|| | MAIN HAND:      | ||";

    for( int MainCount = 0 ; MainCount < 8 ; MainCount++ )
    { RightHandBar[ 14 + MainCount ] = "|| |" + Player->getCharacterWeapon( 0 )->Image[ MainCount ] + "| ||"; }

    RightHandBar[ 22 ] = "|| |_________________| ||" ;
    RightHandBar[ 23 ] = "||  _________________  ||";
    RightHandBar[ 24 ] = "|| | OFF HAND :      | ||";

    for( int OffCount = 0 ; OffCount < 8 ; OffCount++ )
    { RightHandBar[ 25 + OffCount ] = "|| |" + Player->getCharacterWeapon( 1 )->Image[ OffCount ] + "| ||"; }

    RightHandBar[ 33 ] = "|| |_________________| ||" ;

}

void Display::setLeftHandBar()
{
    string Health[ 3 ];
    string Energy[ 3 ];
    string Mana[ 3 ];
    string Focus[ 3 ];

    for( int StatCount = 0 ; StatCount < 3 ; StatCount++ )
    {

        Health[ StatCount ] = to_string( Player->CharacterHealth[ StatCount ] );
        while( Health[ StatCount ].length() < 3  ) { Health[ StatCount ] += " "; }

        Energy[ StatCount ] = to_string( Player->CharacterEnergy[ StatCount ] );
        while( Energy[ StatCount ].length() < 3  ) { Energy[ StatCount ] += " "; }

        Mana[ StatCount ] = to_string( Player->CharacterMana[ StatCount ] );
        while( Mana[ StatCount ].length() < 3  ) { Mana[ StatCount ] += " "; }

        Focus[ StatCount ] = to_string( Player->CharacterFocus[ StatCount ] );
        while( Focus[ StatCount ].length() < 3  ) { Focus[ StatCount ] += " "; }

    }

    string PlayerItemImage[ 8 ] = 
    { 
        "       __        " , 
        "      [__]       " , 
        "     {_  _}      " , 
        "     _|  |_      " , 
        "    /-____-\\     " ,
        "   | //     |    " , 
        "   | HEALTH |    " ,
        "    -______-     " , 
    };

    LeftHandBar[ 0 ] =  "| __|      -=-      |__ |";
    LeftHandBar[ 1 ] =  "|| | HEALTH :        | ||";
    LeftHandBar[ 2 ] =  "|| | " + Health[ 0 ] + " / " + Health[ 1 ] + " / " + Health[ 2 ] + " | ||";
    LeftHandBar[ 3 ] =  "|| | " + getStatBar( Player->CharacterHealth ) + " | ||";
    LeftHandBar[ 4 ] =  "||                     ||";
    LeftHandBar[ 5 ] =  "||   --==__-=-__==--   ||";
    LeftHandBar[ 6 ] =  "||                     ||";
    LeftHandBar[ 7 ] =  "|| | ENERGY :        | ||";
    LeftHandBar[ 8 ] =  "|| | " + Energy[ 0 ] + " / " + Energy[ 1 ] + " / " + Energy[ 2 ] + " | ||";
    LeftHandBar[ 9 ] =  "|| | " + getStatBar( Player->CharacterEnergy ) + " | ||";
    LeftHandBar[ 10 ] = "||                     ||";
    LeftHandBar[ 11 ] = "||       __-=-__       ||";
    LeftHandBar[ 12 ] = "||                     ||";
    LeftHandBar[ 13 ] = "|| | MANA :          | ||";
    LeftHandBar[ 14 ] = "|| | " + Mana[ 0 ] + " / " + Mana[ 1 ] + " / " + Mana[ 2 ] + " | ||";
    LeftHandBar[ 15 ] = "|| | " + getStatBar( Player->CharacterMana ) + " | ||";
    LeftHandBar[ 16 ] = "||                     ||";
    LeftHandBar[ 17 ] = "||  -==-==-___-==-==-  ||";
    LeftHandBar[ 18 ] = "||                     ||";
    LeftHandBar[ 19 ] = "|| | FOCUS :         | ||";
    LeftHandBar[ 20 ] = "|| | " + Focus[ 0 ] + " / " + Focus[ 1 ] + " / " + Focus[ 2 ] + " | ||";
    LeftHandBar[ 21 ] = "|| | " + getStatBar( Player->CharacterFocus ) + " | ||";
    LeftHandBar[ 22 ] = "||_____________________||";
    LeftHandBar[ 23 ] = "||  _________________  ||";
    LeftHandBar[ 24 ] = "|| | ITEM :          | ||";
    for( int ItemCount = 0 ; ItemCount < 8 ; ItemCount++ )
    { LeftHandBar[ 25 + ItemCount ] = "|| |" + PlayerItemImage[ ItemCount ] + "| ||"; }
    LeftHandBar[ 33 ] = "|| |_________________| ||";

}

void Display::setCombatScreen() // TODO: Make a display
{
    for( int CombatCount = 0 ; CombatCount < 34 ; CombatCount++ )
    {
        CombatDisplay[ CombatCount ] = "           |           |           |           |           |           |           |           " ;
    }
}

void Display::addLineToStream( string NewLine = "                                          " )
{
    while( Stream.size() <  11) { Stream.push_back( "                                          ") ; }
    Stream[ 0 ] = Stream[ 1 ];
    Stream[ 1 ] = Stream[ 2 ];
    Stream[ 2 ] = Stream[ 3 ];
    Stream[ 3 ] = Stream[ 4 ];
    Stream[ 4 ] = Stream[ 5 ];
    Stream[ 5 ] = Stream[ 6 ];
    Stream[ 6 ] = Stream[ 7 ];
    Stream[ 7 ] = Stream[ 8 ];
    Stream[ 8 ] = Stream[ 9 ];
    Stream[ 9 ] = Stream[ 10 ];
    while( NewLine.length() < 42 ) { NewLine += " "; }
    Stream[ 10 ] = NewLine;

    setStreamBar();

}

void Display::setDisplayMove( int PlayerInput ) 
{ 
    switch( PlayerInput )
    {
        case 1 :
            Move = "- LIGHT ATTACK";
        break;
        case 2 :
            Move = "- HEAVY ATTACK";
        break;
        case 3 :
            Move = "- BLOCK       ";
        break;
        case 4 :
            Move = "- LIGHT MAGIC ";
        break;
        case 5 :
            Move = "- HEAVY MAGIC ";
        break;
        case 6 :
            Move = "- SPECIAL     ";
        break;
        case 7 :
            Move = "- USE ITEM    ";
        break;
        case 8 :
            Move = "- ESCAPE      ";
        break;

        Target = ">>       ";
    };

    setStreamBar();

}

void Display::setDisplayTarget( int PlayerInput ) 
{ 
    Target = "- ENEMY " + to_string( PlayerInput );

    setStreamBar();
}

void Display::resetDisplayMoveAndTarget() 
{  
    Move = ">>            ";
    Target = "         ";

    setStreamBar();
}


void Display::setStreamBar()
{   
    for( int StreamCount ; StreamCount < 11 ; StreamCount++ )
    { StreamBar[ StreamCount ] = "|| - " + Stream[ StreamCount ]; }

    StreamBar[ 11 ] = "||    _____________________________________    ";
    StreamBar[ 12 ] = "||=============================================";
    StreamBar[ 13 ] = "||  What will be your move ?                   ";
    StreamBar[ 14 ] = "||  " + Move + "                             ";
    StreamBar[ 15 ] = "||  Who are you going to target ?              ";
    StreamBar[ 16 ] = "||  " + Target + "                                  ";
}

