#include<bits/stdc++.h>
#define ll long long 
#define LL __int128
#define dd double
using namespace std;
char gc(){static char buf[1<<16],*s,*t;if(s==t){t=(s=buf)+fread(buf,1,1<<16,stdin);if(s==t)return EOF;};return *s++;}
#define getchar gc
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
void real()
{
	dd A,B;
	freopen("a.out","r",stdin);
	scanf("%lf",&A);
	freopen("b.out","r",stdin);
	scanf("%lf",&B);
	const dd eps=1e-4;
	if(abs(A-B)<eps)exit(0);
	exit(1);
}
char c[(int)3e8+5];
int tt=0;
void spj()
{
	freopen("a.out","r",stdin);
	int a=read();
	random_device R;
	if(a==2)
	{
		cerr<<"A="<<a<<"##$#$#$\n";
		exit(1);
	}
	exit(0);
}
void full_text()
{
	freopen("a.out","r",stdin);
	char p;
	while((p=getchar())!=EOF)
		if(p!=' '&&p!='\n'&&p!='\r'&&p!='\0'&&p!='	')c[tt++]=p;
	freopen("b.out","r",stdin);
	int ce=0;
	while((p=getchar())!=EOF)
		if(p!=' '&&p!='\n'&&p!='\r'&&p!='\0'&&p!='	')if(c[ce++]!=p)exit(1);
	if(ce!=tt)exit(1);
	exit(0);
}
int main(){
//	exit(1)
//	spj();
	
	full_text();
	
	freopen("a.out","r",stdin);
	int A=read();
	freopen("b.out","r",stdin);
	int B=read();
	if(A!=B)
	{
		if(min(A,B)<10)return cerr<<A<<" 左是你的，右是正确的 "<<B<<"\n",1;
		else cerr<<A<<" 太大了不要 "<<B<<"\n";
	}
	pc('1',1);
	return 0;
}
