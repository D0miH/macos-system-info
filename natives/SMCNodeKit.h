#include <napi.h>

namespace testfunction {
    std::string test();
    Napi::String TestWrapped(const Napi::CallbackInfo& info);

    Napi::Object Init(Napi::Env env, Napi::Object exports);
}