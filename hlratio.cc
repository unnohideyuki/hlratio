namespace HaskellLike {
  class rat {
  private:
    long long x, y;
    static __int128 gcd(__int128 a, __int128 b)
    {
      __int128 x = a >= 0 ? a : -a;
      __int128 y = b >= 0 ? b : -b;
      while (y > 0){
	__int128 r = x % y;
	x = y;
	y = r;
      }
      return x;
    }
    static void reduce128(__int128& x, __int128& y)
    {
      __int128 g = gcd(x, y);
      x /= g;
      y /= g;
    }
    static void reducell(long long& x, long long& y)
    {
      long long g = gcd(x, y);
      x /= g;
      y /= g;
    }
  public:
    rat() : x{0}, y{1} {}
    explicit rat(long long a) : x{a}, y{1} {}
    rat(long long n, long long d) : x{n}, y{d}
    {
      if (y < 0){
	x = -x;
	y = -y;
      }
      reducell(x, y);
    }
    rat(const rat& a) = default; // copyable
    rat& operator=(const rat& a) = default; // copyable
    explicit rat(double a)
    {
      int e;
      long long c = 1LL << DBL_MANT_DIG;
      double m = std::frexp(a, &e);
      __int128 n = (long long)(m * std::pow(2, DBL_MANT_DIG));
      __int128 d = c;
      if (e >= 0) n *= (long long)(std::pow(2, e));
      else d *= (long long)(std::pow(2, -e));
      reduce128(n, d);
      x = (long long) n;
      y = (long long) d;
    }
    explicit operator double() const
    {
      double n = double(x);
      double d = double(y);
      return n/d;
    }
    explicit operator long long() const
    {
      return x/y;
    }
    long long numerator() const { return x; }
    long long denominator() const { return y; }
    rat reduce()
    {
      reducell(x, y);
      return *this;
    }
    friend rat reduce(const rat& a)
    {
      rat r = a;
      return r.reduce();
    }
    bool operator==(const rat& rhs)
    {
      __int128 n1 = x;
      __int128 n2 = rhs.x;
      return (n1 * rhs.y == n2 * y);
    }
    bool operator!=(const rat& rhs){ return !(*this == rhs); }
    bool operator<=(const rat& rhs)
    {
      __int128 n1 = x;
      __int128 n2 = rhs.x;
      return (n1 * rhs.y <= n2 * y);
    }
    bool operator<(const rat& rhs)
    {
      __int128 n1 = x;
      __int128 n2 = rhs.x;
      return (n1 * rhs.y < n2 * y);
    }
    bool operator>(const rat& rhs){ return !(*this <= rhs); }
    bool operator>=(const rat& rhs){ return !(*this < rhs); }
    friend rat operator+(const rat& a, const rat& b)
    {
      __int128 xa = a.x;
      __int128 ya = a.y;
      __int128 xb = b.x;
      __int128 yb = b.y;
      __int128 n = xa * yb + xb * ya;
      __int128 d = ya * yb;
      reduce128(n, d);
      return rat((long long) n, (long long) d);
    }
    rat operator-() const { return rat(-x, y); }
    friend rat operator-(const rat& a, const rat& b){ return (a + -(b)); }
    friend rat operator*(const rat& a, const rat& b)
    {
      __int128 xa = a.x;
      __int128 ya = a.y;
      __int128 xb = b.x;
      __int128 yb = b.y;
      __int128 n = xa * xb;
      __int128 d = ya * yb;
      reduce128(n, d);
      return rat((long long) n, (long long) d);
    }
    friend rat operator/(const rat& a, const rat& b)
    {
      __int128 xa = a.x;
      __int128 ya = a.y;
      __int128 xb = b.x;
      __int128 yb = b.y;
      __int128 n = xa * yb;
      __int128 d = ya * xb;
      reduce128(n, d);
      return rat((long long) n, (long long) d);
    }
    rat operator+=(const rat& rhs){ return (*this = *this + rhs); }
    rat operator-=(const rat& rhs){ return (*this = *this - rhs); }
    rat operator*=(const rat& rhs){ return (*this = *this * rhs); }
    rat operator/=(const rat& rhs){ return (*this = *this / rhs); }
  };
  rat abs(const rat& a){ return rat(std::abs(a.numerator()), a.denominator()); }
  rat recip(const rat& a){ return rat(a.denominator(), a.numerator()); }
  double sqrt(const rat& a)
  {
    double p = std::sqrt(a.numerator());
    double q = std::sqrt(a.denominator());
    return p/q;
  }
  rat storat(const std::string& s)
  {
    int epos = -1;
    int pos = -1;
    std::string t;
    for (int i = 0; i < int(s.size()); i++){
      if (s[i] == 'e' || s[i] == 'E'){ epos = i; break; }
      if (s[i] == '.') pos = i;
      else t += s[i];
    }
    long long n = std::stod(t);
    long long d = 1;
    if (pos >= 0){
      d = (long long) std::pow(10, t.size() - pos);
    }
    if (epos >= 0){
      n *= (long long) std::pow(10, std::stol(s.substr(epos+1)));
    }
    return rat(n, d);
  }
  std::istream& operator>>(std::istream& is, rat& a)
  {
    std::string s;
    is >> s;
    a = storat(s);
    return is;
  }
} // HaskellLike
