#./src/utils/*.cpp
cc = g++
all_file_compile = ./src/main.cpp ./src/app/*.cpp ./src/utils/*.cpp
path_include = ./include
path_lib = ./lib
lInclude = -lraylib -lwinmm -lgdi32 -lopengl32
path_build = ./build/index.exe


compile:
	$(cc) $(all_file_compile) -o $(path_build) -L$(path_lib) -I$(path_include) $(lInclude)
run:
	$(path_build)
git_push:
	git add .
	git commit -m "m"
	git push
