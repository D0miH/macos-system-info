#include "SMCNodeKit.h"

Napi::FunctionReference SMCNodeKit::constructor;

Napi::Object SMCNodeKit::Init(Napi::Env env, Napi::Object exports){
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "SMCNodeKit", {
        InstanceMethod("open", &SMCNodeKit::OpenWrapper),
        InstanceMethod("close", &SMCNodeKit::CloseWrapper),
        InstanceMethod("getKeyInfo", &SMCNodeKit::GetKeyInfoWrapper),
        InstanceMethod("getCPUTemp", &SMCNodeKit::GetCPUTempWrapper)
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("SMCNodeKit", func);
    return exports;
}

SMCNodeKit::SMCNodeKit(const Napi::CallbackInfo& info) : Napi::ObjectWrap<SMCNodeKit>(info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(info.Length() != 0) {
        Napi::TypeError::New(env, "No arguments expected").ThrowAsJavaScriptException();
    }

    this->smcKit_ = new SMCKit();
}

void SMCNodeKit::OpenWrapper(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(info.Length() != 0) {
        Napi::TypeError::New(env, "No arguments expected").ThrowAsJavaScriptException();
    }

    try {
        this->smcKit_->open();
        return;
    } catch(const std::runtime_error& e) {
        throw Napi::Error::New(env, e.what());
    }
}

void SMCNodeKit::CloseWrapper(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(info.Length() != 0) {
        Napi::TypeError::New(env, "No arguments expected").ThrowAsJavaScriptException();
    }

    try {
        this->smcKit_->close();
    } catch(const std::runtime_error& e) {
        throw Napi::Error::New(env, e.what());
    }
}

Napi::Value SMCNodeKit::GetKeyInfoWrapper(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(info.Length() != 1 || !info[0].IsString()) {
        Napi::TypeError::New(env, "Expected a SMC key").ThrowAsJavaScriptException();
    }

    Napi::String givenKey = info[0].As<Napi::String>();
    DataType keyInfo = this->smcKit_->getKeyInfo(givenKey);
    Napi::String fourCharCode = Napi::String::New(env, Utils::fourCharCodeToString(keyInfo.type));
    Napi::Number size = Napi::Number::New(env, keyInfo.size);

    // create the return object and assign the values
    Napi::Object returnObject = Napi::Object::New(env);
    returnObject.Set("type", fourCharCode);
    returnObject.Set("size", size);

    return returnObject;
}

Napi::Value SMCNodeKit::GetCPUTempWrapper(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if(info.Length() != 0) {
        Napi::TypeError::New(env, "No arguments expected").ThrowAsJavaScriptException();
    }

    try {
        int cpuTemp = this->smcKit_->getCPUTemp();
        return Napi::Number::New(env, cpuTemp);
    } catch (const std::runtime_error& e) {
        throw Napi::Error::New(env, e.what());
    }
}

SMCKit* SMCNodeKit::GetInternalInstance() {
    return this->smcKit_;
}