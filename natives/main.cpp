#include <nan.h>
#include "SystemInfo.h"

NAN_MODULE_INIT(InitModule)
{
    SystemInfo::Init(target);
}

NODE_MODULE(myModule, InitModule);