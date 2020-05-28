#include "activitymonitor.h"
#include "ui_activitymonitor.h"
#include <iostream>

activitymonitor::activitymonitor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::activitymonitor)
{
    ui->setupUi(this);
    setWindowTitle("Activity Monitor");
    ui->setupUi(this);

    tim = new QTimer();

    tim->setInterval(1000);

    connect(tim,SIGNAL(timeout()),this,SLOT(onTimeOut()));

    tim->start();
}

activitymonitor::~activitymonitor()
{
    delete ui;
}

void activitymonitor::onTimeOut()
{
    static int value = 0;
    static int count = 0;

    ui->MemBar->setValue(value++);

    QTableWidgetItem *tlb_idx_entry;
    tlb_idx_entry = new QTableWidgetItem;
    QString tlb_idx = QString("%1").arg(count);
    tlb_idx_entry->setText(tlb_idx);

    ui->ACTable->setItem(count, 2, tlb_idx_entry);

    count++;
    ui->ACTable->viewport()->update();

    if(value > 100) {
        tim->stop();
    }
}
