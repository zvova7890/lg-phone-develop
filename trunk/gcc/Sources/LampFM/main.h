#ifndef __MAIN_H__
#define __MAIN_H__

#include <Ui/EventManager.h>
#include <Ui/ActiveList.h>
#include "ResourceManager.h"
#include "EffectManager.h"
#include "ExtManager.h"
#include "FSProtocol.h"


EventManager & eventManager();
ResourceManager & resourceManager();
ExtManager & extensionManager();
UActiveArea & mainActiveArea();
FSProtocolsContainer & protocolsContainer();

#endif // __MAIN_H__
