#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include "mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_loginBtn_clicked();

    void on_userLineEdit_returnPressed();

    void on_pwdLineEdit_returnPressed();

private:
    Ui::LoginWindow *ui;
    MainWindow* mainW;
    QNetworkAccessManager* manager;
};
#endif // LOGINWINDOW_H
