#include <napi.h>
#include "SMCNodeKit.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    return SMCNodeKit::Init(env, exports);
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, InitAll)