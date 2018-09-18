#ifndef CREATENOTE_H
#define CREATENOTE_H

#include "diary.h"
#include <QMainWindow>

namespace Ui {
class CreateNote;
}

class CreateNote : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreateNote(QWidget *parent = 0);
    ~CreateNote();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CreateNote *ui;
};

#endif // CREATENOTE_H
