#ifndef VIGNER_H
#define VIGNER_H
#include <QVector>
#include <QTextEdit>

class Vigner
{
public:
    Vigner(const QString &inS, const QString &KEY);
    void PrintEncrypt(QTextEdit*);
    void PrintDecipher(QTextEdit*);
    ~Vigner();

private:
    QChar vTable[31][31];
    QString key;
    QString encStr;
    QString Encrypt();
    QString Decipher();
    int GetIndex(int k,QChar);

};

#endif // VIGNER_H
