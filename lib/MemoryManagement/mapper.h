#ifndef MAPPER_H
#define MAPPER_H
// impl of paging mapper API
#include <string>
#include <iostream>
#include <map>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include "mappingdisplayer.h"

using namespace std;

/* Virtual Address: 32-bit
 *
 * 0000 0000 01 00 0000 0010 0000 0000 1101
 * ------------ ------------ --------------
 * 1st page no. 2nd page no.   page offset
 * (actually only 6 bits of page number is used)
 *
 * 1st page number = vir_addr[31:22]
 * 2nd page number = vir_addr[21:12]
 * offset = vir_addr[11:0]
 *
 *
 * Physical Address: 28-bit
 * 0000 0000 0000 1010 0000 0000 1101
 * ------------------- --------------
 *  physical page no.   page offset
 *
 */


/* Multi-level Page Table (1st level and second level)
 * There is one 1st level page table with 64 PTE (page table entries)
 * because the page number is 6-bit binary numbers 111111(bin) = 63(dec)
 *
 *         |-----------|
 * 0x0000  |           |
 *         |-----------|
 * 0x0001  |           |
 *         |-----------|
 * 0x0002  |           |
 *         |-----------|
 * 0x0003  |           |
 *         |-----------|
 * 0x0004  |           |
 *         |-----------|
 *         .           .
 *         .           .
 *         .           .
 *         |           |
 *         |-----------|
 * 0x0062  |           |
 *         |-----------|
 * 0x0063  |           |
 *         |-----------|
 *
 *
 * There are 64 2nd-level page tables.
 */


/*
 * Each TLB Table -- 2D array
 * ------------------------
 * size = TLBSize = 8
 * |----------|-------|
 * | vpage_no | frame |
 * |----------|-------|
 *
 * Since there PTSize is 64, 64 TLB are required.
 */


class VM {

private:
    // VM size: (64*64)*4/1024 = 16MB
    // PM size: 8 MB
    static const int TLBSize = 8;
    const int PTSize = 64;
    const int page_size = 4*1024; // 4*1024 byte /4 KB each page, total 2048 pages

    int TLBTable [64][8][2] = {{{0}}};
    int LV1_PT [64];

    // LV2_PT_SET is a vector to store the initialized 2nd level PTs
    // PT should have a ID since it is out of order in a vector during simulation
    // LV2_PT_SET = { [ID, (PT)], [ID, (PT)], ..., [ID, (PT)] }
    map< int, vector<int> >  LV2_PT_SET;

    // store the status of the 2nd-level PT to tell which PT has been initialized
    // initially all zero
    int lv2_pt_status [64] = {0};

    // fpage
    int fpage;

    int tlbIndexSet [64] = {0};

public:

    // constructor
    VM();

    // destructor
    ~VM();

    // conversion funciton
    int binToInt(string str);
    string decToBinStr(int n);
    int strToInt(string s);
    string intToStr(int i);

    // search the TLB to get the frame
    int tlbSearch(int index, int target);

    // when TLB Miss occurs, updateTLB information
    void updateTLB(int index, int page, int frame);

    // core function to perform translation from virtual to physical
    void mapper_test();

    void zero_extend(string &target, unsigned int len);

    // intialize one LV2 page table according to the given VD
    void random_init(int id);

    // get value in lv1 pt with idx
    int lv1_pt_get(int idx);

    // get value of fpage
    int fpage_get();

    // set value fo fpage
    void fpage_set(int value);

    // get lv2_pt
    vector<int> lv2_pt_get(int index);

    // get TLB table
    vector<int> tlb_get(int index, int row_idx);

    // generate random virtual address string, following specific rule
    string generate_VA();

    friend void mappingdisplayer::onTimeOut();
};

#endif
