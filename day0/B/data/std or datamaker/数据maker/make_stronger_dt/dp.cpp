#include<bits/stdc++.h>
#define ll long long
using namespace std;
int read()
{
	char c;
	int w=1;
	while((c=getchar())>'9'||c<'0')if(c=='-')w=-1;
	int ans=c-'0';
	while((c=getchar())>='0'&&c<='9')ans=(ans<<1)+(ans<<3)+c-'0';
	return ans*w;
}

int l,r;
//默认使用checker，不要fc。 
string to[]={"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58","59","60","61","62","63","64","65","66","67","68","69","70","71","72","73","74","75","76","77","78","79","80","81","82","83","84","85","86","87","88","89","90","91","92","93","94","95","96","97","98","99","100"};

int main(){
	puts("想要范围");
	cin>>l>>r;
	int tt=l;
	for(int i=1;i;i++)
	{
		cerr<<"TT="<<i<<"\n";
		/*
		system("random.exe");
		double st=clock();
		system("zj.exe");
		double ed=clock();
		cout<<ed-st;puts("AC");*/
//		

		system("random.exe");
		system("bf.exe");
		double st=clock();
		system("zj.exe");
		double ed=clock();
		if(system("checker.exe"))
		{
			cerr<<"Out the "<<tt<<"\n";
			system(("rename a.in hack"+to[tt]+".in").c_str());
			++tt;
			if(tt>r)
			{
				cerr<<"Over\n";
				exit(0);
			}
		}
		cerr<<ed-st;cerr<<"AC\n";
		
		
//		*/
	}
	return 0;
}
