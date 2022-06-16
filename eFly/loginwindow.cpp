#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    //connect(ui->loginBtn, &QPushButton::clicked,
    //this, &LoginWindow::on_loginBtn_clicked);
    //connect(ui->userLineEdit, &QLineEdit::returnPressed,
    //this, &LoginWindow::on_userLineEdit_returnPressed);
    //connect(ui->pwdLineEdit, &QLineEdit::returnPressed,
    //this, &LoginWindow::on_pwdLineEdit_returnPressed);
    manager = new QNetworkAccessManager();
}

LoginWindow::~LoginWindow()
{
    delete manager;
    delete ui;
}


void LoginWindow::on_loginBtn_clicked()
{
    QString username = ui->userLineEdit->text();
    QString password = ui->pwdLineEdit->text();

    //服务器未联网时测试用
    if(username == "test") {
        mainW = new MainWindow();
        mainW->username = username;
        mainW->show();
        this->hide();
        return;
    }

    ui->loginBtn->setText("……");
    //请求地址
    QString requestUrl;
    QNetworkRequest request;
    //请求地址
    requestUrl="http://101.76.254.181:10086/login/";//"http://192.168.1.123:6666/carmonitorsys/errlog/upload.action?"
    //requestUrl="http://127.0.0.1:10086/";
    //设置请求地址
    request.setUrl(QUrl(requestUrl));
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    //request.setHeader(QNetworkRequest::CookieHeader,"");
    //打包请求参数赋值
    QJsonObject post_data;
    QJsonDocument document;
    QByteArray post_param;
    post_data.insert("username",username);//user0
    post_data.insert("password",password);//123456
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

            if(result == QString("success")){
                mainW = new MainWindow();
                ui->loginBtn->setText("Verification successful");
                QVariant variantCookies = reply->header(QNetworkRequest::SetCookieHeader);
                MainWindow::cookies->append(qvariant_cast<QList<QNetworkCookie> >(variantCookies));
                mainW->username = username;
                qDebug()<<*(MainWindow::cookies);
                this->hide();
                mainW->show();
            }
            else{
                ui->hintLabel->setText("Username or password is wrong.");
                ui->loginBtn->setText("Login");
            }
        }
        else // handle error
        {
            QMessageBox::information(this,"提示信息","连接服务器失败");
            qDebug()<<reply->errorString();
            ui->loginBtn->setText("登录");
        }
    });



    //QMessageBox::information(this,cookie.toString(),QString::fromStdString(result.toStdString()));
    //sql compare
//    if(username == "test" && password == ""){
//        ui->loginBtn->setText("Verification successful");
//        this->hide();
//        mainW.show();
//    }
//    else{
//        ui->hintLabel->setText("Username or password is wrong.");
//        ui->loginBtn->setText("Login");
//    }
}


void LoginWindow::on_userLineEdit_returnPressed()
{
    ui->pwdLineEdit->setFocus();
}


void LoginWindow::on_pwdLineEdit_returnPressed()
{
    on_loginBtn_clicked();
}

