#ifndef SELECTSEAT_H
#define SELECTSEAT_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class SelectSeat;
}

class SelectSeat : public QWidget
{
    Q_OBJECT

public:
    explicit SelectSeat(QWidget *parent = nullptr);
    ~SelectSeat();

private:
    Ui::SelectSeat *ui;
};

#endif // SELECTSEAT_H
