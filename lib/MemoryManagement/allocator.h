#ifndef ALLOCATOR_H
#define ALLOCATOR_H
#include <iostream>
#include <vector>

/*
 * Like the linked list allocator, we keep track of the unused memory by
 * creating a linked list in the unused memory.
 * However, instead of using a single list with different block sizes,
 * we create a separate list for each size class.
 * Each list then only stores blocks of a single size.
 * In our project, there are totally 9 different sizes
 *
 * Each fixed size have one separate singly linked block
 * So we need a block_map to record all the linked block
 * head_8 means it the head of the linked block which contains 8 bytes memory blocks
 *  block_map         -------||
 * |---------|        |   +-------+        +-------+        +-------+
 * |head_8   |--------    |   o---+------->|   A1  |------->|   A2  |
 * |---------|            +-------+        +-------+        +-------+
 * |head_16  |----------------
 * |---------|               ||
 * |head_32  |            +-------+        +-------+        +-------+
 * |---------|            |   o---+------->|   B1  |------->|   B2  |
 *                        +-------+        +-------+        +-------+
 *
 * Top down structure: block_map -> block_list (singly linked list of blocks) -> single block
 *
 * TODO: consider using hash mapping to make this process faster
 *
 */

// each element of one linked list (block)

struct block {
   // point to the data
   void * data_ptr;
   // a block ptr points to the next block
   block *link;

   // malloc a block of memory and assign to data_ptr
    void alloc_data_mem(size_t size) {
        data_ptr = std::malloc(size);
    };
};




/* fixed-sized block memory allocator*/

// Class definition for fixed size block allocator class.
// Simulate allocation process with alloc call, free memory with decalloc call
class FSB_allocator {
public:

   // constructor
    FSB_allocator();

   // destructor
    ~FSB_allocator();

   // Take in layout required size,
   // Return ptr of first byte of the allocated memory
   // Take out one block from the corresponding free-list
   void * alloc(size_t mem_size);

   // Take in pointer given by malloc and delete it
   // Add one block back to the corresponding free-list
    template <typename ValueType>
    void dealloc(ValueType * ptr, size_t size) {
        std::cout << "Start dealloc" << std::endl;

        // get the proper size that should be deallocated
        size_t dealloc_size = size;
        size_t block_header_idx = memory_alignment(dealloc_size);

        // Add one block back to the corresponding free-list
        block * new_free_block = new block;
        new_free_block->data_ptr = nullptr;
        block * temp = block_map[block_header_idx];

        // insert the new block at the beginning
        new_free_block->link = temp->link;
        (block_map[block_header_idx])->link = new_free_block;

        // set the deallocated pointer as nullptr
        free(ptr);
        ptr = nullptr;
        display();
        std::cout << "" << std::endl;
    };

   // adjust the size of allocated memory region and return a new pointer
   void * realloc(void * ptr, size_t size);

   // check the number of blocks in corresponding free-list
    int loop_test(int header_idx);

    block* get_block_map(int idx);

    private:
    std::vector<size_t> BLOCK_SIZES = {8, 16, 32, 64, 128};
    std::vector<block*> block_map; // vector of different block pointer, each points to a free-list

    // Round the required size to the nearest block size,
    // return the index of that free-block list (a block pointer) in block_map
    size_t memory_alignment (size_t required_mem_size);

    // expand block_map if over-sized meomory size is required
    void expand_mem(size_t mem_size);

    // calculate the proper size for given mem_size
    size_t calculate_mem_size(size_t mem_size);

    // display block num info
    void display();

};



/* linked-list based memory allocator */

// node structure in singly linked list
struct Node {
    bool usage_flag;
    size_t size;
    Node * next;
};

// Class definition for linked list allocator class.
class LL_allocator {
public:
    // constructor
    LL_allocator();

    // destructor
    ~LL_allocator();

    // Take in required size
    // Return ptr of first byte of the allocated memory,
    void * alloc(size_t size);

    // Take in ptr returned by alloc
    void dealloc(void * ptr);

    // test LL_allocator
    void test();

private:

    // start of the linked list
    Node * start;

    // to do memory alignment
    size_t memory_alignment (size_t required_mem_size);

    // find the first free block in the linked list
    void * first_fit();

    // find the most suitable block in the linked list
    void * best_fit();

    // split large blocks into small blocks
    void split_block();

    // merge small blocks into lager block
    void merge_block();

};

#endif
