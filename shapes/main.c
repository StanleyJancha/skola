#include <stdio.h>

void obdelnik(int a, int b);
void dutyObdelnik(int a, int b);
void obdelnikCisla(int a, int b);
void diagonalPrava(int a);
void diagonalLeva(int a);
void trojuhelnik(int a);
void tecko(int a, int b);
void pecko(int a, int b);
void bonus(int a, int b);

int main() {
    int obrazec = 0;
    int a = 0;
    int b = 0;

    scanf("%d%d%d", &obrazec, &a, &b);

    switch (obrazec) {
        case 0: obdelnik(a,b); break;
        case 1: dutyObdelnik(a,b); break;
        case 2: obdelnikCisla(a,b); break;
        case 3: diagonalPrava(a); break;
        case 4: diagonalLeva(a); break;
        case 5: trojuhelnik(a); break;
        case 6: tecko(a,b); break;
        case 7: pecko(a,b); break;
        case 9: bonus(a,b); break;

        default: {
            printf("Neznamy obrazec\n");
        }
    }

    return 0;
}

void obdelnik(int a, int b) {

    for (int i = 0; i < b; i++) {
        for (int j = 0; j < a; j++) {
            printf("x");
        }
        printf("\n");
    }

}

void dutyObdelnik(int a, int b) {

    for (int i = 0; i < b; i++) {
        for (int j = 0; j < a; j++) {
            if (i == 0 || i == b-1) { // kdyz je to prvni nebo posledni radek
                printf("x");
            }
            else if (j == 0 || j == a-1) { // kdyz je to prvni nebo psoledni sloupec
                printf("x");
            }
            else {printf(" ");} // jinak mezera
        }
        printf("\n");
    }

}

void obdelnikCisla(int a, int b) {

    int counter = 0; // inkrementuju vzdy po vypasni cisla

    for (int i = 0; i < b; i++) {
        for (int j = 0; j < a; j++) {
            if (i == 0 || i == b-1) { // kdyz je to prvni nebo posledni radek
                printf("x");
            }
            else if (j == 0 || j == a-1) { // kdyz je to prvni nebo psoledni sloupec
                printf("x");
            }
            else {
                printf("%d", counter%10); // % pozuivam, abych dostal jenom cislo na pozici jendotek
                counter++;
            }
        }
        printf("\n");
    }

}

void diagonalPrava(int a) {
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < i; j++) {printf(" ");}
        printf("x\n");
    }
}
void diagonalLeva(int a) {
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < a-1-i; j++) {printf(" ");}
        printf("x\n");
    }
}

void trojuhelnik(int a) {
    for (int i = 0; i < a; i++) {
        if (i != a-1) {
            for (int j = 0; j < a-i-1; j++) {printf(" ");}
            printf("x");
            for (int j = 0; j < i+i-1; j++) {printf(" ");}
            if (i != 0) {
                printf("x");
            }
            printf("\n");
        }
        else {
            for (int j = 0; j < i+i+1; j++) {printf("x");}
        }

    }
}

void tecko(int a, int b) {
    for (int i = 0; i < a; i++) {printf("x");}
    printf("\n");
    for (int i = 1; i < b; i++) {
        for (int j = 0; j < a/2; j++) {printf(" ");}
        printf("x\n");
    }
}
void pecko(int a, int b) {
    for (int i = 0; i < b; i++) {
        if (i == 0 || i == b/2) { // vypise plne radky, coz je prvni a prostredni
            for (int j = 0; j < a; j++) {printf("x");}
        }
        else {
            printf("x");
            if (i < b/2) {
                for (int j = 0; j < a-2; j++) {printf(" ");}
                printf("x");
            }

        }
        printf("\n");
    }
}

void bonus(int a, int b) {
    for (int i = 0; i < b; i++) {
        int counter = i-1;

        for (int j = 0; j < a; j++) {
            if (i == 0 || i == b-1) { // kdyz je to prvni nebo posledni radek
                printf("x");
            }
            else if (j == 0 || j == a-1) { // kdyz je to prvni nebo psoledni sloupec
                printf("x");
            }
            else {
                printf("%d", counter%10); // % pozuivam, abych dostal jenom cislo na pozici jendotek
                counter += b-2;
            }
        }
        printf("\n");
    }
}
/*
 Obrazce
    0 - obdélník s šířkou A a výškou B
    1 - "dutý" obdélník s šířkou A a výškou B
    2 - vykreslete obdélník s šířkou A a výškou B, který bude mít uprostřed (mimo svůj obvod) čísla se vzrůstající hodnotou
    3 - diagonálu, která bude mířit doprava dolů, a bude obsahovat A bodů (hodnotu B zde ignorujte).
    4 - vykreslete diagonálu, která bude mířit doleva dolů, a bude obsahovat A bodů (hodnotu B zde ignorujte).
    5 - trojúhelník, který bude mít A bodů na výšku (hodnotu B zde ignorujte). Můžete předpokládat, že hodnota A bude vždy lichá.
    6 - písmeno T, které bude A bodů široké a B bodů vysoké. Můžete předpokládat, že hodnota A bude vždy lichá.
    7 - písmeno P, které bude A bodů široké a B bodů vysoké. Můžete předpokládat, že hodnota B bude vždy lichá.
    9 - obdélník s šířkou A a výškou B, který bude mít uprostřed (mimo svůj obvod) čísla se vzrůstající hodnotou. Narozdíl od obrazce 2 se zde ale čísla budou zvyšovat po sloupcích, ne po řádcích

    jine - Neznamy obrazec a ukončete prorgam.

*/