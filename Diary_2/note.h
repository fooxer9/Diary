#ifndef NOTE_H
#define NOTE_H
#include <iostream>
#include <QString>
#include <QDate>

class Note
{
public:
    std::string name;
    std::string note;
    QTime time;
    std::string printedName;
    QDate date;
    //std::string date;

    bool completeFlag = false;      // Галочка у заметки отсутствует
    int id;

    void setName(std::string text);
    void setNote(std::string text);
    void setTime(QTime time);
    void setDate(QDate date);
    void setId(int num);

};

#endif // NOTE_H
