all:
	g++ -g --std=c++17 -IDependancies -LDependancies/lib Enviroments/*.cpp Client/*.cpp Physics/*.cpp Realms/*.cpp Enviroments/Buffers/*.cpp Enviroments/Terrain/*.cpp Enviroments/Humanoid/*.cpp Dependancies/imgui/*.cpp Main.cpp glad.c -lwinmm -lglfw3dll -o Dependancies/dll/Main
