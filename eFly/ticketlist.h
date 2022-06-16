#ifndef TICKETLIST_H
#define TICKETLIST_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "ticketpay.h"

namespace Ui {
class TicketList;
}

class TicketList : public QWidget
{
    Q_OBJECT

public:
    explicit TicketList(QWidget *parent = nullptr);
    void appendTicket();
    void appendTicket(QJsonValue value);
    ~TicketList();
    void setTicketInfos(QByteArray bytes);
private:
    int offset;
    Ui::TicketList *ui;
    QString* ticketInfos;
    TicketPay* ticketpay;
};

#endif // TICKETLIST_H
