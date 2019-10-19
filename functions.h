#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "data.h"

void myscanint ( int*, int, int);
void myscanstring(char [BUFFER_SIZE]);
int ParamReading(int, char *[], char [2][50]);
void MenuSurfer(int*, int*, int*, int*, int*, int*, char [BUFFER_SIZE],int*);
int MainMenu();
int DataFilter();
void TemperatureHistory(int*, int*, char [BUFFER_SIZE]);
void YearTempAnalise(int*, int*);
int GlobalTempAnalise(int*);

#endif
