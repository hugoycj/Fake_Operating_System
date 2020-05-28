#ifndef ACTIVITYMONITOR_H
#define ACTIVITYMONITOR_H
#include <QMainWindow>
#include <QTimer>

namespace Ui {
class activitymonitor;
}

class activitymonitor : public QMainWindow
{
    Q_OBJECT

public:

    explicit activitymonitor(QWidget *parent = nullptr);

    ~activitymonitor();

public slots:

    void onTimeOut();

private:
    Ui::activitymonitor *ui;
    QTimer *tim;
};

#endif // ACTIVITYMONITOR_H
