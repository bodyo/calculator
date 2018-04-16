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

    Q_INVOKABLE double calculateInputString() const;
    Q_INVOKABLE void setInputString(const QString &inputString);

private:
    double calculate(const std::vector<Token> &reversePolishNotation) const;
    std::vector<Token> getReversePolishNotation(const QStringList &inputString) const;
    bool checkIsNumber(const QString &cData) const;
    void parseToken(std::vector<Token> &outputStack, std::vector<Token> &operatorStack, const Token token) const;

private:
    bool calculated;
    mutable double cache;
    QString m_inputString;
    std::vector<Token> m_reversePolishNotation;
};

#endif // SHUNTINGYARD_H
