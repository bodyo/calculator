#include "token.h"

#include <QDebug>

#include <cmath>

Token::Token(const QVariant& data, bool association, const TokenType &tType)
    :m_data(data), m_association(association), m_tType(tType)
{
}

Token Token::defineOperatorType(const QChar &tok)
{
    Token token;
    token.m_data = tok;
    token.m_tType = TokenType::Operator;

    switch (tok.toLatin1())
    {
    case '(':
    {
        token.sEvent = StackEvent::PushWithoutCheck;
        token.priority = 0;
        return token;
    }
    case ')':
    {
        token.sEvent = StackEvent::PopWhile;
        token.priority = 0;
        return token;
    }
    case '+':
    {
        token.sEvent = StackEvent::PushIn;
        token.priority = 1;
        token.action = &Token::add;
        return token;
    }
    case '-':
    {
        token.sEvent = StackEvent::PushIn;
        token.priority = 1;
        token.action = &Token::subtract;
        return token;
    }
    case '*':
    {
        token.sEvent = StackEvent::PushIn;
        token.priority = 2;
        token.action = &Token::multiply;
        return token;
    }
    case '/':
    {
        token.sEvent = StackEvent::PushIn;
        token.priority = 2;
        token.action = &Token::divide;
        return token;
    }
    case '%':
    {
        token.sEvent = StackEvent::PushIn;
        token.priority = 2;
        token.action = &Token::remOfDiv;
        return token;
    }
    case '^':
    {
        token.sEvent = StackEvent::PushIn;
        token.priority = 3;
        token.action = &Token::power;
        return token;
    }
    default:
    {
        token.m_tType = TokenType::None;
        return token;
    }
    }
}

double Token::add(double val1, double val2)
{
    return val1 + val2;
}

double Token::subtract(double val1, double val2)
{
    return val1 - val2;
}

double Token::divide(double val1, double val2)
{
    return val1 / val2;
}

double Token::multiply(double val1, double val2)
{
    return val1 * val2;
}

double Token::remOfDiv(double val1, double val2)
{
    return fmod(val1, val2);
}

double Token::power(double val, double pow)
{
    return std::pow(val, pow);
}
