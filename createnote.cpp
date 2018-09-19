#include "createnote.h"
#include "ui_createnote.h"

CreateNote::CreateNote(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreateNote)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->timeEdit->setTime(QTime :: currentTime());

}

CreateNote::~CreateNote()
{
    delete ui;
}

void CreateNote::on_backButton_clicked()
{
    Diary *d = new Diary;
    //d->setEnabled(true);
    d->show();

    this->close();
}




void CreateNote::on_dateEdit_dateChanged(const QDate &date) // запрет на создание событий в прошлом
{
    if (date < QDate :: currentDate() || (date == QDate::currentDate() && this->ui->timeEdit->time() <= QTime::currentTime())) this->ui->saveNoteButton->setDisabled(true);
        else this->ui->saveNoteButton->setDisabled(false);
}

void CreateNote::on_timeEdit_timeChanged(const QTime &time) // запрет на игры со временем
{
    if (this->ui->dateEdit->date() == QDate::currentDate()) {
        if (time <= QTime::currentTime()) this->ui->saveNoteButton->setDisabled(true);
            else this->ui->saveNoteButton->setDisabled(false);
    } else ui->saveNoteButton->setDisabled(false);

}

Note CreateNote :: newNote () {
    Note note;
    note.setName(ui->titleEdit->text().toStdString());
    note.setNote(ui->textEdit->toPlainText().toStdString());
    //note.setTime(ui->timeEdit->time());
    note.setDate(ui->dateEdit->date());
    return note;

}

void CreateNote::on_saveNoteButton_clicked()
{


    // сохранение в notes - нужно придумать, как передадим заметку в diary
    // нужно придумать как передать дату в календарь (считывать дату последней созданной заметки?)
}
