compile with -
gcc -g -c client.c -Isrc/Include -Lsrc/lib -lmingw32 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL_mixer -lSDL2  
gcc -g -o client.exe client.o -Isrc/Include -Lsrc/lib -lmingw32 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2 -lws2_32


compile server with:
gcc server.c -o server -lws2_32