#include"hanzi.h"
#include"ZiKu.h"
#include"Trainer.h"
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<fstream>
using namespace std;

double f[113][113];
int from[113][113];
int input[1000];
hanzi ans[1000];
bool getline(string &s) {
	s = "";
	char ch = getchar();
	if (ch == EOF) return false;
	while (ch != '\n'&&ch != EOF) {
		if (ch >= 'A'&&ch <= 'Z') ch += 'a' - 'A';
		s += ch;
		ch = getchar();
	}
	return true;
}
void output(ZiKu* ziku, int i, int j) {
	if (i == -1) return;
	output(ziku, i - 1, from[i][j]);
	ziku->b[ziku->a[input[i]][j]].output();
	ans[i] = ziku->b[ziku->a[input[i]][j]];
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

	freopen("1.txt", "r", stdin);
	int tot1 = 0, tot2 = 0, num1 = 0, num2 = 0;
	for (;;){
		for (int i = 0; i < 113; i++)for (int j = 0; j < 113; j++)f[i][j] = 0;
		memset(from, 0, sizeof(from));
		int n = 0;
		string s;
		if (!getline(s)) break;
		cout << "s=" << s << endl;
		tot1++;
		while (s.length() > 0) {
			int t = s.find(' ');
			string ss = s.substr(0, t);
			input[n++] = ziku->getPinyinNumber(ss);// , cout << a[n - 1] << endl;
			tot2++;
			if (s.length() <= ss.length()) break;
			s = s.substr(t + 1, s.length());
		}
		for (unsigned int j = 0; j < ziku->a[input[0]].size(); j++)
			f[0][j] = trainer->num[ziku->a[input[0]][j]];
		for (int i=1;i<n;i++)
			for (unsigned int j=0;j<ziku->a[input[i]].size();j++)
				for (unsigned int k = 0; k < ziku->a[input[i - 1]].size(); k++) {
					double P = trainer->num2[ziku->a[input[i - 1]][k]][ziku->a[input[i]][j]];
					double tmp = f[i - 1][k] * (P + trainer->num[ziku->a[input[i - 1]][k]] / 50000.0 + trainer->num[ziku->a[input[i]][j]] / 50000.0);
					if (tmp > f[i][j]) {
						f[i][j] = tmp;
						from[i][j] = k;
					}
				}
		double res = 0;
		int that;
		for (unsigned int j=0;j<ziku->a[input[n-1]].size();j++)
			if (f[n - 1][j] > res) {
				res = f[n - 1][j];
				that = j;
			}
		output(ziku, n - 1, that);
		cout << endl;
		bool flag = true;
		for (int i = 0; i < n; i++) {
			char x = getchar(), y = getchar();
			hanzi tmp = hanzi(x, y);
			//cout << "tmp: "; tmp.output(); cout << endl;
			if (tmp == ans[i]) num2++;
			else flag = false;
		}
		if (flag) num1++;
		getchar();
	}
	cout << endl << endl;
	cout << "单字匹配成功：" << num2 << "/" << tot2 << endl;
	cout << "全句匹配成功：" << num1 << "/" << tot1 << endl;
	return 0;
}