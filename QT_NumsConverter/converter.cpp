#include "converter.h"

Converter::Converter() {}

bool Converter::isValidString(const QString& str) {
    if (str.isEmpty() || str == "0" || str[0] == '.') {
        return false;
    }

    bool hasDot = false;
    bool hasOpenParentheses = false;
    bool hasCloseParentheses = false;
    bool hasOpenShape = false;
    int bracketCount = 0;
    int pointIndex = -1;

    for (int i = 0; i < str.size(); ++i) {
        QChar c = str[i];

        if (c == '.') {
            if (hasDot) {
                return false;
            }
            hasDot = true;
            pointIndex = i;
        }
        else if (c == '(') {
            if (hasCloseParentheses) {
                return false;
            }
            hasOpenParentheses = true;
            bracketCount++;
        } else if (c == ')') {
            hasCloseParentheses = true;
            if (bracketCount <= 0) {
                return false;
            }
            bracketCount--;
        }
        else if (c == '[') {
            if(!hasOpenShape)
                hasOpenShape = true;
            else
                return false;
        } else if (c == ']') {
            if(hasOpenShape)
                hasOpenShape = false;
            else
                return false;
        } else if(hasOpenShape && !c.isDigit() && c != ']') {
            return false;
        } else if(!c.isDigit() && !c.isLetter())
            return false;
    }

    if (bracketCount != 0 || (pointIndex == str.size() - 1) || hasOpenShape) {
        return false;
    }

    return true;
}

QString Converter::convert(QString str, BigInteger fromBase, BigInteger toBase) {
    QString num, den, per;
    bool dis = false;
    if(str[0] == '-') {
        str.remove(0, 1);
        dis = true;
    }
    //if (!isValidString(str))
      //  return "0";
    QMap<QChar, QString> letterToNumber;
    for (char c = 'A'; c <= 'Z'; ++c) {
        letterToNumber[c] = QString("[%1]").arg(10 + (c - 'A'));
    }

    QString beforeDot, afterDot;
    QStringList parts = str.split('.');
    if (!parts.isEmpty()) beforeDot = parts[0];
    if (parts.size() > 1) afterDot = parts[1];

    QStringList numParts;
    for (int i = 0; i < beforeDot.size(); ++i) {
        QChar ch = beforeDot[i];
        if (ch.isLetter() && letterToNumber.contains(ch)) {
            numParts.append(letterToNumber[ch]);
        } else {
            numParts.append(ch);
        }
    }
    num = numParts.join("");

    QString denTemp, perTemp;
    bool insideParentheses = false;
    for (int i = 0; i < afterDot.size(); ++i) {
        QChar ch = afterDot[i];
        if (ch == '(') {
            insideParentheses = true;
            continue;
        } else if (ch == ')') {
            insideParentheses = false;
            continue;
        }

        if (insideParentheses) {
            if (ch.isLetter() && letterToNumber.contains(ch)) {
                perTemp.append(letterToNumber[ch]);
            } else {
                perTemp.append(ch);
            }
        } else {
            if (ch.isLetter() && letterToNumber.contains(ch)) {
                denTemp.append(letterToNumber[ch]);
            } else {
                denTemp.append(ch);
            }
        }
    }

    den = denTemp;
    per = perTemp;
    QString check = num + den + per;
    for (int i = 0; i < check.size(); i++) {
        QChar c = check[i];
        if(c.isDigit() && c.unicode() - '0' >= fromBase) {
            return "0";
        }
        else if(!c.isDigit() && c == '[') {
            QString tmp;
            int j = i + 1;
            while(j < check.size() && check[j] != ']') {
                tmp.push_back(check[j]);
                ++j;
            }
            i = j;
            bool ok;
            int val = tmp.toInt(&ok);
            if(val >= fromBase)
                return "0";
        }

    }
    BigInteger convNum;
    BigFraction convDen, convPer;
    int DenSize = 0, PerSize = 0;
    int bracketCount = 0;
    bool inBrackets = false;

    for (const QChar &ch : den) {
        if (ch == '[') {
            bracketCount++;
            inBrackets = true;
        } else if (ch == ']') {
            inBrackets = false;
        } else if (!inBrackets && ch.isDigit()) {
            DenSize++;
        }
    }

    DenSize += bracketCount;
    bracketCount = 0;
    inBrackets = false;
    for (const QChar &ch : per) {
        if (ch == '[') {
            bracketCount++;
            inBrackets = true;
        } else if (ch == ']') {
            inBrackets = false;
        } else if (!inBrackets && ch.isDigit()) {
            PerSize++;
        }
    }
    PerSize += bracketCount;

    if(!num.isEmpty())
        convNum = convertNumToDecimal(num, fromBase);
    if(!den.isEmpty())
        convDen = convertDenToDecimal(den, fromBase, DenSize);
    if(!per.isEmpty())
        convPer = convertPerToDecimal(per, fromBase, DenSize, PerSize);
    BigFraction res = convDen + convPer;
    QString convResFr = convertDenFromDecimal(res, toBase);
    bool flag = false;
    int finalNumber = 0;
    int cnt = 0;
    for (int j = 0; j < convResFr.length(); ++j) {
        if (!flag) {
            if (convResFr[j].isDigit()) {
                flag = true;
                finalNumber = convResFr[j].digitValue();
            } else if (convResFr[j].isLetter()) {
                flag = true;
                int number = (convResFr[j].toUpper().unicode() - 'A' + 10);
                finalNumber = number;
            } else if (convResFr[j] == '[') {
                QString tmp;
                ++j;
                while (convResFr[j] != ']' && j < convResFr.length()) {
                    tmp.append(convResFr[j]);
                    ++j;
                    ++cnt;
                }
                if (!tmp.isEmpty()) {
                    finalNumber = tmp.toInt();
                }
                flag = true;
            }
        } else {
            ++j;
        }
    }
    if(finalNumber >= toBase) {
        ++convNum;
        if(convResFr[0] == '[') {
            convResFr.remove(0, cnt + 2);
            convResFr = '0' + convResFr;
        } else {
            convResFr[0] = '0';
        }
    }

    QString convNumFr = convertNumFromDecimal(convNum, toBase);
    if(dis)
        convNumFr = '-' + convNumFr;
    if(convResFr != "0" && convResFr != "")
        return convNumFr + '.' + convResFr;
    else
        return convNumFr;
}

