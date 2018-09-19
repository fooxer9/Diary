#ifndef DIARY_H
#define DIARY_H

#include "note.h"
#include "menu.h"
#include "createnote.h"
#include <QMainWindow>
#include <vector>
#include <QListWidget>
#include <QMessageBox>
#include <string>
#include <QDebug>
#include "createnote.h"

namespace Ui {
class Diary;
}

class Diary : public QMainWindow
{
    Q_OBJECT

public:
    explicit Diary(QWidget *parent = 0);
    ~Diary();

//friend class CreateNote;

private slots:
    void write();

    void writeUnchecked();

    int getIndex(std::string);

    void on_saveButton_clicked();

    void on_deleteButton_clicked();

    void on_editButton_clicked();

    void on_taskList_itemDoubleClicked();

    void on_hideCompleted_stateChanged(int arg1);

    void on_taskList_itemChanged(QListWidgetItem *item);

    void on_calendar_clicked(const QDate &date);

    bool day_is_empty(QDate &date);

    void on_todayTasks_stateChanged(int arg1);

    void on_instruction_triggered();

    void on_exit_triggered();

    void on_timeEdit_timeChanged(const QTime &time);

    void on_menuButton_clicked();

    void on_newNoteButton_clicked();

private:
    Ui::Diary *ui;
    std::vector <Note> notes;   // Все заметки
    int editFlag = -1;          // Флаг редактирования, содержит номер редактируемой заметки или значение = -1
    bool hide = false;          // Успокаивает обработчик событий на листе
};


#endif // DIARY_H
