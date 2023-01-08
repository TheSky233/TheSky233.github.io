#include <bits/stdc++.h>
using namespace std;
// 0.3 qpow
/*
template<class T = long long> T qpow(T a, T b,const T mod = 998244353){
	T ans = 1, base = a;
	while(b){
		if(b & 1) ans = ans * base % mod;
		base = base * base % mod;
		b >>= 1;
	}
	return ans;
}
*/

// 1.2.2 prime check O(n)
bool check_linear(int x){
	for(int i = 2; i < x; i++){
		if(x % i == 0) return false;
	}
	return true;
}

// 1.2.2 prime check O(sqrt(n))
bool check_sqrt(int x){
	for(int i = 2; i * i <= x; i++){
		if(x % i == 0) return false;
	}
	return true;
}

// 1.2.3.1 Eratosthenes sieve
//bool vis[1000005];
//vector<int> prime;
/*
void Eratosthenes_sieve(int n){
	vis[1] = 1;
	for(int i = 2; i <= n; i++){
		if(vis[i] == 0){
			prime.push_back(i);
			for(int j = i + i; j <= n; j += i){
				vis[j] = 1;
			}
		}
	}
}
*/

// 1.2.3.2 Euler seive
bool vis[1000005];
vector<int> prime;
void Euler_sieve(int n){
	vis[1] = 1;
	for(int i = 2; i <= n; i++){
		if(!vis[i]) prime.push_back(i);
		for(int j = 0; (size_t)j < prime.size(); j++){
			int it = prime.at(j);
			if(1ll * it * i > n) break;
			vis[1ll * it * i] = 1;
			if(i % it == 0){
				// i % pri[j] == 0
		        // 换言之，i 之前被 pri[j] 筛过了
		        // 由于 pri 里面质数是从小到大的，所以 i 乘上其他的质数的结果一定也是
		        // pri[j] 的倍数 它们都被筛过了，就不需要再筛了，所以这里直接 break
		        // 掉就好了
		        // From OI-Wiki
				break;
			}
		}
	}
}

// 1.2.3.3 Miller-Rabin

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

ll mul(ll a,ll b,ll mod){
    ll c=(ld)a/mod*b;
    ll res=(ull)a*b-(ull)c*mod;
    return (res+mod)%mod;
}

ll qpow(ll a,ll b,const ll p){
	ll ans=1ll,base=a;
	while(b){
		if(b&1) ans=mul(ans,base,p);
		base=mul(base,base,p);
		b>>=1;
	}
	return ans;
}

// ll ud[]={2,325,9375,28178,450775,9780504,1795265022};
ll ud[]={2,3,5,7,11,13,17,19,23};

bool MRtest(ll n){
	if(n%2==0 || n<3) return n==2;
	ll u=n-1,t=0;
	while(u%2==0) u>>=1,++t;
	ll x,pre;
	for(auto p:ud){
		if(p==n) return true;
		x=qpow(p,u,n);
		pre=x;
		for(int i=1;i<=t;i++){
			x=mul(x,x,n);
			if(x==1 && pre!=1 && pre!=n-1) return false;
			pre=x;
		}
		if(x!=1) return false;
	}
	return true;
}


vector<pair<int,int> > factor(ll x){
	vector<pair<int,int> > v;
	for(ll i=2;i*i<=x;i++){
		if(x%i==0){
			int t=0;
			while(x%i==0) t++,x/=i;
			v.push_back(make_pair(i,t));
		}
	}
	if(x>1) v.push_back(make_pair(x,1));
	return v;
}

ll gcd0(ll a,ll b){
    int tmp;
    while(b!=0){
        tmp=b;
        b=a%b;
        a=tmp;
    }
    return a;
}

ll gcd(ll a,ll b){
	if(b==0) return a;
	return gcd(b,a%b);
}

ll gcd2(ll a,ll b){
	return b==0?a:gcd(b,a%b);
}

ll gcd03(ll a,ll b){
    while(b){
        a%=b;
        b^=a;
        a^=b;
        b^=a;
    }
    return a;
}

ll gcd3(ll a,ll b){
	while(b^=a^=b^=a%=b);
	return a;
}

ll lcm(ll a,ll b){
	return a/gcd(a,b)*b;
}

ll exgcd(ll a,ll b,ll &x,ll &y){
	if(b==0){
		x=1; y=0;
		return a;
	}
	ll d=exgcd(b,a%b,x,y);
	ll t=x;
	x=y;
	y=t-(a/b)*y;
	return d;
}

int n;
ll x,y;

using ld = long double;

int main(){
	ll p=exgcd(114514,1919810,x,y);
	cout<<x<<' '<<y<<' '<<p<<endl;
}
