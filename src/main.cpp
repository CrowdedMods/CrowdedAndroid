#define _DEBUG 1

#include <jni.h>

#include "hook.h"

inline void init()
{
    init_functions();
    LOGF("set function pointers");
    init_hooks();
    LOGF("set hooks");
    MeetingHudPatches::init();
    LOGF("inited meeting hud patches");
    GameDataPatches::init();
    LOGF("inited gamedata patches");
}

JNIEXPORT jint JNI_OnLoad(JavaVM*, void*)
{
    LOGF("loaded");
    init();
    return JNI_VERSION_1_4;
}