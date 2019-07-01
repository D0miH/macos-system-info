#include "SMCNodeKit.h"
#include <iostream>

Nan::Persistent<v8::FunctionTemplate> SMCNodeKit::constructor;

NAN_MODULE_INIT(SMCNodeKit::Init)
{
    v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(SMCNodeKit::New);
    constructor.Reset(ctor);
    ctor->InstanceTemplate()->SetInternalFieldCount(1);
    ctor->SetClassName(Nan::New("SMCNodeKit").ToLocalChecked());

    Nan::SetPrototypeMethod(ctor, "open", OpenWrapper);
    Nan::SetPrototypeMethod(ctor, "close", CloseWrapper);
    Nan::SetPrototypeMethod(ctor, "getKeyInfo", GetKeyInfoWrapper);
    Nan::SetPrototypeMethod(ctor, "getCpuTemp", GetCpuTempWrapper);
    Nan::SetPrototypeMethod(ctor, "getFanCount", GetFanCountWrapper);
    Nan::SetPrototypeMethod(ctor, "getMinFanSpeed", GetMinFanSpeedWrapper);
    Nan::SetPrototypeMethod(ctor, "getMaxFanSpeed", GetMaxFanSpeedWrapper);
    Nan::SetPrototypeMethod(ctor, "getCurrentFanSpeed", GetCurrentFanSpeedWrapper);
    Nan::SetPrototypeMethod(ctor, "getBatteryCount", GetBatteryCountWrapper);
    Nan::SetPrototypeMethod(ctor, "isChargingBattery", IsChargingBatterWrapper);

    Nan::Set(target, Nan::New("SMCNodeKit").ToLocalChecked(), Nan::GetFunction(ctor).ToLocalChecked());
}

