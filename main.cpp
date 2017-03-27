#include"hanzi.h"
#include"ZiKu.h"
#include"Trainer.h"
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<fstream>
using namespace std;

map<int, double> f[100][100][113];
map<int, pair<int, pair<int, int> > > from[100][100][113];
int input[1000];
void output(ZiKu* ziku, int l, int r, int i, int j) {
	if (l == r) {
		ziku->b[ziku->a[input[l]][i]].output();
		return;
	}
	pair<int, pair<int, int> > tmp = from[l][r][i][j];
	int mid = tmp.first, k1 = tmp.second.first, k2 = tmp.second.second;
	output(ziku, l, mid, i, k1);
	output(ziku, mid + 1, r, k2, j);
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
	for (int i = 0; i < n; i++)
		for (unsigned int j = 0; j < ziku->a[input[i]].size(); j++)
			f[i][i][j][j] = trainer->num[ziku->a[input[i]][j]] / 1000.0;
	for (int len = 2; len <= n; len++)
		for (int l = 0; l + len - 1 < n; l++) {
			cout << "len=" << len << endl;
			int r = l + len - 1;
			for (unsigned int i = 0; i < ziku->a[input[l]].size(); i++)
				for (unsigned int j = 0; j < ziku->a[input[r]].size(); j++) {
					// f[l][r][i][j]
					int ci = ziku->a[input[l]][i];
					int cj = ziku->a[input[r]][j];
					for (int mid = l; mid<r; mid++)
						for (unsigned int k1 = 0; k1<ziku->a[input[mid]].size(); k1++)
							for (unsigned int k2 = 0; k2 < ziku->a[input[mid + 1]].size(); k2++) {
								int ck1 = ziku->a[input[mid]][k1];
								int ck2 = ziku->a[input[mid + 1]][k2];
								double P = trainer->num2[ck1][ck2] + trainer->num[ck1] / 1000.0 + trainer->num[ck2] / 1000.0;
								double res = f[l][mid][i][k1] * f[mid + 1][r][k2][j] * P;
								if (res > f[l][r][i][j]) {
									f[l][r][i][j] = res;
									from[l][r][i][j] = make_pair(mid, make_pair(k1, k2));
								}
							}
				}
		}
	double ans = 0;
	pair<int, int> that;
	for (unsigned int i = 0; i<ziku->a[input[0]].size(); i++)
		for (unsigned int j = 0; j<ziku->a[input[n - 1]].size(); j++)
			if (f[0][n - 1][i][j] > ans) {
				ans = f[0][n - 1][i][j];
				that = make_pair(i, j);
			}
	output(ziku, 0, n - 1, that.first, that.second);
	return 0;
}