#include <windows.h>
#include <stdio.h>
#include <conio.h>

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//--------------------------------------------------------------------------
#pragma argsused
struct dane_dla_watku // tablica zawiera dane, ktore otrzymaja watki
{
    char nazwa[50];
    int parametr;
} dane[5] = { { "[1]", 5}, { "[2]", 8}, { "[3]", 12}, {"[4]", 1}, {"[5]", 15} };

// priorytety watkow
int priorytety[5] = { THREAD_PRIORITY_BELOW_NORMAL, THREAD_PRIORITY_LOWEST, THREAD_PRIORITY_HIGHEST, THREAD_PRIORITY_NORMAL, THREAD_PRIORITY_ABOVE_NORMAL
};

// z jednego pobrać informacje i go zakończyć

HANDLE watki[5]; // uchwyt watku

// deklaracja funkcji watku
DWORD WINAPI funkcja_watku(void *arguemnty);

//--------------------------------------------------------------------------

int main(int argc, char **argv)
{
    int i;
    DWORD id; // identyfikator watku
    // system("cls"); // clrscr();
    printf("Program uruchomiony\n");

    // tworzenie watkow
    for(i=0;i<5;i++) {
        watki[i] = CreateThread(
                NULL, // atrybuty bezpieczenstwa
                0, // inicjalna wielkosc stosu
                funkcja_watku, // funkcja watku
                (void *) &dane[i], // dane dla funkcji watku
                0, // flagi utworzenia
                &id);
        if (watki[i] != INVALID_HANDLE_VALUE) {
            printf("Utworzylem watek %s o id %lx\n", dane[i].nazwa, id);
            // ustawienie priorytetu
            SetThreadPriority(watki[i], priorytety[i]);
        }
    }
    Sleep(2000);
    int mainThreadPriority = GetThreadPriority(GetStdHandle(id));
    //printf("PRIOERYTET GLOWNY: %d\n", mainThreadPriority);
    for(i=0;i<5;i++)
    {
        //printf("Watek %s ma priorytet %d\n", dane[i].nazwa, GetThreadPriority(watki[i]));
        if(GetThreadPriority(watki[i]) > 0)        {
            printf("Watek %s ma priorytet wyzszy od zera\n", dane[i].nazwa);
        }
        else {
            printf("Watek %s ma priorytet nizszy od zera lub rowny zero, wiec go usuwam\n", dane[i].nazwa);
            TerminateThread(watki[i], 0);
        }
    }
    Sleep(20000); // uspienie watku glownego na 20s
    return 0;
}
//--------------------------------------------------------------------------
// trzy takie funkcje pracuja wspolbieznie w programie
DWORD WINAPI funkcja_watku(void *arguemnty)
{
    unsigned int licznik = 0;

    // rzutowanie struktury na wlasny wskaznik
    struct dane_dla_watku *moje_dane = (struct dane_dla_watku *) arguemnty;

    // wyswietlenie informacji o uruchomieniu
    Sleep(1000);

    // praca, watki sa terminowane przez zakonczenie programu funkcji main

    while(1)
    {
        printf("%s is running.\n", moje_dane->nazwa);
        Sleep(1000);
    }
    return 0;
}