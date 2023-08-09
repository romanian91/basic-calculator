#pragma once

#include <string>
#include <sstream>
#include <memory>

constexpr char DIGIT{'0'};

// ------------------------------------------------------------------
class Calculator {
    struct Token {
        explicit Token(char _ch) : symbol(_ch) {}
                 Token(char _ch, double _val) : value(_val), symbol(_ch) {}

        double value{0.};
        char   symbol{DIGIT};
    };
public:
    explicit Calculator(std::string&& _expr);
    ~Calculator() = default;

    double Calculate();

private:
    std::unique_ptr<Calculator::Token> NextToken();
    void SaveToken(std::unique_ptr<Calculator::Token>);

    double PrimaryExpression();
    double Term();

private:
    std::stringstream      m_stream;
    std::unique_ptr<Token> m_buf;
};
