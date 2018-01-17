#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QLineEdit>
#include <QTextCodec>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    enum Labs {mirror, skitala, cipher_of_Caesar, vidgner};

    //QString inpStr;
    //QString outStr;
    QTextCodec *codec;
    Labs lab;


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:


    void on_OpenButton_clicked();

    void on_CryptButton_clicked();  

    void on_decryptButton_clicked();    

    void on_choose_skitala_triggered();

    void on_choose_mirror_triggered();

    void on_SaveButton_clicked();

    void on_choose_cipher_of_Caesar_triggered();

    void on_test_triggered();

    void on_Choose_Vigner_triggered();

private:
    Ui::MainWindow *ui;
    bool AcceptTableInp();
    void Skitala_Encrypt();
    void Skitala_Decifer();
    void Caesar_Encrypt();
    void Caesar_Decrypt();
    void Mirror(const QString);
    void Vigner_Encrypt();
    void Vigner_Decript();

};

#endif // MAINWINDOW_H
