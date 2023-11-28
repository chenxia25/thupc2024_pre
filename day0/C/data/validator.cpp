#include"testlib.h"
#include <bits/stdc++.h>
#define re register
using namespace std;

int main(int argc, char* argv[]) {
	registerValidation(argc, argv);
	int n = inf.readInt(1, 1000000000, "n"); inf.readSpace();
	double p = inf.readStrictDouble(0.000001, 0.999999, 1, 6, "p"); inf.readSpace();
	int l = inf.readInt(1, n, "l"); inf.readSpace();
	int r = inf.readInt(l, n, "r");
	char c = inf.readChar();
	assert(c == 10 || c == 13);
	if (c == 13) inf.readChar(10);
	inf.readEof();
	return 0;
}