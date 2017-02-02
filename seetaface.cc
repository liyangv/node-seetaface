#include <node.h>
#include <node_buffer.h>
#include <nan.h>
#include "face_detectionImp.h"
using v8::FunctionTemplate;

NAN_METHOD(detect) {
  if (info.Length() < 4) {
   // ThrowException(v8::Exception::TypeError(v8::String::New("Bad argument!")));  //抛出js异常 
  }
  v8::Local<v8::Function> cb = info[3].As<v8::Function>();
  bool bFaceDetected = false;
  if (node::Buffer::HasInstance(info[0])) {
      uint8_t *buf = (uint8_t *) node::Buffer::Data(info[0]->ToObject());
      unsigned len = node::Buffer::Length(info[0]->ToObject());
      int width = info[1]->IntegerValue();
      int height = info[2]->IntegerValue();
      printf("get data width:%d,height:%d size: %d\n",width,height,len);
      int nFaces = processFrame(buf,width,height);
      if(nFaces > 0){
        bFaceDetected = true;
      }
  }

  if(bFaceDetected){
      const unsigned argc = 1;
      v8::Local<v8::Value> argv[argc] = { Nan::New("detected").ToLocalChecked() };
      Nan::MakeCallback(Nan::GetCurrentContext()->Global(), cb, argc, argv);
  }else{
      const unsigned argc = 1;
      v8::Local<v8::Value> argv[argc] = { Nan::New("empty").ToLocalChecked() };
      Nan::MakeCallback(Nan::GetCurrentContext()->Global(), cb, argc, argv);
  }
}

NAN_MODULE_INIT(Init) {
  Nan::Set(target, Nan::New("detect").ToLocalChecked(),Nan::GetFunction(Nan::New<FunctionTemplate>(detect)).ToLocalChecked());
}


NODE_MODULE(seetaface, Init)
