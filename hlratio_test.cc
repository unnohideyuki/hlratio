#include <gtest/gtest.h>
#include "hlratio.h"
using namespace HaskellLike;
#include <cmath>

TEST(RatioTest, Constructors){
  rat a;
  EXPECT_EQ(0, a.numerator());
  EXPECT_EQ(1, a.denominator());

  rat b = rat(1LL << 60);
  EXPECT_EQ(1LL << 60, b.numerator());
  EXPECT_EQ(1, b.denominator());
  
  rat c = rat(10, -2);
  EXPECT_EQ(-5, c.numerator());
  EXPECT_EQ(1, c.denominator());

  rat d = c;
  EXPECT_EQ(-5, d.numerator());
  EXPECT_EQ(1, d.denominator());

  rat e(b);
  EXPECT_EQ(1LL << 60, e.numerator());
  EXPECT_EQ(1, e.denominator());

  rat f = rat(1.625);
  EXPECT_EQ(13, f.numerator());
  EXPECT_EQ(8, f.denominator());
}

TEST(RatioTest, Casts){
  EXPECT_EQ(1LL << 60, (long long) rat(1LL << 60));
  double d = 2526287.875;
  EXPECT_EQ(d, double(rat(d)));
}

TEST(RatioTest, RelationalOperators){
  rat a = rat(10LL);
  rat b = rat(100, 10);
  rat c = rat(0LL);
  rat d = rat(-1.5);

  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a == c);

  EXPECT_FALSE(a != b);
  EXPECT_TRUE(a != c);
  
  EXPECT_TRUE(a <= b);
  EXPECT_TRUE(d <= c);
  EXPECT_FALSE(a <= c);

  EXPECT_FALSE(a < b);
  EXPECT_TRUE(d <= c);
  EXPECT_FALSE(a <= c);

  EXPECT_TRUE(a >= b);
  EXPECT_TRUE(c >= d);
  EXPECT_FALSE(c >= a);

  EXPECT_FALSE(a > b);
  EXPECT_TRUE(c >= d);
  EXPECT_FALSE(c >= a);
}

TEST(RatioTest, Arithmetic){
  EXPECT_TRUE(rat(5, 6) == rat(1,3) + rat(1,2));
  EXPECT_TRUE(rat(-1, 6) == rat(1,3) - rat(1,2));
  EXPECT_TRUE(rat(1, 6) == rat(1,3) * rat(1,2));
  EXPECT_TRUE(rat(2, 3) == rat(1,3) / rat(1,2));

  rat a = rat(1, 9);
  rat b = rat(3, 7);
  rat x;

  x = a; x += b;
  EXPECT_TRUE(x == a + b);
  x = a; x -= b;
  EXPECT_TRUE(x == a - b);
  x = a; x *= b;
  EXPECT_TRUE(x == a * b);
  x = a; x /= b;
  EXPECT_TRUE(x == a / b);

  EXPECT_TRUE(recip(a) == rat(1LL) / a);
  EXPECT_TRUE(-b == rat(0LL) - b);
}

TEST(RatioTest, Sqrt){
  rat a = rat(2, 10000);
  EXPECT_EQ(std::sqrt(2.0)/100, sqrt(a));
}

TEST(RatioTest, StringToRatio){
  rat a = storat("0.0001");
  EXPECT_EQ(1, a.numerator());
  EXPECT_EQ(10000, a.denominator());
  rat b = storat("1.2345e+03");
  EXPECT_EQ(2469, b.numerator());
  EXPECT_EQ(2, b.denominator());
}
