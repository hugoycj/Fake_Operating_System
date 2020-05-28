#include "activitymonitor.h"
#include "ui_activitymonitor.h"
#include <iostream>
#include "gobalPL.h"

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

    global_pl.display();
    if (!global_pl.isEmpty())
    {
        global_pl.output();
        cout << "runed a process" << endl;
    }

    int memory_size = 0;
    int total_number_of_process = global_pl.Process_List.size();
    for (int i = 0; i < total_number_of_process; i++)
    {
        ProcessControlBlock *temp_pcb = &global_pl.Process_List[i];
        memory_size += temp_pcb->process_link->size;

        QString tbl_id = QString("%1").arg(temp_pcb->process_id);
        QString tbl_pri = QString("%1").arg(temp_pcb->process_priority);
        QString tbl_name = QString::fromStdString(temp_pcb->process_name);

        QTableWidgetItem *tbl_id_entry = new QTableWidgetItem;
        QTableWidgetItem *tbl_pri_entry = new QTableWidgetItem;
        QTableWidgetItem *tbl_name_entry = new QTableWidgetItem;
        tbl_id_entry->setText(tbl_id);
        tbl_pri_entry->setText(tbl_pri);
        tbl_name_entry->setText(tbl_name);

        ui->ACTable->setItem(i, 0, tbl_id_entry);
        ui->ACTable->setItem(i, 1, tbl_pri_entry);
        ui->ACTable->setItem(i, 2, tbl_name_entry);

    }

    ui->ACTable->viewport()->update();
    ui->MemBar->setValue(memory_size);

    if(value > 100) {
        tim->stop();
    }
}
