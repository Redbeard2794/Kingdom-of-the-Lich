// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#ifndef STDAFX_H
#define STDAFX_H

//#Defines
#define SCREENWIDTH 800
#define SCREENHEIGHT 600


#include "targetver.h"

//SFML includes
#include "SFML\Graphics.hpp"
#include "SFML\OpenGL.hpp"
#include "SFML\Window\Keyboard.hpp"
#include "SFML/Audio.hpp"

//Standard includes
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>
#include <mutex>
#include <stdlib.h>     /* srand, rand */
//using std::atomic_int;
//using std::thread;

//project headers
#include "STP/TMXLoader.hpp"
#include "AudioManager.h"
#include "Player.h"
#include "Hud.h"
#include "Quest.h"
#include "QuestStage.h"
#include "Compass.h"
#include "Menu.h"
#include "ChooseRaceAndGenderMenu.h"
#include "Gamepad.h"
#include "ConfirmationDialogBox.h"
#include "Inventory.h"
#include "Chest.h"
#include "QuestController.h"
#include "Npc.h"
#include "CollidableObject.h"



#endif