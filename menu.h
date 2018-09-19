#ifndef MENU_H
#define MENU_H

#include "diary.h"
#include <QMainWindow>

namespace Ui {
class Menu;
}

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();

private slots:

    void on_lastButton_clicked();

    void on_exitButton_clicked();

private:
    Ui::Menu *ui;
};

#endif // MENU_H
