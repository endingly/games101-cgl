// clang-format off
#pragma once
    #ifdef _WIN32
        #ifdef CGL_BUILD_SHARED_LIBS
            #define CGL_EXPORT __declspec(dllexport)
        #else
            #define CGL_EXPORT
        #endif
#endif