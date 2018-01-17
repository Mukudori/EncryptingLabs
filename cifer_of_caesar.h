#ifndef CIFER_OF_CAESAR_H
#define CIFER_OF_CAESAR_H

#include <QString>
#include <QTextEdit>
#include <QChar>
#include <QList>

class Cifer_of_Caesar
{
    QString out;
    QList<QChar> outCh;
    int key;
    short direction;
public:
    Cifer_of_Caesar(const QString&, const int&, const QChar&);
    void GetEncryptText(QTextEdit*);
    void GetEncryptTextWithKey(QTextEdit*);
    void GetDeciferText(QTextEdit*);
    void GetDeciferWithKey(QTextEdit*);
    void Encrypt(QString&);
private:
    void ChangeChar(QChar&);
    QChar GetCharAdd(const int &a, const int &z, QChar& ch);
    QChar GetCharDec(const int &a, const int &z, QChar& ch);

};

#endif // CIFER_OF_CAESAR_H
