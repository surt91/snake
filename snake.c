/***
 *  Snake
 *
 *  02.10.2011
 *
 *  License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.
 *  This is free software: you are free to change and redistribute it."
 *  There is NO WARRANTY, to the extent permitted by law.
 *
 *  Hendrik Schawe <hendrik.schawe@gmail.com>
 *
 ***/

#include "snake.h"

static const char *titel = "\
 ____  _   _    _    _  _______ \n\
/ ___|| \\ | |  / \\  | |/ / ____|\n\
\\___ \\|  \\| | / _ \\ | ' /|  _|  \n\
 ___) | |\\  |/ ___ \\| . \\| |___ \n\
|____/|_| \\_/_/   \\_\\_|\\_\\_____|\n\
                                 \n";
static const char *optionen = "\
  ___        _   _                        \n\
 / _ \\ _ __ | |_(_) ___  _ __   ___ _ __  \n\
| | | | '_ \\| __| |/ _ \\| '_ \\ / _ \\ '_ \\ \n\
| |_| | |_) | |_| | (_) | | | |  __/ | | |\n\
 \\___/| .__/ \\__|_|\\___/|_| |_|\\___|_| |_|\n\
      |_|                                 \n";
static const char *verloren = "\
__     __        _                      _ \n\
\\ \\   / /__ _ __| | ___  _ __ ___ _ __ | |\n\
 \\ \\ / / _ \\ '__| |/ _ \\| '__/ _ \\ '_ \\| |\n\
  \\ V /  __/ |  | | (_) | | |  __/ | | |_|\n\
   \\_/ \\___|_|  |_|\\___/|_|  \\___|_| |_(_)\n\
                                          \n";
static const char *hilfe = "\
 _   _ _ _  __      \n\
| | | (_) |/ _| ___ \n\
| |_| | | | |_ / _ \\\n\
|  _  | | |  _|  __/\n\
|_| |_|_|_|_|  \\___|\n\
                    \n";
static const char *credits = "\
  ____              _ _ _       \n\
 / ___|_ __ ___  __| (_) |_ ___ \n\
| |   | '__/ _ \\/ _` | | __/ __|\n\
| |___| | |  __/ (_| | | |_\\__ \\\n\
 \\____|_|  \\___|\\__,_|_|\\__|___/\n\
                                \n";
static const char *pause = "\
 ____                                      \n\
|  _ \\ __ _ _   _ ___  ___                 \n\
| |_) / _` | | | / __|/ _ \\                \n\
|  __/ (_| | |_| \\__ \\  __/                \n\
|_|   \\__,_|\\__,_|___/\\___|                \n\
                                           \n";
static const char *mampf = "\
 __  __                        __ _ \n\
|  \\/  | __ _ _ __ ___  _ __  / _| |\n\
| |\\/| |/ _` | '_ ` _ \\| '_ \\| |_| |\n\
| |  | | (_| | | | | | | |_) |  _|_|\n\
|_|  |_|\\__,_|_| |_| |_| .__/|_| (_)\n\
                       |_|          \n";


static const char snake_themes[3][4] = {{'+','0','X',}, {'o','O','X'}, {'*','X','@'}};
static const int geschw[9] =
{LEVEL1, LEVEL2, LEVEL3, LEVEL4, LEVEL5, LEVEL6, LEVEL7, LEVEL8, LEVEL9};

void snake_menu()
{
    int exit = 0, m, level = 3, torus = 0, theme = 0, i;
    char k;
    initscr();
    raw();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    snake_load_config(&level, &torus, &theme);
    hs_highscore_init(SNAKE_HIGHSCORE_FILENAME);
    while(!exit)
    {
        m=0;
        erase();
        snake_buchstabiere(0, 0, titel);
        addch('\n' | A_UNDERLINE);
        addch('S' | A_UNDERLINE);
        printw("piele Snake:  1\n");
        addch('E' | A_UNDERLINE);
        printw("instellungen: 2\n");
        addch('H' | A_UNDERLINE);
        printw("ighscore:     3\n");
        printw("Hilfe:         4\n");
        addch('C' | A_UNDERLINE);
        printw("redits:       5\n");
        addch('Q' | A_UNDERLINE);
        printw("uit Snake:    6\n");
        refresh();
        m=getch();
        switch(m)
        {
            case '2':
            case 'E':
            case 'e':
                erase();
                snake_buchstabiere(0, 0, optionen);
                printw("Schwierigkeitsgrad zwischen 1 und 9 [3]\n");
                refresh();
                k = getch();
                level = k-48;
                if(level < 1 || level >9)
                    level = 3;
                printw("Spiele auf Level %d\n", level);

                printw("Torusförmiges Spielfeld y/n [y]\n");
                refresh();
                k = getch();
                torus = k == 'n' ? 0 : 1;
                if(torus)
                    printw("Spiele auf Torusförmigem Spielfeld\n");
                else
                    printw("Spiele auf begrenztem Spielfeld\n");

                printw("Wähle Theme [1]\n");
                for(i = 0;i<3;i++)
                    printw("%d: %s\n", i+1, snake_themes[i]);
                refresh();
                k = getch();
                theme = k-48;
                if(theme < 1 || theme >3)
                    theme = 1;
                printw("%d", theme);
                theme--;
                refresh();

                snake_save_config(level, torus, theme);
                break;

            case '1':
            case 'S':
            case 's':
                erase();
                snake(level, torus, theme);
                break;
            case 'H':
            case 'h':
            case '3':
                erase();
                hs_load_highscore(SNAKE_HIGHSCORE_FILENAME, "Punkte", "Laenge");
                getch();
                break;
            case '4':
                erase();
                snake_help();
                getch();
                break;
            case '5':
            case 'C':
            case 'c':
                erase();
                snake_credits();
                getch();
                break;
            case 'Q':
            case 'q':
            case '6':
                endwin();
                return;
                break;
        }
    }
}

