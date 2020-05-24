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


public:
    MappingDisplayer(const MappingDisplayer& obj);
    MappingDisplayer(QWidget *parent = 0);
    ~MappingDisplayer();
};

#endif // TEXTEDITOR_H
