#include "shuntingyard.h"

#include <QDebug>

std::vector<Token> ShuntingYard::getReversePolishNotation(const QStringList &inputString) const
{
    qDebug() << inputString;
    std::vector<Token> outputStack;
    std::vector<Token> operatorStack;

    for (auto cData : inputString)
    {
        Token token;

        if (Token::isOperator(cData))
            token = Token::defineOperatorType(cData);
        else if (checkIsNumber(cData))
            token = {cData.toDouble(), false, Token::TokenType::Number};

        parseToken(outputStack, operatorStack, token);
    }

    for (auto riter = operatorStack.rbegin(); riter != operatorStack.rend(); riter++)
        outputStack.push_back(*riter);

    return outputStack;
}

double ShuntingYard::calculate(const std::vector<Token> &reversePolishNotation) const
{
    std::stack<double> resultStack;

    for (auto &token : reversePolishNotation)
    {
        switch (token.m_tType)
        {
        case Token::TokenType::Number:
            resultStack.push(token.m_data.toDouble());
            break;

        case Token::TokenType::Operator:
        {
            if (resultStack.empty())
                continue;

            auto val1 = resultStack.top();
            resultStack.pop();

            auto val2 = resultStack.top();
            resultStack.pop();

            resultStack.push(token.action(val2, val1));

            break;
        }
        default:
            break;
        }
    }

    return resultStack.top();
}

ShuntingYard::ShuntingYard(QObject *parent)
    :QObject(parent)
{
}

double ShuntingYard::calculateInputString() const
{
    if (calculated)
        return cache;
    else
    {
        auto inputString = m_inputString.simplified();

        auto reversePolishNotation = getReversePolishNotation(inputString.split(" "));

        cache = calculate(reversePolishNotation);

        return cache;
    }
}

bool ShuntingYard::checkIsNumber(const QString &cData) const
{
    bool isOk = false;
    cData.toDouble(&isOk);
    return isOk;
}

void ShuntingYard::parseToken(std::vector<Token> &outputStack, std::vector<Token> &operatorStack, const Token token) const
{
    switch (token.m_tType)
    {
    case Token::TokenType::Number:
        outputStack.push_back(token);
        return;
    case Token::TokenType::Operator:
    {
        if (operatorStack.empty())
        {
            operatorStack.push_back(token);
            return;
        }

        if (token.sEvent == Token::StackEvent::PushWithoutCheck)
        {
            operatorStack.push_back(token);
            return;
        }

        if (token.sEvent == Token::StackEvent::PopWhile)
        {
            while(operatorStack.back().m_data != "(")
            {
                outputStack.push_back(operatorStack.back());
                operatorStack.pop_back();
            }
            operatorStack.pop_back();

            return;
        }

        if (token.sEvent == Token::StackEvent::PushIn)
        {
            if (token.priority > operatorStack.back().priority)
            {
                operatorStack.push_back(token);
                return;
            }

            if (token.priority  <= operatorStack.back().priority)
            {
                outputStack.push_back(operatorStack.back());
                operatorStack.pop_back();
                operatorStack.push_back(token);
                return;
            }
        }
        break;
    }
    case Token::TokenType::None:
    default:
        return;
    }
}

void ShuntingYard::setInputString(const QString &inputString)
{
    if (m_inputString == inputString)
        return;
    calculated = false;
    m_inputString = inputString;
}

