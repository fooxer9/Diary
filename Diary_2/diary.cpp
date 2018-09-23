#include "diary.h"
#include "ui_diary.h"
#include "note.h"

Diary::Diary(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Diary)
{

    ui->setupUi(this);

}

Diary::~Diary()
{
    delete ui;
}

void Diary::write() { // Запись в лист всех задач
    for(unsigned int i = 0; i < notes.size(); i++) {
        notes[i].id = i;
        notes[i].setName(notes[i].name);
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(notes[i].printedName), ui->taskList);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        if(notes[i].completeFlag == true) {
            item->setCheckState(Qt::Checked);
        }
        else {
            item->setCheckState(Qt::Unchecked);
        }
    }
}

void Diary::writeUnchecked() { // Запись в лист невыполненных задач
    for(unsigned int i = 0; i < notes.size(); i++) {
        if(notes[i].completeFlag == false) {
            QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(notes[i].printedName), ui->taskList);
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            item->setCheckState(Qt::Unchecked);
        }
    }
}

int Diary::getIndex(std::string text) { // Получить индекс элемента списка
    int index = 0;
    unsigned int i = 0;
    for(; i < 5; i++) {
        if(text[i + 1] == '.') {
            break;
        }
    }
    for(int j = i; j >= 0; j--) {
        index += (text[i - j] - 48) * pow(10, j);
    }
    return index;
}

void Diary :: calendar_color() { // календарь будет закрашивать дату последней созданной заметки
    QTextCharFormat format = ui->calendar->dateTextFormat(notes[notes.size()-1].date); // закрашивание ячейки календаря
    format.setBackground(QBrush(QColor (200,244,99), Qt::SolidPattern));                 // в QColor потом подберем цвет ячейки календаря
    ui->calendar->setDateTextFormat(notes[notes.size()-1].date, format);
}

void Diary::on_saveButton_clicked() // Сохранения заметки - теперь это не тут должно быть
{
    /*if(editFlag != -1 && ui->taskText->toPlainText().toStdString() != "") { // Редактирование существующей заметки
        notes[editFlag].setId(editFlag);
        notes[editFlag].setName(ui->taskText->toPlainText().toStdString());
        notes[editFlag].setNote(ui->taskText->toPlainText().toStdString());
        notes[editFlag].setTime(ui->timeEdit->text().toStdString());
        QDate tmp = notes[editFlag].date;
        notes[editFlag].setDate ( ui->calendar->selectedDate());
        //sorting
        // в локальной QDate сохраняем предыдущую дату и проверяем на оставшиеся задачи, удаляем окрашивание
        if (day_is_empty(tmp)) {
            QTextCharFormat format = ui->calendar->dateTextFormat(tmp); // закрашивание ячейки календаря
            format.clearBackground();                                   // в QColor потом подберем цвет ячейки календаря
            ui->calendar->setDateTextFormat(tmp, format);
        }
        QTextCharFormat format = ui->calendar->dateTextFormat(ui->calendar->selectedDate()); // закрашивание ячейки календаря
        format.setBackground(QBrush(QColor (200,244,99), Qt::SolidPattern));                 // в QColor потом подберем цвет ячейки календаря
        ui->calendar->setDateTextFormat(ui->calendar->selectedDate(), format);

        ui->timeEdit->setTime(QTime::fromString("00:00"));
        ui->taskText->clear();
        hide = true;                // Охлаждает обработчик событий на листе
        ui->taskList->clear();      // Здесь
        if(ui->hideCompleted->isChecked())
            writeUnchecked();
        else
            Diary::write();         // Обработчик
        editFlag = -1;              // Отдыхает
        hide = false;               // Обработчик снова в деле
    }

    else if(ui->taskText->toPlainText().toStdString() != "") { // Создание новой заметки
        Note note;
        note.id = notes.size();
        note.setName(ui->taskText->toPlainText().toStdString());
        note.setNote(ui->taskText->toPlainText().toStdString());
        note.setTime(ui->timeEdit->text().toStdString());
        note.setDate(ui->calendar->selectedDate());
        notes.push_back(note);
        //sorting

        ui->timeEdit->setTime(QTime::fromString("00:00"));
        ui->taskText->clear();
        hide = true;
        ui->taskList->clear();
        if(ui->hideCompleted->isChecked())
            writeUnchecked();
        else
            Diary::write();
        QTextCharFormat format = ui->calendar->dateTextFormat(ui->calendar->selectedDate()); // закрашивание ячейки календаря
        format.setBackground(QBrush(QColor (200,244,99), Qt::SolidPattern)); // в QColor потом подберем цвет ячейки календаря
        ui->calendar->setDateTextFormat(ui->calendar->selectedDate(), format);

        hide = false;
    }*/
}

void Diary::on_deleteButton_clicked()  // Удаление заметки
{
    if(ui->taskList->currentItem()) {
        QMessageBox del(QMessageBox::Question, tr("Удаление задачи"), tr("Вы действительно хотите удалить задачу?"),
                                                                QMessageBox::Yes | QMessageBox::No, this);
        del.setButtonText(QMessageBox::Yes, tr("Хочу!"));
        del.setButtonText(QMessageBox::No, tr("Не хочу!"));
        if(del.exec() == QMessageBox::Yes) {

            QDate tmp =  notes[getIndex(ui->taskList->currentItem()->text().toStdString())].date;

            qDebug() << "deleted from vector - " << getIndex(ui->taskList->currentItem()->text().toStdString());
            qDebug() << "deleted - " << ui->taskList->currentRow();

            notes.erase(notes.begin() + getIndex(ui->taskList->currentItem()->text().toStdString()));
            delete ui->taskList->currentItem();
            ui->taskText->clear();

            // перекрашивание ячейки, если на день нет больше заданий
            if (day_is_empty(tmp)) {
                QTextCharFormat format = ui->calendar->dateTextFormat(tmp);
                format.clearBackground();
                ui->calendar->setDateTextFormat(tmp, format);
            }
        }
    }
}

