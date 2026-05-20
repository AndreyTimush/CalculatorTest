#include <gtest/gtest.h>

#include "parser.h"
#include "data.h"   
#include "runner.h" 
#include "checker.h"
#include "calculator.h"
#include <nlohmann/json.hpp>

TEST(ParserTest, ParseValidJson)
{
    Parser parser;
    Data data;

    char arg0[] = "prog";
    char arg1[] = "{\"firstArgument\":5,\"operation\":\"+\",\"secondArgument\":3}";
    char* argv[] = {arg0, arg1};

    parser.parsing(data, 2, argv);

    EXPECT_EQ(data.getFirstArg(), 5);
    EXPECT_EQ(data.getSecondArg(), 3);
    EXPECT_EQ(data.getOperation(), '+');
}

TEST(ParseTest, FirstInvalidArgument)
{
    Parser parser;
    Data data;

    char arg0[] = "prog";
    char arg1[] = "{\"firstArgument\":\"1231231\",\"operation\":\"+\",\"secondArgument\": 5}";
    char* argv[] = {arg0, arg1};

    EXPECT_THROW(parser.parsing(data, 2, argv), std::exception);
}

TEST(ParseTest, OperationInvalidArgument)
{
    Parser parser;
    Data data;

    char arg0[] = "prog";
    char arg1[] = "{\"firstArgument\":3,\"operation\":\"+123\",\"secondArgument\": 5}";
    char* argv[] = {arg0, arg1};

    EXPECT_THROW(parser.parsing(data, 2, argv), std::exception);
}

TEST(ParseTest, SecondInvalidArgument)
{
    Parser parser;
    Data data;

    char arg0[] = "prog";
    char arg1[] = "{\"firstArgument\":123,\"operation\":\"+\",\"secondArgument\":\"5sada\"}";
    char* argv[] = {arg0, arg1};

    EXPECT_THROW(parser.parsing(data, 2, argv), std::exception);
}

TEST(ParseTest, IntegerOverflowFirstArgument)
{
    Parser parser;
    Data data;

    char arg0[] = "prog";
    char arg1[] = "{\"firstArgument\":21474836747,\"operation\":\"+\",\"secondArgument\": 5}";
    char* argv[] = {arg0, arg1};

    EXPECT_THROW(parser.parsing(data, 2, argv), std::exception);
}

TEST(ParseTest, IntegerOverflowSecondArgument)
{
    Parser parser;
    Data data;

    char arg0[] = "prog";
    char arg1[] = "{\"firstArgument\":123,\"operation\":\"+\",\"secondArgument\": 21474832647}";
    char* argv[] = {arg0, arg1};

    EXPECT_THROW(parser.parsing(data, 2, argv), std::exception);
}

TEST(CheckerTest, ValidOperationCalculatesResult)
{
    Data data;
    data.setFirstArg(10);
    data.setOperation('+');
    data.setSecondArg(5);

    Checker checker;

    EXPECT_NO_THROW(checker.checkData(data));
}

TEST(CheckerTest, InvalidOperationCheckerError)
{
    Data data;
    data.setFirstArg(10);
    data.setOperation('?');
    data.setSecondArg(5);

    Checker checker;

    EXPECT_THROW(checker.checkData(data), std::exception);
}

TEST(CalculatorTest, ValidPlusResult)
{
    Data data;
    data.setFirstArg(10);
    data.setOperation('+');
    data.setSecondArg(5);

    Calculator calculator;
    calculator.calculating(data);
    EXPECT_FLOAT_EQ(data.getResult(), 15.0f);
}

TEST(CalculatorTest, InvalidPlusResult)
{
    Data data;
    data.setFirstArg(2147483647);
    data.setOperation('+');
    data.setSecondArg(100000);

    Calculator calculator;
    EXPECT_THROW(calculator.calculating(data), std::exception);
}

TEST(CalculatorTest, ValidSubtractionResult)
{
    Data data;
    data.setFirstArg(230);
    data.setOperation('-');
    data.setSecondArg(22);
    
    Calculator calculator;
    calculator.calculating(data);

    EXPECT_EQ(data.getResult(), 208);
}

TEST(CalculatorTest, InvalidSubtractionResult)
{
    Data data;
    data.setFirstArg(-2147483647);
    data.setOperation('-');
    data.setSecondArg(22);
    
    Calculator calculator;

    EXPECT_THROW(calculator.calculating(data), std::exception);
}

TEST(CalculatorTest, ValidMultiplicationResult)
{
    Data data;
    data.setFirstArg(7);
    data.setOperation('*');
    data.setSecondArg(8);
    
    Calculator calculator;
    calculator.calculating(data);

    EXPECT_EQ(data.getResult(), 56);
}

TEST(CalculatorTest, InvalidMultiplicationResult)
{
    Data data;
    data.setFirstArg(2147483647);
    data.setOperation('*');
    data.setSecondArg(8);
    
    Calculator calculator;
    
    EXPECT_THROW(calculator.calculating(data), std::exception);
}

TEST(CalculatorTest, ValidDivisionResult)
{
    Data data;
    data.setFirstArg(13);
    data.setOperation('/');
    data.setSecondArg(3);
    
    Calculator calculator;
    calculator.calculating(data);

    EXPECT_FLOAT_EQ(data.getResult(), 13.0f / 3.0f);
}

TEST(CalculatorTest, InvalidDivisionResult)
{
    Data data;
    data.setFirstArg(10);
    data.setOperation('/');
    data.setSecondArg(0);

    Calculator calculator;
    
    EXPECT_THROW(calculator.calculating(data), std::exception);
}

TEST(CalculatorTest, ValidPowResult)
{
    Data data;
    data.setFirstArg(2);
    data.setOperation('^');
    data.setSecondArg(3);
    
    Calculator calculator;
    calculator.calculating(data);

    EXPECT_EQ(data.getResult(), 8);
}

TEST(CalculatorTest, InvalidPowResult)
{
    Data data;
    data.setFirstArg(2147483647);
    data.setOperation('^');
    data.setSecondArg(3);
    
    Calculator calculator;

    EXPECT_THROW(calculator.calculating(data), std::exception);
}

TEST(CalculatorTest, ValidFactorialResult)
{
    Data data;
    data.setFirstArg(4);
    data.setOperation('!');
    
    Calculator calculator;
    calculator.calculating(data);

    EXPECT_EQ(data.getResult(), 24);
}

TEST(CalculatorTest, InvalidFactorialResult)
{
    Data data;
    data.setFirstArg(13);
    data.setOperation('!');
    
    Calculator calculator;

    EXPECT_THROW(calculator.calculating(data), std::exception);
}