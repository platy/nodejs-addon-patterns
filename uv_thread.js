const EventEmitter = require('events')
const uv_thread_addon = require('./build/Release/binding.node')

const uv_thread_interface = new EventEmitter()

uv_thread_addon.setListener(function (message) {
  uv_thread_interface.emit('message', message)
})
uv_thread_interface.start = uv_thread_addon.start

module.exports = uv_thread_interface
