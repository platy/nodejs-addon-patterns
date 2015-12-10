
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <v8.h>
#include <uv.h>
#include "functions.h"

struct Event {
  uv_work_t  request;
  std::string message;
};

static v8::Persistent<v8::Object> listener;

void emitterSetListener(v8::Isolate* isolate, v8::Local<v8::Object> localListener) {
    listener.Reset(isolate, localListener);
}

// called by libuv worker in separate thread
static void EmitAsync(uv_work_t *req)
{
    // TODO I'm not actually using the worker - there should be some other libuv feature for just adding to the loop
}

// called by libuv in event loop when async function completes
static void EmitAsyncComplete(uv_work_t *req,int status)
{
    v8::Isolate * isolate = v8::Isolate::GetCurrent();

    // Fix for Node 4.x - thanks to https://github.com/nwjs/blink/commit/ecda32d117aca108c44f38c8eb2cb2d0810dfdeb
    v8::HandleScope handleScope(isolate);

    Event *work = static_cast<Event *>(req->data);

    // set up return arguments
    v8::Handle<v8::Value> argv[] = { v8::String::NewFromUtf8(isolate, work->message.c_str()) };

    // execute the callback
    // https://stackoverflow.com/questions/13826803/calling-javascript-function-from-a-c-callback-in-v8/28554065#28554065
    v8::Local<v8::Object> localCallback = v8::Local<v8::Object>::New(isolate, listener);
    localCallback->CallAsFunction(isolate->GetCurrentContext()->Global(), 1, argv);

    delete work;

}

void emitMessage(std::string message) {

  Event *event = new Event();
  event->request.data = event;
  event->message = message;

  uv_queue_work(uv_default_loop(),&event->request,EmitAsync,EmitAsyncComplete);
}
