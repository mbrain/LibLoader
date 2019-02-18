#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
typedef HANDLE lib_t;
#else
#include <dlfcn.h>
typedef void* lib_t;
#endif

lib_t MyLoadLib(const char* lib) {
    #ifdef _WIN32
    return LoadLibraryA(lib);
    #else 
    return dlopen(lib, RTLD_NOW);
    #endif 
}

void MyUnloadLib(lib_t lib) {
    #ifdef _WIN32
    FreeLibrary(lib);
    #else 
    dlclose(lib);
    #endif 
}

void* MyLoadProc(lib_t lib, const char* proc) {
    #ifdef _WIN32
    return GetProcAddress(lib, proc);
    #else 
    return dlsym(lib, proc);
    #endif 
}

int main(int argc, char **argv) {

    lib_t myLib = NULL;
    #ifdef _WIN32
    myLib = MyLoadLib("lib.dll");
    #else
    myLib = MyLoadLib("./lib.so");
    #endif 
    
    char *funcname;
    if(argc > 1) funcname = argv[1];
    else funcname = "init";
    
    if(!MyLoadProc(myLib, funcname)) return 0;      
    char* (*func_ptr)() = MyLoadProc(myLib, funcname); 
    
    char *result;
    result = (*func_ptr)();
    printf("%s", result);
    
    MyUnloadLib(myLib); 
        
    return 0;
    
}