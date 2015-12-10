// for addon
#include <node.h>
#include <v8.h>
#include <string>
#include <iostream>
#include "functions.h"
#include "emitter.h"
#include "thread.h"


// start(numberOfMessages)
// starts the worker thread which sends the specified number of messages back to the event loop
NAN_METHOD(start) {
  v8::Isolate* isolate = info.GetIsolate();
  v8::HandleScope scope(isolate);

  int32_t numberOfMessages = info[0]->ToInt32()->Value();
  startThread(numberOfMessages);
  info.GetReturnValue().Set(Undefined(isolate));
}

// setListener(listener)
// register the listener which receives the messages
NAN_METHOD(setListener) {
  v8::Isolate* isolate = info.GetIsolate();
  v8::HandleScope scope(isolate);

  v8::Local<v8::Object> localListener = info[0]->ToObject();
  emitterSetListener(isolate, localListener);

  info.GetReturnValue().Set(Undefined(isolate));
}
