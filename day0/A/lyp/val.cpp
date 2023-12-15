#include"testlib.h"
#include<bits/stdc++.h>
using namespace std;

const int CASES = 19;

int main(void)
{
	for(int i = 1 ; i <= CASES ; ++i)
	{
		freopen(("../data/" + to_string(i) + ".in").c_str() , "r" , stdin);
		registerValidation();
		
		int n = inf.readInt(1, 2000 , "n"); inf.readEoln();
		
		vector<int> a(n+1), bak(n+1);
		for(int i=1; i<=n; ++i)
		{
			a[i] = inf.readInt(1, n, "a[i]");
			if(i == n) inf.readEoln();
			else inf.readSpace();
		}
		
		for(int i=1; i<=n; ++i)
			++bak[a[i]];
		
		for(int i=1; i<=n; ++i)
			ensuref(bak[i] == 1, "Not a permutation");
		
		inf.readEof();
		cerr << "Case " << i << " complete" << endl;
		fclose(stdin);
	}
	return 0;
}
