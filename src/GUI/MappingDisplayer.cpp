#include <cmath>
#include <iostream>

#include <QIcon>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QHeaderView>

#include "ui_mainwindow.h"
#include "ui_mappingdisplayer.h"
#include "mappingdisplayer.h"
#include "mapper.h"


using namespace std;

//Convert int to hex
string intToHex(int n, int len) {

    char buf[100] = {0};
    sprintf(buf, "%x", n);
    char result[100] = {0};
    result[0] = '0';
    result[1] = 'x';
    strcat(result, buf);

    string result_str(result);

    while (int(result_str.length()) < (len+2)) {
        result_str = "0x0" + result_str.substr(2);
    }

    return result_str;
}

mappingdisplayer::mappingdisplayer(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::mappingdisplayer)
{
    setWindowTitle("Mapping Displayer");
    ui->setupUi(this);

    connect(ui->StartButton, &QPushButton::clicked,this, &mappingdisplayer::on_StartButton_clicked);
    connect(ui->PauseButton, &QPushButton::clicked,this, &mappingdisplayer::on_PauseButton_clicked);

    tim = new QTimer();

    tim->setInterval(1500);

    connect(tim,SIGNAL(timeout()),this,SLOT(onTimeOut()));

    tim->start();
}

mappingdisplayer::~mappingdisplayer()
{
    delete ui;
};


void mappingdisplayer::on_StartButton_clicked()
{
    cout<<"start"<<endl;
    flag = true;
}

void mappingdisplayer::on_PauseButton_clicked()
{
    cout<<"pause"<<endl;
    flag = false;
}

void mappingdisplayer::onTimeOut()
{
    const int value = 0;

    if (flag) {

        // clear previous content
        ui->MDTable->clear();

        // set headers
        QStringList headerLabels;
        headerLabels << "VM" << "TLB page no" << "TLB frame" << "LV1_PT" << "LV2_PT" << "PM";
        ui->MDTable->setHorizontalHeaderLabels(headerLabels);

        // set table size
        ui->MDTable->setRowCount(64);
        ui->MDTable->setColumnCount(6);

        // set same column width
        ui->MDTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        // read only
        ui->MDTable->setEditTriggers(QTableWidget::NoEditTriggers);

        // construct mapper
        VM mapper;

        // set contents for LV1_PT
        for (int row = 0; row < 64; ++row) {
            QTableWidgetItem *lv1_pte;
            lv1_pte = new QTableWidgetItem;

            QString txt = intToHex(mapper.LV1_PT[row],2).c_str();
            lv1_pte->setText(txt);
            ui->MDTable->setItem(row, 3, lv1_pte);
        };

        // generate VA
        string addr = mapper.generate_VA();
        cout<<"virtual addr: "<<addr<<endl;

        string phy_addr;
        // get approximate row position of VA in the displaying table
        int VA = mapper.binToInt(addr);
        const int range = 537399296;
        int vm_row_idx = floor(VA / (range/64));

        // fill in vm entry
        QTableWidgetItem *vm_entry;
        vm_entry = new QTableWidgetItem;

        QString txt = intToHex(VA,7).c_str();
        vm_entry->setText(txt);
        ui->MDTable->setItem(vm_row_idx, 0, vm_entry);

        // 1.page_no1 is the position of target entry in 1st-level PT
        // 2.page_no2 is the position of target entry in 2nd-level PT
        // 3.page2Index is used to find the target 2nd-level PT in PT sets
        // 4.fpage is the final result of the frame
        int page_no1, page_no2, page2Index;
        page_no1 = mapper.binToInt(addr.substr(0,10));
        page_no2 = mapper.binToInt(addr.substr(10,10));
        page2Index = mapper.lv1_pt_get(page_no1);

        // call a initialize function to initialize the specific 2nd level PT
        mapper.random_init(page2Index);
        vector<int> updated_lv2_pt = mapper.lv2_pt_get(page2Index);

        for (unsigned int i = 0; i < updated_lv2_pt.size(); i++) {
            QTableWidgetItem *lv2_pte;
            lv2_pte = new QTableWidgetItem;

            QString txt = intToHex(updated_lv2_pt[i],3).c_str();
            lv2_pte->setText(txt);
            ui->MDTable->setItem(i, 4, lv2_pte);
        };

        // calling tlbSearch to find out the frame page value
        int fpage_value = mapper.tlbSearch(page2Index, page_no2);
        mapper.fpage_set(fpage_value);

        // set tlb/level2_pt idx
        QTableWidgetItem *tlb_idx_entry;
        tlb_idx_entry = new QTableWidgetItem;

        string page2Index_str = "LV2_PT idx: " + to_string(page2Index);
        QString tlb_idx = QString::fromStdString(page2Index_str);

        tlb_idx_entry->setText(tlb_idx);
        ui->MDTable->setItem(0, 1, tlb_idx_entry);

        for (int row_idx = 0; row_idx < 8; row_idx++) {

            // set tlb page no entry
            int tlb_page_no = mapper.tlb_get(page2Index,row_idx)[0];
            QTableWidgetItem *tlb_page_no_entry;
            tlb_page_no_entry = new QTableWidgetItem;

            QString txt = intToHex(tlb_page_no,2).c_str();
            tlb_page_no_entry->setText(txt);
            ui->MDTable->setItem(row_idx+1, 1, tlb_page_no_entry);

            // set tlb frame no entry
            int tlb_frame_no = mapper.tlb_get(page2Index,row_idx)[1];
            QTableWidgetItem *tlb_frame_no_entry;
            tlb_frame_no_entry = new QTableWidgetItem;

            QString txt2 = intToHex(tlb_frame_no,3).c_str();
            tlb_frame_no_entry->setText(txt2);
            ui->MDTable->setItem(row_idx+1, 2, tlb_frame_no_entry);

        };

        // get the offset from vir_addr
        string offset_str = addr.substr(20,12);

        // combine the frame and offset to get the physical address
        phy_addr = mapper.decToBinStr(mapper.fpage_get());
        mapper.zero_extend(phy_addr,16);
        phy_addr += offset_str;

        int PA = mapper.binToInt(phy_addr);
        string max_phy = "11111111111111111111111";
        mapper.zero_extend(max_phy,28);
        const int range2 = mapper.binToInt(max_phy);
        int pm_row_idx = floor(PA / (range2/64));

        // set pm entry
        QTableWidgetItem *pm_entry;
        pm_entry = new QTableWidgetItem;

        QString txt_pm = intToHex(PA,6).c_str();
        pm_entry->setText(txt_pm);
        ui->MDTable->setItem(pm_row_idx, 5, pm_entry);

        cout<<"physical address: "<<phy_addr<<endl;

        // automatically change size
        ui->centralwidget->setLayout(ui->verticalLayout);

        // update contents
        ui->MDTable->viewport()->update();
    }

    if(value > 100) {
        tim->stop();
    }
}




