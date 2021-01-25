#ifndef LOG_H
#define LOG_H

#if 1
    #include <android/log.h>
    #define LOG_TAG "AnimeCrowdedMod"
    #define LOGF(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#else
    #define LOGF(...)
#endif

#endif