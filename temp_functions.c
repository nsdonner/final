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
    /*int med = 0;
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
    if (count == 0) {
        return -100;
    }
    return med / count;*/
    short count = 0;
    short result[13];
    short sum = 0;
    for (int i = 1; i < 13; i++) {
        result[i] = medTempinMonth(data, i);
    }
    if (((result[1] + result[2] + result[3]) < -100) || ((result[4] + result[5] + result[6]) < -100) ||
        ((result[7] + result[8] + result[9]) < -100) || ((result[10] + result[11] + result[12]) < -100)) {
        return -101;
    } else {
        for (int i = 1; i < 13; i++) {
            if (result[i] > -100) {
                count++;
                sum = sum + result[i];
            }
        }
        if (count == 0) {
            return -100;
        } else {
            return sum / count;
        }

    }


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

    if (count == 0) {
        return -100;
    }
    return med / count;
}

int tempMath(char filename[], int monthNum) {

    FILE *f;
    int a = 0;
    char MONTH[13][10] = {{""},
                          {"January\0"},
                          {"February\0"},
                          {"March\0"},
                          {"April\0"},
                          {"May\0"},
                          {"June\0"},
                          {"July\0"},
                          {"August\0"},
                          {"September\0"},
                          {"October\0"},
                          {"November\0"},
                          {"December\0"}};
    char s = 1;
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
            if (data[month][day][hour][minute] == 100) {
                data[month][day][hour][minute] = t;
                continue;
            } else {
                printf("Error at line %d, duplicate data\n", i);
            }
        } else if (a != EOF) {
            printf("Error at line %d\n", i);
            while ((s != 10) && (s != -1) && (s != 0) && (a != EOF)) {
                a = fscanf(f, "%c", &s);
            }
            s = 1;
        }
    }
    fclose(f);


    if (monthNum == 0) {
        for (int i = 1; i < 13; i++) {
            if (medTempinMonth(data, i) == -100) {
                printf("No data for %s\n", MONTH[i]);
            } else {
                printf("Temperature of %s: med: %hi, min %hi, max %hi\n", MONTH[i], medTempinMonth(data, i),
                       minTempinMonth(data, i), maxTempinMonth(data, i));
            }
        }
    } else if (medTempinMonth(data, monthNum) == -100) {
        printf("No data for %s\n", MONTH[monthNum]);
    } else {
        printf("Temperature of %s: med: %hi, min %hi, max %hi\n", MONTH[monthNum], medTempinMonth(data, monthNum),
               minTempinMonth(data, monthNum), maxTempinMonth(data, monthNum));
    }

    if ((year > 999) && (year < 10000)) {
        if (medTemp(data) == -101) {
            printf("Not enough data for year median. Temperature of %d: min %hi, max %hi\n", year, minTemp(data),
                   maxTemp(data));
            return 0;
        } else if (medTemp(data) == -100) {
            printf("Error: no correct data in file");
            return 1;
        } else {
            printf("Temperature of %d: med: %hi, min %hi, max %hi\n", year, medTemp(data), minTemp(data),
                   maxTemp(data));
            return 0;
        }
    } else {
        printf("Error: no correct data in file");
        return 1;
    }
    //printf("%d minimum temp is %hi\n", year, minTemp(data));
    //printf("%d maximum temp is %hi\n", year, maxTemp(data));


}
