#include<bits/stdc++.h>
#define ll long long 
#define LL __int128
#define ull unsigned ll
#define dd double
using namespace std;
char gc(){static char buf[1<<16],*s,*t;if(s==t){t=(s=buf)+fread(buf,1,1<<16,stdin);if(s==t)return EOF;};return *s++;}
//#define getchar gc
ll read()
{
    char c;
    ll w=1;
    while((c=getchar())>'9'||c<'0')if(c=='-')w=-1;
    ll ans=c-'0';
    while((c=getchar())>='0'&&c<='9')ans=(ans<<1)+(ans<<3)+c-'0';
    return ans*w;
}
void pc(char c,int op)
{
	static char buf[1<<16],*s=buf,*t=buf+(1<<16);
    (op||((*s++=c)&&s==t))&&(fwrite(buf,1,s-buf,stdout),s=buf);
}
void wt(int x)
{
    if(x>9)wt(x/10);
    pc('0'+x%10,0);
}
void wts(int x,char op)
{
    if(x<0)pc('-',0),x=-x;
    wt(x),pc(op,0);
}
int n,m;
int a[45][45];
int get(int A,int b,int c,int d){return /*cerr<<A<<" "<<b<<" "<<c<<" "<<d<<" "<<a[c][d]+a[A-1][b-1]-a[A-1][d]-a[c][b-1]<<"\n",*/a[c][d]+a[A-1][b-1]-a[A-1][d]-a[c][b-1];}
int tx,ty;
int f[42][42][42][42];
char vs[42][42][42][42];
int solve(int l,int r,int L,int R)
{
	if(!(tx<=r&&l<=tx)||!(ty<=R&&L<=ty))return 0;
//	assert(tx<=r&&l<=tx);
//	assert(ty<=R&&L<=ty);
	if(vs[l][r][L][R])return f[l][r][L][R];
	vs[l][r][L][R]=1;
	int ans=min(get(l,L,tx,ty),min(get(tx,L,r,ty),min(get(l,ty,tx,R),get(tx,ty,r,R))));
//	for(int i=l;i<r;i++)
//		for(int j=L;j<R;j++)
//			ans=min(ans,get(l,L,i,j)+get(i+1,j+1,r,R)+solve(i+1,r,L,j)+solve(l,i,j+1,R));
//	
//	for(int i=l;i<r;i++)
//		for(int j=L;j<R;j++)
//			ans=min(ans,get(i+1,L,r,j)+get(l,j+1,i,R)+solve(l,i,L,j)+solve(i+1,r,j+1,R));
	
	
	return f[l][r][L][R]=ans;
}
signed main(){
	freopen("a.in","r",stdin);
	freopen("b.out","w",stdout);
	n=read(),m=read();
//	,tx=read(),ty=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			char c;
			while((c=getchar())!='+'&&c!='#'&&c!='P');
			
			if(c=='+')a[i][j]=1;
			if(c=='P')a[i][j]=1,tx=i,ty=j;
			if(c=='#')a[i][j]=2;
//			a[i][j]=read(),assert(a[i][j])
			a[i][j]--;
			
			
		}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			a[i][j]+=a[i-1][j];
			a[i][j]+=a[i][j-1];
			a[i][j]-=a[i-1][j-1];
		}
	}
	cout<<solve(1,n,1,m)<<"\n";
    pc('1',1);
    return 0;
}
