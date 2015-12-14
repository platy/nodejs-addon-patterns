
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <v8.h>
#include <uv.h>
#include "functions.h"

using namespace v8;

struct Event {
  uv_work_t  request;
  std::string eventId;
  std::string message;
};

static Persistent<Object> listener;

void emitterSetListener(Isolate* isolate, Local<Object> localListener) {
    listener.Reset(isolate, localListener);
}

// called by libuv worker in separate thread
static void EmitAsync(uv_work_t *req) {
    // TODO I'm not actually using the worker - there should be some other libuv feature for just adding to the loop
}

// called by libuv in event loop when async function completes
static void EmitAsyncComplete(uv_work_t *req,int status) {
    Isolate * isolate = Isolate::GetCurrent();
    HandleScope handleScope(isolate);

    Event *work = static_cast<Event *>(req->data);

    // set up return arguments
    Local<Value> argv[] = {
        String::NewFromUtf8(isolate, work->eventId.c_str()),
        String::NewFromUtf8(isolate, work->message.c_str())
    };

    Local<Object> eventEmitter = Local<Object>::New(isolate, listener);
    Nan::MakeCallback(eventEmitter, "emit", 2, argv);

    delete work;
}

void queueEmit(std::string eventId, std::string message) {
  Event *event = new Event();
  event->request.data = event;
  event->eventId = eventId;
  event->message = message;

  uv_queue_work(uv_default_loop(),&event->request,EmitAsync,EmitAsyncComplete);
}
