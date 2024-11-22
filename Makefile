#./src/utils/*.cpp
# all_cpp_app = ./src/app/docGhiFile.cpp ./src/app/nguoi.cpp ./src/app/Phong.cpp ./src/app/sinhVien.cpp ./src/app/Vector.cpp  ./src/app/QuanLyKTX.cpp 
all_cpp_app = ./src/app/*.cpp
cc = g++
all_file_compile = ./src/main.cpp $(all_cpp_app) ./src/gui/*.cpp ./src/gui/*.c
path_include = ./include
path_lib = ./lib
lInclude = -lraylib -lwinmm -lgdi32 -lopengl32 -lole32 -lcomdlg32 
path_build = ./index.exe
paht_test = ./test/test.exe

compile:
	$(cc) $(all_file_compile) -o $(path_build) -L$(path_lib) -I$(path_include) $(lInclude)
	$(path_build)

tt:
	$(cc)  $(all_file_compile) -o $(paht_test) -L$(path_lib) -I$(path_include) $(lInclude)
	$(paht_test)

debug:
#$(cc) -g  $(all_file_compile) -o $(path_build) -L$(path_lib) -I$(path_include) $(lInclude)
	gdb $(path_build)
run:
	$(path_build)
	
git_push:
	git add .
	git commit -m "m"
	git push
t:
	g++ ./test/main.cpp -o ./test/main  -L$(path_lib) -I$(path_include) $(lInclude)
	./test/main
