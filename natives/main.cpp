#include <nan.h>
#include "SMCNodeKit.h"

NAN_MODULE_INIT(InitModule)
{
    SMCNodeKit::Init(target);
}

NODE_MODULE(myModule, InitModule);