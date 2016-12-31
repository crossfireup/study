#ifdef __cplusplus
extern "C" {
#endif

#ifndef DIPSLIBAPI
#define DIPSLIBAPI __declspec(dllimport)
#endif


DIPSLIBAPI BOOL WINAPI SetDIPSHook(DWORD dwThreadId);

#ifdef __cplusplus
}
#endif