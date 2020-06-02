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

public:
    void receiveOriginalText(std::string text, std::string filename);
    TextEditor(QWidget *parent = 0);
    TextEditor(const TextEditor& obj);
    static TextEditor* NewInstance();
    std::string filename;
    ~TextEditor();

private slots:
    void save_action_slot();
    void exit_action_slot();
    void undo_action_slot();
    void redo_action_slot();
    void cut_action_slot();
    void copy_action_slot();
    void paste_action_slot();
    void delete_action_slot();
    void select_all_action_slot();

private:
    QPlainTextEdit mainEdit;

    TextEditor* operator = (const TextEditor& obj);
    bool construct();

    bool initMenuBar();
    bool initToolBar();
    bool initStatusBar();
    bool initinitMainEditor();

    bool initFileMenu(QMenuBar* mb);
    bool initEditMenu(QMenuBar* mb);
    bool initFileToolItem(QToolBar* tb);

    bool makeAction(QAction*& action, QString text, int key);
    bool makeAction(QAction*& action, QString tip, QString icon);

signals:
    void sendText(QVector<QString>);

protected:
    void closeEvent(QCloseEvent* event);
};

#endif // TEXTEDITOR_H
