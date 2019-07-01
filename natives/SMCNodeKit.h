#ifndef SMC_NODE_KIT_H
#define SMC_NODE_KIT_H

#include <nan.h>
#include "SMCPPKit/SMCKit.h"

class SMCNodeKit : public Nan::ObjectWrap
{
public:
    static Nan::Persistent<v8::FunctionTemplate> constructor;

    static NAN_MODULE_INIT(Init);
    static NAN_METHOD(New);

    static NAN_METHOD(OpenWrapper);
    static NAN_METHOD(CloseWrapper);

    static NAN_METHOD(GetKeyInfoWrapper);

    static NAN_METHOD(GetCpuTempWrapper);

    static NAN_METHOD(GetFanCountWrapper);
    static NAN_METHOD(GetMinFanSpeedWrapper);
    static NAN_METHOD(GetMaxFanSpeedWrapper);
    static NAN_METHOD(GetCurrentFanSpeedWrapper);

    static NAN_METHOD(GetBatteryCountWrapper);
    static NAN_METHOD(IsChargingBatterWrapper);

private:
    SMCKit *smcKit;
};

#endif