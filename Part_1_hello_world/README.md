# Node.js Addons


## Node-Gyp

Node-gyp is what is going to compile your C++ code. binding.gyp files are just like the package.json file in that they specify certain parameters that Node will use. They are different in that Node-gyp uses this file when you build your file.

Start by first using npm install -g node-gyp

Your system may have different needs, check out https://github.com/nodejs/node-gyp#installation for more information


building a file will

Go to the root directory of your addon

$ cd my_node_addon

The next step will make the configuration files for the current platform

$ node-gyp configure

then generate the build files

node-gyp build

## Including an addon

Including addons use the familiar pattern of including node modules

const addon = require("./build/Release/addon");

Anyone familiar with Android development will note that in the build directory you can have either a "Release" or a "Debug" directory or both.

You can target these using a try-catch pattern

try {
  return require("./build/Release/addon.node");
} catch (err) {
  return require("./build/Debug/addon.node");
}




# Resources

https://nodejs.org/api/addons.html
https://github.com/nodejs/nan/blob/master/doc/node_misc.md#api_nan_export
https://github.com/nodejs/nan/blob/master/doc/methods.md
https://github.com/nodejs/node-addon-examples/blob/master/2_function_arguments/nan/addon.cc
https://github.com/nodejs/nan/blob/master/examples/async_pi_estimate/addon.js
http://andrewaustin.com/compiling-native-node-addons-on-os-x-10-9/

















