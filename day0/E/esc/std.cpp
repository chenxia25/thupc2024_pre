#include<bits/stdc++.h>
#define cmin(a,b) (a>(b)?a=(b),1:0)
#define cmax(a,b) (a<(b)?a=(b),1:0)
#define dmin(a,b) ((a)<(b)?(a):(b))
#define dmax(a,b) ((a)>(b)?(a):(b))
namespace io{
	int F(){
		int n=0,F=0;
		char ch;
		while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
		ch=='-'?F=1:n=ch-'0';
		while((ch=getchar())>='0'&&ch<='9')n=n*10+ch-'0';
		return F?-n:n;
	}
	long long G(){
		long long n=0,F=0;
		char ch;
		while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
		ch=='-'?F=1:n=ch-'0';
		while((ch=getchar())>='0'&&ch<='9')n=n*10+ch-'0';
		return F?-n:n;
	}
}
int a[355555];
struct it{
	int b,comb,c;
}v[355555];
bool vis[355555];
int main(){
	int n=io::F();
	for(int i=1;i<=n;++i){
		a[i]=io::F();
	}
	for(int i=1;i<=n;++i){
		int b=io::F(),c=io::F();
		if(b)v[i]=(it){dmax(0,b-c-1),dmin(b-1,c),dmax(0,c-b+1)};
			else v[i]=(it){0,0,c};
	}
	long long wild=0;
	for(int z=0;z<=1;++z){
		for(int i=1;i<=n;++i){
			int tmp=dmin(a[i],v[i].b);
			if(a[i])vis[i]=1;
			wild+=tmp;
			a[i]-=tmp;
			v[i].b-=tmp;
			if(a[i]&&v[i].comb){
				wild+=v[i].comb+1;
				v[i].comb=0;
				a[i]--;
			}
			if(wild&&v[i].comb){
				wild+=v[i].comb;
				v[i].comb=0;
				vis[i]=1;
			}
		}
	}
	for(int i=1;i<=n;++i){
		printf("%lld%c",wild+a[i]+v[i].c," \n"[i==n]);
	}
	long long ans=wild;
	for(int i=1;i<=n;++i){
		if(vis[i]){
			ans+=v[i].c;
			v[i].c=0;
		}
	}
	std::sort(v+1,v+n+1,[&](const it &x, const it &y){return x.c>y.c;});
	for(int i=1;i<=n;++i){
		if(wild&&v[i].c){
			--wild;
			ans+=v[i].c;
			v[i].c=0;
		}
	}
	printf("%lld\n",ans);
	return 0;
}