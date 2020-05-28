/*
 * File: disk.h
 * --------------------
 * The header file of disk.cpp
 */
#ifndef DISK_H
#define DISK_H
#include "tools.h"

using namespace std;

class Disk{
    private:
		void loadDiskInfo(); // Load disk info from superblock to memory
		void writeDiskInfo(); // Write disk info from memory to superblock
		string magic_number = "a1b2c3d4e5f6g7h8"; // Just a randomize sequence of 16 bytes
		FILE *diskimg;  // pointer to the disk image
		string drive_letter;  // drive letter of the disk
		string disk_name; // Disk name
		int total_space; // total space of the disk
		int used_space; // used space of the disk
		int Blocks; // the number of blocks in the disk
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
		bool getBlock(int blocknum, string &data); // get data blocks
		bool putBlock(int blocknum, string &data); // put data blocks
		bool getINode(int nodenum, string &data); // get inodes
		bool putINode(int nodenum, string &data); // put inodes
		bool getBitmap(int nodenum, int position); // get bitmap value
		void changeBitmap(int nodenum, int position); // change bitmap value
		int searchBitmap(int type); // search bitmap to find the first 0
		vector<string> loadDirEntries(int nodenum); // load directory entry to vector
		void dumpDirEntries(int nodenum, vector<string> raw); // dump directory entry to disk
};

void loadDirEntry(int &INodenum, string &name, string raw);

string dumpDirEntry(int INodenum, string name);

#endif // DISK_H

