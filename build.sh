#!/bin/bash
package="..."
package_manager="..."
Install_Dependency="..."
$Install_Dependency

CC="gcc"
LIB="Lib"
INCLUDE="Lib/Include"
#CFLAGS="-O3 -march=native -flto -Wall -Wextra -pedantic -g -fsanitize=address -fsanitize=undefined -pthread -fanalyzer"
CFLGAG_NOMAL="-o"
EXTERN="-lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer"
#compile to objcet file 

echo compiling flags 
echo $CFLAGS
$CC -v -c -I$INCLUDE $LIB/game_lib.c -o game_lib.o 
$CC -v -c -I$INCLUDE $LIB/sdl_component.c -o sdl_component.o 
$CC -v -c -I$INCLUDE main.c -o main.o   

# Linking objcet file 
$CC -v sdl_component.o game_lib.o main.o -o my_game $EXTERN 
echo cleaning build 
rm sdl_component.o game_lib.o main.o 

