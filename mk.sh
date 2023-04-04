// Windows
gcc -c myLib.c -o myLib.o
gcc -shared myLib.o -o myLib.dll

// Linux
gcc -c -fPIC myLib.c -o myLib.o
gcc -shared myLib.o -o myLib.so
