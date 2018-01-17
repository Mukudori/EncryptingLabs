#ifndef MYLIB_H
#define MYLIB_H
#include <QString>

namespace MyLib {


void InsertSpacesAndKey(QString &str, int &key);
void InsertSpaces(QString &str, int I=0);
//QString DeleteExtraChars(QString &str);
QString DeleteExtraCharsFromStr(QString &str, int I=0);


}


#endif // MYLIB_H
