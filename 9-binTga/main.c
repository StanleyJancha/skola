#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <dirent.h>

typedef struct {
    uint8_t  id_length;
    uint8_t  color_map_type;
    uint8_t  image_type;

    uint8_t color_map_first[2];
    uint8_t color_map_length[2];
    uint8_t  color_map_depth;

    uint8_t x_origin[2];
    uint8_t y_origin[2];
    uint8_t width[2];
    uint8_t height[2];

    uint8_t  pixel_depth;
    uint8_t  image_descriptor;
} TGAHeader;

typedef struct {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
} Pixel;

typedef struct {
    TGAHeader header;
    Pixel *pixels;
    int height;
    int width;
} TGAImage;

typedef struct {
    char character;
    TGAImage tgaImage;
} Letter;



Pixel* loadPixels(TGAHeader header, FILE* file) {
    int width = 0;
    int height = 0;

    memcpy(&width, header.width, 2);
    memcpy(&height, header.height, 2);

    Pixel* pixels = (Pixel*) malloc(sizeof(Pixel) * width * height);
    if (fread(pixels, sizeof(Pixel) * width * height, 1, file) != 1) {
        return NULL;
    };
    return pixels;
}

bool loadTga(char *fileName, TGAImage *tgaImage) {
    FILE *file = fopen(fileName,"rb");
    if (file == NULL) {
        return false;
    }

    fread(&tgaImage->header, sizeof(TGAHeader), 1, file);
    tgaImage->pixels = loadPixels(tgaImage->header,file);

    tgaImage->height = 0;
    tgaImage->width = 0;

    memcpy(&tgaImage->width , tgaImage->header.width, 2);
    memcpy(&tgaImage->height , tgaImage->header.height, 2);

    fclose(file);

    return true;
}


void saveTga(char *fileName, TGAImage *tgaImage) {

    int width = 0;
    int height = 0;

    memcpy(&width,tgaImage->header.width,2);
    memcpy(&height,tgaImage->header.height,2);

    FILE *tgaFile = fopen(fileName,"wb");

    fwrite(&tgaImage->header, sizeof(TGAHeader),1,tgaFile);
    fwrite(tgaImage->pixels, sizeof(Pixel),width * height,tgaFile);

}

Letter *getLetterByChar(Letter *letters, char character) {
    for (int i = 0; i < 26; ++i) {
        if (letters[i].character == toupper(character)) {
            return &letters[i];
        }
    }
    return NULL;
}

bool getAllLetters(Letter *letters, char *lettersPath) {
    DIR *dir = opendir(lettersPath);
    if (!dir) {
        //printf("Cannot open directory: %s\n", lettersPath);
        return false;
    }

    int i = 0;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;

        if (strcmp(strrchr(entry->d_name,'.'),".tga") == 0) {
            char newPath[100];
            strcpy(newPath,lettersPath);
            strcat(newPath,"/");
            strcat(newPath,entry->d_name);
            letters[i].character = entry->d_name[0];
            if (loadTga(newPath,&letters[i].tgaImage) == false) {
                closedir(dir);
                return false;
            }
            i++;

        }
    }

    closedir(dir);
    return true;
}

void printLetter(TGAImage *canvasImage, TGAImage *letter, int xStart, int yStart) {
    if (letter == NULL) {
        printf("print letter - letter is null");
        return;
    }

    for (int row = 0; row < letter->height; row++) {
        int yCanvas = row + yStart;
        if (yCanvas < 0 || yCanvas >= canvasImage->height) continue;

        for (int col = 0; col < letter->width; col++) {
            int xCanvas = col + xStart;
            if (xCanvas < 0 || xCanvas >= canvasImage->width) continue;

            Pixel* pixel = canvasImage->pixels + (yCanvas * canvasImage->width + xCanvas);
            Pixel* letterPixel = letter->pixels + (row * letter->width + col);

            if (letterPixel->blue == 255 && letterPixel->green == 255 && letterPixel->red == 255) {
                *pixel = *letterPixel;
            }
        }
    }
}

int main(int argc, char *argv[]) {

    char inputPath[50];
    char outputPath[50];
    char fontsPath[50];

    if (argc < 4) {
        printf("Wrong parameters\n");
        return 1;
    }

    strcpy(inputPath,argv[1]);
    strcpy(outputPath,argv[2]);
    strcpy(fontsPath,argv[3]);

    TGAImage inputImage;
    loadTga(inputPath,&inputImage); // nasceteme vstupni obrazek


    Letter letters[26];
    if (getAllLetters(letters,fontsPath) == false) { // kdyz se nepodari nacist vsechny tga obrazku ve slozce
        printf("Could not load image\n");
        return 1;
    }



    int top;
    int bottom;
    fscanf(stdin,"%d %d\n",&top,&bottom);

    int xCursor = 0;
    int yCursor = 0;
    int xSpaceSize = 15;
    int yLetterSize = letters[0].tgaImage.height; // pocitame s tim, ze vsechny pismenka maji stejnou vysku

    for (int i = 0; i < top + bottom; ++i) {
        if (i < top) { // jestli ma byt text nahore
            yCursor = i * yLetterSize; // pocitej nove radky od vrchu
        } else {
            int bottomIndex = i - top;
            yCursor = inputImage.height - (bottom - bottomIndex) * yLetterSize; // kdyz ma byt text dole, tak pocitat radky od spodku input fokty
        }
        char line[100];
        fgets(line,sizeof(line),stdin);

        xCursor = 0;

        for (int j = 0; j < strlen(line); ++j) {
            Letter *letter = getLetterByChar(letters,line[j]); // ziska pismeno

            if (letter != NULL) { // jestli mame tga pismena, tak ho vypiseme a posuneme x kurzor
                printLetter(&inputImage,&letter->tgaImage,xCursor,yCursor);
                xCursor += letter->tgaImage.width;
            }
            if (line[j] == ' ') { // jestli je znak mezera, tak kurzor pridame o sirku mezery
                xCursor += xSpaceSize;
            }
            saveTga(outputPath,&inputImage);
        }
    }

    free(inputImage.pixels);
    inputImage.pixels = NULL;

    return 0;
}
