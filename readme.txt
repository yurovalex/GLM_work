

#Console build #1
mkdir build
cd build
cmake ..
cmake --build . --config Release -j40
#cmake --build . --config Debug --parallel 16


#Console build #2
mkdir build
cd    build
cmake -DCMAKE_BUILD_TYPE=Release -G Ninja ..
//По умолчанию собирается Debug версия
cmake -G Ninja ..
ninja


#remove folder
cd ..ls
rm -R build [Enter]

