#include "OptionMode.h"
#include "HomeMode.h"
#include "PlayMode.h"
#include "PauseMode.h"

//////////////////////////////////// Start Mode Option
// Specifies the mode to run first when the program starts.
//You must include the mode header file, and declare the mode class and mode's instance.

Option_Mode OptionMode;
Option_Mode* Option_Mode::M_Inst;

Home_Mode HomeMode;
Home_Mode* Home_Mode::M_Inst;

Play_Mode PlayMode;
Play_Mode* Play_Mode::M_Inst;

Pause_Mode PauseMode;
Pause_Mode* Pause_Mode::M_Inst;

START_MODE_PTR START_MODE = HomeMode.Start;