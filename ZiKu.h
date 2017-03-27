#ifndef ZiKu_h
#define ZiKu_h
#include"hanzi.h"
#include<cstdio>
#include<algorithm>
#include<string>
#include<map>
#include<vector>
using namespace std;
class ZiKu {
public:
	int cnt,TTT;
	string pinyin[501];
	vector<int> a[501];
	map<hanzi, int> hao;
	hanzi b[7000];
	ZiKu() :cnt(0), TTT(0) {}
	void init(const char*, const char *);
	int getPinyinNumber(string);
	int getHanziNumber(hanzi);
	hanzi getHanzi(int);
};
#endif