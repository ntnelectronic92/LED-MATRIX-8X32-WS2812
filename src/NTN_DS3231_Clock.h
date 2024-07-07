#ifndef NTN_DS3231_CLOCK_H
#define NTN_DS3231_CLOCK_H
#include "NTN_System.h"
typedef struct
{
    uint8_t hour;
    uint8_t minutes;
    uint8_t second;
} NTN_TIME;
void NTN_DS3231_Clock_Init();
void NTN_DS3231_Clock_Handler();
NTN_TIME NTN_DS3231_Clock_GetCurrentTime();
DateTime NTN_DS3231_Clock_Get_Date_Time();
#endif
