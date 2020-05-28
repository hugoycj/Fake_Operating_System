#include "activitymonitor.h"
#include "ui_activitymonitor.h"
#include <iostream>

activitymonitor::activitymonitor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::activitymonitor)
{
    ui->setupUi(this);
    setWindowTitle("Activity Monitor");

}

activitymonitor::~activitymonitor()
{
    delete ui;
}

void activitymonitor::on_BackButton_clicked()
{
    std::cout << "BackButton Clicked" << std::endl;
    // cd ..
}

void activitymonitor::update_table(bool flag, int i) {
    QTableWidgetItem *tlb_idx_entry;
    tlb_idx_entry = new QTableWidgetItem;

    QString tlb_idx = QString("%1").arg(i);
    tlb_idx_entry->setText(tlb_idx);

    ui->ACTable->setItem(0, 2, tlb_idx_entry);
};
