#include "SMCNodeKit.h"

std::string testfunction::test() {
    return "Test";
}

Napi::String testfunction::TestWrapped(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::String returnValue = Napi::String::New(env, testfunction::test());
    return returnValue;
}

Napi::Object testfunction::Init(Napi::Env env, Napi::Object exports) {
    exports.Set("test", Napi::Function::New(env, testfunction::TestWrapped));
    return exports;
}