#ifndef INFORM_CRASH_H
#define INFORM_CRASH_H
#pragma pack(push, 1)

EXPORT void Crash(LPCSTR Text);
EXPORT void Crash(LPCSTR Text1, LPCSTR Text2 );
EXPORT void CrashFull(LPCSTR Text, ...);
EXPORT void ExitSystem(int);
EXPORT void Printf(LPCSTR...);

#pragma pack(pop)
#endif
