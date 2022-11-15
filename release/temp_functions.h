//
// Created by Donner on 14.11.2022.
//

#ifndef FINAL_TEMP_FUNCTIONS_H
#define FINAL_TEMP_FUNCTIONS_H

void fillIt(short data[13][32][24][60]);
short minTemp(short data[13][32][24][60]);
short minTempinMonth(short data[13][32][24][60], int mon);
short maxTemp(short data[13][32][24][60]);
short maxTempinMonth(short data[13][32][24][60], int mon);
short medTemp(short data[13][32][24][60]);
short medTempinMonth(short data[13][32][24][60], int mon);
int tempMath(char filename[], int monthNum);


#endif //FINAL_TEMP_FUNCTIONS_H
