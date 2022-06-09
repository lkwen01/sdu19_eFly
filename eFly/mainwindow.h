#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QMessageBox>
#include <QDebug>
#include "targetplaceselect.h"
#include "flightlist.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static QList<QNetworkCookie>* cookies;

private slots:
    void on_startBtn_clicked();
    void setBtnText(QString str);

    void on_endBtn_clicked();
    void on_convertBtn_clicked();

    void on_pushButton_clicked();

private:
    bool startClicked;
    Ui::MainWindow *ui;
    targetPlaceSelect* targetWindow;
    FlightList flightWindow;
    QNetworkAccessManager* manager;

};

#endif // MAINWINDOW_H
