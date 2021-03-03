// g++ -O2 -I.. --std=gnu++17 -o abc191d abc191d.cc
#include "hlratio.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const double pi = 3.14159265359;

using namespace HaskellLike;

rat cx, cy, r;

bool llvalid = false;
ll cxll, cyll, rll;


bool incircle(ll x, ll y)
{
  if (!llvalid){
    cxll = ll(cx * rat(10000LL));
    cyll = ll(cy * rat(10000LL));
    rll = ll(r * rat(10000LL));
  }
  x *= 10000;
  y *= 10000;
  return  (x - cxll) * (x - cxll) + (y - cyll) * (y - cyll) <= rll*rll;
}

int main()
{
  cin >> cx >> cy >> r;
  ll ans = 0;
  for (ll i = ceil(double(cx - r)); i <= floor(double(cx + r)); i++){
    rat j = rat(i);
    double y1 = sqrt(r*r - (j - cx)*(j - cx));
    ll uy = floor(double(cy) + y1);
    ll ly = ceil(double(cy) - y1);

    if (incircle(i, uy+1)) uy++;
    else if (!incircle(i, uy)) uy--;
    if (incircle(i, ly-1)) ly--;
    else if (!incircle(i, ly)) ly++;
    
    if (uy >= ly) ans += uy - ly + 1;
  }
  cout << ans << endl;
  return 0;
}
