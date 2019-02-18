#include <stdio.h>

#ifdef _WIN32
__declspec(dllimport) char *init() {
    return "CustomMethods: hello, bye";
}

__declspec(dllimport) char *hello() {
    return "Hello";
}

__declspec(dllimport) char *bye() {
    return "Bye";
}
#else
__attribute__ ((visibility ("default"))) char *init() {
    return "CustomMethods: hello, bye";
}

__attribute__ ((visibility ("default"))) char *hello() {
    return "Hello";
}

__attribute__ ((visibility ("default"))) char *bye() {
    return "Bye";
}
#endif