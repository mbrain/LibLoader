# Linux
gcc -c -fPIC lib1.c -o lib1.o
gcc -shared lib1.o -o lib1.so
gcc main.c -o main -ldl

# Windoof
gcc -c myLib.c -o myLib.o
gcc -shared myLib.o -o myLib.dll
gcc main.c -o main -lmyLib
