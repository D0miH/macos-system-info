#ifndef SYSTEM_INFO_H
#define SYSTEM_INFO_H

#include <nan.h>
#include "lib/System.h"

class SystemInfo : public Nan::ObjectWrap
{
public:
    static Nan::Persistent<v8::FunctionTemplate> constructor;

    static NAN_MODULE_INIT(Init);
    static NAN_METHOD(New);

    static NAN_METHOD(OpenWrapper);
    static NAN_METHOD(CloseWrapper);

    static NAN_METHOD(GetKeyInfoWrapper);

    static NAN_METHOD(GetMemoryUsageWrapper);
    static NAN_METHOD(GetTotalMemoryWrapper);

    static NAN_METHOD(GetCpuTempWrapper);
    static NAN_METHOD(GetCpuUsageWrapper);

    static NAN_METHOD(GetFanCountWrapper);
    static NAN_METHOD(GetMinFanSpeedWrapper);
    static NAN_METHOD(GetMaxFanSpeedWrapper);
    static NAN_METHOD(GetCurrentFanSpeedWrapper);

    static NAN_METHOD(GetBatteryCountWrapper);
    static NAN_METHOD(IsChargingBatteryWrapper);
    static NAN_METHOD(GetBatteryHealthWrapper);
    static NAN_METHOD(GetBatteryCyclesWrapper);

private:
    System *system;
};

#endif