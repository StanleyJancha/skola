#include <stdio.h>

unsigned int pocetCislic(unsigned int n);
unsigned int prvekSNejviceZastoupeni(unsigned int* histogram);
int main(void) {

    char mod;
    scanf("%c", &mod);

    unsigned int pocetNactenychCisel; // n
    unsigned int prvniCisloIntervalu; // m   //(rozsah je prvniCisloIntervalu + 8)

    unsigned int invalidCounter = 0;


    scanf("%u", &pocetNactenychCisel);
    scanf("%u", &prvniCisloIntervalu);

    unsigned int histogram[9];

    for (int i = 0; i < 9; i++) {histogram[i] = 0;} // nacteni nul do pole

    for (unsigned i = 0; i < pocetNactenychCisel; i++) {

        unsigned int tempCislo;

        scanf("%u", &tempCislo);

        if (tempCislo >= prvniCisloIntervalu && tempCislo <= prvniCisloIntervalu + 8) {
            histogram[tempCislo-prvniCisloIntervalu]++;
        }
        else {
            invalidCounter++;
        }
    }

    switch (mod) {
        case 'h': {
            for (unsigned int i = 0; i < 9; i++) {
                if (pocetCislic(prvniCisloIntervalu+i) < pocetCislic(prvniCisloIntervalu+8)){printf(" ");}
                printf("%d", prvniCisloIntervalu + i);
                if (histogram[i] > 0){printf(" ");}
                for (unsigned int j = 0; j < histogram[i]; j++) {printf("#");}
                printf("\n");
            }
            if (invalidCounter > 0) {
                printf("invalid: ");
                for (unsigned int j = 0; j < invalidCounter; j++) {printf("#");}
                printf("\n");
            }

        }break;
        case 'v': {
            unsigned int pocetRadku = histogram[prvekSNejviceZastoupeni(histogram)];
            for (unsigned int r = 0; r < pocetRadku + (pocetRadku > 0)?1:0; r++) {
                printf("#");
                for (unsigned int s = 0; s < 9; s++){
                    if (histogram[s] > pocetRadku - r && histogram[s] > 0) {printf("#");}
                    else {printf(" ");}
                }
                printf("\n");
            }
            printf("i");
            for (int i = 1; i <= 9; ++i) {printf("%d",i);}
            printf("\n");

        }break;
        default: {
            printf("Neplatny mod vykresleni\n");
            return 1;
        }
    }
    return 0;
}

unsigned int pocetCislic(unsigned int n) {
    unsigned int counter = 0;
    do  {
        counter++;
        n /= 10;
    } while (n > 0);
    return counter;
}

unsigned int prvekSNejviceZastoupeni(unsigned int* histogram) {
    unsigned int index = 0;
    for (unsigned int i = 0; i < 9; ++i) {
        if (histogram[i] > index) {
            index = i;
        }
    }
    return index;
}