#include "selectseat.h"
#include "ui_selectseat.h"

SelectSeat::SelectSeat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectSeat)
{
    ui->setupUi(this);
    int offset1 = 0;
    for (int i = 0; i < 10; i++){
        int offset2 = 0;
        for(int j = 0; j < 3; j++){
            QPushButton* seat = new QPushButton(this);
            seat->setFixedSize(30,30);
            seat->setGeometry(50+offset2,60+offset1,30,30);
            seat->setCheckable(true);
            seat->show();
            //int id = offset;
            connect(seat,&QPushButton::clicked, this, [ = ] {
                //seat->setText(QString("%1").arg(id));

            });
            offset2 += 50;
        }
        offset2 += 20;
        for(int j = 0; j < 3; j++){
            QPushButton* seat = new QPushButton(this);
            seat->setFixedSize(30,30);
            seat->setGeometry(50+offset2,60+offset1,30,30);
            seat->setCheckable(true);
            seat->show();
            //int id = offset;
            connect(seat,&QPushButton::clicked, this, [ = ] {
                //seat->setText(QString("%1").arg(id));

            });
            offset2 += 50;
        }
        offset1 += 30;
    }

}

SelectSeat::~SelectSeat()
{
    delete ui;
}
