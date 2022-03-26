#pragma once

#include <iostream>
using namespace std; 
//Z1.0
char* AlocirajIKopiraj(const char* tekst) {
    if (tekst == nullptr)
        return nullptr;
    int vel = strlen(tekst) + 1;
    char* novi = new char[vel];
    strcpy_s(novi, vel, tekst);
    return novi;
}

int Min(int a, int b) { return (a <= b) ? a : b; }
int Max(int a, int b) { return (a >= b) ? a : b; }
