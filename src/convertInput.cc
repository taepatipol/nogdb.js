#include <iostream>
#include <nan.h>
#include <nogdb/nogdb.h>

nogdb::ClassDescriptor toClassDescriptor(v8::Local<v8::Object> ClassDescIn){
  v8::Local<v8::String> idProp = Nan::New("id").ToLocalChecked();
  v8::Local<v8::String> nameProp = Nan::New("name").ToLocalChecked();
  v8::Local<v8::String> baseProp = Nan::New("base").ToLocalChecked();
  v8::Local<v8::String> typeProp = Nan::New("type").ToLocalChecked();

  double id = 0;
  std::string name = "";
  double baseClass = 0;
  std::string classType = "";

  if (Nan::HasOwnProperty(ClassDescIn, idProp).FromJust()) {
      v8::Local<v8::Value> idValue = Nan::Get(ClassDescIn, idProp).ToLocalChecked();
      id = idValue->NumberValue();
  }
  if (Nan::HasOwnProperty(ClassDescIn, nameProp).FromJust()) {
      v8::Local<v8::Value> nameValue = Nan::Get(ClassDescIn, nameProp).ToLocalChecked();
      name = *Nan::Utf8String(nameValue->ToString());
  }
  if (Nan::HasOwnProperty(ClassDescIn, baseProp).FromJust()) {
      v8::Local<v8::Value> baseValue = Nan::Get(ClassDescIn, baseProp).ToLocalChecked();
      baseClass = baseValue->NumberValue();
  }
  if (Nan::HasOwnProperty(ClassDescIn, typeProp).FromJust()) {
      v8::Local<v8::Value> typeValue = Nan::Get(ClassDescIn, typeProp).ToLocalChecked();
      classType = *Nan::Utf8String(typeValue->ToString());
  }

  nogdb::ClassId *nogid = new nogdb::ClassId(id);
  nogdb::ClassId *nogBase = new nogdb::ClassId(id);
  nogdb::ClassType *nogType = new nogdb::ClassType();
  if (strcmp(classType.c_str(),"EDGE")){
      *nogType = nogdb::ClassType::EDGE;
  } else if (strcmp(classType.c_str(),"VERTEX")){
      *nogType = nogdb::ClassType::VERTEX;
  } else if (strcmp(classType.c_str(),"UNDEFINED")){
      *nogType = nogdb::ClassType::UNDEFINED;
  } else {
      return Nan::ThrowError(Nan::New("Txn.getPropertiesByClassDescriptor() - invalid classType").ToLocalChecked());
  }

  nogdb::ClassDescriptor classDesc = nogdb::ClassDescriptor(*nogid,name,*nogBase,*nogType);

  return classDesc;
}