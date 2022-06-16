#include "ticketlist.h"
#include "ui_ticketlist.h"

TicketList::TicketList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TicketList)
{
    ui->setupUi(this);
    offset = 0;
    appendTicket();
}

TicketList::~TicketList()
{
    delete ui;
}
void TicketList::appendTicket()
{
    QPushButton *ticketInfo = new QPushButton(this);
    ticketInfo->setFixedSize(300,60);
    ticketInfo->setGeometry(50,50+offset,300,60);
    ticketInfo->show();
    //int id = offset;
    connect(ticketInfo,&QPushButton::clicked, this, [ = ] {
        //ticketInfo->setText(QString("%1").arg(id));
        ticketpay = new TicketPay();
        ticketpay->show();
    });
    QLabel *startPlace = new QLabel("startplace", this);
    startPlace->setFixedSize(100,20);
    startPlace->setGeometry(50,50+offset,100,20);
    startPlace->show();
    QLabel *arrivePlace = new QLabel("arriveplace", this);
    arrivePlace->setFixedSize(100,20);
    arrivePlace->setGeometry(170,50+offset,100,20);
    arrivePlace->show();
//    QLabel *startTime = new QLabel(starttime, this);
    QLabel *startTime = new QLabel("starttime", this);
    startTime->setFixedSize(100,20);
    startTime->setGeometry(50,90+offset,100,20);
    startTime->show();
//    QLabel *arriveTime = new QLabel(arrivetime, this);
    QLabel *arriveTime = new QLabel("arrivetime", this);
    arriveTime->setFixedSize(100,20);
    arriveTime->setGeometry(170,90+offset,100,20);
    arriveTime->show();
//    QLabel *priceLabel = new QLabel(price, this);
    QLabel *priceLabel = new QLabel("price", this);
    priceLabel->setFixedSize(100,20);
    priceLabel->setGeometry(280,70+offset,100,20);
    priceLabel->show();
    offset += 120;
}
void TicketList::appendTicket(QJsonValue value)
{
    qDebug() << value.toString();
    QString startplace = value.toObject()["start_code"].toString();
    QString arriveplace = value.toObject()["end_code"].toString();
    QString starttime = value.toObject()["start_time"].toString();
    QString arrivetime = value.toObject()["end_time"].toString();
    QString price = value.toObject()["price"].toString();
    QPushButton *ticketInfo = new QPushButton(this);
    ticketInfo->setFixedSize(300,60);
    ticketInfo->setGeometry(50,50+offset,300,60);
    ticketInfo->show();
    //int id = offset;
    connect(ticketInfo,&QPushButton::clicked, this, [ = ] {
        //ticketInfo->setText(QString("%1").arg(id));
        ticketpay = new TicketPay();
        ticketpay->setTicketInfos(value);
        ticketpay->show();
    });
    QLabel *startPlace = new QLabel(startplace, this);
//    QLabel *startPlace = new QLabel("startplace", this);
    startPlace->setFixedSize(100,20);
    startPlace->setGeometry(50,50+offset,100,20);
    startPlace->show();
    QLabel *arrivePlace = new QLabel(arriveplace, this);
//    QLabel *arrivePlace = new QLabel("arriveplace", this);
    arrivePlace->setFixedSize(100,20);
    arrivePlace->setGeometry(170,50+offset,100,20);
    arrivePlace->show();
    QLabel *startTime = new QLabel(starttime, this);
//    QLabel *startTime = new QLabel("starttime", this);
    startTime->setFixedSize(100,20);
    startTime->setGeometry(50,90+offset,100,20);
    startTime->show();
    QLabel *arriveTime = new QLabel(arrivetime, this);
//    QLabel *arriveTime = new QLabel("arrivetime", this);
    arriveTime->setFixedSize(100,20);
    arriveTime->setGeometry(170,90+offset,100,20);
    arriveTime->show();
    QLabel *priceLabel = new QLabel(price, this);
//    QLabel *priceLabel = new QLabel("price", this);
    priceLabel->setFixedSize(100,20);
    priceLabel->setGeometry(280,70+offset,100,20);
    priceLabel->show();
    offset += 120;
}

void TicketList::setTicketInfos(QByteArray bytes){
    QJsonParseError parseJsonErr;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(bytes,&parseJsonErr);
    if (!(parseJsonErr.error == QJsonParseError::NoError)){
            qDebug() << QString("解析json文件错误!");
            return;
        }
    QJsonArray res = jsonDoc.array();
    for(int i = 0; i < res.size(); i++){
        appendTicket(res[i]);
    }
}
