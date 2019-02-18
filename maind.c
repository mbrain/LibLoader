#include <stdio.h>
#include <dirent.h>

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

// https://stackoverflow.com/questions/744766/
int EndsWith(const char *str, const char *suffix) {
    if (!str || !suffix) return 0;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix >  lenstr) return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

int main(int argc, char **argv) {

    struct dirent *de;
    DIR *dr = opendir(".");

    lib_t myLib = NULL;
    
    while ((de = readdir(dr)) != NULL) {
        
        #ifdef _WIN32
        if(EndsWith(de->d_name, ".dll") == 0) continue;
        #else
        if(EndsWith(de->d_name, ".so") == 0) continue;
        #endif
         
        myLib = MyLoadLib(de->d_name); 
        
        char *funcname;
        if(argc > 1) funcname = argv[1];
        else funcname = "init";
        
        if(!MyLoadProc(myLib, funcname)) continue;      
        char* (*func_ptr)() = MyLoadProc(myLib, funcname); 
        
        char *result;
        result = (*func_ptr)();
        printf("%s", result);
        
        MyUnloadLib(myLib);
    
    } 
        
    return 0;
    
}
