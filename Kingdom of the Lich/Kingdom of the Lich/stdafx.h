// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#ifndef STDAFX_H
#define STDAFX_H

//#Defines

#include "targetver.h"
#define SCREENWIDTH 800
#define SCREENHEIGHT 600

//SFML includes
#include "SFML\Graphics.hpp"
#include "SFML\OpenGL.hpp"
#include "SFML\Window\Keyboard.hpp"
#include "SFML/Audio.hpp"

//Standard includes
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>
#include <mutex>
#include <stdlib.h>     /* srand, rand */
//using std::atomic_int;
//using std::thread;

//project headers
#include "PopupMessageController.h"
#include "PopupMessage.h"
#include "SplashScreen.h"
#include "Credits.h"
#include "STP/TMXLoader.hpp"
#include "AudioManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Hud.h"
#include "Quest.h"
#include "QuestStage.h"
#include "Compass.h"
#include "Menu.h"
#include "ChooseRaceAndGenderMenu.h"
#include "CombatMenu.h"
#include "Gamepad.h"
#include "ConfirmationDialogBox.h"
#include "Inventory.h"
#include "ItemSlot.h"
#include "Chest.h"
#include "QuestController.h"
#include "Npc.h"
#include "CollidableObject.h"
#include "DamageCalculator.h"
#include "Area.h"
#include "AreaManager.h"
#include "Door.h"
#include "Attack.h"
#include "OptionsMenu.h"
#include "Emitter.h"
#include "FootprintEmitter.h"
#include "BloodEmitter.h"
#include "Particle.h"
#include "FootprintParticle.h"
#include "BloodParticle.h"
#include "Subject.h"
#include "Observer.h"
#include "Achievement.h"
#include "AchievementTracker.h"
#include "Item.h"
#include "ShopInventory.h"
#include "SaveManager.h"
#include "PauseMenu.h"


#endif