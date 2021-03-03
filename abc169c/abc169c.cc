// g++ -O2 -I.. --std=gnu++17 -o abc169c abc169c.cc
#include "hlratio.h"
#include <bits/stdc++.h>
using namespace std;
using namespace HaskellLike;
int main()
{
  rat a, b;
  cin >> a >> b;
  long long ans = (long long)(a*b);
  cout << ans << endl;
}
