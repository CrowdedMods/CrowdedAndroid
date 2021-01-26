#ifndef LOG_H
#define LOG_H

#if _DEBUG
    #include <android/log.h>
    #define LOG_TAG "AnimeCrowdedMod"
    #define LOGF(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
    // printing it in error level since it easier to track
#else
    #define LOGF(...)
#endif

#endif