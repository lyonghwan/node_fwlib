#include <napi.h>

/**
 * 
 * 
 * 
 * */
extern int getMachine(const char *host, int port);

Napi::Value MapperGetMachine(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  const char *host = info[0].ToString().Utf8Value().c_str();
  int port = info[1].As<Napi::Number>().Int32Value();
  Napi::Number num = Napi::Number::New(env, getMachine(host, port));
  return num;
}

/**
 * 
 * 
 * 
 * */
extern char *connect(char *host, int ip, unsigned short cncLibHandler);

Napi::Value MapperConnect(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  const char *host = info[0].ToString().Utf8Value().c_str();
  int port = info[1].As<Napi::Number>().Int32Value();
  unsigned short *cncLibHandler;
  Napi::String str = Napi::String::New(env, connect(host, port, &cncLibHandler));
  return cncLibHandler;
}

/**
 * 
 * 
 * 
 * */
extern int disconnect(unsigned short cncLibHandler);

Napi::Value MapperDisconnect(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  unsigned short cncLibHandler = info[1].As<Napi::Number>().Int32Value();
  Napi::Number num = Napi::String::New(env, disconnect(cncLibHandler));
  return num;
}

/**
 * 
 * 
 * 
 * */
extern uint32_t *readCncId(unsigned short cncLibHandler);

Napi::Value MapperReadCncId(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  //TODO
  unsigned short cncLibHandler = info[1].As<Napi::Number>().Int32Value();
  Napi::Number num = Napi::String::New(env, readCncId(cncLibHandler));
  return num;
}

/**
 * 
 * 
 * 
 * */
extern ODBSYS sysinfo(unsigned short cncLibHandler);

Napi::Value MapperSysinfo(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  //TODO
  unsigned short cncLibHandler = info[1].As<Napi::Number>().Int32Value();
  Napi::Object odbsys = Napi::String::New(env, sysinfo(cncLibHandler));

  return odbsys;
}

/**
 * 
 * 
 * 
 * */
extern ODBST statinfo(unsigned short cncLibHandler);

Napi::Value MapperStatinfo(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  //TODO
  unsigned short cncLibHandler = info[1].As<Napi::Number>().Int32Value();
  Napi::Object odbst = Napi::String::New(env, statinfo(cncLibHandler));

  return odbsys;
}

/**
 * 
 * 
 * 
 * */
extern ODBDY2_T readDynamicTow(unsigned short cncLibHandler);

Napi::Value MapperReadDynamicTow(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  //TODO
  unsigned short cncLibHandler = info[1].As<Napi::Number>().Int32Value();
  Napi::Object odbdy2_t = Napi::String::New(env, readDynamicTow(cncLibHandler));

  return odbsys;
}

/**
 * Method Mapper
 * */
Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set(Napi::String::New(env, "getMachineId"),
              Napi::Function::New(env, MapperGetMachine));

  exports.Set(Napi::String::New(env, "connect"),
              Napi::Function::New(env, MapperConnect));

  exports.Set(Napi::String::New(env, "disconnect"),
              Napi::Function::New(env, MapperDisconnect));

  exports.Set(Napi::String::New(env, "disconnect"),
              Napi::Function::New(env, MapperDisconnect));

  return exports;
}

NODE_API_MODULE(cppPartExportedByNapi, Init)