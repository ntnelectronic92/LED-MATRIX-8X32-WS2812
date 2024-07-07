#include "NTN_App.h"
#include "NTN_System.h"
void setup()
{
  NTN_APP_Int();
  NTN_System_Int();
}

void loop()
{
   //NTN_PRINT_START();
   NTN_APP_Handler(); 
   NTN_System_Handler();
}
