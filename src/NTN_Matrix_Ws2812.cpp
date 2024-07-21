#include "NTN_Matrix_Ws2812.h"
String stringView = "hh:mm";
int16_t lengthTextForViewScroll;
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(COLUMNS, ROWS, PIN_DATA,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS,
  NEO_GRB            + NEO_KHZ800);
int startView = 0;
int indexColor = 0;
char charArray[100];
const uint16_t colorsText[] =
{
  matrix.Color(204, 0, 204),
  matrix.Color(204, 204, 0),
  matrix.Color(0, 255, 255),
  matrix.Color(255, 10, 127),
  matrix.Color(0, 0, 255),
  matrix.Color(0, 255, 0),
  matrix.Color(255, 99, 255)
};
void NTN_Matrix_Ws2812_DisplayClock()
{
    NTN_TIME timeGet ={0};
    static uint8_t lastMinute =  timeGet.minutes;
    char formatFullClock[] = "hh:mm";
    char formatNoneClock[] = "hh mm";
    timeGet = NTN_DS3231_Clock_GetCurrentTime();
    NTN_PRINTF("%d: %d : %d \r\n", timeGet.hour, timeGet.minutes, timeGet.second);
    if(lastMinute!= timeGet.minutes)
    {
       lastMinute = timeGet.minutes;
       if (++indexColor >= 8) indexColor = 0;
       matrix.setTextColor(colorsText[indexColor]);
    }
    // Start Display.
    matrix.fillScreen(0);
    matrix.setCursor(2, 0);
    if(timeGet.second%2)
    {
       NTN_DS3231_Clock_Get_Date_Time().toString(formatFullClock);
       matrix.print(formatFullClock);
    }
    else
    {
       NTN_DS3231_Clock_Get_Date_Time().toString(formatNoneClock);
       matrix.print(formatNoneClock);
    }
    matrix.show();
    delay(50); 
}
void NTN_Matrix_Ws2812_Init(void)
{
    NTN_PRINT_START();
    matrix.begin();
    matrix.setTextWrap(false);
    matrix.setBrightness(25);
    matrix.setTextColor(colorsText[0]);
    lengthTextForViewScroll = - (stringView.length() * WIDTH_FONT);
    startView = matrix.width();
}
void NTN_Matrix_Ws2812_RollingText()
{
    matrix.setCursor(startView, 0);
    matrix.print(stringView);
    if (--startView < lengthTextForViewScroll)
    {
    startView = matrix.width();
    if (++indexColor >= 8) indexColor = 0;
    matrix.setTextColor(colorsText[indexColor]);
    }
}
void NTN_Matrix_Ws2812_Handle(void)
{
#if(DS3231_DEVICE == ON)
    NTN_Matrix_Ws2812_DisplayClock();
#endif
}