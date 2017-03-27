#include"hanzi.h"
#include<iostream>
void hanzi::output() {
	cout << z.first << z.second;
}
bool operator <(const hanzi &a, const hanzi &b) {
	if (a.z.first != b.z.first) return a.z.first < b.z.first;
	return a.z.second < b.z.second;
}
bool operator ==(const hanzi &a, const hanzi &b) {
	return a.z.first == b.z.first&&a.z.second == b.z.second;
}