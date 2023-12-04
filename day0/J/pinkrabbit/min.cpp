#include<bits/stdc++.h>
using namespace std;
#define F(i,a,b)for(int i=a;i<=(b);++i)
const int S=1<<17;
int n,t[S*2],c[S];
void M(int i,int x){
	for(t[i+=S]=x;i>>=1;)t[i]=min(t[i<<1],t[i<<1|1]);
}
int Q(int x){
	int i=1;
	while(i<S)i=i<<1|(t[i<<1]>x);
	return i-S;
}
vector<int>V[S];
set<array<int,3>>s;
pair<int,int>D(int x,int i){
	auto it=s.lower_bound({x,0,0});
	auto&&d=*it;
	if(d[0]!=x)return{1,0};
	int l=(*next(it))[1]+1;
	int r=d[1];
	V[d[2]-r+1].push_back(x);
	V[i-l+1].push_back(~x);
	s.erase(it);
	return{l,r};
}
void I(int x,int r,int i){
	auto it=s.lower_bound({x,0,0});
	if((*it)[0]==x)D(x,i);
	s.insert({x,r,i});
}
int main(){
	cin.sync_with_stdio(false);
	cin.tie(nullptr);
	memset(t,0x3f,sizeof t);
	cin>>n;
	F(i,0,n)M(i,0);
	s.insert({n+1,0,0});
	F(i,1,n){
		int x;
		cin>>x;
		auto[l,r]=D(x,i);
		M(x,i);
		for(int p=r,y,q;p>=l;p=q)q=t[(y=Q(p-1))+S],I(y,p,i);
		I(!x,i,i);
	}
	F(i,0,n)D(i,n+1);
	set<int>w;
	F(i,0,n)w.insert(i);
	F(i,1,n){
		for(int x:V[i])
			if(x<0){
				if(!--c[~x])w.insert(~x);
			}else{
				if(!c[x]++)w.erase(x);
			}
		cout<<*w.begin()<<" \n"[i==n];
	}
}
