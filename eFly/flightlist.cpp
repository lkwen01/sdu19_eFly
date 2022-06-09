#include "flightlist.h"
#include "ui_flightlist.h"

FlightList::FlightList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FlightList)
{
    ui->setupUi(this);
}

FlightList::~FlightList()
{
    delete ui;
}
