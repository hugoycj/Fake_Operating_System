#ifndef FILEEXPLORER_H
#define FILEEXPLORER_H

#include <QMainWindow>
#include <QMessageBox>
#include <QInputDialog>
#include <QListWidget>
#include "fs.h"
#include "logger.h"

namespace Ui {
class fileexplorer;
}

class fileexplorer : public QMainWindow
{
    Q_OBJECT

public:
    explicit fileexplorer(QWidget *parent = nullptr);
    void contextMenuEvent(QContextMenuEvent *e);
    ~fileexplorer();
private slots:
    void on_BackButton_clicked();
    void on_MountButton_clicked();
    void on_UnmountButton_clicked();
    void on_FormatButton_clicked();
    void on_CopyInButton_clicked();
    void on_CopyOutButton_clicked();
    void on_ExecuteButton_clicked();

    void on_lineEdit_returnPressed();
    void on_comboBox_activated(const QString &arg1);

    void open_action_slot();
    void delete_action_slot();
    void create_file_action_slot();
    void create_dir_action_slot();
    void rename_action_slot();
    void properties_action_slot();
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

public slots:
    void receiveText(QVector<QString> data);
    void receiveAttr(QVector<QString> attrs);

private:
    logger l;
    Ui::fileexplorer *ui;
    QString path;

    // right click actions
    QAction* open_action;
    QAction* delete_action;
    QAction* create_file_action;
    QAction* create_dir_action;
    QAction* properties_action;
    QAction* rename_action;

    // file system
    FileSystem fs;

    // update functions
    void updateDirView();
};

#endif // FILEEXPLORER_H
