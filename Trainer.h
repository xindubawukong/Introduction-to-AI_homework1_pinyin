#ifndef Trainer_h
#define Trainer_h
#include"ZiKu.h"
#include<set>
class Trainer {
private:
	const char * source;
	ZiKu *ziku;
	set<hanzi> S;
public:
	int num2[7000][7000];
	int num[7000];
	Trainer(const char *_source, ZiKu* _ziku) :source(_source), ziku(_ziku) {
		string a[100] = {"£¬","¡£","¡ñ","¨","¡°","¡±","£¿","£¡","£º","£»","£¨","£©","¡¶","¡·","¡ª","¡¢","¡¾","¡¿","¡­","¡¤","¡ö","¡ï"};
		for (string s : a) S.insert(hanzi(s));
		for (int i = 0; i < 7000; i++) {
			num[i] = 0;
			for (int j = 0; j < 7000; j++) num2[i][j] = 0;
		}
	}
	void tongji(vector<hanzi> &a);
	void train(const char *);
	void train_all();
	void output(const char *);
};
#endif