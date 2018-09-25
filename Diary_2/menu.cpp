#include "menu.h"
#include "ui_menu.h"

Menu::Menu(Diary *d, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    this->d = d;
}

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
    if(!d) {
        Diary *di = new Diary;
        di->show();

        this->close();
    }
    else {
        d->show();

        this->close();
    }
}

void Menu::on_exitButton_clicked() {
    QMessageBox exit(QMessageBox::Question,
                tr("Выход"),
                tr("Вы действительно хотите выйти?"),
                QMessageBox::Yes | QMessageBox::No,
                this);
        exit.setButtonText(QMessageBox::Yes, tr("Действительно хочу!"));
        exit.setButtonText(QMessageBox::No, tr("НЕТ!"));

    if (exit.exec() == QMessageBox::Yes){
        QApplication::exit();
    }
}
