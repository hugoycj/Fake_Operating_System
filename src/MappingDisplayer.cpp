#include <cmath>
#include <fstream>
#include <iostream>

#include <QIcon>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QHeaderView>

#include "ui_mainwindow.h"
#include "lib/MappingDisplayer.h"
#include "lib/mapper.h"

using namespace std;

//Convert int to hex
string intToHex(int n) {

    char buf[100] = {0};
    sprintf(buf, "%x", n);
    char result[100] = {0};
    result[0] = '0';
    result[1] = 'x';
    strcat(result, buf);

    return result;
}

MappingDisplayer::MappingDisplayer(int current_line_num, QWidget *parent)
    : QMainWindow(parent)
{
//    cout<<"???????"<<endl;

    // create a 64*9 table
    QTableWidget *table = new QTableWidget(64,10);

    // set header labels
    QStringList headerLabels;
    headerLabels << "VM" << "" << "TLB page no" << "TLB frame" << "" << "LV1_PT" << "" << "LV2_PT" << "" << "PM";
    table->setHorizontalHeaderLabels(headerLabels);

    // set alignment
    table->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);

    // set width for each line
    for(int i = 0; i < 64; i++) {
        table->setRowHeight(i, 22);
    };

    // adjust the width of the last row
    // right align to the right border
    table->horizontalHeader()->setStretchLastSection(true);

    // set the selection approach for the table
    table->setSelectionBehavior(QAbstractItemView::SelectItems);

    // read only
    table->setEditTriggers(QTableWidget::NoEditTriggers);

    // set contents for LV1_PT
    for (int row = 0; row < 64; ++row) {
        QTableWidgetItem *lv1_pte;
        lv1_pte = new QTableWidgetItem;

        QString txt = intToHex(row).c_str();
        lv1_pte->setText(txt);
        table->setItem(row, 5, lv1_pte);
    };


    ifstream infile;
//    string filename = "address_2.txt";
//    string filename = "/Users/alanzyt/Desktop/Fake_Operating_System/src/address.txt";
    string filename = "/Users/alanzyt/Desktop/Fake_Operating_System/src/address_2.txt";
//    string filename = "/Users/alanzyt/Desktop/Fake_Operating_System/src/duplicated_address.txt";

    infile.open(filename.c_str());

    VM mapper;
    string addr;

    int count = 0;
    cout << "Check cln: " << current_line_num << endl;
    while(getline(infile, addr)) {
        if (count == current_line_num) {

            // clear previous contents
            table->clearContents();

            cout<<"virtual addr: "<<addr<<endl;
            string phy_addr;

            int VA = mapper.binToInt(addr);
            const int range = 537399296;
            int vm_row_idx = floor(VA / (range/64));

            QTableWidgetItem *vm_entry;
            vm_entry = new QTableWidgetItem;

            QString txt = intToHex(VA).c_str();
            vm_entry->setText(txt);
            table->setItem(vm_row_idx, 0, vm_entry);

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

                QString txt = intToHex(updated_lv2_pt[i]).c_str();
                lv2_pte->setText(txt);
                table->setItem(i, 7, lv2_pte);
            };

            // calling tlbSearch to find out the frame page value
            int fpage_value = mapper.tlbSearch(page2Index, page_no2);
            mapper.fpage_set(fpage_value);

            // set tlb idx
            QTableWidgetItem *tlb_idx_entry;
            tlb_idx_entry = new QTableWidgetItem;

            QString tlb_idx = QString("%1").arg(page2Index);
            tlb_idx_entry->setText(tlb_idx);
            table->setItem(0, 2, tlb_idx_entry);

            for (int row_idx = 0; row_idx < 8; row_idx++) {

                cout << "Check tlb idx(page2idx): " << page2Index << endl;
                cout << "row_idx: " << row_idx << endl;

                // set tlb page no entry
                int tlb_page_no = mapper.tlb_get(page2Index,row_idx)[0];
                QTableWidgetItem *tlb_page_no_entry;
                tlb_page_no_entry = new QTableWidgetItem;

                QString txt = intToHex(tlb_page_no).c_str();
                tlb_page_no_entry->setText(txt);
                table->setItem(row_idx+1, 2, tlb_page_no_entry);

                // set tlb frame no entry
                int tlb_frame_no = mapper.tlb_get(page2Index,row_idx)[1];
                QTableWidgetItem *tlb_frame_no_entry;
                tlb_frame_no_entry = new QTableWidgetItem;

                QString txt2 = intToHex(tlb_frame_no).c_str();
                tlb_frame_no_entry->setText(txt2);
                table->setItem(row_idx+1, 3, tlb_frame_no_entry);

    //            cout << "Check tlb page no: " << tlb_page_no << endl;
    //            cout << "Check frame no: " << tlb_frame_no << endl;
            };

            // get the offset from vir_addr
            string offset_str = addr.substr(20,12);

            // combine the frame and offset to get the physical address
            phy_addr = mapper.decToBinStr(mapper.fpage_get());
            mapper.zero_extend(phy_addr,16);
            phy_addr += offset_str;


            cout<<"physical address: "<<phy_addr<<endl;

            // pause for 3s before the next read operation
    //        sleep(1);
    //        table->viewport()->update();
    //        table->update();
            table->show();
        };
        count++;
    };
    infile.close();
};

MappingDisplayer::~MappingDisplayer()
{

};

