#ifndef FILEEXPLORER_H
#define FILEEXPLORER_H

#include <QMainWindow>

namespace Ui {
class fileexplorer;
}

class fileexplorer : public QMainWindow
{
    Q_OBJECT

public:
    explicit fileexplorer(QWidget *parent = nullptr);
    ~fileexplorer();

private slots:
    void on_BackButton_clicked();

private:
    Ui::fileexplorer *ui;
};

#endif // FILEEXPLORER_H
