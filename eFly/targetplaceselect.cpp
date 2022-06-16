#include "targetplaceselect.h"
#include "ui_targetplaceselect.h"

targetPlaceSelect::targetPlaceSelect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::targetPlaceSelect)
{
    ui->setupUi(this);
    connect(ui->ABCDETableView, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(rowDoubleClicked(const QModelIndex &)));
}

void targetPlaceSelect::rowDoubleClicked(const QModelIndex index)
{
    if (index.isValid())
    {
        QString targetId = ui->ABCDETableView->model()->index(index.row(),0).data().toString();
        QString target = ui->ABCDETableView->model()->index(index.row(),1).data().toString();
        sendData(target);
        sendId(targetId);
        this->close();
    }
}

void targetPlaceSelect::query()
{
    if(username == "test"){
        QStandardItemModel* model = new QStandardItemModel();
        model->setHorizontalHeaderItem(0, new QStandardItem("代号"));
        model->setHorizontalHeaderItem(1, new QStandardItem("机场"));
        model->setItem(0, 0, new QStandardItem("fzs"));
        model->setItem(0, 1, new QStandardItem("反正是个机场"));
        ui->ABCDETableView->setModel(model);
        return;
    }
    qDebug()<<*cookies;
    manager = new QNetworkAccessManager();
    QString requestUrl;
    QNetworkRequest request;
    //请求地址
    requestUrl="http://101.76.254.181:10086/airport/";//"http://192.168.1.123:6666/carmonitorsys/errlog/upload.action?"
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
            QJsonParseError parseJsonErr;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(resultB,&parseJsonErr);
            if (!(parseJsonErr.error == QJsonParseError::NoError)){
                    qDebug() << QString("解析json文件错误!");
                    return;
                }
            QJsonArray res = jsonDoc.array();
            //QString result = QString::fromStdString(resultB.toStdString());
            qDebug()<<QJsonValue(res[0]).toObject();
            QStandardItemModel* model = new QStandardItemModel();
            model->setHorizontalHeaderItem(0, new QStandardItem("代号"));
            model->setHorizontalHeaderItem(1, new QStandardItem("城市"));
            model->setHorizontalHeaderItem(2, new QStandardItem("机场"));
            for(int i = 0 ; i < res.size(); i++){
                model->setItem(i, 0, new QStandardItem(QJsonValue(res[i]).toObject()["code"].toString()));
                model->setItem(i, 1, new QStandardItem(QJsonValue(res[i]).toObject()["city"].toString()));
                model->setItem(i, 2, new QStandardItem(QJsonValue(res[i]).toObject()["name"].toString()));
            }
            ui->ABCDETableView->setModel(model);
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

