#include "NTN_System.h"
void NTN_System_Int()
{
     NTN_Print_Init();
     NTN_DS3231_Clock_Init();
     NTN_PRINT_START();
}
void NTN_System_Handler()
{
  NTN_DS3231_Clock_Handler();
}