BigInteger Converter::convertNumToDecimal(const QString& num, BigInteger fromBase) {
    BigInteger decimal = 0;
    for (int i = 0; i < num.length(); i++) {
        int digit = 0;
        bool ok;
        if(num[i] == '[') {
            QString tmp;
            int j = i + 1;
            while(num[j] != ']' && j < num.length()) {
                tmp.push_back(num[j]);
                ++j;
            }
            i = j;
            digit = tmp.toInt(&ok);
        }
        else {
            digit = num[i].digitValue();
        }

        decimal = decimal * fromBase + digit;
    }
    return decimal;
}

QString Converter::convertNumFromDecimal(BigInteger decimal, BigInteger toBase) {
    if (toBase <= 1) {
        throw std::invalid_argument("Base must be greater than 1");
    }

    QString result;
    if (decimal == 0) {
        return "0";
    }

    while (decimal > 0) {
        BigInteger remainder = decimal % toBase;
        if(remainder > 9 && remainder < 36) {
            result.prepend(QChar('A' + (static_cast<int>(remainder.toInt()) - 10)));
        } else if(remainder >= 36) {
            result.prepend(QString("[%1]").arg(remainder.toQString()));
        } else {
            result.prepend(remainder.toQString());
        }
        decimal /= toBase;
    }
    return result;
}

BigFraction Converter::convertDenToDecimal(const QString& den, BigInteger fromBase, int DenSize) {
    BigInteger up = convertNumToDecimal(den, fromBase);
    BigInteger down = fromBase.pow(DenSize);;

    return BigFraction(up, down);
}

BigFraction Converter::convertPerToDecimal(const QString& per, BigInteger fromBase, int DenSize, int PerSize) {
    BigInteger up = convertNumToDecimal(per, fromBase);
    BigInteger down = fromBase.pow(PerSize);
    --down;

    if (DenSize > 0) {
        down *= fromBase.pow(DenSize);
    }
    return BigFraction(up, down);
}

QString Converter::convertDenFromDecimal(BigFraction fr, BigInteger toBase) {
    QString result;
    QMap<BigInteger, int> seenRemainders;
    int index = 0;
    BigInteger num = fr.num();
    BigInteger den = fr.den();

    int maxDecimalPlaces = 11000;
    int decimalPlacesCount = 0;

    while (num != 0 && decimalPlacesCount < maxDecimalPlaces) {
        num *= toBase;

        BigInteger integerPart = num / den;
        num = num % den;

        if(integerPart >= 10 && integerPart < 36) {
            result.append(QChar('A' + (static_cast<int>(integerPart.toInt()) - 10)));
        } else if(integerPart >= 36) {
            result.append(QString("[%1]").arg(integerPart.toQString()));
        } else {
            result.append(integerPart.toQString());
        }

        if (seenRemainders.contains(num)) {
            int repeatIndex = seenRemainders[num];
            QString period = result.mid(repeatIndex + 1);

            result = result.left(repeatIndex + 1) + '(' + period + ')';
            break;
        } else {
            seenRemainders[num] = index++;
            decimalPlacesCount++;
        }
    }

    return result;
}
