#pragma once

class Player
{
public:
  Player();

  void
  init(int level, int health, int attack, int defense, int experience);

  int
  attack();

  void
  addExperience(int xp);

  int
  takeDamage(int attack);

  //Getters
  void
  getPosition(int& x, int& y);

  int
  getLevel()
  { return _level; };

  int
  getHealth()
  { return _health; };

  int
  getAttack()
  { return _attack; };

  int
  getDefense()
  { return _defense; };

  int
  getExperience()
  { return _experience; };

  //Setters
  void
  setPosition(int x, int y);

private:
  //Properties
  int _level;
  int _health;
  int _attack;
  int _defense;
  int _experience;

  //Position
  int _x;
  int _y;
};