void Diary::on_editButton_clicked()  // Редактирование заметки //будет тоже вызываться окошко createnote, но с выставленными данными
{
    if(ui->taskList->currentItem()) {
        editFlag = getIndex(ui->taskList->currentItem()->text().toStdString());

        QDate tmp =  notes[getIndex(ui->taskList->currentItem()->text().toStdString())].date;
        QTextCharFormat format = ui->calendar->dateTextFormat(tmp);
        format.clearBackground();
        ui->calendar->setDateTextFormat(tmp, format);

        on_newNoteButton_clicked();
    }
}

void Diary::on_taskList_itemDoubleClicked()  // Редактирование заметки
{
    Diary::on_editButton_clicked();
}

void Diary::on_hideCompleted_stateChanged(int arg1) // Скрыть выполненные задачи
{
    if(arg1) {
        // Write unchecked
        hide = true;
        ui->taskList->clear();
        Diary::writeUnchecked();
        hide = false;
        ui->taskText->clear();
    }
    else {
        // Write all
        hide = true;
        ui->taskList->clear();
        Diary::write();
        hide = false;
    }
}


void Diary::on_taskList_itemChanged(QListWidgetItem *item) // Обработчик событий на листе, синхронизирует переменные и галочки
{

    ui->calendar->setSelectedDate(notes[getIndex(item->text().toStdString())].date);
    if(!hide) {
        if(item->checkState() == Qt::Checked) {
            notes[getIndex(item->text().toStdString())].completeFlag = true;
            qDebug() << "true" << ui->taskList->row(item);
            qDebug() << "true at vector" << getIndex(item->text().toStdString());
        }

        else {
            notes[getIndex(item->text().toStdString())].completeFlag = false;
            qDebug() << "false" << ui->taskList->row(item);
            qDebug() << "false at vector" << getIndex(item->text().toStdString());
        }
    }

}

/*void Diary::on_calendar_clicked(const QDate &date) //Запрет на создание новых дел для прошедших дней
{
    if (date < QDate::currentDate()) ui->saveButton->setDisabled(true);
    else ui->saveButton->setDisabled(false);
}*/

void Diary::on_todayTasks_stateChanged(int arg1) // Список событий на конкретную дату
{
    if (arg1) {
        hide = true;
        ui->taskList->clear();
        hide = false;

        for (unsigned int i = 0; i < notes.size(); i++){

            if (notes[i].date == ui->calendar->selectedDate()) {
                QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(notes[i].printedName), ui->taskList);
                if(notes[i].completeFlag == true) {
                    item->setCheckState(Qt::Checked);
                }
                else {
                    item->setCheckState(Qt::Unchecked);
                }
            }
         }
     }  else {
        hide = true;
        ui->taskList->clear();
        this->write();
        hide = false;
    }
 }


bool Diary :: day_is_empty(QDate &date) { //проверка, остались ли дела на указанный день

    for (unsigned int i = 0; i < notes.size(); i++)
        if (date == notes[i].date) return 0;
    return 1;
}

void Diary::on_instruction_triggered()
{
    QString information = "Приложение \"Ежедневник\" позволяет создавать и редактировать задачи, отсортированные по дате и времени, а также контролировать их выполнение.\n"
                          "В левом поле Ваша заметка Вы можете ввести задачу, в календаре над полем выбрать дату не чёто плохо заходит и спать охота напишу потом";
    QMessageBox::information(this, "Инструкция", information);
}

void Diary::on_exit_triggered()
{
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

/*void Diary::on_timeEdit_timeChanged(const QTime &time) //это теперь тоже должно быть не здесь
{
    if (ui->calendar->selectedDate() == QDate :: currentDate()) {
    if (time < QTime::currentTime()) ui->saveButton->setDisabled(true);
    else ui->saveButton->setDisabled(false);
    }
    else ui->saveButton->setDisabled(false);
}*/

void Diary::on_menuButton_clicked()
{
    Menu *m = new Menu(this);
    m->show();
    m->setFixedSize(m->size());

    ui->taskText->clear();
    this->close();
}

void Diary::on_newNoteButton_clicked()
{
    CreateNote *c = new CreateNote(this);
    c->show();
    c->setFixedSize(c->size());
    ui->taskList->clear();

    ui->taskText->clear();
    this->close();
}

void Diary::on_taskList_itemClicked(QListWidgetItem *item)
{
    ui->taskText->setPlainText(QString::fromStdString(notes[getIndex(item->text().toStdString())].note));
}

void Diary::on_clearTextButton_clicked()
{
    ui->taskText->clear();
}

void Diary::on_clearTasksButton_clicked()
{
    QMessageBox clear(QMessageBox::Question,
                tr("Очистка"),
                tr("Вы действительно хотите очистить ежедневник?"),
                QMessageBox::Yes | QMessageBox::No,
                this);
        clear.setButtonText(QMessageBox::Yes, tr("Действительно хочу!"));
        clear.setButtonText(QMessageBox::No, tr("НЕТ!"));

    if (clear.exec() == QMessageBox::Yes){
        for (unsigned int i = 0; i < notes.size(); i++) {
            if (i >=1 && notes[i].date == notes[i-1].date) continue;
            QTextCharFormat format = ui->calendar->dateTextFormat(notes[i].date);
            format.clearBackground();
            ui->calendar->setDateTextFormat(notes[i].date, format);
        }
        notes.clear();
        notes.resize(0);
        ui->taskList->clear();
        ui->taskText->clear();

    }
}
