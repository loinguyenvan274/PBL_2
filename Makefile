#./src/utils/*.cpp
cc = g++
all_file_compile = ./src/main.cpp ./src/app/*.cpp ./src/utils/*.cpp ./src/app/*.c
path_include = ./include
path_lib = ./lib
lInclude = -lraylib -lwinmm -lgdi32 -lopengl32 -lole32 -lcomdlg32
path_build = ./build/index.exe

compile:
	$(cc) $(all_file_compile) -o $(path_build) -L$(path_lib) -I$(path_include) $(lInclude)
	$(path_build)
debug:
	$(cc) -g  $(all_file_compile) -o $(path_build) -L$(path_lib) -I$(path_include) $(lInclude)
	gdb $(path_build)
run:
	$(path_build)
git_push:
	git add .
	git commit -m "m"
	git push
t:
	g++ ./test/main.cpp -o ./test/main -L$(path_lib)  -I$(path_include) $(lInclude)
	./test/main
