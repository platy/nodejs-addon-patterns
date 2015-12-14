const EventEmitter = require('events').EventEmitter
const uv_thread_addon = require('./build/Release/binding.node')

const uv_thread_interface = new EventEmitter()

uv_thread_addon.setListener(uv_thread_interface)
uv_thread_interface.start = uv_thread_addon.start

module.exports = uv_thread_interface
