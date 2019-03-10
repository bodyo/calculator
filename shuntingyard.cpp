#include "shuntingyard.h"

#include <QDebug>

ShuntingYard::ShuntingYard(QObject *parent)
    :QObject(parent)
{
}

std::vector<Token> ShuntingYard::getReversePolishNotation(const std::vector<Token> &inputTokens) const
{
    std::vector<Token> outputStack;
    std::vector<Token> operatorStack;

    for (auto token : inputTokens)
        parseToken(outputStack, operatorStack, token);

    for (auto riter = operatorStack.rbegin(); riter != operatorStack.rend(); riter++)
        outputStack.push_back(*riter);

    return outputStack;
}

double ShuntingYard::calculateReversePolishNotation(const std::vector<Token> &reversePolishNotation) const
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

    if (resultStack.empty())
        return 0;

    return resultStack.top();
}

double ShuntingYard::calculate(const QString &basicInputString)
{
    setInputString(basicInputString);
    
    if (calculated)
        return cache;

    auto inputString = m_inputString.simplified();
    inputString.replace(" ", "");

    auto parsedTokens = parseInputString(inputString);
    detectUnaryOperations(parsedTokens);
    auto reversePolishNotation = getReversePolishNotation(parsedTokens);
    cache = calculateReversePolishNotation(reversePolishNotation);
    calculated = true;

    return cache;
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

void ShuntingYard::detectUnaryOperations(std::vector<Token> &parsedTokens) const
{
    for (auto iter = parsedTokens.begin(); iter != parsedTokens.end(); ++iter)
    {
        if (iter+1 == parsedTokens.end())
            break;

        if (iter->m_tType == Token::TokenType::Operator && iter->m_data.toChar() == "-")
        {
            if (iter == parsedTokens.begin())
            {
                if ((iter+1)->m_tType == Token::TokenType::Number)
                {
                    iter->m_association = true;
                    auto data = -(iter+1)->m_data.toDouble();
                    (iter+1)->m_data = data;
                }
            }
        }
        if (iter + 2 == parsedTokens.end())
            break;

        if (iter->m_tType == Token::TokenType::Operator &&
                (iter+1)->m_tType == Token::TokenType::Operator &&
                (iter+2)->m_tType == Token::TokenType::Number)
        {
            if ((iter+1)->m_data.toChar() == "-")
            {
                (iter+1)->m_association = true;
                auto data = -(iter+2)->m_data.toDouble();
                (iter+2)->m_data = data;
            }
            else if ((iter+1)->m_data.toChar() == "+")
                (iter+1)->m_association = true;
        }

    }
    parsedTokens.erase(std::remove_if(parsedTokens.begin(), parsedTokens.end(), [](const Token &tok){
        return tok.m_association;
    }), parsedTokens.end());
}

void ShuntingYard::setInputString(const QString &inputString)
{
    if (m_inputString == inputString)
        return;
    calculated = false;
    m_inputString = inputString;
}

std::vector<Token> ShuntingYard::parseInputString(const QString &inputString) const
{
    std::vector<Token> parsedTokens;
    for (auto iter = inputString.begin(); iter != inputString.end(); ++iter)
    {
        QString string;
        Token token;
        while (iter->isDigit() || (*iter == '.'))
        {
            string.push_back(*iter);
            auto nextIt = iter+1;
            if ((nextIt->isDigit() || (*nextIt == '.')) && (nextIt != inputString.end()))
                iter++;
            else
            {
                token = {string.toDouble(), false, Token::TokenType::Number};
                break;
            }
        }

        if (token.m_tType != Token::TokenType::Number)
        {
            token = Token::defineOperatorType(*iter);
            if (token.m_tType == Token::TokenType::None)
                return {}; // replace to exception in future
        }

        parsedTokens.push_back(token);
    }

    return parsedTokens;
}
