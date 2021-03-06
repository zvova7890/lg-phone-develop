#ifndef __MAIN_H__
#define __MAIN_H__

#include <EventManager.h>
#include <Widget.h>
#include "ResourceManager.h"
#include "EffectManager.h"
#include "ExtManager.h"
#include "FSProtocol.h"



EventManager & eventManager();
ResourceManager & resourceManager();
ExtManager & extensionManager();
Widget & mainWidget();
FSProtocolsContainer & protocolsContainer();


#endif // __MAIN_H__
