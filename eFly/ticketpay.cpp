#include "ticketpay.h"
#include "ui_ticketpay.h"

TicketPay::TicketPay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TicketPay)
{
    ui->setupUi(this);
}

TicketPay::~TicketPay()
{
    delete ui;
}

void TicketPay::setTicketInfos(QJsonValue value){
    QString flightId = value.toObject()["name"].toString();
    QString startplace = value.toObject()["start_code"].toString();
    QString arriveplace = value.toObject()["end_code"].toString();
    QString starttime = value.toObject()["start_time"].toString();
    QString arrivetime = value.toObject()["end_time"].toString();
    QString price = value.toObject()["price"].toString() + "￥";
    ui->idLabel->setText(flightId);
    ui->spLabel->setText(startplace);
    ui->stLabel->setText(starttime);
    ui->apLabel->setText(arriveplace);
    ui->atLabel->setText(arrivetime);
    ui->priceLabel->setText(price);
}

void TicketPay::on_buyBtn_clicked()
{
    QString identId = ui->identLineEdit->text();
    if(identId.length() != 18){
        QMessageBox::information(this,"错误","无效身份证号码");
        return;
    }
    int totalsum = 0;
    int factor[] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
    char checksum[] = {'1', '0', 'X', '9', '8', '7', '6', '5', '4', '3'};
    for (int i = 0; i < 17; i++){
        if(!identId[i].isDigit()){
            QMessageBox::information(this,"错误","无效身份证号码");
            return;
        }
        else{
            int currIndex = QString(identId[i]).toInt();
            totalsum += currIndex * factor[i];
        }
    }
    int index = totalsum % 11;
    if(checksum[index] != identId[17].toLatin1()){
        QMessageBox::information(this,"错误","无效身份证号码");
        return;
    }
    QMessageBox::information(this,"成功","订单已生成");
    selectseat = new SelectSeat();
    selectseat->show();
}

