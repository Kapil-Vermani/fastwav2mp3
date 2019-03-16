# fastwav2mp3
This is a c++ wrapper over LAME library and it utilizes c++11 multithreading concepts to efficiently achieve this task.
It takes directory name as command line option and convert all .wav files in that directory to .mp3 keeping same file name.
This is portable c++11 code and it can be compiled using both msvc and g++ compiler but may be in windows you have to seperately install dirent.h and its dependencies. 
