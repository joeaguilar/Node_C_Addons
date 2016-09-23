// hello.cc
#include <node.h>

// First define a namespace, or dont
namespace helloworld {
  using v8::FunctionCallbackInfo;
  using v8::Isolate;
  using v8::Local;
  using v8::Object;
  using v8::String;
  using v8::Value;

// Pass the FunctionCallbackInfo template "args"
// You may call this function anything you'd like.
void Method(const FunctionCallbackInfo<Value>& args) {

  // Grab a pointer to the isolate passed into the function
  Isolate* isolate = args.GetIsolate();
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
}

// This is where you will set your methods
void init(Local<Object> exports) {
  // Set the name associated with your previously defined function with a string
  NODE_SET_METHOD(exports, "hello", Method);
}
// You must use this macro to call the initializer function you defined above
NODE_MODULE(addon, init)

} // namespace helloworld