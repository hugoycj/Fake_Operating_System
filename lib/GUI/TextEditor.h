#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H
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
class TextEditor : public QMainWindow
{
    Q_OBJECT
private:
    QPlainTextEdit mainEdit;
    QLabel statusLabel;

    TextEditor* operator = (const TextEditor& obj);
    bool construct();

    bool initMenuBar();//菜单栏
    bool initToolBar();//工具栏
    bool initStatusBar();//状态栏
    bool initinitMainEditor();//编辑窗口

    bool initFileMenu(QMenuBar* mb);//文件菜单
    bool initEditMenu(QMenuBar* mb);//编辑菜单
    bool initFormatMenu(QMenuBar* mb);//格式菜单
    bool initViewMenu(QMenuBar* mb);//视图菜单
    bool initHelpMenu(QMenuBar* mb);//帮助菜单
    bool initFileToolItem(QToolBar* tb);

    bool makeAction(QAction*& action, QString text, int ket);//菜单项
    bool makeAction(QAction*& action, QString tip, QString icon);
public:
    TextEditor(QWidget *parent = 0);
    TextEditor(const TextEditor& obj);
    static TextEditor* NewInstance();
    ~TextEditor();
};

#endif // TEXTEDITOR_H
