#include"ZiKu.h"
#include"hanzi.h"
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<string>
#include<fstream>
using namespace std;
#define debug(x) cout<<#x<<"="<<x<<endl;
void ZiKu::init(const char* hanzibiao, const char* pinyinbiao) {
	freopen(hanzibiao, "r", stdin);
	for (char x = getchar(), y = getchar(); x != EOF; x = getchar(), y = getchar()) {
		hanzi tmp=hanzi(x,y);
		hao[tmp] = TTT++;
		b[TTT - 1] = tmp;
	}
	fclose(stdin);
	freopen(pinyinbiao, "r", stdin);
	char ch = 'a';
	while (ch != EOF) {
		cin >> pinyin[cnt++];
		for (ch = getchar(); ch != '\n'&&ch != EOF; ch = getchar()) {
			char x = getchar(), y = getchar();
			hanzi t = hanzi(x, y);
			//t.output();
			a[cnt - 1].push_back(t);
			if (a[cnt - 1].size() > maxsize) maxsize = a[cnt - 1].size();
		}
	}
	fclose(stdin);
}
int ZiKu::getPinyinNumber(string s) {
	int l = 0, r = cnt - 1;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (pinyin[mid] == s) return mid;
		if (s < pinyin[mid]) r = mid - 1;
		else l = mid + 1;
	}
	return -1;
}
int ZiKu::getHanziNumber(hanzi a) {
	return hao[a];
}
hanzi ZiKu::getHanzi(int x) {
	return b[x];
}