/*
* Reference:
* Perez, R., Brunette, A. & Zhang, A., (2019) Virtual Memory Manager [Source code]. https://github.com/abrunette/Virtual_Memory_Manager
*/

#include <string>
#include <iostream>
#include <map>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include "mapper.h"
#include <vector>
#include <ctime>

using namespace std;

// impl of paging mapper API

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

/*                                      Translation Process
 *
 *              Virtual Address: 32-bit
 *
 *      0000 0000 01 00 0000 0010 0000 0000 1101
 *      ------------ ------------ --------------
 *      1st page no. 2nd page no.   page offset
 *          ||           ||             ||
 *          ||           ||              --------------------------------------------------------------
 *   --------             -----------------------------------                                         ||
 *  ||                                                      ||                                        ||
 *  ||       1st-lv-pt        =====> (index: i) 2nd-lv-pt   ||                                        ||
 *  \/     |-----------|     ||         |-----------|       \/                                        ||
 * 0x0000  | page2Idx  | =====          | frame no  |---   0x0000                                     ||
 *         |-----------|                |-----------|  ||                                             ||
 * 0x0001  |           |                |           |   -------------------------                     ||
 *         |-----------|                |-----------|                           ||                    ||
 * 0x0002  |           |                |           |      0x0002               ||                    ||
 *         |-----------|                |-----------|                           \/                    \/
 * 0x0003  |           |                |           |      0x0003       0000 0000 01 00 0000 0010 0000 0000 1101
 *         |-----------|                |-----------|                   ------------ ------------ --------------
 * 0x0004  |           |                |           |      0x0004       1st page no. 2nd page no.   page offset
 *         |-----------|                |-----------|
 *         .           .                .           .                           Physical Address: 28-bit
 *         .           .                .           .
 *         .           .                .           .
 *         |           |                |           |
 *         |-----------|                |-----------|
 * 0x0062  |           |                |           |      0x0062
 *         |-----------|                |-----------|
 * 0x0063  |           |                |           |      0x0063
 *         |-----------|                |-----------|
 *
 */


void VM::zero_extend(string &target, unsigned int len) {
    while (target.length() < len) {
        target = "0" + target;
    };
}


// constructor
VM::VM() {
    for (int i = 0; i < (this->PTSize); i ++) {
        LV1_PT[i] = (rand() % (63-0+1)) + 0;
    };
};


// destructor
VM::~VM() {

};


void VM::mapper_test() {

    string addr = generate_VA();
    cout<<"virtual addr: "<<addr<<endl;
    string phy_addr;

    // 1.page_no1 is the position of target entry in 1st-level PT
    // 2.page_no2 is the position of target entry in 2nd-level PT
    // 3.page2Index is used to find the target 2nd-level PT in PT sets
    // 4.fpage is the final result of the frame
    int page_no1, page_no2, page2Index;
    page_no1 = binToInt(addr.substr(0,10));
    page_no2 = binToInt(addr.substr(10,10));
    page2Index = LV1_PT[page_no1];

    // call a initialize function to initialize the specific 2nd level PT
    random_init(page2Index);

    // calling tlbSearch to find out the frame page value
    fpage = tlbSearch(page2Index, page_no2);

    // get the offset from vir_addr
    string offset_str = addr.substr(20,12);

    // combine the frame and offset to ge the physical address
    phy_addr = decToBinStr(fpage);
    zero_extend(phy_addr,16);
    phy_addr += offset_str;

    cout<<"physical address: "<<phy_addr<<endl;
};


// search tlb and get the physical page number
// the function will return the result of 28-bit frame value
// TLBHit -> found = 1
// TLBMiss -> found = 0
// Page Fault -> found = -1

