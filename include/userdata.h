#ifndef USERDATA_H
#define USERDATA_H

#include <Preferences.h>

void init_UserData(void);
void Save_UserData(String inputText);

extern Preferences preferences;
extern String stringView;

#endif // USERDATA_H