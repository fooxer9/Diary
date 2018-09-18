#include "createnote.h"
#include "ui_createnote.h"

CreateNote::CreateNote(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreateNote)
{
    ui->setupUi(this);
}

CreateNote::~CreateNote()
{
    delete ui;
}

void CreateNote::on_pushButton_clicked()
{
    Diary *d = new Diary;
    //d->setEnabled(true);
    d->show();

    this->close();
}
