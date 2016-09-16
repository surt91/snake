#include "highscore.h"

static const char *highscore = "\
 _   _ _       _                                 \n\
| | | (_) __ _| |__  ___  ___ ___  _ __ ___  ___ \n\
| |_| | |/ _` | '_ \\/ __|/ __/ _ \\| '__/ _ \\/ __|\n\
|  _  | | (_| | | | \\__ \\ (_| (_) | | |  __/\\__ \\\n\
|_| |_|_|\\__, |_| |_|___/\\___\\___/|_|  \\___||___/\n\
         |___/                                   \n";

int hs_show_highscore(int punkte, char* sPunkte, int level, char* sLevel, char *filename)
{
    char name[80];

    printw("\nHighscore:\n\n");
    printw("%s: ", sPunkte);
    printw("% 5d\n", punkte);
    printw("%s: ", sLevel);
    printw("% 5d\n", level);
    if(punkte > hs_load_highscore(filename, sPunkte, sLevel))
    {
        nocbreak();
        printw("Das ist ein neuer Highscore!\n");
        printw("Trage deinen Namen ein:\n");
        refresh();
        echo();
        scanw("%s",name);
        noecho();
        hs_save_highscore(punkte, level, name, filename);
        cbreak();
    }
    return 0;
}

int hs_load_highscore(char *filename, char* sPunkte, char* sLevel)
{
    FILE *datei;
    int i, punkte, level, day, month, year, hour, min, tmp=0;
    char name[80];
    datei = fopen (filename, "r");
    if (datei == NULL)
    {
        return 1;
    }
    erase();
    printw("%s\n", highscore);
    printw("\tName\t\t% 6s\t\t% 6s\t\t     Datum\t  Uhr\n", sPunkte, sLevel);
    for(i=0;i<NUMHS;i++)
    {
        fscanf (datei, "%d;%d;%d-%d-%dT%d:%d;%s\n", &punkte, &level,\
                                &year, &month, &day, &hour, &min, name);
        printw("\t%s", name);
        printw("\t\t% 6d",punkte);
        printw("\t\t% 6d",level);
        printw("\t\t%02d.%02d.%04d",day,month,year);
        printw("\t%02d:%02d",hour,min);
        printw("\n");
    }
    fclose (datei);
    printw("\n");
    refresh();
    tmp = punkte;
    return tmp;
}

int hs_save_highscore(int punkte, int level, char *name, char *filename)
{
    FILE *datei;

    struct tm *ts;
    time_t t;

    datei = fopen (filename, "a");
    if (datei == NULL)
    {
        return 1;
    }

    t = time(NULL);
    ts = localtime(&t);

    fprintf (datei, "%d;%d;%d-%d-%dT%d:%d;%s\n", punkte, level,\
    ts->tm_year+1900, ts->tm_mon+1, ts->tm_mday, ts->tm_hour, ts->tm_min,\
    name);
    fclose (datei);
    hs_highscore_sort(filename);
    return 0;
}

void hs_highscore_sort(char *filename)
{
    FILE *datei;
    int i, j, data[NUMHS+1], itmp, index[NUMHS+1];
    char rest[NUMHS+1][100];
    for(i=0;i<NUMHS+1;i++)
        index[i] = i;
    datei = fopen (filename, "r");
    if (datei == NULL)
    {
        return;
    }
    for(i=0;i<NUMHS+1;i++)
        fscanf (datei, "%d;%s\n", &data[i], rest[i]);
    fclose (datei);
    for(i=0;i<NUMHS+1;i++)
        for(j=NUMHS;i<j;j--)
            if(data[index[j-1]]<data[index[j]])
            {
                itmp = index[j-1];
                index[j-1] = index[j];
                index[j] = itmp;
            }

    datei = fopen (filename, "w");
    for(i=0;i<NUMHS;i++)
        fprintf(datei, "%d;%s\n", data[index[i]], rest[index[i]]);
    fclose (datei);
    return;
}

void hs_highscore_init(char *filename)
{
    FILE *datei;
    int i, tmp;
    datei = fopen (filename, "r");
    if (datei != NULL)
    {
        tmp = fgetc(datei);
        fclose(datei);
    }
    else
    {
        tmp = EOF;
    }
    if (tmp == EOF)
    {
        datei = fopen (filename, "w");
        for (i = 0; i<10; i++)
            fprintf(datei,"0;0;2011-10-3T15:31;Abe\n");
        fclose(datei);
    }
    return;
}
