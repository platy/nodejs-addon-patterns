
#ifndef EMITTER_H
#define EMITTER_H

#include <stdint.h>
#include <string.h>
#include <v8.h>

void queueEmit(std::string event, std::string message);
void emitterSetListener(v8::Local<v8::Object> listener);

#endif
