#ifndef __MAIN_H__
#define __MAIN_H__

#include "EventManager.h"
#include "ActiveList.h"
#include "GlobalMenu.h"
#include "ResourceManager.h"
#include "EffectManager.h"
#include "ExtManager.h"



EventManager & eventManager();
ResourceManager & resourceManager();
ExtManager & extensionManager();
UActiveArea & mainActiveArea();

#endif // __MAIN_H__
