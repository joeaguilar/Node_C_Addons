// datatypes.ccp
#include <nan.h>
#include <node.h>


// namespace valuepassing {
  using v8::FunctionCallbackInfo;
  using v8::Isolate;
  using v8::Local;
  using v8::Object;
  using v8::String;
  using v8::Value;


void testNumber(const v8::FunctionCallbackInfo<v8::Value> & args) {

  if (args.Length() < 1) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if (!args[0]->IsNumber()) {
    Nan::ThrowTypeError("Must provide a number");
    return;
  }

  double testNum = args[0]->NumberValue();
  v8::Local<v8::Number> num = Nan::New(testNum + 1);

  args.GetReturnValue().Set(num);

}


void testString(const v8::FunctionCallbackInfo<v8::Value>& args) {
  if (args.Length() < 1) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if (!args[0]->IsString()) {
    Nan::ThrowTypeError("Must provide a string");
    return;
  }

  // std::string testStr = args[0]->ToString();
  v8::String::Utf8Value testStr(args[0]->ToString());
  std::string from = std::string(*testStr) + "!";

  v8::Local<v8::String> str = Nan::New(from).ToLocalChecked().As<v8::String>();

  args.GetReturnValue().Set(str);

}



void testBoolean(const v8::FunctionCallbackInfo<v8::Value>& args) {
  if (args.Length() < 1) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if (!args[0]->IsBoolean()) {
    Nan::ThrowTypeError("Must provide a boolean");
    return;
  }

  // std::string testStr = args[0]->ToString();
  bool boo  = args[0]->BooleanValue();
  v8::Local<v8::Boolean> notBoo = Nan::New(!boo);

  args.GetReturnValue().Set(notBoo);

}



void testArray(const v8::FunctionCallbackInfo<v8::Value>& args) {
  if (args.Length() < 1) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if (!args[0]->IsObject() ) {
    Nan::ThrowTypeError("Must provide an array");
    return;
  }
  v8::Local<v8::Array> arr = args[0].As<v8::Array>();
  std::string buildString = "Array contains: ";
  std::size_t l = arr->Length();
  for (std::size_t i = 0; i < l; ++i ) {
    // std::string tempString(*NanAsciiString(arr.Get(i)));
    v8::String::Utf8Value tempString(arr->Get(i)->ToString());
    buildString += std::string(*tempString) + " ";
  }

  v8::Local<v8::String> str = Nan::New(buildString).ToLocalChecked().As<v8::String>();

  args.GetReturnValue().Set(str);

}


void testObject(const v8::FunctionCallbackInfo<v8::Value>& args) {
  if (args.Length() < 1) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if (!args[0]->IsObject()) {
    Nan::ThrowTypeError("Must provide an object");
    return;
  }
  v8::Local<v8::Object> obj = args[0].As<v8::Object>();
  v8::Local<v8::Array> props = obj->GetOwnPropertyNames();
  std::string buildString = "Object contains: ";
  std::size_t l = props->Length();
  
  for (std::size_t i = 0; i < l; ++i) {

      v8::Local<v8::Value> key = props->Get(i);
      v8::Local<v8::Value> val = obj->Get(key);

      v8::String::Utf8Value keyString(key->ToString());
      v8::String::Utf8Value valString(val->ToString());
      buildString += std::string(*keyString) + ": " + std::string(*valString) + " ";
      
  }

  v8::Local<v8::String> str = Nan::New(buildString).ToLocalChecked().As<v8::String>();

  args.GetReturnValue().Set(str);

}


void testFunction(const v8::FunctionCallbackInfo<v8::Value>& args) {
  if (args.Length() < 1) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }
  v8::Isolate* isolate = args.GetIsolate();

  v8::Local<v8::Function> callback = args[0].As<v8::Function>();
  v8::Local<v8::String> messageString = Nan::New("A mesaage from C++").ToLocalChecked().As<v8::String>();
  v8::Local<v8::Value> argv[1] = { messageString };
  callback->Call(Null(isolate), 1, argv);
  // Callback cb(args[0].As<v8::Function>());
  // cb.Call(1, messageString)
}



NAN_MODULE_INIT(Init) {

  NODE_SET_METHOD(target, "number", testNumber);
  NODE_SET_METHOD(target, "string", testString);
  NODE_SET_METHOD(target, "bool", testBoolean);
  NODE_SET_METHOD(target, "array", testArray);
  NODE_SET_METHOD(target, "object", testObject);
  NODE_SET_METHOD(target, "function", testFunction);

}

NODE_MODULE(example, Init)

// }