// index: 2nd_level page table no.
// target: target entry in the specific 2nd_level page table
int VM::tlbSearch(int index, int target) {
    cout << "start tlb search" << endl;

    int found = -1;
    int frame;

    // Search TLB for target page number
    // TLB Hit -> get frame value directly
    for (int i = 0; i < (TLBSize-1); i++) {
        if (TLBTable[index][i][0] == target) {
            cout << "TLB hit" << endl;
            found = 1;
            frame = TLBTable[index][i][1];
        };
    };

    // TLB Miss -> Search PageTable and Update TLB
    if (found == -1) {
        cout << "TLB miss" << endl;
        map< int, vector<int> >::iterator it;
        for (it = LV2_PT_SET.begin(); it!= LV2_PT_SET.end(); it++) {
            int id = it->first;
            if (id == index) {
                vector<int> pt = it->second;
                frame = pt[target];
            }
        }
        updateTLB(index, target, frame);
        cout<<index<<"-th TLB"<<endl;
        cout<<"tlb idx: "<<tlbIndexSet[index]<<endl;
    }

    cout<<"Finish tlbSearch."<<endl;
    return frame;
}


void VM::updateTLB(int index, int page, int frame) {
    if (tlbIndexSet[index] == TLBSize-1) {
        tlbIndexSet[index] = 0;
    };

    TLBTable[index][(tlbIndexSet[index])][0] = page;
    TLBTable[index][(tlbIndexSet[index])][1] = frame;

    (tlbIndexSet[index])++;
};


// create a new 2nd level PT and initialize it
void VM::random_init(int id) {
    vector<int> pt;

    // initialize pt
    for (int i = 0; i < (this->PTSize); i++) {
        // generate random pte
        int page_no = (rand() % (2047-0+1)) + 0; // 0~2047 pysical page number
        pt.push_back(page_no);
    }

    // update lv2 pt status
    lv2_pt_status[id] = 1;

    // put pt into LV2_PT_SET according to id
    LV2_PT_SET[id] = pt;
};


// get value in lv1 pt with idx
int VM::lv1_pt_get(int idx) {
    return LV1_PT[idx];
}

// get value of fpage
int VM::fpage_get() {
    return fpage;
}

// set value fo fpage
void VM::fpage_set(int value) {
    fpage = value;
}

// get lv2 pt
vector<int> VM::lv2_pt_get (int index) {
    vector<int> temp;
    map< int, vector<int> >::iterator it;
    for (it = LV2_PT_SET.begin(); it!= LV2_PT_SET.end(); it++) {
        int id = it->first;
        if (id == index) {
            temp = it->second;
            break;
        };
    };
    return temp;
}

// get TLB idx-th table
vector<int> VM::tlb_get(int index, int row_idx) {
    vector<int> buf;

    buf.push_back(TLBTable[index][row_idx][0]);
    buf.push_back(TLBTable[index][row_idx][1]);

    return buf;
}

int VM::binToInt(string str) {
    int n = 0;
    for (unsigned int i = 0; i < str.size(); i++)
    {
        n = n * 2 + (str[i] - '0');
    };
    return (int)n;
};


//converts a string of decimal to binary
string VM::decToBinStr(int n) {//turns passed integer into a 32 bit binary string
    string r;
    while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}

    return r;
}


//convert a string to number
int VM::strToInt(string s) {
    int tmp=0;
    int multiplier=1;

    for(int i=s.length()-1;i>=0;i--){
        if (s[i]=='-') break;
        tmp+=(s[i]-'0')*multiplier;
        multiplier*=10;
    };

    if (s[0]=='-') tmp*=-1;

    return tmp;
};


//convert a int to string
string VM::intToStr(int i) {
    stringstream ss2;
    string strTemp;
    ss2<<i;
    ss2>>strTemp;

    return strTemp;
};


string VM::generate_VA() {

    VM mid_mapper;
    int LV1_page_no = (rand() % (63-0+1)) + 0;
    int LV2_page_no = (rand() % (63-0+1)) + 0;
    int b = this->page_size;
    int offset = (rand() % (b-0+1)) + 0;

    string LV1_page_no_str = mid_mapper.decToBinStr(LV1_page_no);
    string LV2_page_no_str = mid_mapper.decToBinStr(LV2_page_no);
    string offset_str = mid_mapper.decToBinStr(offset);

    mid_mapper.zero_extend(LV1_page_no_str,10);
    mid_mapper.zero_extend(LV2_page_no_str,10);
    mid_mapper.zero_extend(offset_str,12);

    string result = LV1_page_no_str + LV2_page_no_str + offset_str;
    return result;
}