void snake(int stufe, int torus, int theme)
{
    struct snake_map map;
    int status = 1, timer = 0;
    map.level = stufe;
    map.richtung = 's';
    map.runde = 0;
    map.punkte = 0;
    srand( (unsigned) time(NULL) ) ;

    map.x = 30;
    map.y = 15;
    map.length = 3;
    map.schlange = (int *) calloc(map.x * map.y, sizeof(int));

    snake_random_pos(map.kopf, &map);
    snake_random_pos(map.futter, &map);

    // Hauptspielschleife
    while(status)
    {
        map.runde++;
        timer++;
        snake_draw(&map, theme);
        refresh();
        snake_steuerung(&map);

        timeout(1000/geschw[map.level]);

        if(torus)
            snake_torus(&map);
        else
            status = snake_rand(&map);
        switch (snake_dead_or_eating(&map))
        {
            case 1:
                map.length++;
                snake_buchstabiere(map.x+5, 1, mampf);
                map.punkte += map.level;
                timer = 0;
                snake_random_pos(map.futter, &map);
                break;
            case 0:
                if(timer > 3)
                    erase();
                break;
            case 2:
                status = 0;
                mvprintw(3,map.x+5,"In den Schwanz gebissen.");
                break;
        }
        snake_koerper(&map);
        map.schlange[map.kopf[1] * map.x + map.kopf[0]] = 1;
    }
    free(map.schlange);
    timeout(5000);
    snake_verloren(map.punkte);
    timeout(-1);
    hs_show_highscore(map.punkte, "Punkte", map.length, "Länge", SNAKE_HIGHSCORE_FILENAME);
}

void snake_draw(struct snake_map *map, int theme)
{
    int i,j;
    mvprintw(map->y-3, map->x+4, "Level:  % 5d", map->level);
    mvprintw(map->y-1, map->x+4, "Runde:  % 5d", map->runde);
    mvprintw(map->y,   map->x+4, "Laenge: % 5d", map->length);
    mvprintw(map->y+1, map->x+4, "Punkte: % 5d", map->punkte);
    move(0,0);
    addch('+');
    for(i=0; i < map->x; i++)
        addch('-');
    addch('+');
    move(1,0);
    for(j=0; j < map->y; j++)
    {
        printw("|");
        for(i=0; i < map->x; i++)
        {
            if(map->kopf[0] == i && map->kopf[1] == j)
                addch(snake_themes[theme][1]);
            else if(snake_get_status(i, j, map))
                addch(snake_themes[theme][0]);
            else if(map->futter[0] == i && map->futter[1] == j)
                addch(snake_themes[theme][2]);
            else
                addch(' ');
        }
        addch('|');
        move(j+2,0);
    }
    addch('+');
    for(i=0; i < map->x; i++)
        addch('-');
    addch('+');
    return;
}

