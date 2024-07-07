#include "NTN_App.h"
void NTN_APP_Int()
{
    NTN_PRINT_START();
    NTN_Matrix_Ws2812_Init();
}
void NTN_APP_Handler()
{
   // NTN_PRINT_START();
    NTN_Matrix_Ws2812_Handle();
}