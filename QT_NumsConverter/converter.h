#ifndef CONVERTER_H
#define CONVERTER_H

#include "bigfraction.h"

#include <QString>
#include <QHash>
#include <QVector>
#include <QString>
#include <QRegularExpression>
#include <QList>
#include <QMap>
#include <QStack>

class Converter {
public:
    Converter();

    QString convert(QString str, BigInteger fromBase, BigInteger toBase);

private:
    bool isValidString(const QString& str);

    BigInteger convertNumToDecimal(const QString& num, BigInteger fromBase);
    QString convertNumFromDecimal(BigInteger decimal, BigInteger toBase);
    BigFraction convertDenToDecimal(const QString& den, BigInteger fromBase, int DenSize);
    BigFraction convertPerToDecimal(const QString& per, BigInteger fromBase, int DenSize, int PerSize);
    QString convertDenFromDecimal(BigFraction fr, BigInteger toBase);
};


#endif // CONVERTER_H
