#pragma once

#include <string>
#include <functional>

#ifdef _WIN32
# ifndef USE_JSCRIPT
#   define JSCRIPT_EXTERN __declspec(dllexport)
# else
#   define JSCRIPT_EXTERN __declspec(dllimport)
# endif
#else
# define JSCRIPT_EXTERN /* nothing */
#endif

#ifdef USE_JSCRIPT
#  include "v8.h"
#endif


namespace node {
namespace jscript {


typedef void(*JSCallback)(const v8::FunctionCallbackInfo<v8::Value>& args);
enum JSLogType {
    LOG_TYPE,
    WARN_TYPE, 
    ERROR_TYPE,
    
    DEFAULT_TYPE = LOG_TYPE
};
typedef std::function<void(const v8::FunctionCallbackInfo<v8::Value>&, const JSLogType)>  JSLogCallback;

struct JSCallbackInfo {
    const char*    name     = nullptr;
    JSCallback     function = nullptr;
    void*          external = nullptr;
};

class JSInstance { };

JSCRIPT_EXTERN void Initialize(int argc, const char* const argv_[]);
JSCRIPT_EXTERN void Initialize(const std::string& origin, const std::string& externalOrigin,
                               const std::string& executeFile, const std::string& coreFolder, const std::string& nodeFolder);

JSCRIPT_EXTERN void SetLogCallback(JSInstance* instance, JSLogCallback& cb);

JSCRIPT_EXTERN void Uninitilize();

JSCRIPT_EXTERN int  RunInstance();

typedef enum {
    JS_SUCCESS = 0,
    JS_ERROR
} result_t;

JSCRIPT_EXTERN result_t CreateInstance(JSInstance** outNewInstance);
JSCRIPT_EXTERN result_t StopInstance(JSInstance* instance);

JSCRIPT_EXTERN result_t RunScriptText(const char* script);
JSCRIPT_EXTERN result_t RunScriptText(const char* script, JSCallbackInfo* callbacks[]);

JSCRIPT_EXTERN result_t RunScriptText(JSInstance* instance, const char* script);
JSCRIPT_EXTERN result_t RunScriptText(JSInstance* instance, const char* script, JSCallbackInfo* callbacks[]);


} // namespace jscript
} // namespace node


#ifdef USE_JSCRIPT
namespace jscript = node::jscript;
#endif
