# Experiments with Node.js addon patterns

[![Build Status](https://travis-ci.org/platy/nodejs-addon-patterns.svg)](https://travis-ci.org/platy/nodejs-addon-patterns)

I'm learning about how to make node.js addons (and a whole bunch of related stuff). This repository is for the stuff 
I need to try out in isolation from the other projects I'm working on.

### uv_thread

The first one is running a worker thread using libuv, which calls back to javascript with it's results over the course of its 
execution, on the javascript side this is converted to a emit from an EventEmitter.

- It is static and so only allows the client to create one worker
- It can only emit one kind of event from the c++ side - this could be made more generic I think
- It seems far too complicated for what its doing
