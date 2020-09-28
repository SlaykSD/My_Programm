
#include "pch.h"
#include "../Line_line/Catenary.cpp"

TEST(CatenaryConstructor, DefaultConstructor) {
    Chain_Line::CH_Line line;
    Chain_Line::Point p;
    double a = 1;
    ASSERT_EQ(a, line.getHeight());    
    ASSERT_EQ(-1, line.getP1().x);
    ASSERT_EQ(1, line.getP2().x);
}

TEST(CatenaryConstructor, InitConstructors)
{
    Chain_Line::CH_Line a(2,3,1);
    Chain_Line::Point p(2, 3);
    Chain_Line::Point p0(3, 3);
    ASSERT_EQ(p.x, a.getP1().x);
    ASSERT_EQ(p0.x, a.getP2().x);
    ASSERT_EQ(1, a.getHeight());    
}

TEST(CatenaryConstructor, TestException)
{
    ASSERT_ANY_THROW(Chain_Line::CH_Line(2, 5, -5));
}

TEST(CatenaryMethods, Setters)
{
    Chain_Line::CH_Line a;
    Chain_Line::Point p1(3, 2);
    a.setPoints(p1.x, p1.y);
    ASSERT_EQ(2, a.getP1().x);
    ASSERT_EQ(3, a.getP2().x);
    Chain_Line::CH_Line a0(2, 3, 2);
    a0.setHeight(3);
    ASSERT_EQ(3, a0.getHeight());
    ASSERT_ANY_THROW(a0.setHeight(-1));
}

TEST(CatenaryMethods, Parameters)
{
    Chain_Line::CH_Line a1;
    const double PI = 3.14159, err = 0.0001;
    ASSERT_NEAR(1.543080, a1.f(1), err);
    ASSERT_NEAR(1, a1.f(0), err);
    ASSERT_NEAR(1.0000000, a1.L(10), err);
    /*ASSERT_NEAR(1.0000000, a1.Integral(), err);
    ASSERT_NEAR(1.0000000, a1.L2(), err);
    ASSERT_NEAR(1.0000000, a1.R(2), err);
    ASSERT_EQ(0, a1.distance());
    ASSERT_EQ(0, a1.f(1).x);
    ASSERT_EQ(0, a1.f(1).y);
    ASSERT_EQ(1, a1.f(0).x);
    ASSERT_EQ(-1, a1.f(0).y);
    ASSERT_ANY_THROW(a1.f(2));
    ASSERT_STREQ("x ^ 2 + y ^ 2 = 1.00\n", a1.frm());
    Prog2::Circle a2(1, 3, 2);
    ASSERT_NEAR(PI * 4, a2.area(), err);
    ASSERT_NEAR(2 * PI * 2, a2.perimeter(), err);
    ASSERT_EQ(sqrt(10), a2.distance());
    ASSERT_EQ(5, a2.f(1).x);
    ASSERT_EQ(1, a2.f(1).y);
    ASSERT_NEAR(3 + sqrt(3), a2.f(0).x, err);
    ASSERT_EQ(3 - sqrt(3), a2.f(0).y);
    ASSERT_ANY_THROW(a2.f(-2));
    ASSERT_STREQ("(x - 1.00) ^ 2 + (y - 3.00) ^ 2 = 4.00\n", a2.frm());*/
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}