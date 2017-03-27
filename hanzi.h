#ifndef hanzi_h
#define hanzi_h
#include<cstdlib>
#include<algorithm>
using namespace std;
class hanzi {
private:
	pair<char, char> z;
public:
	hanzi() = default;
	hanzi(char a, char b) :z(make_pair(a, b)) {}
	hanzi(string s) :z(make_pair(s[0], s[1])) {}
	hanzi(const char* s) :z(make_pair(s[0], s[1])) {}
	void output();
	friend bool operator <(const hanzi &a, const hanzi &b);
	friend bool operator ==(const hanzi &a, const hanzi &b);
};
#endif