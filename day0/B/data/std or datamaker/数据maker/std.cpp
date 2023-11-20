#include<bits/stdc++.h>
#define lc(x) t[x].c[0]
#define rc(x) t[x].c[1]
using namespace std;
typedef long long ll;
const int maxn=2e5+5;
const ll inf=1ll<<60;
struct node {
	ll a,b,c;
	node() {}
	node(ll a,ll b,ll c) {
		this->a=a,this->b=b,this->c=c;
	}
	ll cal(ll x) {
		return (a*x+b)*x+c;
	}
};
struct tree {
	int c[2];
	ll tag;
	node x;
} t[maxn*40];
struct edge {
	int next,to;
} e[maxn*2];
int n,m,d[maxn],mxd,T,h[maxn],cnt,rt[maxn],tot;
ll s[maxn],f[maxn],C[maxn],H[maxn];
void addedge(int x,int y) {
	e[++cnt].next=h[x],e[cnt].to=y,h[x]=cnt;
}
void adtag(int id,ll k) {
	t[id].tag+=k,t[id].x.c+=k;
}
void pushdown(int id) {
	ll &k=t[id].tag;
	if(lc(id))adtag(lc(id),k);
	if(rc(id))adtag(rc(id),k);
	k=0;
}
void add(int &id,int l,int r,node x) {
	if(!id)return id=++tot,t[id].x=x,void();
	if(l==r) {
		if(x.cal(l)>t[id].x.cal(l))t[id].x=x;
		return;
	}
	pushdown(id);
	if(t[id].x.cal(l)>x.cal(l))swap(t[id].x,x);
	int mid=l+r>>1;
	if(t[id].x.cal(mid)>x.cal(mid))swap(t[id].x,x),add(lc(id),l,mid,x);
	else add(rc(id),mid+1,r,x);
}
int merge(int x,int y,int l,int r) {
	if(!x||!y)return x+y;
	pushdown(x),pushdown(y);
	int mid=l+r>>1;
	lc(x)=merge(lc(x),lc(y),l,mid),rc(x)=merge(rc(x),rc(y),mid+1,r);
	add(x,l,r,t[y].x);
	return x;
}
ll ask(int id,int l,int r,int p) {
//	cerr<<l<<' '<<r<<'\n';
	if(!id)return inf;
	int mid=l+r>>1;
	pushdown(id);
	return min(t[id].x.cal(p),p<=mid?ask(lc(id),l,mid,p):ask(rc(id),mid+1,r,p));
}
void dfs1(int u,int fa) {
	d[u]=d[fa]+1,mxd=max(mxd,d[u]);
	for(int i=h[u]; i; i=e[i].next) {
		int v=e[i].to;
		if(v==fa)continue;
		dfs1(v,u);
	}
}
void dfs2(int u,int fa) {
	s[u]=rt[u]=0;
	for(int i=h[u]; i; i=e[i].next) {
		int v=e[i].to;
		if(v==fa)continue;
		dfs2(v,u),s[u]+=f[v];
	}
//	if(u==1)cerr<<u<<' ';
//	cout<<u<<' '<<C[u]<<' '<<2*C[u]*C[u]+C[u]<<' '<<C[u]*(C[u]+d[u]+C[u])*(1-d[u])-2*H[u]<<'\n';
	add(rt[u],0,mxd,node(C[u],2*C[u]*C[u]+C[u],C[u]*(C[u]+d[u]+C[u])*(1-d[u])-2*H[u]+s[u]));
	for(int i=h[u]; i; i=e[i].next) {
		int v=e[i].to;
		if(v==fa)continue;
		adtag(rt[v],s[u]-f[v]),rt[u]=merge(rt[u],rt[v],0,mxd);
//		if(u==1)cerr<<u<<' '<<v<<"*\n";
	}
//	if(u==1)cerr<<"* ";
	f[u]=ask(rt[u],0,mxd,d[u]);
//	if(u==1)cerr<<"*\n";
}
int main() {
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int x,y;
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n),cnt=tot=mxd=0;
		for(int i=1; i<=n; i++)h[i]=0,scanf("%lld%lld",&H[i],&C[i]);
		for(int i=1; i<n; i++) {
			scanf("%d%d",&x,&y);
			addedge(x,y),addedge(y,x);
		}
		dfs1(1,0);
		for(int i=1; i<=n; i++)d[i]=mxd-d[i];
		dfs2(1,0);
		printf("%lld\n",f[1]/2);
		for(int i=1; i<=tot; i++)lc(i)=rc(i)=t[i].tag=0;
	}
	return 0;
}
