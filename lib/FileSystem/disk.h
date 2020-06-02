/*
 * File: disk.h
 * --------------------
 * The header file of disk.cpp
 */
#ifndef DISK_H
#define DISK_H
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<ctime>
#include "logger.h"

using namespace std;

class Disk{
    private:
		void loadDiskInfo(); // Load disk info from superblock to memory
		void writeDiskInfo(); // Write disk info from memory to superblock
		string magic_number = "a1b2c3d4e5f6g7h8"; // Just a randomize sequence of 16 bytes
        fstream diskimg;  // fstream instance of the disk image
		string drive_letter;  // drive letter of the disk
		string disk_name; // Disk name
		int total_space; // total space of the disk
		int used_space; // used space of the disk
        int Blocks = 41484; // the number of blocks in the disk
		int inode_bitmap_location; // INode Bitmap Location
		int block_bitmap_location; // Block Bitmap Location
		int inode_location; // Inode Location
		const int BlockSize = 4096; // the number of bytes in each block
		const int iNodeSize = 512; // the number of tytes taken by each i-node
		// Maximum file size



    public:
		Disk(); // constructor
		~Disk(); // destructor
		bool open(string filepath, string drive_letter); // open disk image
		bool close(); // close file
        bool clear(); // clear the diskimg for next open
		bool getBlock(int blocknum, string &data); // get data blocks
		bool putBlock(int blocknum, string &data); // put data blocks
		bool getINode(int nodenum, string &data); // get inodes
		bool putINode(int nodenum, string &data); // put inodes
		bool getBitmap(int nodenum, int position); // get bitmap value
		void changeBitmap(int nodenum, int position); // change bitmap value
		int searchBitmap(int type); // search bitmap to find the first 0
		vector<string> loadDirEntries(int nodenum); // load directory entry to vector
		void dumpDirEntries(int nodenum, vector<string> raw); // dump directory entry to disk
        bool format(); // format the disk
};

void loadDirEntry(int &INodenum, string &name, string raw);

string dumpDirEntry(int INodenum, string name);



// tool functions
string strip(string str);

int getindex(string element, string array[], int length);

bool file_exist(string filename);

vector<string> process_path(string raw);

string slash_trans(string raw);

string add_placeholder(string raw, int length);

string add_placeholder(int raw, int length);

string chartostring(char* raw, int size);

bool all_placeholder(string raw);

int get_cur_time();

// process functions
vector<string> extract_part(string line, string seperator);
vector<int> locate_parameter(vector<string> parameters);



#endif // DISK_H

