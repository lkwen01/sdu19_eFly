#ifndef FLIGHTLIST_H
#define FLIGHTLIST_H

#include <QWidget>

namespace Ui {
class FlightList;
}

class FlightList : public QWidget
{
    Q_OBJECT

public:
    explicit FlightList(QWidget *parent = nullptr);
    ~FlightList();

private:
    Ui::FlightList *ui;
};

#endif // FLIGHTLIST_H
