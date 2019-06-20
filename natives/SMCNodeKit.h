#ifndef SMC_NODE_KIT_H
#define SMC_NODE_KIT_H

#include <napi.h>
#include "SMCPPKit/SMCKit.h"

class SMCNodeKit : public Napi::ObjectWrap<SMCNodeKit> {
public:
    static Napi::Object Init(Napi::Env ennv, Napi::Object exports);
    SMCNodeKit(const Napi::CallbackInfo& info);
    SMCKit* GetInternalInstance();

private:
    static Napi::FunctionReference constructor;

    void OpenWrapper(const Napi::CallbackInfo& info);
    void CloseWrapper(const Napi::CallbackInfo& info);
    
    Napi::Value GetKeyInfoWrapper(const Napi::CallbackInfo& info);
    
    Napi::Value GetCPUTempWrapper(const Napi::CallbackInfo& info);
    
    Napi::Value GetFanCountWrapper(const Napi::CallbackInfo& info);
    Napi::Value GetFanMinSpeedWrapper(const Napi::CallbackInfo& info);
    Napi::Value GetFanMaxSpeedWrapper(const Napi::CallbackInfo& info);
    Napi::Value GetCurrentFanSpeedWrapper(const Napi::CallbackInfo& info);

    Napi::Value GetBatteryCountWrapper(const Napi::CallbackInfo& info);
    Napi::Value IsOnACWrapper(const Napi::CallbackInfo& info);

    SMCKit *smcKit_;
};

#endif