NAN_METHOD(SMCNodeKit::New)
{
    // if there were arguments given throw an exception
    if (info.Length() != 0)
    {
        Nan::ThrowError(Nan::New("No arguments expected").ToLocalChecked());
    }

    // create the instance and wrap it
    SMCNodeKit *nodeKit = new SMCNodeKit();
    nodeKit->Wrap(info.Holder());

    // create an SMCKit instance
    nodeKit->smcKit = new SMCKit();

    info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(SMCNodeKit::OpenWrapper)
{
    // unwrap the instance
    SMCNodeKit *self = Nan::ObjectWrap::Unwrap<SMCNodeKit>(info.This());

    if (info.Length() != 0)
    {
        return Nan::ThrowError(Nan::New("No arguments expected").ToLocalChecked());
    }

    try
    {
        self->smcKit->open();
        return;
    }
    catch (const std::runtime_error &e)
    {
        return Nan::ThrowError(Nan::New(e.what()).ToLocalChecked());
    }
}

NAN_METHOD(SMCNodeKit::CloseWrapper)
{
    // unwrap the instance
    SMCNodeKit *self = Nan::ObjectWrap::Unwrap<SMCNodeKit>(info.This());

    if (info.Length() != 0)
    {
        return Nan::ThrowError(Nan::New("No arguments expected").ToLocalChecked());
    }

    try
    {
        self->smcKit->close();
        return;
    }
    catch (const std::runtime_error &e)
    {
        return Nan::ThrowError(Nan::New(e.what()).ToLocalChecked());
    }
}

NAN_METHOD(SMCNodeKit::GetKeyInfoWrapper)
{
    // unwrap the instance
    SMCNodeKit *self = Nan::ObjectWrap::Unwrap<SMCNodeKit>(info.This());

    if (info.Length() != 1 || !info[0]->IsString())
    {
        return Nan::ThrowError(Nan::New("Expected a SMC key").ToLocalChecked());
    }

    v8::Local<v8::Context> context = Nan::GetCurrentContext();

    try
    {
        DataType keyInfo = self->smcKit->getKeyInfo(std::string(*Nan::Utf8String(info[0]->ToString(context).ToLocalChecked())));
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

NAN_METHOD(SMCNodeKit::GetCpuTempWrapper)
{
    // unwrap the instance
    SMCNodeKit *self = Nan::ObjectWrap::Unwrap<SMCNodeKit>(info.This());

    if (info.Length() != 0)
    {
        return Nan::ThrowError(Nan::New("No arguments expected").ToLocalChecked());
    }

    try
    {
        info.GetReturnValue().Set(self->smcKit->getCPUTemp());
        return;
    }
    catch (const std::runtime_error &e)
    {
        return Nan::ThrowError(Nan::New(e.what()).ToLocalChecked());
    }
}

NAN_METHOD(SMCNodeKit::GetFanCountWrapper)
{
    // unwrap the instance
    SMCNodeKit *self = Nan::ObjectWrap::Unwrap<SMCNodeKit>(info.This());

    if (info.Length() != 0)
    {
        return Nan::ThrowError(Nan::New("No arguments expected").ToLocalChecked());
    }

    try
    {
        info.GetReturnValue().Set(self->smcKit->getFanCount());
        return;
    }
    catch (const std::runtime_error &e)
    {
        return Nan::ThrowError(Nan::New(e.what()).ToLocalChecked());
    }
}

NAN_METHOD(SMCNodeKit::GetMinFanSpeedWrapper)
{
    // unwrap the instance
    SMCNodeKit *self = Nan::ObjectWrap::Unwrap<SMCNodeKit>(info.This());

    if (info.Length() == 0 || !info[0]->IsNumber())
    {
        return Nan::ThrowError(Nan::New("Expected the id of the fan").ToLocalChecked());
    }

    try
    {
        int fanId = info[0]->IntegerValue(Nan::GetCurrentContext()).FromMaybe(-1);

        // check if the fan id is out of bound
        int fanCount = self->smcKit->getFanCount();
        if (fanCount <= fanId)
        {
            throw std::runtime_error(
                std::string("Fan ID is too high. This machine has only ") +
                std::to_string(fanCount) +
                std::string(" fans."));
        }

        info.GetReturnValue().Set(self->smcKit->getMinFanSpeed(fanId));
        return;
    }
    catch (const std::runtime_error &e)
    {
        return Nan::ThrowError(Nan::New(e.what()).ToLocalChecked());
    }
}

NAN_METHOD(SMCNodeKit::GetMaxFanSpeedWrapper)
{
    // unwrap the instance
    SMCNodeKit *self = Nan::ObjectWrap::Unwrap<SMCNodeKit>(info.This());

    if (info.Length() == 0 || !info[0]->IsNumber())
    {
        return Nan::ThrowError(Nan::New("Expected the id of the fan").ToLocalChecked());
    }

    try
    {
        int fanId = info[0]->IntegerValue(Nan::GetCurrentContext()).FromMaybe(-1);

        // check if the fan id is out of bound
        int fanCount = self->smcKit->getFanCount();
        if (fanCount <= fanId)
        {
            throw std::runtime_error(
                std::string("Fan ID is too high. This machine has only ") +
                std::to_string(fanCount) +
                std::string(" fans."));
        }

        info.GetReturnValue().Set(self->smcKit->getMaxFanSpeed(fanId));
        return;
    }
    catch (const std::runtime_error &e)
    {
        return Nan::ThrowError(Nan::New(e.what()).ToLocalChecked());
    }
}

NAN_METHOD(SMCNodeKit::GetCurrentFanSpeedWrapper)
{
    // unwrap the instance
    SMCNodeKit *self = Nan::ObjectWrap::Unwrap<SMCNodeKit>(info.This());

    if (info.Length() == 0 || !info[0]->IsNumber())
    {
        return Nan::ThrowError(Nan::New("Expected the id of the fan").ToLocalChecked());
    }

    try
    {
        int fanId = info[0]->IntegerValue(Nan::GetCurrentContext()).FromMaybe(-1);

        // check if the fan id is out of bound
        int fanCount = self->smcKit->getFanCount();
        if (fanCount <= fanId)
        {
            throw std::runtime_error(
                std::string("Fan ID is too high. This machine has only ") +
                std::to_string(fanCount) +
                std::string(" fans."));
        }

        info.GetReturnValue().Set(self->smcKit->getCurrentFanSpeed(fanId));
        return;
    }
    catch (const std::runtime_error &e)
    {
        return Nan::ThrowError(Nan::New(e.what()).ToLocalChecked());
    }
}

NAN_METHOD(SMCNodeKit::GetBatteryCountWrapper)
{
    // unwrap the instance
    SMCNodeKit *self = Nan::ObjectWrap::Unwrap<SMCNodeKit>(info.This());

    if (info.Length() != 0)
    {
        return Nan::ThrowError(Nan::New("No arguments expected").ToLocalChecked());
    }

    try
    {
        info.GetReturnValue().Set(self->smcKit->getBatteryCount());
        return;
    }
    catch (const std::runtime_error &e)
    {
        return Nan::ThrowError(Nan::New(e.what()).ToLocalChecked());
    }
}

NAN_METHOD(SMCNodeKit::IsChargingBatteryWrapper)
{
    // unwrap the instance
    SMCNodeKit *self = Nan::ObjectWrap::Unwrap<SMCNodeKit>(info.This());

    if (info.Length() != 0)
    {
        return Nan::ThrowError(Nan::New("No arguments expected").ToLocalChecked());
    }

    try
    {
        info.GetReturnValue().Set(self->smcKit->isChargingBattery());
        return;
    }
    catch (const std::runtime_error &e)
    {
        return Nan::ThrowError(Nan::New(e.what()).ToLocalChecked());
    }
}
