# Basic NAN


## nan Native Abstractions for Node.js

The V8 API can and will change overtime, and this means that addons may break. The best way to safeguard yuorself from this is to use nan. And no it is not the same as the value NaN. (Not a number) NAN is a set of macros designed to make your life easier. 

https://github.com/nodejs/nan


To use nan you'll have to install it using NPM

npm install --save nan

Then put the path to NAN in your binding.gyp file

"include_dirs" : [
    "<!(node -e \"require('nan')\")"
]

This is here for markdown compat >


And lastly include nan in your C header

#include <nan.h>



# Nan::Maybe types

Nan::MaybeLocal and Nan::Maybe types are monads that encapsulate v8::Local handles that may be empty. It is best to use these over the v8::Local handle whenever possible. This is a safeguard in case a value is empty so you can catch errors.





## Passing in a number
## Passing in a string
## Passing in a boolean
## Passing in an array
## Passing in an object
