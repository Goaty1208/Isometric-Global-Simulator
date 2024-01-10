main:
	g++ ../src/*.cpp ../src/engine/*.cpp -o igsMain.exe -O3 -Wall -Wno-missing-braces -I ../include/ -L ../lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows -static-libstdc++ -static-libgcc -static
debug:
	g++ ../src/*.cpp ../src/engine/*.cpp -o igsMain.exe -O2 -Wall -Wno-missing-braces -I ../include/ -L ../lib/ -lraylib -lopengl32 -lgdi32 -lwinmm 
debugButCool:
	g++ -g -fsanitizer=address ../src/*.cpp ../src/engine/*.cpp -o igsMain.exe -O2 -Wall -Wno-missing-braces -I ../include/ -L ../lib/ -lraylib -lopengl32 -lgdi32 -lwinmm 
	gdb -ex run ./igsMain
