#include"hanzi.h"
#include"ZiKu.h"
#include"Trainer.h"
#include<cstdio>
#include<iostream>
using namespace std;

int main() {
	ZiKu *ziku = new ZiKu();
	ziku->init("../yierjihanzibiao.txt", "../pinyinhanzibiao.txt");
	Trainer *trainer = new Trainer("../sina_news/", ziku);
	freopen("num3.out", "r", stdin);
	int x, y, z;
	scanf("%d", &x);
	while (x != -1) {
		scanf("%d", &y);
		trainer->num[x] = y;
		scanf("%d", &x);
	}
	while (scanf("%d%d%d", &x, &y, &z) != EOF) {
		trainer->num2[x][y] = z;
	}
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
	static string a[1000];
	return 0;
}