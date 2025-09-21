#include <stdio.h>

int main(void) {

    unsigned int money = 16230;

    printf("Bankovka 5000: %dx\n", money/5000);
    money = money%5000;

    printf("Bankovka 2000: %dx\n", money/2000);
    money = money%2000;

    printf("Bankovka 1000: %dx\n", money/1000);
    money = money%1000;

    printf("Bankovka 500: %dx\n", money/500);
    money = money%500;

    printf("Bankovka 200: %dx\n", money/200);
    money = money%200;

    printf("Bankovka 100: %dx\n", money/100);
    money = money%100;


    return 0;
}