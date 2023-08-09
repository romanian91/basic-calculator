#pragma once

#include <cxxtest/TestSuite.h>
#include "calculator.h"

class CalculatorTestSuite : public CxxTest::TestSuite
{
public:

    void test_addition(void) {
        Calculator c("2+2");
        TS_ASSERT_EQUALS(c.Calculate(), 4.);
    }

    void test_substraction(void) {
        Calculator c("2-2");
        TS_ASSERT_EQUALS(c.Calculate(), 0.);
    }

    void test_multiplication(void) {
        Calculator c("2*10)");
        TS_ASSERT_EQUALS(c.Calculate(), 20.);
    }

    void test_division(void) {
        Calculator c("100/10");
        TS_ASSERT_EQUALS(c.Calculate(), 10.);
    }

    void test_division_by_zero1(void) {
        Calculator c("50/0");
        TS_ASSERT_THROWS_EQUALS(c.Calculate(), std::runtime_error& _e, _e.what(), "division by zero");
    }

    void test_division_by_zero2(void) {
        Calculator c("100 / (10 - 10)");
        TS_ASSERT_THROWS_EQUALS(c.Calculate(), std::runtime_error& _e, _e.what(), "division by zero");
    }

    void test_spaces_ignore(void) {
        Calculator c("  2  *  (  1 + 3  )");
        TS_ASSERT_EQUALS(c.Calculate(), 8.);
    }

    void test_no_closed_brace(void) {
        Calculator c("  2  *  ((  1 + 3  )*2");
        TS_ASSERT_THROWS_EQUALS(c.Calculate(), std::runtime_error& _e, _e.what(), "')' expected. got: 0");
    }

    void test_dot_separator(void) {
        Calculator c("2.5 * (1.0+3.0)");
        TS_ASSERT_EQUALS(c.Calculate(), 10.);
    }

    void test_comma_separator(void) {
        Calculator c("2,5 * (1,0+3,0)");
        TS_ASSERT_EQUALS(c.Calculate(), 10.);
    }

    void test_operation_priority1(void) {
        Calculator c("2*(1+3)");
        TS_ASSERT_EQUALS(c.Calculate(), 8.);
    }
    
    void test_operation_priority2(void) {
        Calculator c("(2*1)+3");
        TS_ASSERT_EQUALS(c.Calculate(), 5.);
    }
    
    void test_operation_priority3(void) {
        Calculator c("2*1+3");
        TS_ASSERT_EQUALS(c.Calculate(), 5.);
    }

    void test_operation_priority4(void) {
        Calculator c("2+1*3");
        TS_ASSERT_EQUALS(c.Calculate(), 5.);
    }
    
    void test_unsupported_character(void) {
        Calculator c("a");
        TS_ASSERT_THROWS_EQUALS(c.Calculate(), std::runtime_error& _e, _e.what(), "wrong symbol: a");
    }

    void test_expression1(void) {     
        Calculator c( " -1 + 5 - 3" );
        TS_ASSERT_EQUALS(c.Calculate(), 1.);
    }

    void test_expression2(void) {
        Calculator c( " - 10 + (8 * 2.5) - (3 / 1,5)");
        TS_ASSERT_EQUALS(c.Calculate(), 8.);
    }
    
    void test_expression3(void) {
        Calculator c( "1 + (2 * (2.5 + 2.5 + (3-2))) - (3 / 1.5)" );
        TS_ASSERT_EQUALS( c.Calculate(), 11. );	
    }
};