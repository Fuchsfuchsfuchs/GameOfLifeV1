#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAXX 50      // maximale Ausdehnung des Spielfelds in X Richtung
#define MAXY 20      // maximale Ausdehnung des Spielfelds in Y Richtung
#define ZelleAn '#'  // Symbol einer aktiven Zelle
#define ZelleAus 'O' // Symbol einer inaktiven Zelle
#define FREQUENZ 2   // Aktualisierungsfrequenz in Sekunden

int zeile = 0;  // Zeilen der Spielfeldmatrix
int spalte = 0; // Spalten der Spielfeldmatrix
int wdh = 0;    // Zählt die Anzahl der Wiederholungen

int altGen[MAXX + 2][MAXY + 2], // Die Ausgangsgeneration des Spielfelds
    neuGen[MAXX + 2][MAXY + 2];

void initialisiere(void);
void SpielfeldDrucken(void);
void spielen(void);

int main(void)
{
    srand(time(NULL)); // Seed für rand() wird kontinuierlich neu gesetzt
    initialisiere();   // Spielfeld wird erstellt und Matrizen initialisiert
    spielen();
    return (0);
}

void initialisiere(void)
{
    int i, j, k;
    // int eingabe = 0;
    //  char string[100], zeichen;
    // TODO Eingabeüberprüfung

    printf("Spielfeldgröße: Zeilen (1, %d): ", MAXY);
    scanf("%d", &zeile);

    printf("Spielfeldgröße: Spalten (1, %d): ", MAXX);
    scanf("%d", &spalte);

    for (i = 0; i < MAXY; i++)
    {
        for (j = 0; j < MAXX; j++)
        {
            altGen[i][j] = 0;
            neuGen[i][j] = 0;
        }
    }

    for (i = 0; i < zeile; i++)
    {
        for (j = 0; j < spalte; j++)
        {
            altGen[i + 1][j + 1] = rand() % 2;
        }
    }

    // zufällige Startvorraussetzung und while schleife
    // Möglichkeit zum neuinitialisieren besteht

    // SpielfeldDrucken();
}

void spielen(void)
{
    while (1)
    {
        int i, j = 0;
        sleep(FREQUENZ);
        SpielfeldDrucken();

        for (i = 1; i < zeile + 1; i++)
        {
            for (j = 1; j < spalte + 1; j++)
            {
                int summe = 0;
                summe = altGen[i][j - 1] + altGen[i][j + 1] + altGen[i + 1][j - 1] + altGen[i + 1][j] + altGen[i + 1][j + 1] + altGen[i - 1][j - 1] + altGen[i - 1][j] + altGen[i - 1][j + 1];

                if (summe < 2 || summe > 3)
                {
                    neuGen[i][j] = 0;
                }
                else if (summe == 3)
                {
                    neuGen[i][j] = 1;
                }
                else
                {
                    neuGen[i][j] = altGen[i][j];
                }
            }
        }

        for (i = 0; i < zeile + 2; i++)
        {
            for (j = 0; j < spalte + 2; j++)
            {
                altGen[i][j] = neuGen[i][j];
            }
        }
    }
}

void SpielfeldDrucken(void)
{
    wdh++; // Jeder Aufruf erhöht den Wiederholungszähler
    int i, j;
    printf("  ");
    for (i = 0; i < spalte; i++)
    {
        printf(" %d", (i + 1) % 10);
    }
    printf("\n\n");

    for (i = 0; i < zeile; i++)
    {
        printf("%d ", (i + 1) % 10);
        for (j = 0; j < spalte; j++)
        {
            if (altGen[i + 1][j + 1] == 0)
            {
                printf(" %c", ZelleAus);
            }
            if (altGen[i + 1][j + 1] == 1)
            {
                printf(" %c", ZelleAn);
            }
            // printf(" %c", altGen[i + 1][j + 1]);
        }
        printf("\n");
    }
    printf("%d. Durchlauf\n\n ", wdh);
}
