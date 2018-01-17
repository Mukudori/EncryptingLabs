#include "skitala.h"
#include "mainwindow.h"
#include "qstringfuncs.h"
#include "mylib.h"

Skitala::Skitala(const QString &inp, const int &k)
{
    key=k;
    out=inp;
    len=n;

}

void Skitala::CreateCh(QString &str)
{
    n = str.length()/key; n+= str.length()%key?1:0;

    ch = new QChar*[key];
    for (int i=0; i<key; i++)
            ch[i]=new QChar[n];

    if (str.length()%key)
     for (int i=str.length()%key; i<n; i++)
         ch[key-1][i]=QChar(48);
}

void Skitala::DeleteCh()
{
    for(int i=0; i<key; i++)
        delete[] ch[i];
    delete[] ch;
}

Skitala::~Skitala()
{
    DeleteCh();
}

QString Skitala::Encrypt(QString &str)
{
    CreateCh(str);
    int  k=0;
    for (int i=0;    i<key; i++)
        for (int j=0; j<n ; j++,k++)
            if (k<str.length()) ch[i][j] = str[k];
            else break;


    // считывание марицы
    str.clear();
    for (int j=0; j<n; j++)
        for(int i=0; i<key;  i++)
            if (ch[i][j].unicode()!=48) str+=ch[i][j];
    return str;
}

QString Skitala::Decipher(QString &str)
{
    CreateCh(str);
    int k=0;
    int mod =str.length()%n;
    bool newKey = mod;
    bool flag = true;

    for(int j=0; j<n ; j++){
        if (j==mod && newKey && flag) {key--; flag=false;}
        for (int i=0; i<key; i++, k++)

            if (k<str.length()) ch[i][j]=str[k];
            else break;
    }

    if (newKey) key++;

    str.clear();
    for(int i=0; i<key; i++)
        for(int j=0; j<n; j++)
            if (ch[i][j].unicode()!=48) str+=ch[i][j];
            else break;
    return str;
}
void Skitala::GetEncryptText(QTextEdit *te)
{
    te->clear();
    te->append(Encrypt(out));
}

void Skitala::GetDecipher(QTextEdit *te)
{
    te->clear();
    te->append(Decipher(out));
}

void Skitala::GetDecipherLarinaText(QTextEdit *te)
{
    out.remove(QChar(32),Qt::CaseInsensitive);
    key = out[0].unicode()-1039;
    out.remove(0,1);
    QString encStr=out;
    encStr=Decipher(encStr);
    te->clear();
    te->append(encStr);

}

void Skitala::GetEncryptLarinaText(QTextEdit *te)
{
    QString encStr=MyLib::DeleteExtraCharsFromStr(out);
    encStr=Encrypt(encStr);
    MyLib::InsertSpacesAndKey(encStr, key);
    te->clear();
    te->append(encStr);
}


