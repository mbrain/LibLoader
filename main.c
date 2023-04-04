#include <stdio.h>
#include <dirent.h>
#include <string.h>

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
    return dlopen(lib, RTLD_LAZY);
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
    
    myLib = MyLoadLib("./myLib.so"); 
        
    void *funcname;
    funcname = "init";
        
    void *(*func_ptr)() = MyLoadProc(myLib, funcname); 
        
    char *result;
    result = (*func_ptr)();
    printf("%s", result);
        
    MyUnloadLib(myLib);
            
    return 0;
    
}
