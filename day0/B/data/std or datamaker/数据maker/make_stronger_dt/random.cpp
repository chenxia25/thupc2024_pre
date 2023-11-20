#include<bits/stdc++.h>
#define ll long long
using namespace std;
char gc(){static char buf[1<<16],*s,*t;if(s==t){t=(s=buf)+fread(buf,1,1<<16,stdin);if(s==t)return EOF;}return *s++;}
//#define getchar gc
int read()
{
	char c;
	int w=1;
	while((c=getchar())>'9'||c<'0')if(c=='-')w=-1;
	int ans=c-'0';
	while((c=getchar())>='0'&&c<='9')ans=(ans<<1)+(ans<<3)+c-'0';
	return ans*w;
}
void pc(char c,int op)
{
	static char buf[1<<16],*s=buf,*t=buf+(1<<16);
	(op||((*s++=c)&&s==t))&&(fwrite(buf,1,s-buf,stdout),s=buf);
}
void wt(ll x)
{
	if(x>9)wt(x/10);
	pc('0'+x%10,0);
}
void wts(ll x,char c)
{
	if(x<0)pc('-',0),x=-x;
	wt(x),pc(c,0);
}
/*以下写一个较为完备的生成数据的东西 */
//默认是windows环境 
ll rd32(){return (rand()|(rand()<<15));}//到1e9 
ll rd64(){return rd32()|(rd32()<<30);}//到1e18 
ll rd(ll l,ll r){return l+rd64()%(r-l+1);}
int n,m,q;
struct nod{int x,y,z;};
vector<nod>v;
const int xx=5e6+5;//默认1e6 
int id[xx];
void remark()
{
	for(int i=1;i<=n;i++)id[i]=i;
	random_shuffle(id+1,id+n+1);
}
void on()
{
	for(int i=0;i<v.size();i++)
	{
		v[i].x=id[v[i].x];
		v[i].y=id[v[i].y];
	}
}
void rdm_tree(){for(int i=2;i<=n;i++)v.push_back((nod){rd32()%(i-1)+1,i,0});}
void rerand(){random_shuffle(v.begin(),v.end());}
void reswap(){for(int i=0;i<v.size();i++)if(rand()&1)swap(v[i].x,v[i].y);}
void fstout(int op)
{
	//op=0表示不带权值 
	for(auto it:v)
	{
		wts(it.x,' ');
		wts(it.y,' ');
		if(op)wts(it.z,'\n');
		else pc('\n',0);
	}
}
void fullqz(ll L,ll R){/*cerr<<v.size()<<"%%\n";*/for(int i=0;i<v.size();i++)v[i].z=rd(L,R);/*,cerr<<L<<" "<<R<<" "<<v[i].z<<"%\n";*/}
namespace pf
{
	int f[xx],p[xx];//父亲和prufer 
	int rd[xx];
	void prufer()
	{
		for(int i=1;i<=n-2;i++)p[i]=rd32()%n+1;
		for(int i=1;i<n-1;i++)rd[p[i]]++;p[n-1]=n;
		int j=1;
		for(int i=1;i<=n-1;i++,j++)
		{
			while(rd[j])j++;f[j]=p[i];
			while(!(--rd[p[i]])&&p[i]<j&&i<=n-1)f[p[i]]=p[i+1],i++;
		}
		for(int i=1;i<n;i++)v.push_back((nod){f[i],i,0});//注意prufer是以n为根的 
	}
}using pf::prufer;
struct node{int next,to,v;}e[xx<<1];
int cnt,h[xx];
void add(int x,int y,int z)
{
	cnt++;
	e[cnt].next=h[x];
	h[x]=cnt;
	e[cnt].to=y;
	e[cnt].v=z;
}
void bd(int op)//0表示有向 
{
	for(auto it:v)
	{
		add(it.x,it.y,it.z);
		if(op)add(it.y,it.x,it.z);
	}
}
//不保证无重边，保证无自环 
void fill()
{
	while(v.size()<m)
	{
		int x=rd32()%n+1,y=rd32()%n+1;
		if(x==y)continue;
		v.push_back({x,y,0});
	}
}
void fill2()//可以带自环 
{
	while(v.size()<m)
	{
		int x=rd32()%n+1,y=rd32()%n+1;
		v.push_back({x,y,0});
	}
}
ll a[xx];
void r_seq(ll L,ll R){for(int i=1;i<=n;i++)a[i]=rd(L,R);}
void outseq(){for(int i=1;i<=n;i++)wts(a[i],' ');pc('\n',0);}
map<pair<int,int> ,int>mp;
void cls(int op)//0表示也不存在反向边，1表示存在 
{
	vector<nod>w;
	mp.clear();
	for(auto it:v)
	{
		if(!op&&it.x>it.y)swap(it.x,it.y);
		if(mp[make_pair(it.x,it.y)])continue;
		mp[make_pair(it.x,it.y)]=1;
		w.push_back(it);
	}
	swap(w,v);
	while(v.size()<m)
	{
		int x=rd32()%n+1,y=rd32()%n+1;
		if(x==y)continue;
		if(x>y)swap(x,y);
		if(mp[make_pair(x,y)])continue;
		mp[make_pair(x,y)]=1;
		v.push_back({x,y,0});
	}
	return ;
}
void connected_map(int N,int M)//无重边/自环 
{
	n=N,m=M;
	prufer();
	fill();
	cls(0);
	remark();
	on();
	rerand();
}
void out()
{
	for(auto it:v)cout<<it.x<<" "<<it.y<<" "<<it.z<<"\n";
}
void glr(int &l,int &r)
{
	l=rd(1,n),r=rd(1,n);
	if(l>r)swap(l,r);
}
namespace ssc
{
	char ans[55][55];
	int tx,ty;
	void solve()
	{
		n=rd(35,40),m=rd(35,40);
		cout<<n<<' '<<m<<"\n";
		tx=rd(1,n),ty=rd(1,m);
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				int op=rd(1,2);
//				if(op==1)
				ans[i][j]='+';
//				else ans[i][j]='#';
			}
		}
		ans[tx][ty]='P';
		int num=100;
		while(num--)
		{
			tx=rd(1,n),ty=rd(1,m);
			if(ans[tx][ty]!='P')ans[tx][ty]='#';
		}
		for(int i=1;i<=n;i++)cout<<(ans[i]+1)<<"\n";
	}
}
signed main(){
	freopen("seed.in","r",stdin);
	int ooo=read();
	srand(ooo);
	freopen("a.in","w",stdout);
//	exit(0);
	ssc::solve();
//	n=rd(3,3);
//	cout<<n<<"\n";
//	for(int i=1;i<=n;i++)cout<<rd(1,3)<<" ";puts("");
//	for(int i=1;i<=n;i++)cout<<rd(1,3)<<" ";puts("");
//	int k=rd(1,3);
//	cout<<k<<"\n";
//	int q[50],r=0;
//	
//	while(k--)
//	{
//		int w=rd(1,n);
//		while(w--)q[++r]=rd(1,n);
//		sort(q+1,q+r+1);
//		r=unique(q+1,q+r+1)-q-1;
//		cout<<r<<" ";
//		for(int i=1;i<=r;i++)cout<<q[i]<<" ";
//		cout<<rd(1,3)<<" ";cout<<rd(1,3)<<"\n";
//	}
//	vector<int>v;
//	n=6,m=rd(8,8);
//	cout<<n<<" "<<m<<"\n";
//	connected_map(n,m);
//	fullqz(1,5);
//	out();
//	int q=(n*(n-1))/2;
//	cout<<q<<"\n";
//	for(int i=1;i<=n;i++)
//	{
//		for(int j=i+1;j<=n;j++)cout<<i<<" "<<j<<"\n";
//	}
//	fill();
//	fullqz(1,5);
//	while(n--)v.push_back(0);
//	while(m--)v.push_back(1);
//	random_shuffle(v.begin(),v.end());
//	for(auto it:v)cout<<it;puts("");
//	random_shuffle(v.begin(),v.end());
//	for(auto it:v)cout<<it;puts("");
//	int T=2;
//	wts(T,'\n');
//	while(T--)
//	{
//		n=200,m=rd(200,1000);
//		v.clear();
//		for(int i=1;i<=n;i++)v.push_back({i,(i%n+1),0});
//		fill2();
//		wts(n,' ');
//		wts(m,'\n');
//		fstout(0);
//		for(int i=1;i<=n;i++)wts(i,' ');pc('\n',0);
//	//	wts(1,' ');
//	//	wts(n,'\n');
//	//	cout<<1<<" "<<n<<"\n";
////		fullqz(-1000,1000);
//		
//	}
//	prufer();
//	wts(n,' ');
//	wts(m,'\n');
//	cls(0);
//	remark();
//	reswap();
//	on();
//	fullqz(-5,9);
//	out();
//	/*
//	int n;
//	if(ooo<=10000)n=rd(1,500);
//	else n=rd(1,100000);
//	int n=rd(1,500);
//	cout<<n<<"\n";
//	r_seq(n,1,n);
//	if((rand()&1)&&ooo<=6000)
//	if(ooo!=0&&ooo!=15000)
//	prufer(n,v);
//	fill(v,n,m);
//	remark(n);
//	on(v);
//	rerand(v);
//	wts(n,' '),
//	wts(m,' '),
//	wts(id[n],'\n');
//	fullqz(v,1,9);
//	fstout(v,1);
//	*/
	
	
	pc('1',1);
	freopen("seed.in","w",stdout);
	cout<<ooo+1000<<"\n";
	return 0;
}
