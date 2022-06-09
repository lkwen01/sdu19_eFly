#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager();
    targetWindow = new targetPlaceSelect();
    targetWindow->setCookies(cookies);
    startClicked = true;
    connect(targetWindow,SIGNAL(sendData(QString)),this,SLOT(setBtnText(QString)));
}

MainWindow::~MainWindow()
{
    delete targetWindow;
    delete ui;
}

QList<QNetworkCookie>* MainWindow::cookies = new QList<QNetworkCookie>();

void MainWindow::on_startBtn_clicked()
{
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

void MainWindow::on_endBtn_clicked()
{
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
}


void MainWindow::on_pushButton_clicked()
{
    QString startPlace = ui->startBtn->text();
    QString endPlace = ui->endBtn->text();
    QString month = ui->monthComboBox->currentText();
    QString date = ui->dateComboBox->currentText();
    bool isEconomic = ui->ecoBtn->isChecked();

    //请求地址
    QString requestUrl;
    QNetworkRequest request;
    //请求地址
    requestUrl="http://101.76.254.181:10086/query/test/";//"http://192.168.1.123:6666/carmonitorsys/errlog/upload.action?"
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

    post_data.insert("startPlace", startPlace); //插入数据
    post_data.insert("endPlace", endPlace);
    post_data.insert("month", month);
    post_data.insert("date", date);
    post_data.insert("isEconomic",isEconomic);
    document.setObject(post_data);
    post_param = document.toJson(QJsonDocument::Compact);
    //开始上传
    QNetworkReply* reply = manager->post(request,post_param);
    connect(reply,&QNetworkReply::finished,[=]() {
        if(reply->error() == QNetworkReply::NoError)
        {

        }
        else // handle error
        {
            QMessageBox::information(this,"提示信息","连接服务器失败");
            qDebug()<<reply->errorString();
        }
    });
}

