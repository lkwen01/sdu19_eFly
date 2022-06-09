#include "loginwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow w;
    w.show();

//    QNetworkAccessManager *manager = new QNetworkAccessManager();
//    QString url = "http://101.76.254.181:10086/login/";
//    QNetworkRequest request;
//    request.setUrl(QUrl(url));
//    QNetworkReply *pReply = manager->post(request,"");

    return a.exec();
}
