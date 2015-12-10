{
  "targets": [
    {
      "target_name": "binding",
      "cflags": ["-Wall", "-std=c++11"],
      'xcode_settings': {
        'OTHER_CFLAGS': [
          '-std=c++11'
        ],
      },
      "defines": ["PRINT_ENABLED=1"],
      "sources": [
        "src/module.cc",
        "src/functions.cc",
        "src/emitter.cc",
        "src/thread.cc",
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "include"
      ]
    }
  ]
}