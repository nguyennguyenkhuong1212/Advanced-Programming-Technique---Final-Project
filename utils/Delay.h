#ifndef DELAY_H
#define DELAY_H
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <conio.h>

void delay(int milliseconds){
    #ifdef _WIN32
        Sleep(milliseconds);
    #else
        usleep(milliseconds*1000);
    #endif
}

void waitUntilKeyPressed(string prefix = ""){
    cout << "\n" << prefix << "Progress is done. Press any key to continue...\n";
    while(true){
        if (getch()) break;
    }
}

#endif