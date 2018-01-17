#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QStringList>
#include <QValidator>
#include <QMessageBox>
#include "skitala.h"
#include <QTextStream>
#include "cifer_of_caesar.h"
#include "vigner.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    lab = Labs::mirror;
    this->setWindowTitle("Королевство кривых зеркал");
    ui->Caption_Label->setText("Выбран алгоритм: <b><u>Зеркало</u></b>");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_OpenButton_clicked()
{
    QFile inpF(QFileDialog::getOpenFileName(0, "Выбор файла", "", "*.*"));

    if (inpF.open(QIODevice::ReadOnly))
    {
        QTextStream input(&inpF);
        input.setCodec("UTF-8");
        ui->inpTE->clear();
        ui->inpTE->append(input.readAll());

    }
    inpF.close();
}

void MainWindow::Mirror(const QString inpStr)
{
    QString outStr;
    for (int i =inpStr.length()-1; i>=0; i--)
        outStr[inpStr.length()-1-i]=inpStr[i];

    ui->outTE->clear();
    ui->outTE->append(outStr);

}

bool MainWindow::AcceptTableInp()
{
    QMessageBox msg;


    if (ui->inpTE->toPlainText().length()>ui->keyLE->text().toInt())
    {

        if (!ui->keyLE->hasAcceptableInput())
        {
            msg.setText("Ошибка : ключ введен в неправильном формате.");
            msg.setWindowTitle("Ошибка");
            msg.exec();

            return false;
        }

    }
    else
    {
        msg.setText("Ошибка : значение ключа превышает длинну текста.");
        msg.setWindowTitle("Ошибка");
        msg.exec();

        return false;
    }


    return true;
}

void MainWindow::Skitala_Decifer()
{
    if (AcceptTableInp())
    {
        Skitala* enc = new Skitala(ui->inpTE->toPlainText(), ui->keyLE->text().toInt());
        enc->GetDecipherLarinaText(ui->outTE);
        delete enc;
    }
}

void MainWindow::Skitala_Encrypt()
{
    if (AcceptTableInp())
    {
        if (ui->keyLE->text().toInt()<32)
        {
            Skitala* enc = new Skitala(ui->inpTE->toPlainText(), ui->keyLE->text().toInt());
            enc->GetEncryptLarinaText(ui->outTE);
            delete enc;
        }
        else
        {
            QMessageBox msg;
            msg.setText("Ошибка : значение ключа превышает длинну алфавита.");
            msg.setWindowTitle("Ошибка");
            msg.exec();
        }
    }
}

void MainWindow::on_CryptButton_clicked()
{
    ui->outTE->clear();
    switch(lab)
    {
        case Labs::mirror: Mirror(ui->inpTE->toPlainText()); break;
        case Labs::skitala: Skitala_Encrypt(); break;
        case Labs::cipher_of_Caesar: Caesar_Encrypt(); break;
        case Labs::vidgner:  Vigner_Encrypt(); break;

    }
}

void MainWindow::on_decryptButton_clicked()
{
    ui->outTE->clear();

    switch(lab)
    {
        case Labs::mirror: Mirror(ui->inpTE->toPlainText()); break;
        case Labs::skitala: Skitala_Decifer(); break;
        case Labs::cipher_of_Caesar: Caesar_Decrypt(); break;
        case Labs::vidgner:  Vigner_Decript(); break;
    }
}

void MainWindow::on_choose_skitala_triggered()
{
    ui->keyLE->setValidator(new QRegExpValidator(QRegExp("^[0-9]{1,4}$")));
    lab=Labs::skitala;
     ui->Caption_Label->setText("Выбран алгоритм: <b><u>Скитала</u></b>");
    this->setWindowTitle("Скитала");
}

void MainWindow::on_choose_mirror_triggered()
{
    lab = Labs::mirror;
    ui->Caption_Label->setText("Выбран алгоритм: <b><u>Зеркало</u></b>");

    this->setWindowTitle("Королевство кривых зеркал");
}

void MainWindow::on_choose_cipher_of_Caesar_triggered()
{
    lab = Labs::cipher_of_Caesar;
    ui->Caption_Label->setText("Выбран алгоритм: <b><u>Простая замена(Шифр Цезаря)</u></b>");
     ui->keyLE->setValidator(new QRegExpValidator(QRegExp(QString::fromUtf8("^[0-9]{1,2}[Л,П]{1}$"))));
    this->setWindowTitle("Простая замена(Шифр Цезаря)");
}

void MainWindow::on_SaveButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить как"), "",
        tr("Текстовый файл (*.txt)"));

        if (fileName != "") {
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly))
            {
               QMessageBox msg;
               msg.setText("Ошибка : файл с таким именем уже существует.");
               msg.setWindowTitle("Ошибка");
               msg.exec();


            } else {
                QTextStream stream(&file);
                stream << ui->outTE->toPlainText();
                stream.setCodec("UTF-8");
                stream.flush();
                file.close();
            }
        }
}

void MainWindow::on_test_triggered()
{
    QChar c = ui->keyLE->text().at(0);
    ui->outTE->clear();
    ui->outTE->append(QString::number(c.unicode()));
}

void MainWindow::Caesar_Encrypt()
{
    if(AcceptTableInp())
    {
        QString str = ui->keyLE->text();
        QChar ch = str[str.length()-1];
        str[str.length()-1]='\n';

        if (str.toInt()<32)
        {
            Cifer_of_Caesar *CoC = new Cifer_of_Caesar(ui->inpTE->toPlainText(), str.toInt(), ch);

            CoC->GetEncryptTextWithKey(ui->outTE);
            delete CoC;
        }
        else
        {
            QMessageBox msg;
            msg.setText("Ошибка : значение ключа превышает длину алфавита.\n Шифр не имеет смысла.");
            msg.setWindowTitle("Ошибка");
            msg.exec();
        }
    }

}

void MainWindow::Caesar_Decrypt()
{
    if (AcceptTableInp())
    {
        QString str = ui->keyLE->text();
        QChar ch = str[str.length()-1];
        str[str.length()-1]='\n';

        if (str.toInt()<32)
        {
            Cifer_of_Caesar *CoC = new Cifer_of_Caesar(ui->inpTE->toPlainText(), str.toInt(), ch);
            CoC->GetDeciferWithKey(ui->outTE);
            delete CoC;
        }
        else
        {
            QMessageBox msg;
            msg.setText("Ошибка : значение ключа превышает длину алфавита.\n Шифр не имеет смысла.");
            msg.setWindowTitle("Ошибка");
            msg.exec();
        }
    }
}

void MainWindow::on_Choose_Vigner_triggered()
{
    ui->keyLE->setValidator(new QRegExpValidator(QRegExp("^[А-Я]{1,30}$")));
    lab=Labs::vidgner;
     ui->Caption_Label->setText("Выбран алгоритм: <b><u>Шифр Вижнера</u></b>");
    this->setWindowTitle("Шифр Вижнера");
}

void MainWindow::Vigner_Encrypt()
{
    Vigner *v = new Vigner(ui->inpTE->toPlainText(), ui->keyLE->text());
    v->PrintEncrypt(ui->outTE);
    delete v;
}
void MainWindow::Vigner_Decript()
{
    Vigner *v = new Vigner(ui->inpTE->toPlainText(), ui->keyLE->text());
    v->PrintDecipher(ui->outTE);
    delete v;
}
