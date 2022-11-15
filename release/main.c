#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "temp_functions.h"
#define VERSION "v0.1"

int main(int argc, char **argv) {

    if ((argc > 5) || (argc == 4)) {
        printf("Error: found wrong arguments.");
        return (1);
    }
    if (argc == 1) {
        printf("%s\nError: type -h for help\n",VERSION);
        return (1);
    }
    if (argc == 2) {
        if (!strcmp(argv[1], "-h")) {
            printf("-h for this help message\n");
            printf("-f for filename\n");
            printf("-m for month number\n");
            printf("\n Examples:\n");
            printf("final.exe -h\n");
            printf("final.exe -f temperature_big.csv\n");
            printf("final.exe -f temperature_big.csv -m 5\n");
            return (0);
        } else printf("%s\nError: type -h for help\n",VERSION);
        return (1);
    }
    if (argc == 3) {
        if (!strcmp(argv[1], "-f")) {
            return (tempMath(argv[2], 0));
        } else {
            printf("%s\nError: type -h for help\n",VERSION);
            return (1);
        }
    }
    if (argc == 5) {
        if ((!strcmp(argv[1], "-f"))&&(!strcmp(argv[3], "-m"))&&(atoi(argv[4])>0)&&(atoi(argv[4])<13)) {
            return (tempMath(argv[2], atoi(argv[4])));
        } else {
            printf("%s\nError: type -h for help\n",VERSION);
            return (1);
        }
    }


    return 0;
}