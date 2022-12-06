#pragma once

#ifdef _WIN32
  #define avrodemo_EXPORT __declspec(dllexport)
#else
  #define avrodemo_EXPORT
#endif

avrodemo_EXPORT void avrodemo();
