#ifndef ACTIVITYMONITOR_H
#define ACTIVITYMONITOR_H

#include <QMainWindow>

namespace Ui {
class activitymonitor;
}

class activitymonitor : public QMainWindow
{
    Q_OBJECT

public:
    explicit activitymonitor(QWidget *parent = nullptr);
    ~activitymonitor();

private slots:
    void on_BackButton_clicked();

    void update_table(bool flag, int i);

private:
    Ui::activitymonitor *ui;
};

#endif // ACTIVITYMONITOR_H
