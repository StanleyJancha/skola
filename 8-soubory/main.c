#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *getSubString(char *string, const char *substring, bool caseSensitive);

int main(int argc, char **argv) {
    char needle[100] = "";
    char inputPath[100] = "";
    char outputPath[100] = "";
    bool caseSensitive = true;

    for (int i = 1; i < argc; ++i) {
        if (argc >= i && argv[i] && argv[i][0] == '-') {
            if (strcmp(argv[i], "-i") == 0) {
                if (caseSensitive == false) {
                    printf("Parameter -i provided multiple times\n");
                    return 1;
                }
                caseSensitive = false;
            }else
            if (strcmp(argv[i], "-o") == 0) {
                if (argc <= i+1) { //4<4
                    printf("Missing output path\n");
                    return 1;
                }
                if (strcmp(outputPath,"") != 0) {
                    printf("Parameter -o provided multiple times\n");
                    return 1;
                }
                strcpy(outputPath, argv[i+1]);
                i++;
            }
        }else
        if (strcmp(inputPath,"") == 0){
            strcpy(inputPath,argv[i]);
        }else
        if (strcmp(needle,"") == 0){
            strcpy(needle,argv[i]);
        }
        else {
            printf("Too many parameters provided\n");
            return 1;
        }
    }

    if (strcmp(inputPath,"") == 0) {
        printf("Input path not provided\n");
        return 1;
    }
    if (strcmp(needle,"") == 0) {
        printf("Needle not provided\n");
        return 1;
    }


    FILE *inputFile = fopen(inputPath,"r");
    FILE *outputFile = fopen(outputPath,"w");

    char line[100];
    while (fgets(line,100,inputFile) != NULL) {
        const char *subString = getSubString(line, needle,caseSensitive);
        if (subString != NULL) {
            if (outputFile != NULL) {
                fprintf(outputFile,"%s",line);
            }else {
                printf("%s",line);
            }
        }
        //if (subString != NULL){free(subString);}
    }

    fclose(inputFile);
    if (outputFile != NULL) {
        fclose(outputFile);
    }

    return 0;
}

char *getSubString(char *string, const char *substring, bool caseSensitive) {
    for (int i = 0; i < strlen(string); ++i) {
        for (int j = 0; j < strlen(substring); ++j) {
            char ic = string[i+j];
            char jc = substring[j];
            if ((caseSensitive? (ic != jc) : (tolower(ic) != tolower(jc)) )) {
                break;
            }
            if (j == strlen(substring) - 1) {
                return &string[i];
            }
        }
    }
    return NULL;
}
