all:main.exe
main.exe: main.cpp Trainer.h Trainer.cpp ZiKu.h ZiKu.cpp hanzi.h hanzi.cpp
	g++ -std=c++11  main.cpp Trainer.cpp Ziku.cpp hanzi.cpp -o main.exe -g
clean:
	del *.exe *.o