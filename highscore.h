#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ncurses.h>
#include <time.h>

#define NUMHS 10

int hs_show_highscore(int punkte, char* sPunkte, int level, char* sLevel, char *filename);
int hs_load_highscore(char *filename, char* sPunkte, char* sLevel);
int hs_save_highscore(int punkte, int level, char *name, char *filename);
void hs_highscore_sort(char *filename);
void hs_highscore_init(char *filename);

#endif //HIGHSCORE_H
