#include <bits/stdc++.h>
#include <bits/extc++.h>
#define $0 get<0>
#define $1 get<1>
#define $2 get<2>
#define $3 get<3>
#define fi first
#define se second
#define gcd __gcd
#define pbds __gnu_pbds
#define popcount __builtin_popcountll
#define seed chrono::steady_clock::now().time_since_epoch().count
using namespace std;
using u16=unsigned short;
using i16=short;
using u32=unsigned int;
using u64=unsigned long long;
using i64=long long;
#ifdef __SIZEOF_INT128__
using u128=unsigned __int128;
using i128=__int128;
#else
using u128=unsigned long long;
using i128=long long;
#endif
struct hash64 
{static constexpr u64 _s(u64 x)
{return x+=0x9e3779b97f4a7c15,x=(x^(x>>30))*0xbf58476d1ce4e5b9,x=(x^(x>>27))*0x94d049bb133111eb,x^(x>>31);}
size_t operator()(u64 x)const{static const u64 f=seed();return _s(x+f);}};
template<class K,class V>using umap=pbds::gp_hash_table<K,V,hash64>;
template<class T,class C=less<T>>using heap=pbds::priority_queue<T,C>;
template<class T,class C=less<T>>using bst=pbds::tree<T,pbds::null_type,C,pbds::rb_tree_tag,pbds::tree_order_statistics_node_update>;
template<class T>constexpr T lowbit(T x){return x&-x;}
template<class T>constexpr T lg(T x){return x?__lg(x):0;}
template<class T>constexpr T ctz(T x){return x?__builtin_ctzll(x):0;}
constexpr u32 popcount128(u128 x){return popcount((u64)x)+popcount((u64)(x>>64));}
constexpr u32 ctz128(u128 x){return x?(u64)x?ctz((u64)x):64+ctz((u64)(x>>64)):0;}
template<class T>constexpr void chkmax(T&x,T y){x=max(x,y);}
template<class T>constexpr void chkmin(T&x,T y){x=min(x,y);}
template<class T1,class T2>ostream&operator<<(ostream&out,const pair<T1,T2>&p){return out<<"("<<p.fi<<", "<<p.se<<")";}
template<class T1,class T2>istream&operator>>(istream&in,pair<T1,T2>&p){return in>>p.fi>>p.se;}
template<class T,typename=decltype(declval<T>().begin()),typename=enable_if_t<!is_same<decay_t<T>,string>::value>>
ostream&operator<<(ostream&out,const T&v){int n=v.size();out<<"[";for(auto&x:v)out<<x<<(--n?", ":"");return out<<"]";}
mt19937 rand32(seed());
mt19937_64 rand64(seed());
#undef assert
#ifdef SPN_LOCAL
#define assert(x) (x)?void():(cerr<<"Assertion Failed On Line "<<__LINE__<<endl,exit(0))
void _o(auto&&...x){int f=1;((cerr<<(f?"":", ")<<x,f=0),...);}
#define mdebug(...) (cerr<<"On Line "<<__LINE__<<": ["<<#__VA_ARGS__<<"] = {",_o(__VA_ARGS__),cerr<<"}\n")
#define debug(x) (cerr<<"On Line "<<__LINE__<<": "<<#x<<" = "<<(x)<<endl)
#define FILE(x) void()
#define FLOCAL(x) freopen(x".in","r",stdin),freopen(x".out","w",stdout)
#define FDEBUG(x) freopen(x".txt","w",stderr)
#else
#define mdebug(...) void()
#define assert(x) void()
#define debug(x) void()
#define FILE(x) freopen(x".in","r",stdin),freopen(x".out","w",stdout)
#define FLOCAL(x) void()
#define FDEBUG(x) void()
#endif //SPN_LOCAL

#define int long long
const int N = 1e5 + 5, inf = 1e18;

int a, b;
int f(int a, int b) {
    if (a > b) return inf;
    return b - a;
}

void _main() {
    cin >> a >> b;
    cout << min({f(a, b), f(-a, b) + 1, f(a, -b) + 1, f(-a, -b) + 2});
} signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr), cerr.tie(nullptr);
    
    int t = 1; for (/*cin >> t*/; t--; ) _main();
    return 0;
}
