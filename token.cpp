#include "token.h"

#include <QDebug>

Token::Token(const QVariant& data, bool association, const TokenType &tType)
    :m_data(data), m_association(association), m_tType(tType)
{

}

bool Token::isOperator(const QString &tok)
{
    if (tok == "(")
        return true;
    else if (tok == ")")
        return true;
    else if (tok == "+")
        return true;
    else if (tok == "-")
        return true;
    else if (tok == "*")
        return true;
    else if (tok == "/")
        return true;
    else if (tok == "^")
        return true;
    else
        return false;
}

Token Token::defineOperatorType(const QString &tok)
{
    Token token;
    token.m_data = tok;
    token.m_tType = TokenType::Operator;

    if (tok == "(")
    {
        token.sEvent = StackEvent::PushWithoutCheck;
        token.priority = 0;
        return token;
    }
    else if (tok == ")")
    {
        token.sEvent = StackEvent::PopWhile;
        token.priority = 0;
        return token;
    }
    else if (tok == "+")
    {
        token.sEvent = StackEvent::PushIn;
        token.priority = 1;
        token.action = &Token::add;
        return token;
    }
    else if (tok == "-")
    {
        token.sEvent = StackEvent::PushIn;
        token.priority = 1;
        token.action = &Token::subtract;
        return token;
    }
    else if (tok == "*")
    {
        token.sEvent = StackEvent::PushIn;
        token.priority = 2;
        token.action = &Token::multiply;
        return token;
    }
    else if (tok == "/")
    {
        token.sEvent = StackEvent::PushIn;
        token.priority = 2;
        token.action = &Token::divide;
        return token;
    }
    else if (tok == "^")
    {
        token.sEvent = StackEvent::PushIn;
        token.priority = 3;
        token.action = &Token::power;
        token.m_association = true;
        return token;
    }
    else
        return token;
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

double Token::power(double val, double pow)
{
    qDebug() << val << pow;
    return std::pow(val, pow);
}
