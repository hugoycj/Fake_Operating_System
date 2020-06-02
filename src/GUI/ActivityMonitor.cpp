#include "activitymonitor.h"
#include "ui_activitymonitor.h"
#include <iostream>
#include "gobalPL.h"
#include <unistd.h>

extern ProcessesList global_pl = ProcessesList();

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
    const int value = 0;

    // clear table contents
    ui->ACTable->clear();

    // set headers
    QStringList headerLabels;
    headerLabels << "Process Name" << "Memory Used" << "Status" << "Priority" << "Process ID";
    ui->ACTable->setHorizontalHeaderLabels(headerLabels);

    // read only
    ui->ACTable->setEditTriggers(QTableWidget::NoEditTriggers);

    global_pl.display();
    if (!global_pl.isEmpty())
    {
        global_pl.output();
        cout << "runed a process" << endl;
    }

    int memory_size = 0;
    int total_number_of_process = global_pl.Process_List.size();

    // update table items
    for (int i = 0; i < total_number_of_process; i++)
    {
        ProcessControlBlock *temp_pcb = &global_pl.Process_List[i];
        memory_size += temp_pcb->process_link->size;

        QString tbl_id = QString("%1").arg(temp_pcb->process_id);
        QString tbl_pri = QString("%1").arg(temp_pcb->process_priority);
        QString tbl_size = QString("%1").arg(temp_pcb->process_link->size);
        QString tbl_name = QString::fromStdString(temp_pcb->process_name);

        char state = temp_pcb->process_state;
        char state_ch[2] = {state, 0};
        string state_str = state_ch;
        QString tbl_state = QString::fromStdString(state_str);


        QTableWidgetItem *tbl_id_entry = new QTableWidgetItem;
        QTableWidgetItem *tbl_pri_entry = new QTableWidgetItem;
        QTableWidgetItem *tbl_name_entry = new QTableWidgetItem;
        QTableWidgetItem *tbl_size_entry = new QTableWidgetItem;
        QTableWidgetItem *tbl_state_entry = new QTableWidgetItem;

        tbl_id_entry->setText(tbl_id);
        tbl_pri_entry->setText(tbl_pri);
        tbl_name_entry->setText(tbl_name);
        tbl_size_entry->setText(tbl_size);
        tbl_state_entry->setText(tbl_state);

        ui->ACTable->setItem(i, 0, tbl_name_entry);
        ui->ACTable->setItem(i, 1, tbl_size_entry);
        ui->ACTable->setItem(i, 2, tbl_state_entry);
        ui->ACTable->setItem(i, 3, tbl_pri_entry);
        ui->ACTable->setItem(i, 4, tbl_id_entry);

    }

    // automatically change size
    ui->centralwidget->setLayout(ui->verticalLayout);

    // update contents
    ui->ACTable->viewport()->update();

    // update memory bar
    ui->MemBar->setValue(memory_size);

    if(value > 100) {
        tim->stop();
    }
}
