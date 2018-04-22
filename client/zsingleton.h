#ifndef ZSINGLETON_H
#define ZSINGLETON_H
#include "parammanager.h"
#include "actionmodule.h"
namespace ZSS{
    typedef Singleton<ParamManager> ZParamManager;
    typedef Singleton<ActionModuleSerialVersion> ZActionModule;
}
#endif // ZSINGLETON_H
