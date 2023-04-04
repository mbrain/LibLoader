#ifdef _WIN32
__declspec(dllimport) char *init() {
    return "lib1(a, b) ";
}
__declspec(dllimport) char *a() {
    return "a";
}
__declspec(dllimport) char *b() {
    return "b";
}
#else
__attribute__ ((visibility ("default"))) char *init() {
    return "lib1(a, b)";
}
__attribute__ ((visibility ("default"))) char *a() {
    return "a";
}
__attribute__ ((visibility ("default"))) char *b() {
    return "b";
}
#endif
