#include <stdint.h>
#include <iostream>
#include <uv.h>
#include <unistd.h>
#include "thread.h"
#include "emitter.h"


void runThread(void *arg) {
    int32_t numberOfMessages = *static_cast<int32_t*>(arg);
    int i;
    for (i=0; i<numberOfMessages; i++) {
        queueEmit("message", "Thread running");
        usleep(1*1000*1000);
    }
}

void startThread(int32_t numberOfMessages) {
    int *arg = new int32_t;
    *arg = numberOfMessages;
    uv_thread_t thread_id;
    uv_thread_create(&thread_id, runThread, arg);
}
