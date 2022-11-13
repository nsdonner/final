//
// Created by Donner on 14.11.2022.
//


#include <stdio.h>
#include "temp_functions.h"
void fillIt(short data[13][32][24][60]) {
    for (int mon = 0; mon < 13; mon++) {
        for (int d = 0; d < 32; d++) {
            for (int h = 0; h < 24; h++) {
                for (int m = 0; m < 60; m++) {
                    data[mon][d][h][m] = 100;
                }
            }
        }
    }
}

short minTemp(short data[13][32][24][60]) {
    short min = 100;
    for (int mon = 0; mon < 13; mon++) {
        for (int d = 0; d < 32; d++) {
            for (int h = 0; h < 24; h++) {
                for (int m = 0; m < 60; m++) {
                    if (data[mon][d][h][m] < min) {
                        min = data[mon][d][h][m];
                    }
                }
            }
        }
    }
    return min;
}

short minTempinMonth(short data[13][32][24][60], int mon) {
    short min = 100;
    for (int d = 0; d < 32; d++) {
        for (int h = 0; h < 24; h++) {
            for (int m = 0; m < 60; m++) {
                if (data[mon][d][h][m] < min) {
                    min = data[mon][d][h][m];
                }
            }
        }

    }
    return min;
}

short maxTemp(short data[13][32][24][60]) {
    short max = -100;
    for (int mon = 0; mon < 13; mon++) {
        for (int d = 0; d < 32; d++) {
            for (int h = 0; h < 24; h++) {
                for (int m = 0; m < 60; m++) {
                    if ((data[mon][d][h][m] > max) && (data[mon][d][h][m] < 100)) {
                        max = data[mon][d][h][m];
                    }
                }
            }
        }
    }
    return max;
}

short maxTempinMonth(short data[13][32][24][60], int mon) {
    short max = -100;
    for (int d = 0; d < 32; d++) {
        for (int h = 0; h < 24; h++) {
            for (int m = 0; m < 60; m++) {
                if ((data[mon][d][h][m] > max) && (data[mon][d][h][m] < 100)) {
                    max = data[mon][d][h][m];
                }
            }
        }
    }
    return max;
}

short medTemp(short data[13][32][24][60]) {
    int med = 0;
    int count = 0;
    for (int mon = 0; mon < 13; mon++) {
        for (int d = 0; d < 32; d++) {
            for (int h = 0; h < 24; h++) {
                for (int m = 0; m < 60; m++) {
                    if (data[mon][d][h][m] < 100) {
                        med = med + data[mon][d][h][m];
                        count++;
                    }
                }
            }
        }
    }

    return med / count;
}

short medTempinMonth(short data[13][32][24][60], int mon) {
    int med = 0;
    int count = 0;
    for (int d = 0; d < 32; d++) {
        for (int h = 0; h < 24; h++) {
            for (int m = 0; m < 60; m++) {
                if (data[mon][d][h][m] < 100) {
                    med = med + data[mon][d][h][m];
                    count++;
                }
            }
        }
    }


    return med / count;
}

int tempMath(char filename[], int monthNum) {

    FILE *f;
    int a = 0;
    char s[10000];
    short data[13][32][24][60] = {0};
    f = fopen(filename, "r");
    if (f == NULL) {
        printf("\n Can't open file %s\n", filename);
        return 1;
    }
    int year, month, day, hour, minute;
    short t;

    fillIt(data);


    for (int i = 1; a != EOF; i++) {
        a = fscanf(f, "%d;%d;%d;%d;%d;%hi", &year, &month, &day, &hour, &minute, &t);
        if ((a == 6) && (year < 10000) && (year > 999) && (month > 0) && (month < 13) && (day > 0) && (day < 32) &&
            (minute >= 0) && (minute < 60) && (t > -100) && (t < 100)) {
            data[month][day][hour][minute] = t;
            continue;
        } else if (a != EOF) {
            printf("Error at line %d\n", i);
            fscanf(f, "%s", s);
        }
    }
    fclose(f);


    if (monthNum == 0) {
        for (int i = 1; i < 13; i++) {
            printf("Month %d median temp is %hi\n", i, medTempinMonth(data, i));
            printf("Mont %d minimum temp is %hi\n", i, minTempinMonth(data, i));
            printf("Mont %d maximum temp is %hi\n", i, maxTempinMonth(data, i));
        }
    } else {
        printf("Month %d median temp is %hi\n", monthNum, medTempinMonth(data, monthNum));
        printf("Mont %d minimum temp is %hi\n", monthNum, minTempinMonth(data, monthNum));
        printf("Mont %d maximum temp is %hi\n", monthNum, maxTempinMonth(data, monthNum));
    }

    printf("%d median temp is %hi\n", year, medTemp(data));
    printf("%d minimum temp is %hi\n", year, minTemp(data));
    printf("%d maximum temp is %hi\n", year, maxTemp(data));

    return 0;

}
