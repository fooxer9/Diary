#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
}

Menu::~Menu()
{
    delete ui;
}


void Menu::on_lastButton_clicked()
{
    Diary *d = new Diary;
    d->show();

    this->close();
}

void Menu::on_exitButton_clicked() {
    this->close();
}
