// advanced.cpp
#include <node.h>
#include <nan.h>
#include "opencvexample.h"

using namespace Nan;

class ImageWorker : public Nan::AsyncWorker {
  public:
    ImageWorker(Nan::Callback *callback, std::string filename, std::string outfile, double param)
      : Nan::AsyncWorker(callback), filename(filename), outfile(outfile), param(param) {}
    ~ImageWorker() {}
    
    void Execute () {
      affectGamma(filename, outfile, param);
    } 

    void HandleOKCallback () {
      Nan::HandleScope scope;

      callback->Call(0, NULL);

    } 

  private:
    std::string filename;
    std::string outfile;
    double param;
};
 

NAN_METHOD(PerformAction) {
  Nan::HandleScope scope;


  v8::Local<v8::String> filename = info[0].As<v8::String>();
  if (filename.IsEmpty()) {
    Nan::SyntaxError("Must pass a file name as first argument");
  }
  std::string imagefile = *v8::String::Utf8Value(filename);

  v8::Local<v8::String> outfile = info[1].As<v8::String>();
  if (filename.IsEmpty()) {
    Nan::SyntaxError("Must pass an out file name as second argument");
  }
  std::string outimage = *v8::String::Utf8Value(outfile);

  v8::Local<v8::Number> numberParameter = info[2].As<v8::Number>();
  // double number = numberParameter->NumberValue();
  v8::Local<v8::Function> callback = info[3].As<v8::Function>();

  Nan::Callback* cb = new Nan::Callback(callback);
  ImageWorker *imworker = new ImageWorker(cb, imagefile, outimage, numberParameter->NumberValue());
  Nan::AsyncQueueWorker(imworker);

}
/*
void PerformAction(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Nan::HandleScope scope;


  v8::Local<v8::String> filename = args[0].As<v8::String>();
  if (filename.IsEmpty()) {
    Nan::SyntaxError("Must pass a file name as first argument");
  }
  std::string imagefile = *v8::String::Utf8Value(filename);

  v8::Local<v8::String> outfile = args[1].As<v8::String>();
  if (filename.IsEmpty()) {
    Nan::SyntaxError("Must pass an out file name as second argument");
  }
  std::string outimage = *v8::String::Utf8Value(outfile);

  v8::Local<v8::Number> numberParameter = args[2].As<v8::Number>();
  // double number = numberParameter->NumberValue();
  v8::Local<v8::Function> callback = args[3].As<v8::Function>();

  Nan::Callback* cb = new Nan::Callback(callback);
  ImageWorker *imworker = new ImageWorker(cb, imagefile, outimage, numberParameter->NumberValue());
  Nan::AsyncQueueWorker(imworker);
}
*/
NAN_MODULE_INIT(Init) {
  NAN_EXPORT(target, PerformAction);
  // NODE_SET_METHOD(target, "perform", PerformAction);
  // Set(target, 
  //   New<v8::String>("perform").ToLocalChecked,
  //   New<v8::FunctionTemplate>(PerformAction)->GetFunction());


}



NODE_MODULE(addon, Init)



