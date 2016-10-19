// complex.cpp
#include <iostream>
#include <sstream>
#include <nan.h>
#include <node.h>


void testArrayOfNumbers(const v8::FunctionCallbackInfo<v8::Value>& args) {
  
  if (args.Length() < 1) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if (!args[0]->IsObject() ) {
    Nan::ThrowTypeError("Must provide an array");
    return;
  }
  double sum = 0;
  v8::Local<v8::Array>arr = args[0].As<v8::Array>();
  
  std::size_t l = arr->Length();
  for (std::size_t i = 0; i < l; ++i ) {
    
    Nan::MaybeLocal<v8::Value> maybeNumber =  arr->Get(i);
    
    if (maybeNumber.IsEmpty()) continue;

    v8::Local<v8::Number> localNum = maybeNumber.ToLocalChecked().As<v8::Number>();

    if ( localNum->IsNumber() ) {
      sum += localNum->NumberValue();
      // sum += arr[i]->NumberValue();
    }

  }

  v8::Local<v8::Number> num = Nan::New(sum);
  args.GetReturnValue().Set(num);

}



void testArrayOfBooleans(const v8::FunctionCallbackInfo<v8::Value>& args) {
  if (args.Length() < 1) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if (!args[0]->IsObject() ) {
    Nan::ThrowTypeError("Must provide an array");
    return;
  }
  bool allTheSame = true;
  bool firstBool = true;
  bool cacheBool = true;
  v8::Local<v8::Array>arr = args[0].As<v8::Array>();
  std::size_t l = arr->Length();
  
  for (std::size_t i = 0; i < l; ++i) {
    
    Nan::MaybeLocal<v8::Value> maybeBoolean =  arr->Get(i);
    
    if (maybeBoolean.IsEmpty()) continue;

    v8::Local<v8::Boolean> localBool = maybeBoolean.ToLocalChecked().As<v8::Boolean>();

    if ( localBool->IsBoolean() ) {
      
      if (firstBool) {
        cacheBool = localBool->BooleanValue();
        firstBool = false;
      }

      if (cacheBool != localBool->BooleanValue()) {
        allTheSame = false;
      }

    }


  }

  
  v8::Local<v8::Boolean> finalBool = Nan::New(allTheSame);

  args.GetReturnValue().Set(finalBool);

}

void testArrayOfStrings(const v8::FunctionCallbackInfo<v8::Value>& args) {
  if (args.Length() < 1) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if (!args[0]->IsObject() ) {
    Nan::ThrowTypeError("Must provide an array");
    return;
  }
  v8::Local<v8::Array> arr = args[0].As<v8::Array>();
  std::string buildString = "";
  std::size_t l = arr->Length();
  
  for (std::size_t i = 0; i < l; ++i ) {
    
    Nan::MaybeLocal<v8::Value> maybeString =  arr->Get(i);
    
    if (maybeString.IsEmpty()) continue;

    v8::Local<v8::String> localString = maybeString.ToLocalChecked().As<v8::String>();

    if ( localString->IsString() ) {
      
      v8::String::Utf8Value tempString(localString->ToString());
      buildString += std::string(*tempString) + " ";
      

    }
  }

  v8::Local<v8::String> str = Nan::New(buildString).ToLocalChecked().As<v8::String>();

  args.GetReturnValue().Set(str);

}

void testArrayOfArrays(const v8::FunctionCallbackInfo<v8::Value>& args) {

}


void testArrayOfObjects(const v8::FunctionCallbackInfo<v8::Value>& args) {

  if (args.Length() < 1) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if (!args[0]->IsObject() ) {
    Nan::ThrowTypeError("Must provide an array");
    return;
  }

  v8::Local<v8::Array> arr = args[0].As<v8::Array>();
  std::size_t l = arr->Length();
  
  std::string buildString = "This array contains ";
  buildString += std::to_string(l);
  buildString += " objects. ";
  
  for (std::size_t i = 0; i < l; ++i ) {
    buildString += "Object contains: ";

    Nan::MaybeLocal<v8::Value> maybeObject = arr->Get(i);
    
    if (maybeObject.IsEmpty()) continue;

    v8::Local<v8::Object> localObject = maybeObject.ToLocalChecked().As<v8::Object>();

    if (localObject->IsObject() ) {
      // v8::Local<v8::Object> obj = arr[i].As<v8::Object>();
      v8::Local<v8::Array> props = localObject->GetOwnPropertyNames();

      std::size_t pl = props->Length();
      
      for (std::size_t n = 0; n < pl; ++n) {

          v8::Local<v8::Value> key = props->Get(n);
          v8::Local<v8::Value> val = localObject->Get(key);

          v8::String::Utf8Value keyString(key->ToString());
          v8::String::Utf8Value valString(val->ToString());
          buildString += std::string(*keyString) + ": " + std::string(*valString) + " ";
          
      }
    }
  }


  v8::Local<v8::String> str = Nan::New(buildString).ToLocalChecked().As<v8::String>();
  args.GetReturnValue().Set(str);

}



void testArrayOfFunctions(const v8::FunctionCallbackInfo<v8::Value>& args) {
  if (args.Length() < 1) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if (!args[0]->IsObject() ) {
    Nan::ThrowTypeError("Must provide an array");
    return;
  }

  v8::Isolate* isolate = args.GetIsolate();
  v8::Local<v8::Array> arr = args[0].As<v8::Array>();
  std::size_t l = arr->Length();
  for (std::size_t i = 0; i < l; ++i ) {
    Nan::MaybeLocal<v8::Value> maybeFunction = arr->Get(i);
    
    if (maybeFunction.IsEmpty()) continue;

    v8::Local<v8::Function> localFunction = maybeFunction.ToLocalChecked().As<v8::Function>();
    if (localFunction->IsFunction() ) {
      std::cout << "From C++: Calling function with argument " << i << std::endl;
      
      // v8::Local<v8::Number> num = Nan::New(i).ToLocalChecked().As<v8::Number>();
      v8::Local<v8::Number> num = Nan::New( (double)i );
      // v8::Local<v8::Function> callback = args[0].As<v8::Function>();
      // v8::Local<v8::String> messageString = Nan::New("A mesaage from C++").ToLocalChecked().As<v8::String>();
      v8::Local<v8::Value> argv[1] = { num };
      localFunction->Call(Null(isolate), 1, argv);
      
    }
  }

}



// void testCallbackFunctions(const v8::FunctionCallbackInfo<v8::Value>& args) {
//   if (args.Length() < 1) {
//     Nan::ThrowTypeError("Wrong number of arguments");
//     return;
//   }

//   v8::Local<v8::Function> callback = args[0].As<v8::Function>();
//   callback->Call(0, NULL);
// }

NAN_MODULE_INIT(Init) {

  NODE_SET_METHOD(target, "numbers", testArrayOfNumbers);
  NODE_SET_METHOD(target, "strings", testArrayOfStrings);
  NODE_SET_METHOD(target, "bools", testArrayOfBooleans);
  NODE_SET_METHOD(target, "arrays", testArrayOfArrays);
  NODE_SET_METHOD(target, "objects", testArrayOfObjects);
  NODE_SET_METHOD(target, "functions", testArrayOfFunctions);


}

NODE_MODULE(example, Init)



