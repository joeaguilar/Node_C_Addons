{
  "targets" : 
    [ 
      { 
        "target_name" : "addon",
        "sources" : [ "advanced.cpp", "/opt/local/include/opencv", "opencvexample.cpp"],
        "include_dirs": [
          "<!(node -e \"require('nan')\")"
        ],
        "cflags": [
          "-std=c++11",
          "<!@(pkg-config --cflags --libs opencv )",
          "-Wall",
          "-m64",
          "-03",
          "stdlib=libc++",
          "-fexceptions",
          "-Wpointer-arith",
          "-Wformat-nonliteral",
          "-Winit-self",
          "Werror",
          "-Wl,-O1",
          "-Wl,--discard-all",
          "-Wl,--no-undefined",
          "-Wl,--build-id=sha1"
          ],
        "conditions": [
          ['OS=="mac"', {
            'include_dirs':['/usr/local/include/opencv'],
            'xcode_settings': {
              'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
            },
            'libraries':[
              '-lopencv_core', 
              '-lopencv_imgproc', 
              '-lopencv_calib3d',
              '-lopencv_features2d', 
              '-lopencv_objdetect', 
              '-lopencv_video', 
              '-lopencv_highgui', 
              '-lopencv_flann', 
              '-lopencv_ml'
            ]
          }]
        ]
       }
    ]
}