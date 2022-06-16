#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QMessageBox>
#include <QDebug>
#include "targetplaceselect.h"
#include "ticketlist.h"

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
    QString username;
private slots:
    void on_startBtn_clicked();
    void setBtnText(QString str);
    void setId(QString str);
    void on_endBtn_clicked();
    void on_convertBtn_clicked();

    void on_pushButton_clicked();

private:
    bool startClicked;
    Ui::MainWindow *ui;
    targetPlaceSelect* targetWindow = nullptr;
    TicketList* ticketWindow;
    QNetworkAccessManager* manager;
    QString startId;
    QString endId;
};

#endif // MAINWINDOW_H
