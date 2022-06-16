#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager();
}

MainWindow::~MainWindow()
{
    delete targetWindow;
    delete ui;
}

QList<QNetworkCookie>* MainWindow::cookies = new QList<QNetworkCookie>();

void MainWindow::on_startBtn_clicked()
{
    if (targetWindow == nullptr){
        targetWindow = new targetPlaceSelect();
        targetWindow->setCookies(cookies);
        targetWindow->username = username;
        connect(targetWindow,SIGNAL(sendData(QString)),this,SLOT(setBtnText(QString)));
        connect(targetWindow,SIGNAL(sendId(QString)),this,SLOT(setId(QString)));
    }
    startClicked = true;
    targetWindow->query();
    targetWindow->show();
}

void MainWindow::setBtnText(QString str){
    if(startClicked)
        ui->startBtn->setText(str);
    else
        ui->endBtn->setText(str);
}

void MainWindow::setId(QString str){
    if(startClicked)
        startId = str;
    else
        endId = str;
}

void MainWindow::on_endBtn_clicked()
{
    if (targetWindow == nullptr){
        targetWindow = new targetPlaceSelect();
        targetWindow->setCookies(cookies);
        targetWindow->username = username;
        connect(targetWindow,SIGNAL(sendData(QString)),this,SLOT(setBtnText(QString)));
    }
    startClicked = false;
    targetWindow->query();
    targetWindow->show();
}

void MainWindow::on_convertBtn_clicked()
{
    QString startPlace = ui->startBtn->text();
    QString endPlace = ui->endBtn->text();
    ui->startBtn->setText(endPlace);
    ui->endBtn->setText(startPlace);
    QString temp = startId;
    startId = endId;
    endId = temp;
}


void MainWindow::on_pushButton_clicked()
{
    if(username == "test"){
        ticketWindow = new TicketList();
        ticketWindow->show();
        return;
    }
    QString startPlace = ui->startBtn->text();
    QString endPlace = ui->endBtn->text();
    QString month = ui->monthComboBox->currentText();
    QString date = ui->dateComboBox->currentText();
    bool isEconomic = ui->ecoBtn->isChecked();

    //请求地址
    QString requestUrl;
    QNetworkRequest request;
    //请求地址
    requestUrl="http://101.76.254.181:10086/flight/";
    //requestUrl+=QString("token=%1&").arg(TOKEN);   //授权码
    //requestUrl+=QString("devId=%1").arg(DeviceID); //设备编号

    //设置请求地址
    QUrl url;
    url.setUrl(requestUrl);
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    request.setHeader(QNetworkRequest::CookieHeader, QVariant::fromValue(*cookies));
    //打包请求参数赋值
    QJsonObject post_data;
    QJsonDocument document;
    QByteArray post_param;

    post_data.insert("startPlace", startId); //插入数据
    post_data.insert("endPlace", endId);
    post_data.insert("month", month);
    post_data.insert("date", date);
    post_data.insert("isEconomic",isEconomic?"1":"0");
    document.setObject(post_data);
    post_param = document.toJson(QJsonDocument::Compact);
    //开始上传
    QNetworkReply* reply = manager->post(request,post_param);
    connect(reply,&QNetworkReply::finished,[=]() {
        if(reply->error() == QNetworkReply::NoError)
        {
            QByteArray resultB = reply->readAll();
            qDebug() << QString(resultB);
            ticketWindow = new TicketList();
            ticketWindow->setTicketInfos(resultB);
            ticketWindow->show();
        }
        else // handle error
        {
            QMessageBox::information(this,"提示信息","连接服务器失败");
            qDebug()<<reply->errorString();
        }
    });
}

