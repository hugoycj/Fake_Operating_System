#ifndef MAPPINGDISPLAYER_H
#define MAPPINGDISPLAYER_H
#include <QMainWindow>
#include <QTimer>

namespace Ui {
class mappingdisplayer;
}

class mappingdisplayer : public QMainWindow
{
    Q_OBJECT

public:
//    mappingdisplayer(const mappingdisplayer& obj);
//    mappingdisplayer(QWidget *parent = 0);

    explicit mappingdisplayer(QWidget *parent = nullptr);

    ~mappingdisplayer();

public slots:

    void onTimeOut();

private slots:
    void on_StartButton_clicked();

    void on_PauseButton_clicked();

private:
    Ui::mappingdisplayer *ui;
    QTimer *tim;
    bool flag = false;

};

#endif // MAPPINGDISPLAYER_H
