#ifdef _WIN32
__declspec(dllimport) char *init() {
    return "lib2(c, d) ";
}
__declspec(dllimport) char *c() {
    return "c";
}
__declspec(dllimport) char *d() {
    return "d";
}
#else
__attribute__ ((visibility ("default"))) char *init() {
    return "lib2(c, d) ";
}
__attribute__ ((visibility ("default"))) char *c() {
    return "c";
}
__attribute__ ((visibility ("default"))) char *d() {
    return "d";
}
#endif