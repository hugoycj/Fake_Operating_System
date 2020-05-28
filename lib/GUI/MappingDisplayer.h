#ifndef MAPPINGDISPLAYER_H
#define MAPPINGDISPLAYER_H
#include <QMainWindow>
#include<QStackedWidget>
#include<QListWidget>
class MappingDisplayer : public QMainWindow
{
    Q_OBJECT
private:

public:
    MappingDisplayer(const MappingDisplayer& obj);
    MappingDisplayer(QWidget *parent = 0);
    ~MappingDisplayer();
};

#endif // TEXTEDITOR_H
