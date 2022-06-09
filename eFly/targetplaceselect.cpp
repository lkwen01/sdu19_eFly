#include "targetplaceselect.h"
#include "ui_targetplaceselect.h"

targetPlaceSelect::targetPlaceSelect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::targetPlaceSelect)
{
    ui->setupUi(this);
}

void targetPlaceSelect::query()
{
    qDebug()<<*cookies;
    manager = new QNetworkAccessManager();
    QString requestUrl;
    QNetworkRequest request;
    //请求地址
    requestUrl="http://101.76.254.181:10086/query/airport/";//"http://192.168.1.123:6666/carmonitorsys/errlog/upload.action?"
    //requestUrl="http://127.0.0.1:10086/";
    //设置请求地址
    request.setUrl(QUrl(requestUrl));
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    request.setHeader(QNetworkRequest::CookieHeader, QVariant::fromValue(*cookies));

    //打包请求参数赋值
    QJsonObject post_data;
    QJsonDocument document;
    QByteArray post_param;
    post_data.insert("space","0");
    document.setObject(post_data);
    post_param = document.toJson(QJsonDocument::Compact);
    //开始上传

    QNetworkReply* reply = manager->post(request,post_param);
    connect(reply,&QNetworkReply::finished,[=]() {
        if(reply->error() == QNetworkReply::NoError)
        {
            QByteArray resultB = reply->readAll();
            QString result = QString::fromStdString(resultB.toStdString());
            qDebug()<<result;

        }
        else // handle error
        {
            QMessageBox::information(this,"提示信息","连接服务器失败");
            qDebug()<<reply->errorString();
        }
    });
}

targetPlaceSelect::~targetPlaceSelect()
{
    delete ui;
}

QString targetPlaceSelect::getPlace(){
    return ui->lineEdit->text();
}

void targetPlaceSelect::setCookies(QList<QNetworkCookie> *mainCookies){
    cookies = mainCookies;
}

void targetPlaceSelect::on_pushButton_clicked()
{
    sendData(ui->lineEdit->text());
    this->close();
}

