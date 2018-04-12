#include "Level.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ncurses.h>

Level::Level() {}

void Level::load(string fileName, Player &player) {
    ifstream file;
    file.open(fileName);
    if (file.fail()) {
        perror(fileName.c_str());
        cin.ignore();
        cin.get();
        exit(1);
    }

    string line;

    while (getline(file, line)) {
        _levelData.push_back(line);
    }

    file.close();

    char tile;
    for (int i = 0; i < _levelData.size(); ++i) {
        for (int j = 0; j < _levelData[i].size(); ++j) {
            tile = _levelData[i][j];

            switch (tile) {
                case '@':
                    player.setPosition(j, i);
                    break;
                case 'S':
                    _enemies.push_back(Enemy("Snake", tile, 1, 15, 5, 2, 51));
                    _enemies.back().setPosition(j, i);
                    break;
                case 'g':
                    _enemies.push_back(Enemy("Goblin", tile, 2, 15, 10, 5, 250));
                    _enemies.back().setPosition(j, i);
                    break;
                case 'O':
                    _enemies.push_back(Enemy("Ogre", tile, 4, 40, 15, 80, 500));
                    _enemies.back().setPosition(j, i);
                    break;
                case 'D':
                    _enemies.push_back(Enemy("Dragon", tile, 100, 2000, 300, 90, 600));
                    _enemies.back().setPosition(j, i);
                    break;
                case 'B':
                    _enemies.push_back(Enemy("Bandit", tile, 3, 500, 40, 10, 250));
                    _enemies.back().setPosition(j, i);
                    break;
            }
        }
    }

}

void Level::print(Player &player) {
    clear();
    for (int i = 0; i < (_levelData.size() > 6 ? _levelData.size() : 6); ++i) {
        if (i < _levelData.size()) {
            mvprintw(i, 0, _levelData[i].c_str());
            refresh();
        }

        switch (i) {
            case 0:
                mvprintw(i, _levelData[i].length(), " Player info");
                refresh();
                break;
            case 1:
                mvprintw(i, _levelData[i].length(), " Level: %d", player.getLevel());
                refresh();
                break;
            case 2:
                mvprintw(i, _levelData[i].length(), " XP: %d", player.getExperience());
                refresh();
                break;
            case 3:
                mvprintw(i, _levelData[i].length(), " HP: %d", player.getHealth());
                refresh();
                break;
            case 4:
                mvprintw(i, _levelData[i].length(), " Attack: %d", player.getAttack());
                refresh();
                break;
            case 5:
                mvprintw(i, _levelData[i].length(), " Defense: %d", player.getDefense());
                refresh();
                break;
            default:;
        }
    }
//    printw("\n");
//    refresh();
}

void Level::movePlayer(char input, Player &player) {
    int playerX;
    int playerY;

    player.getPosition(playerX, playerY);

    switch (input) {
        case 'w':
        case 'W':
            processPlayerMove(player, playerX, playerY - 1);
            break;
        case 's':
        case 'S':
            processPlayerMove(player, playerX, playerY + 1);
            break;
        case 'a':
        case 'A':
            processPlayerMove(player, playerX - 1, playerY);
            break;
        case 'd':
        case 'D':
            processPlayerMove(player, playerX + 1, playerY);
            break;
        default:
            printw("INVALID INPUT!\n");
            cin.get();
            break;
    }

}

void Level::updateEnemies(Player &player) {
    int playerX;
    int playerY;
    int enemyX;
    int enemyY;
    char aiMove;

    player.getPosition(playerX, playerY);

    for (int i = 0; i < _enemies.size(); ++i) {
        aiMove = _enemies[i].getMove(playerX, playerY);

        _enemies[i].getPosition(enemyX, enemyY);

        switch (aiMove) {
            case 'w':
                processEnemyMove(player, i, enemyX, enemyY - 1);
                break;
            case 's':
                processEnemyMove(player, i, enemyX, enemyY + 1);
                break;
            case 'a':
                processEnemyMove(player, i, enemyX - 1, enemyY);
                break;
            case 'd':
                processEnemyMove(player, i, enemyX + 1, enemyY);
                break;
        }

    }
}

void Level::setTile(int x, int y, char tile) {
    _levelData[y][x] = tile;
}

void Level::processPlayerMove(Player &player, int targetX, int targetY) {
    int playerX;
    int playerY;

    player.getPosition(playerX, playerY);

    char moveTile = getTile(targetX, targetY);

    switch (moveTile) {
        case '.':
            player.setPosition(targetX, targetY);
            setTile(playerX, playerY, '.');
            setTile(targetX, targetY, '@');
            break;
        case '#':
            break;
        default:
            battleMonster(player, targetX, targetY);
            break;
    }
}

void Level::processEnemyMove(Player &player, int enemyIndex, int targetX, int targetY) {
    int playerX;
    int playerY;
    int enemyX;
    int enemyY;

    _enemies[enemyIndex].getPosition(enemyX, enemyY);
    player.getPosition(playerX, playerY);

    char moveTile = getTile(targetX, targetY);

    switch (moveTile) {
        case '.':
            _enemies[enemyIndex].setPosition(targetX, targetY);
            setTile(enemyX, enemyY, '.');
            setTile(targetX, targetY, _enemies[enemyIndex].getTile());
            break;
        case '@':
            battleMonster(player, enemyX, enemyY);
            break;
        default:
            break;
    }
}

void Level::battleMonster(Player &player, int targetX, int targetY) {
    int enemyX;
    int enemyY;
    int playerX;
    int playerY;
    int attackRoll;
    int attackResult;
    string enemyName;

    player.getPosition(playerX, playerY);
    for (int i = 0; i < _enemies.size(); ++i) {
        _enemies[i].getPosition(enemyX, enemyY);
        enemyName = _enemies[i].getName();
        if (targetX == enemyX && targetY == enemyY) {
            //battle
            attackRoll = player.attack();
            attackResult = _enemies[i].takeDamage(attackRoll);
            print(player);
            printw("\nPlayer attacked %s with a roll of %d.\n", enemyName.c_str(), attackRoll);
            refresh();

            if (attackResult != 0) {
                setTile(targetX, targetY, '.');
                print(player);
                printw("\nMonster died!\n");

                _enemies[i] = _enemies.back();
                _enemies.pop_back();
                i--;

                cin.get();
                player.addExperience(attackResult);
                return;
            }
            cin.get();

            attackRoll = _enemies[i].attack();
            attackResult = player.takeDamage(attackRoll);

            print(player);
            printw("\n%s attacked player with a roll of %d.\n", enemyName.c_str(), attackRoll);
            refresh();

            if (attackResult != 0) {
                setTile(playerX, playerY, 'x');
                print(player);
                printw("\nYou died!\n");
                refresh();
                cin.get();

                exit(0);
            }
            cin.get();

            return;
        }
    }
}