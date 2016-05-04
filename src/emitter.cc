// FIXME : I've found the way this should be done using uv_async - an example is in github.com/relayr/node-bacnet
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

static Nan::Persistent<Object> listener;

void emitterSetListener(Local<Object> localListener) {
    listener.Reset(localListener);
}

// called by libuv worker in separate thread
static void EmitAsync(uv_work_t *req) {
    // TODO I'm not actually using the worker - there should be some other libuv feature for just adding to the loop
}

// called by libuv in event loop when async function completes
static void EmitAsyncComplete(uv_work_t *req,int status) {
    Nan::HandleScope scope;

    Event *work = static_cast<Event *>(req->data);

    // set up return arguments
    Local<Value> argv[] = {
        Nan::New(work->eventId.c_str()).ToLocalChecked(),
        Nan::New(work->message.c_str()).ToLocalChecked()
    };

    Local<Object> eventEmitter = Nan::New(listener);
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