void snake_steuerung(struct snake_map *map)
{
    int tmp = 0;
    // Input Funktion
    do
    {
        map->richtung = getch();
        if(map->richtung == ERR)
            map->richtung = map->richtung_alt;
        switch (map->richtung)
        {
            case 'p':
            case 'P':
                timeout(-1);
                snake_buchstabiere(map->x+4, 1, pause);
                refresh();
                tmp=1;
                break;
            case 'w':
            case 'W':
            case KEY_UP:
                if (map->richtung_alt == 's')
                    tmp = 1;
                else
                {
                    map->richtung = 'w';
                    map->kopf[1]--;
                    tmp = 0;
                }
                break;
            case 'a':
            case 'A':
            case KEY_LEFT:
                if (map->richtung_alt == 'd')
                    tmp = 1;
                else
                {
                    map->richtung = 'a';
                    map->kopf[0]--;
                    tmp = 0;
                }
                break;
            case 's':
            case 'S':
            case KEY_DOWN:
                if (map->richtung_alt == 'w')
                    tmp = 1;
                else
                {
                    map->richtung = 's';
                    map->kopf[1]++;
                    tmp = 0;
                }
                break;
            case 'd':
            case 'D':
            case KEY_RIGHT:
                if (map->richtung_alt == 'a')
                    tmp = 1;
                else
                {
                    map->richtung = 'd';
                    map->kopf[0]++;
                    tmp = 0;
                }
                break;
            case '+':
                if(map->level < 9)
                    map->level++;
                tmp = 1;
                break;
            case '-':
                if(map->level > 1)
                    map->level--;
                tmp = 1;
                break;
            default:
                tmp = 1;
                break;
        }
    } while(tmp);
    map->richtung_alt = map->richtung;
    return;
}

void snake_verloren(int punkte)
{
    erase();
    snake_buchstabiere(0, 0, verloren);
    printw("Du hast -= %d =- Punkte erzielt", punkte);
    refresh();
    getch();
    return;
}
int snake_set_status(int x, int y, struct snake_map *map, char state)
{
    map->schlange[y * map->x + x] = state;
    return 0;
}
int snake_get_status(int x, int y, struct snake_map *map)
{
    return map->schlange[y * map->x + x];
}

void snake_random_pos(int *pos, struct snake_map *map)
{
    int cordX, cordY;
    do
    {
        cordX = rand()%map->x;
        cordY = rand()%map->y;
    } while (map->schlange[cordY * map->x + cordX] || (map->kopf[0] == cordX && map->kopf[1] == cordY));
    pos[0]=cordX;
    pos[1]=cordY;
    return;
}

int snake_rand(struct snake_map *map)
{
    if(map->kopf[0] >= map->x || map->kopf[1] >= map->y\
                || map->kopf[0] < 0 || map->kopf[1] < 0)
    {
        mvprintw(3,map->x+5,"Gegen die Wand gelaufen.");
        return 0;
    }
    return 1;
}

void snake_torus(struct snake_map *map)
{
    if(map->kopf[0] >= map->x)
        map->kopf[0] = 0;
    if(map->kopf[1] >= map->y)
        map->kopf[1] = 0;
    if(map->kopf[0] < 0)
        map->kopf[0] = map->x-1;
    if(map->kopf[1] < 0)
        map->kopf[1] = map->y-1;
    return;
}

int snake_dead_or_eating(struct snake_map *map)
{
    // 0: leeres Feld
    // 1: Essen
    // 2: tot
    if(map->kopf[0] == map->futter[0] && map->kopf[1] == map->futter[1])
        return 1;
    else if (map->schlange[map->kopf[1] * map->x + map->kopf[0]])
        return 2;
    return 0;
}

void snake_koerper(struct snake_map *map)
{
    int i;
    for(i=0;i<map->x*map->y;i++)
    {
        if(map->schlange[i])
            map->schlange[i]++;
        if(map->schlange[i] > map->length)
            map->schlange[i] = 0;
    }
    return;
}

void snake_buchstabiere(int x, int y, const char *wort)
{
    int i=0, j=0, n=0;
    do {
        if(wort[n] == '\n')
        {
            j++;
            i=0;
        }
        else
        {
            mvaddch(y+j, x+i, wort[n]);
            i++;
        }
        n++;
    } while(wort[n]!='\0');
    move(y+j, x+i);
    return;
}

void snake_help()
{
    snake_buchstabiere(0, 0, hilfe);
    printw("Steuere mit den Pfeiltasten oder WASD\n");
    printw("Erhöhe mit + das Level und die Geschwindigkeit oder veringere sie mit -\n");
}

void snake_credits()
{
    snake_buchstabiere(0, 0, credits);
    printw("Snake\n\
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n\
\n\
Darstellung durch ncurses\
\n\
Hendrik Schawe <hendrik.schawe@gmail.com>");
}

int snake_load_config(int *level, int *torus, int *theme)
{
    FILE *datei;
    datei = fopen (SNAKE_CONFIG_FILENAME, "r");
    if (datei == NULL)
    {
        return 1;
    }
    fscanf (datei, "%d;%d;%d\n", level, torus, theme);
    fclose (datei);

    return 0;
}

int snake_save_config(int level, int torus, int theme)
{
    FILE *datei;
    char *filename = SNAKE_CONFIG_FILENAME;

    datei = fopen (filename, "w");
    if (datei == NULL)
    {
        return 1;
    }
    fprintf (datei, "%d;%d;%d", level, torus, theme);
    fclose (datei);

    return 0;
}
