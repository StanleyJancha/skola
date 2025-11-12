#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Akcie {
    int indexDne;
    char *nazev;
    double hodnotaZacatek;
    double hodnotaKonec;
    int pocetProvedenychObhcodu;
};

void intPrettify(int input, char *output) {
    char str[20];
    sprintf(str, "%d",input);


    int firstNotThree = (strlen(str) % 3 != 0)? (strlen(str) % 3): 3;

    int i = 0;
    int newIndex = 0;

    for (; i < firstNotThree; ++i) {
        output[newIndex] = str[i];
        newIndex++;
    }

    for (; i < strlen(str); ++i) {
        if ((i-firstNotThree) % 3 == 0) {
            output[newIndex] = '_';
            newIndex++;
        }
        output[newIndex] = str[i];
        newIndex++;
    }
    output[newIndex] = '\0';
}


int main(int argc, char** argv) {

    char stint[50];
    intPrettify(15326754,stint);

    if (argc < 3 || atoi(argv[2]) <= 0 ) {
        printf("Wrong parameters\n");
        return 1;
    }
    const int n = atoi(argv[2]);


    struct Akcie *akcie = malloc(sizeof(*akcie) * n);

    int argAkcieIndex = -1;
    
    char line[100];
    for (int i = 0; i < n; ++i) {
        fgets(line,100,stdin);

        struct Akcie akcieJ = {};

        char *stringToken;
        stringToken = strtok(line,",");
        akcieJ.indexDne = atoi(stringToken);
        stringToken = strtok(NULL,",");
        akcieJ.nazev = malloc(sizeof(char) * (strlen(stringToken) + 1));
        strcpy(akcieJ.nazev, stringToken);
        stringToken = strtok(NULL,",");
        akcieJ.hodnotaZacatek = atof(stringToken);
        stringToken = strtok(NULL,",");
        akcieJ.hodnotaKonec = atof(stringToken);
        stringToken = strtok(NULL,",");
        akcieJ.pocetProvedenychObhcodu = atoi(stringToken);

        if ((strcmp(argv[1], akcieJ.nazev) == 0) && argAkcieIndex == -1) {
            argAkcieIndex = i;
        }

        akcie[i] = akcieJ;
    }

    printf("<html>\n<body>\n");

    printf("<div>\n");
    if (argAkcieIndex != -1) {
        printf("<h1>%s: highest volume</h1>\n",akcie[argAkcieIndex].nazev);
        printf("<div>Day: %d</div>\n", akcie[argAkcieIndex].indexDne);
        printf("<div>Start price: %.2f</div>\n",akcie[argAkcieIndex].hodnotaZacatek);
        printf("<div>End price: %.2f</div>\n",akcie[argAkcieIndex].hodnotaKonec);
        char tmp[20];
        intPrettify(akcie[argAkcieIndex].pocetProvedenychObhcodu,tmp);
        printf("<div>Volume: %s</div>\n",tmp);

    }
    else {
        printf("Ticker %s was not found\n",argv[1]);
    }
    printf("</div>\n");

    printf("<table>\n<thead>\n<tr><th>Day</th><th>Ticker</th><th>Start</th><th>End</th><th>Diff</th><th>Volume</th></tr>\n</thead>\n<tbody>\n");

    for (int i = n - 1; i >= 0; --i) {
        bool bold = (strcmp(akcie[i].nazev,argv[1]) == 0);
        printf("<tr>\n");
        printf((bold)?"\t<td><b>%d</b></td>\n":"\t<td>%d</td>\n",akcie[i].indexDne);
        printf((bold)?"\t<td><b>%s</b></td>\n":"\t<td>%s</td>\n",akcie[i].nazev);
        printf((bold)?"\t<td><b>%.2f</b></td>\n":"\t<td>%.2f</td>\n",akcie[i].hodnotaZacatek);
        printf((bold)?"\t<td><b>%.2f</b></td>\n":"\t<td>%.2f</td>\n",akcie[i].hodnotaKonec);
        printf((bold)?"\t<td><b>%.2f</b></td>\n":"\t<td>%.2f</td>\n",akcie[i].hodnotaKonec-akcie[i].hodnotaZacatek);
        char tmp[20];
        intPrettify(akcie[argAkcieIndex].pocetProvedenychObhcodu,tmp);
        printf((bold)?"\t<td><b>%s</b></td>\n":"\t<td>%s</td>\n",tmp);
        printf("</tr>\n");
    }
    printf("</tbody>\n</table>\n</body>\n</html>\n");


    //BONUS NEFUNKCI :(
    // FILE *file = fopen("./graf.svg","w");
    // if (file == NULL) {
    //     printf("Nepodarilo se nacist soubor");
    // }
    // else {
    //     int width = 5000;
    //     int height = 5000;
    //     fprintf(file, "<svg width=\"%d\" height=\"%d\" xmlns=\"http://www.w3.org/2000/svg\">\n",width,height);
    //     fprintf(file, "<g transform=\"translate(0,%d) scale(1,-1)\">\n", height);
    //
    //     int tIndex = 0;
    //     int yScale = 10;
    //     char colorRed[10] = "255,0,0";
    //     char colorGreen[10] = "0,255,0";
    //
    //     for (int i = 0; i < n; ++i) {
    //         if (strcmp(akcie[i].nazev,argv[1]) != 0) {
    //             continue;
    //         }
    //         printf("start %f\nend:%f\ndiff: %f\n",akcie[i].hodnotaZacatek,akcie[i].hodnotaKonec,(akcie[i].hodnotaKonec-akcie[i].hodnotaZacatek));
    //         int sirka = 10;
    //         int vyska = abs((int)((akcie[i].hodnotaKonec-akcie[i].hodnotaZacatek)*100)*yScale)/100;
    //         int x = tIndex*20;
    //         int y = (int)akcie[i].hodnotaZacatek - ((akcie[i].hodnotaKonec-akcie[i].hodnotaZacatek > 0)?0:vyska);
    //         fprintf(file,
    //             "<rect width=\"%d\" height=\"%d\" x=\"%d\" y=\"%d\" style=\"fill:rgb(%s)\" />\n",
    //             sirka,vyska*yScale,
    //             x,y*yScale,
    //             (akcie[i].hodnotaKonec-akcie[i].hodnotaZacatek > 0)?colorGreen:colorRed);
    //
    //         tIndex++;
    //     }
    //     fprintf(file, "</g>\n");
    //     fprintf(file, "</svg>");
    //
    //     fclose(file);
    // }




    // UVOLNENI PAMETI
    for (int i = 0; i < n; ++i) {
        free(akcie->nazev);
        akcie->nazev = NULL;
    }
    free(akcie);
    akcie = NULL;

    return 0;
}
