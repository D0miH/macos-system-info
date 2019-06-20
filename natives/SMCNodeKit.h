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
    Napi::Value GetCPUTempWrapper(const Napi::CallbackInfo& info);
    SMCKit *smcKit_;
};

#endif