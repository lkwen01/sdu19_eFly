#ifndef TICKETPAY_H
#define TICKETPAY_H

#include <QWidget>
#include <QMessageBox>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "selectseat.h"

namespace Ui {
class TicketPay;
}

class TicketPay : public QWidget
{
    Q_OBJECT

public:
    explicit TicketPay(QWidget *parent = nullptr);
    ~TicketPay();
    void setTicketInfos(QJsonValue value);
private slots:
    void on_buyBtn_clicked();

private:
    Ui::TicketPay *ui;
    SelectSeat* selectseat;
};

#endif // TICKETPAY_H
