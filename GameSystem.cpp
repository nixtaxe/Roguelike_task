#include <cstdlib>
#include <ncurses.h>
#include "GameSystem.h"

GameSystem::GameSystem(string levelFile)
{

  _player.init( 1, 100, 10, 10, 0 );

  _level.load( levelFile, _player );

  cin.get();
}

void
GameSystem::playGame()
{
  bool isDone = false;

  //TODO add start page

  while (isDone != true) {
    clear();
    _level.print( _player );
    playerMove();
    _level.updateEnemies( _player );
    refresh();
  }
}

void
GameSystem::playerMove()
{
  char input;
  //printf("Enter a move command (w/s/a/d): ");
  input = getch();
  //TODO add input check

  _level.movePlayer( input, _player );
}

