#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

void delay(int milliseconds){
    #ifdef _WIN32
        Sleep(milliseconds);
    #else
        usleep(milliseconds*1000);
    #endif
}