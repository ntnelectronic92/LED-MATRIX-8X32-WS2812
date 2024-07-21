#include "NTN_System.h"
void NTN_System_Int()
{
     NTN_Print_Init();
#if(DS3231_DEVICE == ON)
     NTN_DS3231_Clock_Init();
#endif
     NTN_PRINT_START();
}
void NTN_System_Handler()
{
#if(DS3231_DEVICE == ON)
  NTN_DS3231_Clock_Handler();
#endif
}