#ifndef SHUNTINGYARD_H
#define SHUNTINGYARD_H

#include <QString>

#include <stack>

#include "token.h"

class ShuntingYard : public QObject
{
    Q_OBJECT

public:
    explicit ShuntingYard(QObject *parent = nullptr);

    Q_INVOKABLE double calculate() const;
    Q_INVOKABLE void setInputString(const QString &inputString);

private:
    std::vector<Token> parseInputString(const QString& inputString) const;
    double calculateReversePolishNotation(const std::vector<Token> &reversePolishNotation) const;
    std::vector<Token> getReversePolishNotation(const std::vector<Token> &inputTokens) const;

    void parseToken(std::vector<Token> &outputStack, std::vector<Token> &operatorStack, const Token token) const;
    void detectUnaryOperations(std::vector<Token> &parsedTokens) const;

private:
    mutable bool calculated;
    mutable double cache;
    QString m_inputString;
    std::vector<Token> m_reversePolishNotation;
};

#endif // SHUNTINGYARD_H
