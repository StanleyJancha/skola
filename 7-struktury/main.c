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

char* intPrettify(int x) {

}


int main(int argc, char** argv) {

    char *stint = intPrettify(15326754);
    printf("int pretify: %s", stint);
    free(stint);
    stint = NULL;

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
        // printf("%s\n",line);

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
        printf("<div>Volume: %d</div>\n",akcie[argAkcieIndex].pocetProvedenychObhcodu);

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
        printf((bold)?"\t<td><b>%d</b></td>\n":"\t<td>%d</td>\n",akcie[i].pocetProvedenychObhcodu);
        printf("</tr>\n");
    }

    printf("</tbody>\n</table>\n</body>\n</html>\n");



    // UVOLNENI PAMETI
    for (int i = 0; i < n; ++i) {
        free(akcie->nazev);
        akcie->nazev = NULL;
    }
    free(akcie);
    akcie = NULL;

    return 0;
}
