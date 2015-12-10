#include "functions.h"

using v8::FunctionTemplate;

NAN_MODULE_INIT(InitAll) {
  Nan::Set(target, Nan::New("start").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(start)).ToLocalChecked());
  Nan::Set(target, Nan::New("setListener").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(setListener)).ToLocalChecked());
}

NODE_MODULE(binding, InitAll)
