#include "SystemInfo.h"
#include <iostream>

Nan::Persistent<v8::FunctionTemplate> SystemInfo::constructor;

NAN_MODULE_INIT(SystemInfo::Init)
{
    v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(SystemInfo::New);
    constructor.Reset(ctor);
    ctor->InstanceTemplate()->SetInternalFieldCount(1);
    ctor->SetClassName(Nan::New("SystemInfo").ToLocalChecked());

    Nan::SetPrototypeMethod(ctor, "open", OpenWrapper);
    Nan::SetPrototypeMethod(ctor, "close", CloseWrapper);
    Nan::SetPrototypeMethod(ctor, "getKeyInfo", GetKeyInfoWrapper);
    Nan::SetPrototypeMethod(ctor, "getMemoryUsage", GetMemoryUsageWrapper);
    Nan::SetPrototypeMethod(ctor, "getCpuTemp", GetCpuTempWrapper);
    Nan::SetPrototypeMethod(ctor, "getCpuUsage", GetCpuUsageWrapper);
    Nan::SetPrototypeMethod(ctor, "getFanCount", GetFanCountWrapper);
    Nan::SetPrototypeMethod(ctor, "getMinFanSpeed", GetMinFanSpeedWrapper);
    Nan::SetPrototypeMethod(ctor, "getMaxFanSpeed", GetMaxFanSpeedWrapper);
    Nan::SetPrototypeMethod(ctor, "getCurrentFanSpeed", GetCurrentFanSpeedWrapper);
    Nan::SetPrototypeMethod(ctor, "getBatteryCount", GetBatteryCountWrapper);
    Nan::SetPrototypeMethod(ctor, "isChargingBattery", IsChargingBatteryWrapper);
    Nan::SetPrototypeMethod(ctor, "getBatteryHealth", GetBatteryHealthWrapper);
    Nan::SetPrototypeMethod(ctor, "getBatteryCycles", GetBatteryCyclesWrapper);

    Nan::Set(target, Nan::New("SystemInfo").ToLocalChecked(), Nan::GetFunction(ctor).ToLocalChecked());
}

