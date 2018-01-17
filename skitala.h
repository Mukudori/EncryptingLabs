#ifndef SKITALA_H
#define SKITALA_H

#include <QString>
#include <QTextEdit>

class Skitala
{
    QString out; // обрабатываемая строка
    int key;// значение ключа
    int n; // количество столбцов
    int len; // длинна текста
    QChar **ch; // матрица шифрования


public:
    Skitala(const QString&, const int&);
    ~Skitala();
    void GetEncryptText(QTextEdit* te); // Зашифровать текст по Скитала
    void GetDecipher(QTextEdit* te); // Расшифровать текст по скитала
    void GetEncryptLarinaText(QTextEdit *te); // Зашифровать текст Ларина-Скитала
    void GetDecipherLarinaText(QTextEdit* te); // Расшифровать текст Ларина-Скитала
private:
    void CreateCh(QString&); // Создание матрицы сиволов
    void DeleteCh(); // Удаление матрицы символов
    QString Encrypt(QString &str); // шифровать строку
    QString Decipher(QString &str); // расшифровать строку
    void InsertSpacesAndKey(QString&); // Вставка пробелов в строку
    void DeleteSpacesAndKey(QString&); // Удалить пробелы в строке
};

#endif // SKITALA_H
