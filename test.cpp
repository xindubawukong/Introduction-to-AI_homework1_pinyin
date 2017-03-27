#include"ZiKu.h"
#include"hanzi.h"
#include"Trainer.h"
#include<cstdio>
#include<ctime>
#include<iostream>
using namespace std;

int main() {
	int time0 = clock();
	ZiKu *ziku = new ZiKu();
	ziku->init("../yierjihanzibiao.txt","../pinyinhanzibiao.txt");
	Trainer *trainer = new Trainer("../sina_news/",ziku);
	trainer->train_all();
	trainer->output("num.out");
	return 0;
}
