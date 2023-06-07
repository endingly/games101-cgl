#pragma once
#ifdef _WIN32
#define CGL_EXPORT __declspec(dllexport)
#else
#define CGL_EXPORT
#endif