#include <iostream>
#include <string>
#include <cstdlib>
#include <ncurses.h>
#include "GameSystem.h"

//using namespace std;

void initNcurses() {
    initscr();
    keypad(stdscr, TRUE);
    resize_term(400, 600);
    start_color();
    noecho();
    nonl();

    clear();
    refresh();
}

int main() {
    GameSystem gameSystem("level1.txt");

    initNcurses();

    gameSystem.playGame();
    endwin();

    return 0;
}

//mvprintw(...)
//mvprintch(...)
//getmaxyx(...)