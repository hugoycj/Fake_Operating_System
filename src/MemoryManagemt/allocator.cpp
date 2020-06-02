#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include <math.h>
#include "allocator.h"
#include "algorithm"
using namespace std;

/* impl for FSB_allocator class */

/* PRIVATE SECTION */
// calculate the proper size for given mem_size
size_t FSB_allocator::calculate_mem_size(size_t mem_size) {
    size_t result = (mem_size > 4) ? pow(2,ceil(log(mem_size)/log(2))) : 8;
    return result;
};


// Round the required size to the nearest block size,
// return the index of that free-block list (a block pointer) in block_map
size_t FSB_allocator::memory_alignment (size_t required_mem_size) {
    // case1: if required memory size is less than the smallest size in block, take the smallest one
    if (required_mem_size < *min_element(BLOCK_SIZES.begin(), BLOCK_SIZES.end())) return 0;

    // case2: get a proper size in the vector
    size_t best_size, min_index;

    // calculate the proper size
    best_size = calculate_mem_size(required_mem_size);

    // find the index of the proper size in the vector
    vector<size_t>::iterator it = find(BLOCK_SIZES.begin(), BLOCK_SIZES.end(), best_size);
    if (it != BLOCK_SIZES.end()) {
        min_index = distance(BLOCK_SIZES.begin(), it);
    } else {
        min_index = -1;
    };

    return min_index;
};


// expand block_map if over-sized meomory size is required
void FSB_allocator::expand_mem(size_t mem_size) {
    cout<<"Start memory expansion"<<endl;

    // calculate the proper size should be added
    size_t adjusted_size = calculate_mem_size(mem_size);
    cout<<"new size: "<<adjusted_size<<endl;

    // update blocksize vector
    BLOCK_SIZES.push_back(adjusted_size);

    // update block_map and initialize new head
    block * head = new block;
    int count_idx = 0;
    for (size_t block_size : BLOCK_SIZES) {
        if (block_size == adjusted_size) {
            block_map[count_idx] = head;
        };
        count_idx++;
    };

    // let the pointers each points to a free list of 16 blocks
    block * current = head;
    for (int j = 0; j < 16; j++) {
        block * next = new block;
        next->data_ptr = nullptr; // initialize data
        current->link = next;
        current = next;
    };
    cout<<"Finish one memory expansion."<<endl;
    display();
    cout << "" << endl;
};


/* PUBLIC SECTION */
// Constructors
FSB_allocator::FSB_allocator() {
    // initialize 9 block head pointers in block_map
    for (unsigned int i = 0; i < BLOCK_SIZES.size(); i++) {

        block * head = new block;
        block_map.push_back(head);

        // let the pointers each points to a free list of 16 blocks
        block * current = head;
        for (int j = 0; j < 16; j++) {
            block * next = new block;
            next->data_ptr = nullptr; // initialize data
            next->link = nullptr; // point the last block to null
            current->link = next;
            current = next;
        };
    };
};


// Destructor
FSB_allocator::~FSB_allocator(){
    for (unsigned int i = 0; i < BLOCK_SIZES.size(); i++) {
        block * head = block_map[i];

        int block_count = 0;
        // delete the blocks of each head one by one
        while (head->link != nullptr) {
            block * temp = head; // old first block
            head = head->link; // re-link the head to the next one
            block_count++;
            temp = nullptr; // delete the old first head
        };

        // delete the head pointer
        block * mid = head;
        block_map[i] = nullptr;
        mid = nullptr;
    };
};


// Take in layout required size,
// Return ptr of first byte of the allocated memory
// Take out one block from the corresponding free-list
void * FSB_allocator::alloc(size_t mem_size) {
    cout << "Start memory allocation" << endl;

    // calculate the proper size
    size_t best_size = calculate_mem_size(mem_size);

    // find whether the proper size is in the size vector or not
    vector<size_t>::iterator it = find(BLOCK_SIZES.begin(), BLOCK_SIZES.end(), best_size);

    // if the proper size is not in the size vector yet,
    // update the vector with this specific size
    if (it == BLOCK_SIZES.end()) {
        expand_mem(mem_size);
    };

    // get the head pointer of the proper size in block_map
    size_t block_header_idx = memory_alignment(mem_size);
    block * temp = block_map[block_header_idx];

    // if the free-list of this specific size is empty,
    // add a new one to free list
    if (temp == NULL) {
        block * new_free_block = block_map[block_header_idx];
        new_free_block->link = temp->link;
        block_map[block_header_idx] = new_free_block;
    }
    // else get the first block in the free-list
    else {
        block_map[block_header_idx] = temp->link; // point to the next block
        temp->link = nullptr; // delete the link between previous head and the next block
    };

    // use this function to malloc a memory and assign to pointer
    temp->alloc_data_mem(BLOCK_SIZES[block_header_idx]);

    cout << "required memory size: " << mem_size << endl;
    cout << "given block size: " << BLOCK_SIZES[block_header_idx] << endl;
    display();
    cout << "Finish one memory allocation." << endl;
    cout << endl;

    return temp->data_ptr;
};



// adjust the size of allocated memory region and return a new pointer
void * FSB_allocator::realloc(void * ptr, size_t mem_size) {
    free(ptr);
    return alloc(mem_size);
};


// check the number of blocks in corresponding free-list
int FSB_allocator::loop_test(int header_idx) {
    int i = 0;
    block * start = block_map[header_idx];
    while (start->link != nullptr) {
        i++;
        start = start->link;
    };
    return i;
};


void FSB_allocator::display() {
    for (unsigned int idx = 0; idx < BLOCK_SIZES.size(); idx++) {
        int i = 0;
        block * start = block_map[idx];
        while (start->link != nullptr) {
            i++;
            start = start->link;
        };
//        cout<<i+1<<"-th one:"<<endl;
        cout << BLOCK_SIZES[idx] << "-bytes list has : " << i << " blocks" << endl;
    }
};


block* FSB_allocator::get_block_map(int idx) {
    return block_map[idx];
}


/* impl for LL_allocator class */

/* PUBLIC SECTION */
// Constructors
LL_allocator::LL_allocator() {

};

