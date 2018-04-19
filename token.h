#ifndef TOKEN_H
#define TOKEN_H

#include <QVariant>

struct Token
{
    enum class TokenType
    {
        None,
        Number,
        Operator,
        Function
    };

    enum class StackEvent
    {
        PopWhile,
        PushIn,
        PushWithoutCheck
    };

    Token() = default;
    Token(const QVariant& data, bool association, const TokenType &tType);

    QVariant m_data{'\0'};
    bool m_association{false}; // false == left assotiation
    TokenType m_tType{TokenType::None};
    unsigned short int priority{0}; // 0 it's lowest priority
    StackEvent sEvent;
    double (*action)(double val1, double val2){nullptr};

    static Token defineOperatorType(const QChar &tok);

private:
    static double add(double val1, double val2);
    static double subtract(double val1, double val2);
    static double divide(double val1, double val2);
    static double multiply(double val1, double val2);
    static double remOfDiv(double val1, double val2);
    static double power(double val, double pow);
};

#endif // TOKEN_H
