all:main.exe
main.exe: main.cpp Trainer.h Trainer.cpp ZiKu.h ZiKu.cpp hanzi.h hanzi.cpp
	g++ -std=c++11  -O2 main.cpp Trainer.cpp Ziku.cpp hanzi.cpp -o main.exe
clean:
	del *.exe *.o