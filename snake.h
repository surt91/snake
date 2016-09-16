#ifndef SNAKE_H
#define SNAKE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ncurses.h>

#include "highscore.h"

// Level definiert in Schritte pro Sekunde
#define LEVEL1 1
#define LEVEL2 2
#define LEVEL3 3
#define LEVEL4 4
#define LEVEL5 5
#define LEVEL6 10
#define LEVEL7 20
#define LEVEL8 30
#define LEVEL9 60

#define SNAKE_CONFIG_FILENAME "snake_config_save.dat"
#define SNAKE_HIGHSCORE_FILENAME "snake_highscore_save.dat"

struct snake_map
{
    int x,y;
    int *schlange;
    int kopf[2];
    int futter[2];
    int level;
    int runde, punkte, length;
    int richtung, richtung_alt;
};

void snake_menu();

void snake(int schwierigkeit, int torus, int theme);
void snake_draw(struct snake_map *map, int theme);
int snake_set_status(int x, int y, struct snake_map *map, char state);
int snake_get_status(int x, int y, struct snake_map *map);
void snake_random_pos(int *pos, struct snake_map *map);
void snake_koerper(struct snake_map *map);
int snake_dead_or_eating(struct snake_map *map);
int snake_rand(struct snake_map *map);
void snake_torus(struct snake_map *map);
void snake_verloren(int punkte);
void snake_steuerung(struct snake_map *map);
void snake_buchstabiere(int x, int y, const char *wort);
void snake_help();
void snake_credits();

int snake_load_config(int *level, int *torus, int *theme);
int snake_save_config(int level, int torus, int theme);

#endif //SNAKE_H
