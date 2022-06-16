#ifndef TARGETPLACESELECT_H
#define TARGETPLACESELECT_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QMessageBox>
#include <QDebug>
#include <QStandardItem>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace Ui {
class targetPlaceSelect;
}

class targetPlaceSelect : public QDialog
{
    Q_OBJECT

public:
    explicit targetPlaceSelect(QWidget *parent = nullptr);
    ~targetPlaceSelect();
    void query();
    QString getPlace();
    void setCookies(QList<QNetworkCookie>* mainCookies);
    QString username;
signals:
   void sendData(QString);
   void sendId(QString);
private slots:
   void on_pushButton_clicked();
   void rowDoubleClicked(const QModelIndex index);
private:
    Ui::targetPlaceSelect *ui;
    QNetworkAccessManager* manager;
    QList<QNetworkCookie>* cookies;
};

#endif // TARGETPLACESELECT_H