NAN_METHOD(SystemInfo::New)
{
    // if there were arguments given throw an exception
    if (info.Length() != 0)
    {
        Nan::ThrowError(Nan::New("No arguments expected").ToLocalChecked());
    }

    // create the instance and wrap it
    SystemInfo *systemInfo = new SystemInfo();
    systemInfo->Wrap(info.Holder());

    // create an system instance
    systemInfo->system = new System();

    info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(SystemInfo::OpenWrapper)
{
    // unwrap the instance
    SystemInfo *self = Nan::ObjectWrap::Unwrap<SystemInfo>(info.This());

    if (info.Length() != 0)
    {
        return Nan::ThrowError(Nan::New("No arguments expected").ToLocalChecked());
    }

    try
    {
        self->system->open();
        return;
    }
    catch (const std::runtime_error &e)
    {
        return Nan::ThrowError(Nan::New(e.what()).ToLocalChecked());
    }
}

NAN_METHOD(SystemInfo::CloseWrapper)
{
    // unwrap the instance
    SystemInfo *self = Nan::ObjectWrap::Unwrap<SystemInfo>(info.This());

    if (info.Length() != 0)
    {
        return Nan::ThrowError(Nan::New("No arguments expected").ToLocalChecked());
    }

    try
    {
        self->system->close();
        return;
    }
    catch (const std::runtime_error &e)
    {
        return Nan::ThrowError(Nan::New(e.what()).ToLocalChecked());
    }
}

NAN_METHOD(SystemInfo::GetKeyInfoWrapper)
{
    // unwrap the instance
    SystemInfo *self = Nan::ObjectWrap::Unwrap<SystemInfo>(info.This());

    if (info.Length() != 1 || !info[0]->IsString())
    {
        return Nan::ThrowError(Nan::New("Expected a SMC key").ToLocalChecked());
    }

    v8::Local<v8::Context> context = Nan::GetCurrentContext();

    try
    {
        DataType keyInfo = self->system->getKeyInfo(std::string(*Nan::Utf8String(info[0]->ToString(context).ToLocalChecked())));
        v8::Local<v8::String> fourCharCode = v8::String::NewFromUtf8(
                                                 context->GetIsolate(),
                                                 Utils::fourCharCodeToString(keyInfo.type).c_str(),
                                                 v8::NewStringType::kNormal)
                                                 .ToLocalChecked();
        v8::Local<v8::Value> size = Nan::New(keyInfo.size);

        // create the return object and assign the values
        v8::Local<v8::Object> returnObject = v8::Object::New(context->GetIsolate());
        bool setType = returnObject->Set(
                                       context,
                                       v8::String::NewFromUtf8(context->GetIsolate(), "type", v8::NewStringType::kNormal).ToLocalChecked(),
                                       fourCharCode)
                           .FromMaybe(false);
        bool setSize = returnObject->Set(
                                       context,
                                       v8::String::NewFromUtf8(context->GetIsolate(), "size", v8::NewStringType::kNormal).ToLocalChecked(),
                                       size)
                           .FromMaybe(false);

        if (!setType || !setSize)
        {
            // if it failed to set the values throw an exception
            return Nan::ThrowError(Nan::New("Failed to create the return object").ToLocalChecked());
        }

        info.GetReturnValue().Set(returnObject);
    }
    catch (const std::runtime_error &e)
    {
        return Nan::ThrowError(Nan::New(e.what()).ToLocalChecked());
    }
}

NAN_METHOD(SystemInfo::GetMemoryUsageWrapper)
{

    // unwrap the instance
    SystemInfo *self = Nan::ObjectWrap::Unwrap<SystemInfo>(info.This());

    if (info.Length() != 0)
    {
        return Nan::ThrowError(Nan::New("No arguments expected").ToLocalChecked());
    }

    try
    {
        std::vector<float> memUsage = self->system->getMemoryUsage();
        v8::Local<v8::Array> result = Nan::New<v8::Array>(4);
        Nan::Set(result, 0, Nan::New(memUsage[0]));
        Nan::Set(result, 1, Nan::New(memUsage[1]));
        Nan::Set(result, 2, Nan::New(memUsage[2]));
        Nan::Set(result, 3, Nan::New(memUsage[3]));
        Nan::Set(result, 4, Nan::New(memUsage[4]));

        info.GetReturnValue().Set(result);
        return;
    }
    catch (const std::runtime_error &e)
    {
        return Nan::ThrowError(Nan::New(e.what()).ToLocalChecked());
    }
}

NAN_METHOD(SystemInfo::GetCpuTempWrapper)
{
    // unwrap the instance
    SystemInfo *self = Nan::ObjectWrap::Unwrap<SystemInfo>(info.This());

    if (info.Length() != 0)
    {
        return Nan::ThrowError(Nan::New("No arguments expected").ToLocalChecked());
    }

    try
    {
        info.GetReturnValue().Set(self->system->getCpuTemp());
        return;
    }
    catch (const std::runtime_error &e)
    {
        return Nan::ThrowError(Nan::New(e.what()).ToLocalChecked());
    }
}

NAN_METHOD(SystemInfo::GetCpuUsageWrapper)
{
    // unwrap the instance
    SystemInfo *self = Nan::ObjectWrap::Unwrap<SystemInfo>(info.This());

    if (info.Length() != 0)
    {
        return Nan::ThrowError(Nan::New("No arguments expected").ToLocalChecked());
    }

    try
    {
        std::vector<float> cpuUsage = self->system->getCpuUsage();
        v8::Local<v8::Array> result = Nan::New<v8::Array>(4);
        Nan::Set(result, 0, Nan::New(cpuUsage[0]));
        Nan::Set(result, 1, Nan::New(cpuUsage[1]));
        Nan::Set(result, 2, Nan::New(cpuUsage[2]));
        Nan::Set(result, 3, Nan::New(cpuUsage[3]));

        info.GetReturnValue().Set(result);
        return;
    }
    catch (const std::runtime_error &e)
    {
        return Nan::ThrowError(Nan::New(e.what()).ToLocalChecked());
    }
}

NAN_METHOD(SystemInfo::GetFanCountWrapper)
{
    // unwrap the instance
    SystemInfo *self = Nan::ObjectWrap::Unwrap<SystemInfo>(info.This());

    if (info.Length() != 0)
    {
        return Nan::ThrowError(Nan::New("No arguments expected").ToLocalChecked());
    }

    try
    {
        info.GetReturnValue().Set(self->system->getFanCount());
        return;
    }
    catch (const std::runtime_error &e)
    {
        return Nan::ThrowError(Nan::New(e.what()).ToLocalChecked());
    }
}

NAN_METHOD(SystemInfo::GetMinFanSpeedWrapper)
{
    // unwrap the instance
    SystemInfo *self = Nan::ObjectWrap::Unwrap<SystemInfo>(info.This());

    if (info.Length() == 0 || !info[0]->IsNumber())
    {
        return Nan::ThrowError(Nan::New("Expected the id of the fan").ToLocalChecked());
    }

    try
    {
        int fanId = info[0]->IntegerValue(Nan::GetCurrentContext()).FromMaybe(-1);

        // check if the fan id is out of bound
        int fanCount = self->system->getFanCount();
        if (fanCount <= fanId)
        {
            throw std::runtime_error(
                std::string("Fan ID is too high. This machine has only ") +
                std::to_string(fanCount) +
                std::string(" fans."));
        }

        info.GetReturnValue().Set(self->system->getMinFanSpeed(fanId));
        return;
    }
    catch (const std::runtime_error &e)
    {
        return Nan::ThrowError(Nan::New(e.what()).ToLocalChecked());
    }
}

NAN_METHOD(SystemInfo::GetMaxFanSpeedWrapper)
{
    // unwrap the instance
    SystemInfo *self = Nan::ObjectWrap::Unwrap<SystemInfo>(info.This());

    if (info.Length() == 0 || !info[0]->IsNumber())
    {
        return Nan::ThrowError(Nan::New("Expected the id of the fan").ToLocalChecked());
    }

    try
    {
        int fanId = info[0]->IntegerValue(Nan::GetCurrentContext()).FromMaybe(-1);

        // check if the fan id is out of bound
        int fanCount = self->system->getFanCount();
        if (fanCount <= fanId)
        {
            throw std::runtime_error(
                std::string("Fan ID is too high. This machine has only ") +
                std::to_string(fanCount) +
                std::string(" fans."));
        }

        info.GetReturnValue().Set(self->system->getMaxFanSpeed(fanId));
        return;
    }
    catch (const std::runtime_error &e)
    {
        return Nan::ThrowError(Nan::New(e.what()).ToLocalChecked());
    }
}

NAN_METHOD(SystemInfo::GetCurrentFanSpeedWrapper)
{
    // unwrap the instance
    SystemInfo *self = Nan::ObjectWrap::Unwrap<SystemInfo>(info.This());

    if (info.Length() == 0 || !info[0]->IsNumber())
    {
        return Nan::ThrowError(Nan::New("Expected the id of the fan").ToLocalChecked());
    }

    try
    {
        int fanId = info[0]->IntegerValue(Nan::GetCurrentContext()).FromMaybe(-1);

        // check if the fan id is out of bound
        int fanCount = self->system->getFanCount();
        if (fanCount <= fanId)
        {
            throw std::runtime_error(
                std::string("Fan ID is too high. This machine has only ") +
                std::to_string(fanCount) +
                std::string(" fans."));
        }

        info.GetReturnValue().Set(self->system->getCurrentFanSpeed(fanId));
        return;
    }
    catch (const std::runtime_error &e)
    {
        return Nan::ThrowError(Nan::New(e.what()).ToLocalChecked());
    }
}

NAN_METHOD(SystemInfo::GetBatteryCountWrapper)
{
    // unwrap the instance
    SystemInfo *self = Nan::ObjectWrap::Unwrap<SystemInfo>(info.This());

    if (info.Length() != 0)
    {
        return Nan::ThrowError(Nan::New("No arguments expected").ToLocalChecked());
    }

    try
    {
        info.GetReturnValue().Set(self->system->getBatteryCount());
        return;
    }
    catch (const std::runtime_error &e)
    {
        return Nan::ThrowError(Nan::New(e.what()).ToLocalChecked());
    }
}

NAN_METHOD(SystemInfo::IsChargingBatteryWrapper)
{
    // unwrap the instance
    SystemInfo *self = Nan::ObjectWrap::Unwrap<SystemInfo>(info.This());

    if (info.Length() != 0)
    {
        return Nan::ThrowError(Nan::New("No arguments expected").ToLocalChecked());
    }

    try
    {
        info.GetReturnValue().Set(self->system->isChargingBattery());
        return;
    }
    catch (const std::runtime_error &e)
    {
        return Nan::ThrowError(Nan::New(e.what()).ToLocalChecked());
    }
}

NAN_METHOD(SystemInfo::GetBatteryHealthWrapper)
{
    // unwrap the instance
    SystemInfo *self = Nan::ObjectWrap::Unwrap<SystemInfo>(info.This());

    if (info.Length() != 0)
    {
        return Nan::ThrowError(Nan::New("No arguments expected").ToLocalChecked());
    }

    try
    {
        info.GetReturnValue().Set(self->system->getBatteryHealth());
        return;
    }
    catch (const std::runtime_error &e)
    {
        return Nan::ThrowError(Nan::New(e.what()).ToLocalChecked());
    }
}

NAN_METHOD(SystemInfo::GetBatteryCyclesWrapper)
{
    // unwrap the instance
    SystemInfo *self = Nan::ObjectWrap::Unwrap<SystemInfo>(info.This());

    if (info.Length() != 0)
    {
        return Nan::ThrowError(Nan::New("No arguments expected").ToLocalChecked());
    }

    try
    {
        info.GetReturnValue().Set(self->system->getBatteryCycles());
        return;
    }
    catch (const std::runtime_error &e)
    {
        return Nan::ThrowError(Nan::New(e.what()).ToLocalChecked());
    }
}
