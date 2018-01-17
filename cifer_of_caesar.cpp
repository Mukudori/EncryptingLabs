#include "cifer_of_caesar.h"
#include "mylib.h"

Cifer_of_Caesar::Cifer_of_Caesar(const QString &str, const int &k, const QChar& dir)
{
    out = str;
    key = k;
    if(dir.unicode()==1055) direction=2;
    else direction=1;


}

void Cifer_of_Caesar::ChangeChar(QChar &c)
{
    switch (direction)
    {
      case 2: {
            if (c.unicode() >1039 && c.unicode()<1072)
            {
                c=GetCharAdd(1039,1071,c);
            }
            else
                if ( c.unicode()>1070 && c.unicode()<1104 )
                {
                    c=GetCharAdd(1070,1104,c);
                }
                else
                    if(c.unicode()>47 && c.unicode()<58)
                        {
                            c=GetCharAdd(47,58,c);
                        }


            break;
        }
    case 1: {
          if (c.unicode() >1039 && c.unicode()<1072)
          {
              c=GetCharDec(1039,1072,c);
          }
          else
              if ( c.unicode()>1070 && c.unicode()<1104 )
              {
                  c=GetCharDec(1070,1104,c);
              }
              else
                  if(c.unicode()>47 && c.unicode()<58)
                      {
                          c=GetCharDec(47,58,c);
                      }


          break;
      }

    }
}

QChar Cifer_of_Caesar::GetCharAdd(const int &a,const int &z, QChar& ch)
{
    if (ch.unicode()+key<z)
        return ch.unicode()+key;
    else
        return a+(ch.unicode()+key)%z;
}

QChar Cifer_of_Caesar::GetCharDec(const int &a, const int &z, QChar &ch)
{
    if (ch.unicode()-key>a && ch.unicode()-key<z)
        return ch.unicode()-key;
    else
        return z-(a+1)%(ch.unicode()-key);
}

void Cifer_of_Caesar::GetEncryptText(QTextEdit *te)
{
    Encrypt(out);
    te->clear();
    te->append(out);
}

void Cifer_of_Caesar::Encrypt(QString &str)
{
    for (int i=0; i<out.length(); i++)
    {
        QChar ch=str[i];
        ChangeChar(ch);
        str[i]=ch;
    }
}

void Cifer_of_Caesar::GetDeciferText(QTextEdit *te)
{
    if (direction==2) direction=1;
    else
        direction=2;


    GetEncryptText(te);
}

void Cifer_of_Caesar::GetEncryptTextWithKey(QTextEdit *te)
{
     out.remove(QChar(32),Qt::CaseInsensitive);
     out = out.toUpper();
     Encrypt(out);
     out = QChar(key + 1039) + QString(1055+direction) + out;
     MyLib::InsertSpaces(out);
     te->clear();
     te->append(out);
}

void Cifer_of_Caesar::GetDeciferWithKey(QTextEdit *te)
{
    out.remove(QChar(32),Qt::CaseInsensitive);
    key = out[0].unicode()-1039;
    direction = out[1].unicode()-1055;
    if (direction==2) direction=1;
    else
        direction=2;

    out.remove(0,2);
    Encrypt(out);
    te->clear();
    te->append(out);

}
