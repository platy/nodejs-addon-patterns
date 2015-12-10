const uv_thread = require('./uv_thread.js')

uv_thread.on('message', console.log)

uv_thread.start(10)

setTimeout(function () {}, 5000)
