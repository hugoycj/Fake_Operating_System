/*
 * File: disk.h
 * --------------------
 * The header file of disk.cpp
 */
#ifndef FS_H
#define FS_H
#include "disk.h"

class INode {
private:
	string name;
	int type_flag;
	int read_only_flag;
	int hidden_flag;
	int system_flag;
	int archive_flag;
	int creation_time;
	int last_access_time;
	int size = 0;
	int last_INode;
	int reference1 = -1;
	int reference2 = -1;
	int reference3 = -1;
	int reference4 = -1;
	int reference5 = -1;
	int reference6 = -1;
	int reference7 = -1;
	int reference8 = -1;
	int IDBlock1 = -1; // Indirect Block
	int IDBlock2 = -1;
public:
	INode(); // constructor
	void loadINode(string data); // load INode from data string
	string dumpINode(); // dump INode from attributes
	void setter(int tf, int rof, int hf, int sf, int af, int ct, int lat, int size, int lIN, string name); // an INode information setter
	int get_reference(int referencenum); // getter of reference
	int get_IDBlock(int IDBnum); // getter of indirect block
	void del(); // set the Inode to delete
	void set_reference(int referencenum, int loc);
	void set_last_node(int loc);

	// TODO: other getters
};

class FileSystem {
private:
	vector<Disk> disks;
	Disk cur_disk;
	const size_t BlockSize = 4096; // for test
	const size_t INodeSize = 512; // for test
	INode cur_INode; // current INode
	int cur_INode_num;
	string cur_path;



public:
	FileSystem(); // constructor
	string ver = "0.0.1"; // version
	bool copyin(); // copy from the real FS to the virtual FS
	bool copyout(); // copy from the virtual FS to the real FS
	bool copybetween(); // copy between disks in the same file system
	bool mount(string path, string drive_letter); // mount a disk to the file system
	bool unmount(string drive_letter); // unmount a disk from the file system
	bool change_cur_disk(); // change the current disk
	// std::string cur_disk(); // return the current disk drive letter

	vector<string> dir();
	bool md(string name); // make directory
	bool rd(string name); // remove directory
	bool cd(string name); // change directory
	bool move(string path1, string path2);
	bool copy(string path1, string path2);
	bool open(string name); // open file
	bool create(string name); // create file


	string get_path(); // return the current path
};


#endif // FS_H

