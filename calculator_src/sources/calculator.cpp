
#include "calculator.h"

#include <algorithm>
#include <cctype>

// ------------------------------------------------------------------
static bool is_digit(char _c) {
    return std::isdigit(_c) || '.' == _c;
}

// ------------------------------------------------------------------
static bool is_operator(char _c) {
    switch (_c) {
        case '(':
        case ')':
        case '+':
        case '-':
        case '*':
        case '/': return true;
    }
    return false;
}

// ------------------------------------------------------------------
Calculator::Calculator(std::string&& _expr) {
    std::replace(_expr.begin(), _expr.end(), ',', '.');
    m_stream.str(_expr);
}

// ------------------------------------------------------------------
std::unique_ptr<Calculator::Token> Calculator::NextToken() {
    if ( m_buf ) {
        return std::move(m_buf);
    }

    if (0 == m_stream.rdbuf()->in_avail())
        return std::make_unique<Token>(DIGIT);

    char ch;
    m_stream >> ch;

    if (::is_operator(ch)) {
        return std::make_unique<Token>(ch);
    }

    if (::is_digit(ch)) {
        m_stream.putback(ch);
        double val{ 0. };
        m_stream >> val;
        return std::make_unique<Token>(DIGIT, val);
    }

    throw std::runtime_error(std::string("wrong symbol: ") + ch);
}

// ------------------------------------------------------------------
void Calculator::SaveToken(std::unique_ptr<Token> _t) {
    if (m_buf) {
        throw std::runtime_error( std::string("buffer already contain Token: ") + m_buf->symbol);
    }
    m_buf = std::move(_t);
}

// -------------------------------------------------------------------
double Calculator::PrimaryExpression() {
    auto t = NextToken();

    switch (t->symbol) {
    case '(': {
        double d = Calculate();
        t = NextToken();

        if (t->symbol != ')') {
            throw std::runtime_error(std::string("')' expected. got: ") + t->symbol);
        }
        return d;
    }
    case DIGIT: return t->value;
    case '-'  : return -PrimaryExpression();

    default:
        throw std::runtime_error(std::string("primary expression expected. got: ") + t->symbol);
    }
}

// -------------------------------------------------------------------
double Calculator::Term() {
    double left = PrimaryExpression();
    auto t = NextToken();

    while (true) {
        switch (t->symbol) {
            case '*': {
                left *= PrimaryExpression();
                t = NextToken();
                break;
            }
            case '/': {
                double d = PrimaryExpression();

                if (d == 0.) {
                    throw std::runtime_error("division by zero");
                }

                left /= d;
                t = NextToken();
                break;
            }
            default: {
                SaveToken(std::move(t));
                return left;
            }
        }
    }
}

// -------------------------------------------------------------------
double Calculator::Calculate() {
    double left = Term();

    auto t = NextToken();
    while (true) {
        switch (t->symbol) {
            case '+':
                left += Term();
                t = NextToken();
                break;
            case '-':
                left -= Term();
                t = NextToken();
                break;
            default:
                SaveToken(std::move(t));
                return left;
        }
    }
}


