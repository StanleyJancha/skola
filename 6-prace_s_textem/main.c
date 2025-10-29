#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

void normalizeLine(char *line);
void removeSpacesFrontAndBack(char *line);
void normalizeWords(char *line);
void removeDoubles(char *line);


void printStatistics(const char *origLine, const char *normLine);

void toLower(char *c);
void toUpper(char *c);
bool isLower(char c);
bool isUpper(char c);

int countLowerCase(const char *line);
int countUpperCase(const char *line);
int countChar(const char *line, const char c);

int stringToInt(const char *string);
int stringLength(const char *string);
void stringCopy(char *dest, char *source);

#define LINE_LENGTH 51

int main(void) {

    char inpt[20];
    fgets(inpt, 20, stdin);

    int n = stringToInt(inpt);

    for (int i = 0; i < n; i++) {
        char line[LINE_LENGTH];
        char normLine[LINE_LENGTH];
        fgets(line, LINE_LENGTH, stdin);
        
        stringCopy(normLine,line);

        removeSpacesFrontAndBack(normLine);
        normalizeLine(normLine);

        normalizeWords(normLine);

        removeDoubles(normLine);

        printf("%s",normLine);
        if (normLine[stringLength(normLine)-1] != '\n')printf("\n");
        printStatistics(line,normLine);
        if (i!=n-1){printf("\n");}
    }
}

void printStatistics(const char *origLine, const char *normLine) {
    printf("lowercase: %d -> %d\n", countLowerCase(origLine), countLowerCase(normLine));
    printf("uppercase: %d -> %d\n", countUpperCase(origLine), countUpperCase(normLine));
    printf("spaces: %d -> %d\n", countChar(origLine,' '), countChar(normLine, ' '));
}

void normalizeLine(char *line) {
    int i = 0;

    while (line[i] != '\0') {
        if (line[i] == ' ' && line[i + 1] == ' ') {
            memmove(line + i, line + i + 1, stringLength(line + i));
        } else {
            i++;
        }
    }
}

void normalizeWords(char *line) {
    int i = 0;

    while (line[i] != '\0') {
        bool hasUpper = false;
        int wordStartIndex = i;

        while (line[i] != ' ' && line[i] != '\0' && line[i] != '\n') {
            if (isUpper(line[i])) {
                hasUpper = true;
            }
            i++;
        }

        int wordEndIndex = i;

        for (int j = wordStartIndex; j < wordEndIndex; ++j) { // upravuje slovo
            if (hasUpper) { // ma v sobe alespon jedno velke pismeno
                if (j == wordStartIndex) { // prvni pismeno
                    toUpper(&line[j]);
                }
                else {
                    toLower(&line[j]);
                }
            }
            else {
                toUpper(&line[j]);
            }
        }
        i++;
    }

}

void removeSpacesFrontAndBack(char *line) {
    int firstNonWS = 0;
    for (int i = 0; i < stringLength(line); ++i) {
        if (line[i] != ' ') {
            firstNonWS = i;
            break;
        }
    }
    if (firstNonWS != 0) {
        memmove(line, line + firstNonWS, stringLength(line) - firstNonWS + 1);
    }

    for (int i = stringLength(line) - 2; i >= 0; --i) {
        if (line[i] == ' ') {
            line[i] = '\0';
        }
        else {
            break;
        }
    }
}

void removeDoubles(char *line) {
    int i = 0;
    while (line[i] != '\0') {
        if (line[i] == line[i + 1]) {
            memmove(line + i, line + i + 1, stringLength(line + i));
        } else {
            i++;
        }
    }
}



void toLower(char *c) {
    if (isUpper(*c)) {
        *c += ('a' - 'A');
    }
}

void toUpper(char *c) {
    if (isLower(*c)) {
        *c -= ('a' - 'A');
    }
}

bool isLower(char c) {
    return (c >= 'a' && c <= 'z');
}

bool isUpper(char c) {
    return (c >= 'A' && c <= 'Z');
}

int countLowerCase(const char *line) {
    int count = 0;
    for (int i = 0; i < stringLength(line); ++i) {
        if (isLower(line[i])) {
            count++;
        }
    }
    return count;
}

int countUpperCase(const char *line) {
    int count = 0;
    for (int i = 0; i < stringLength(line); ++i) {
        if (isUpper(line[i])) {
            count++;
        }
    }
    return count;
}

int countChar(const char *line, const char c) {
    int count = 0;
    for (int i = 0; i < stringLength(line); ++i) {
        if (line[i] == c) {
            count++;
        }
    }
    return count;
}

int stringToInt(const char *string) {
    int number = 0;
    int length = stringLength(string) - 1;
    for (int i = length - 1; i >= 0; --i) {
        if (string[i] >= '0' && string[i] <= '9') {
            number += (string[i] - '0') * pow(10,length - i-1);
        }
        else {
            return 0;
        }
    }
    return number;
}

int stringLength(const char *string) {
    int i = 0;
    while (string[i] != '\0') {
        i++;
    }
    return i;
}

void stringCopy(char *dest, char *source) {

    while (*source != '\0') {
        *dest = *source;
        dest++;
        source++;
    }
    *dest = '\0';
}