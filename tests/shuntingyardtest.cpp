#include <gtest/gtest.h>

#include "../shuntingyard.h"

TEST(ShuntingYardTest, correctSimpleTokenWithAddition)
{
    std::unique_ptr<ShuntingYard> calculator(new ShuntingYard);

    auto res = calculator->calculate("1+3");

    ASSERT_EQ(res, 4);
}

TEST(ShuntingYardTest, correctTokenWithBrackets)
{
    std::unique_ptr<ShuntingYard> calculator(new ShuntingYard);

    auto res = calculator->calculate("(1+1+3)*3");

    ASSERT_EQ(res, 15.0);
}

TEST(ShuntingYardTest, correctTokenWithBracketsAndRiseToDegree)
{
    std::unique_ptr<ShuntingYard> calculator(new ShuntingYard);

    auto res = calculator->calculate("2^2*(1+1+3)*3");

    ASSERT_EQ(res, 60.0);
}

TEST(ShuntingYardTest, invalidToken)
{
    std::unique_ptr<ShuntingYard> calculator(new ShuntingYard);

    auto res = calculator->calculate("lorem ipsum");

    ASSERT_EQ(res, 0);
}
