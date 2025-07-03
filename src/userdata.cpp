#include <Preferences.h>

Preferences preferences;

void init_UserData(void)
{
   preferences.begin("UserData", false);
   if(preferences.getString("stringView") != stringView)
   {
     stringView = preferences.getString("stringView");
     stringView.toCharArray(charArray, stringView.length() + 1);
     Serial.printf("Load string: %s \r\n", charArray);
   }   
}

void Save_UserData(String inputText)
{
     preferences.putString("stringView", inputText);
     inputText.toCharArray(charArray, inputText.length() + 1);
     Serial.printf("Save string: %s \r\n", charArray);
}