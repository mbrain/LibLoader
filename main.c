#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
typedef HANDLE my_lib_t;
#else
#include <dlfcn.h>
typedef void* my_lib_t;
#endif

my_lib_t MyLoadLib(const char* szMyLib) {
    #ifdef _WIN32
    return LoadLibraryA(szMyLib);
    #else 
    return dlopen(szMyLib, RTLD_LAZY);
    #endif 
}

void MyUnloadLib(my_lib_t hMyLib) {
    #ifdef _WIN32
    FreeLibrary(hMyLib);
    #else 
    dlclose(hMyLib);
    #endif 
}

void* MyLoadProc(my_lib_t hMyLib, const char* szMyProc) {
    #ifdef _WIN32
    return GetProcAddress(hMyLib, szMyProc);
    #else 
    return dlsym(hMyLib, szMyProc);
    #endif 
}

int main(int argc, char **argv) {

    my_lib_t myLib = NULL;
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