#ifndef MAPPINGDISPLAYER_H
#define MAPPINGDISPLAYER_H
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QString>
#include <QMainWindow>
#include <QToolBar>
#include <QIcon>
#include <QSize>
#include <QStatusBar>
#include <QLabel>
#include <QPlainTextEdit>
#include<QCalendarWidget>
#include<QStackedWidget>
#include<QListWidget>
class MappingDisplayer : public QMainWindow
{
    Q_OBJECT
private:
<<<<<<< HEAD
=======
    int current_line_num = 0;
>>>>>>> cal


public:
    MappingDisplayer(const MappingDisplayer& obj);
<<<<<<< HEAD
    MappingDisplayer(QWidget *parent = 0);
=======
    MappingDisplayer(int current_line_num, QWidget *parent = 0);
>>>>>>> cal
    ~MappingDisplayer();
};

#endif // TEXTEDITOR_H
