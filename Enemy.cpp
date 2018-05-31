#include "Enemy.h"
#include <random>
#include <ctime>

using namespace std;

Enemy::Enemy(string name, char tile, int level, int attack, int defense, int health, int xp)
{
  _name = name;
  _tile = tile;
  _level = level;
  _attack = attack;
  _defense = defense;
  _health = health;
  _experienceValue = xp;
}

int
Enemy::attack()
{
  static default_random_engine randomEngine( time( NULL ));
  uniform_int_distribution <int> attackRoll( 0, _attack );

  return attackRoll( randomEngine );
}

int
Enemy::takeDamage(int attack)
{
  attack -= _defense;
  if (attack > 0) {
    _health -= attack;
    if (_health <= 0) {
      return _experienceValue;
    }
  }
  return 0;
}

void
Enemy::getPosition(int& x, int& y)
{
  x = _x;
  y = _y;
}

void
Enemy::setPosition(int x, int y)
{
  _x = x;
  _y = y;
}

char
Enemy::getMove(int playerX, int playerY)
{
  static default_random_engine randomEngine( time( NULL ));
  uniform_int_distribution <int> moveRoll( 0, 6 );

  int dist;
  int dx = _x - playerX;
  int dy = _y - playerY;
  int adx = abs( dx );
  int ady = abs( dy );

  dist = adx + ady;

  if (dist <= 5) {
    if (adx > ady) {
      if (dx > 0)
        return 'a';
      else
        return 'd';
    }
    else {
      if (dy > 0)
        return 'w';
      else
        return 's';
    }
  }

  int randomMove = moveRoll( randomEngine );
  switch (randomMove) {
    case 0:
      return 'a';
    case 1:
      return 'w';
    case 2:
      return 's';
    case 3:
      return 'd';
    default:
      return '.';
  }
}