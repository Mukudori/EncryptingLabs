#include "mylib.h"

void MyLib::InsertSpacesAndKey(QString &str, int &key)
{
    QString spSt;
    spSt.append(QChar(key+1039));

    spSt+=str;

    for(int i=4; i<spSt.length(); i+=5)
        spSt=spSt.insert(i,QChar(32));
    str=spSt;
}

void MyLib::InsertSpaces(QString &str, int I)
{
    QString spSt=str;

    for(int i=4; i<spSt.length(); i+=5)
        spSt=spSt.insert(i,QChar(32));
    str=spSt;
}

QString MyLib::DeleteExtraCharsFromStr(QString &str, int I)
{
    QString in = str.toUpper();
    QString out;
    for (int i=0; i<in.length(); i++)
        if (in[i].unicode()>1039 && in[i]<1072)
            out+=in[i];
    return out;
}

