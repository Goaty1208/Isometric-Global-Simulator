main:
	g++ ../src/*.cpp ../src/engine/*.cpp -o igsMain.exe -O2 -Wall -Wno-missing-braces -I ../include/ -L ../lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows
debug:
	g++ -g ../src/*.cpp ../src/engine/*.cpp -o igsMain.exe -O2 -Wall -Wno-missing-braces -I ../include/ -L ../lib/ -lraylib -lopengl32 -lgdi32 -lwinmm 
	gdb igsMain.exe
debugButCoolBecauseLinux:
	g++ -g -fsanitizer=address ../src/*.cpp ../src/engine/*.cpp -o igsMain.exe -O2 -Wall -Wno-missing-braces -I ../include/ -L ../lib/ -lraylib -lopengl32 -lgdi32 -lwinmm 
	gdb igsMain.exe