#include"hanzi.h"
#include"ZiKu.h"
#include"Trainer.h"
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<fstream>
using namespace std;

double f[113][113];
int from[113][113];
int input[1000];
void output(ZiKu* ziku, int i, int j) {
	if (i == -1) return;
	output(ziku, i - 1, from[i][j]);
	ziku->b[ziku->a[input[i]][j]].output();
}
int main() {
	ZiKu *ziku = new ZiKu();
	ziku->init("yierjihanzibiao.txt", "pinyinhanzibiao.txt");
	Trainer *trainer = new Trainer("../sina_news/", ziku);
	ifstream fin("num3.out");
	int x, y, z;
	fin >> x;
	while (x != -1) {
		fin >> y;
		trainer->num[x] = y;
		fin >> x;
	}
	while (fin >> x >> y >> z) {
		trainer->num2[x][y] = z;
	}
	fin.close();
	/*freopen("1.out", "w", stdout);
	for (int i=0;i<7000;i++)
	for (int j=0;j<7000;j++)
	if (trainer->num2[i][j] > 3000) {
	ziku->b[i].output();
	ziku->b[j].output();
	cout << " : " << trainer->num2[i][j] << endl;
	}*/
	// f[l][r][i][j]: [l,r]   l位置上是该拼音的第i个字，r位置上是该拼音的第j个字 的最大概率
	// f[l][r][i][j]=max(f[l][mid][i][k1]*f[mid+1][r][k2][j]*P(k1,k2)
	fin.open("1.in");
	int n = 0;
	string s;
	while (fin >> s) input[n++] = ziku->getPinyinNumber(s);// , cout << a[n - 1] << endl;
	for (unsigned int j = 0; j < ziku->a[input[0]].size(); j++)
		f[0][j] = trainer->num[ziku->a[input[0]][j]];
	for (int i=1;i<n;i++)
		for (unsigned int j=0;j<ziku->a[input[i]].size();j++)
			for (unsigned int k = 0; k < ziku->a[input[i - 1]].size(); k++) {
				double P = trainer->num2[ziku->a[input[i - 1]][k]][ziku->a[input[i]][j]];
				double tmp = f[i - 1][k] * (P + trainer->num[ziku->a[input[i - 1]][k]] / 500.0 + trainer->num[ziku->a[input[i]][j]] / 500.0);
				if (tmp > f[i][j]) {
					f[i][j] = tmp;
					from[i][j] = k;
				}
			}
	double ans = 0;
	int that;
	for (unsigned int j=0;j<ziku->a[input[n-1]].size();j++)
		if (f[n - 1][j] > ans) {
			ans = f[n - 1][j];
			that = j;
		}
	output(ziku, n - 1, that);
	cout << endl;
	return 0;
}