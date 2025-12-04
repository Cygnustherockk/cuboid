HI, this is a stupid game I made in C using the raylib library
theres already an exe just to make it nice
if you wanna compile it yourself if you dont trust me, you need the gcc compiler, specifically one with a raylib devkit

for simplicity, this is the one i used 
https://github.com/skeeto/w64devkit/

instalation can be found on their github

the command used to compile is
gcc -o game main.c -I include -L lib -lraylib -lgdi32 -lwinmm

anyways, have fun i suppose :D
