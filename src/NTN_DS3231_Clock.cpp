
#include "NTN_DS3231_Clock.h"
RTC_DS3231 rtc;
NTN_TIME timeCurrent;
void NTN_DS3231_Clock_Init()
{
  if (! rtc.begin()) {
    NTN_PRINTF("Couldn't find RTC");
    while (1) delay(10);
  }

  if (rtc.lostPower()) 
  {
   NTN_PRINTF("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}
void NTN_DS3231_Clock_Handler()
{
    DateTime now = rtc.now();
    NTN_PRINTF("%d / %d / %d : %d :%d : %d \r\n",now.year(), now.month(),now.day(), now.hour(), now.minute(), now.second());
    timeCurrent.hour = now.hour();
    timeCurrent.minutes = now.minute();
    timeCurrent.second = now.second();
}
NTN_TIME NTN_DS3231_Clock_GetCurrentTime()
{
  return timeCurrent;
}
DateTime NTN_DS3231_Clock_Get_Date_Time()
{
  return  rtc.now();
}