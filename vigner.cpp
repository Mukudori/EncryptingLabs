#include "vigner.h"
#include "mylib.h"

Vigner::Vigner(const QString &inS, const QString &KEY)
{
    QString str;
    encStr = inS.toUpper();
    encStr.remove(QChar(32),Qt::CaseInsensitive);
    key = KEY;



    int i,j;

    for (i=0; i<31; i++)
    {
        str.append(i+1040);

    }
    int indS;
    for (i=0; i<31; i++)
    {
        indS=i+1;
        for(j=0; j<31; j++)
        {
            if(indS==31) indS=0;
            vTable[i][j] = str[indS];
            indS++;
        }
    }



}

Vigner::~Vigner()
{

}

void Vigner::PrintEncrypt(QTextEdit *te)
{
    te->clear();
    /*QString outS;
    for (int i=0; i<31; i++)
    {
        outS.clear();
        for(int j=0; j<31;j++)
            outS+=vTable[i][j]+'\t';
        te->append(outS);
    }*/

    encStr=Encrypt();

    for (int i=0; i<key.length(); i++) key[i] = QChar(key[i].unicode()+1);
    encStr = QChar(key.length()+1040) + key + encStr;
    MyLib::InsertSpaces(encStr);

    te->append(encStr);


}

void Vigner::PrintDecipher(QTextEdit *te)
{
   te->clear();


   te->append(Decipher());
}

QString Vigner::Encrypt()
{
    QString outStr;
    int k=0;

    for (int i=0; i<encStr.length(); i++)
    {

         if (k==key.length()) k=0;
         outStr+= vTable[encStr[i].unicode()-1040][key[k].unicode()-1040];
          k++;

    }

    return outStr;
}

QString Vigner::Decipher()
{
    QString outStr;
    key.clear();
    int n=encStr[0].unicode()-1040;
    for(int i=1; i<=n; i++) key+=QChar(encStr[i].unicode()-1);
    encStr.remove(0,n+1);

    int k=0;
    for (int i=0; i<encStr.length(); i++)
    {
        if(k==key.length()) k=0;
        outStr+=QChar(GetIndex(key[k].unicode()-1040, encStr[i]));
        k++;
    }
    return outStr;
}

int Vigner::GetIndex(int k, QChar c)
{
    for (int i=0; i<31; i++)
        if (vTable[i][k] == c) return i+1040;

}
