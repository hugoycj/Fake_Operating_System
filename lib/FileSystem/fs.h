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
	string name; // name of the INode
	void loadINode(string data); // load INode from data string
	string dumpINode(); // dump INode from attributes
	void setter(int tf, int rof, int hf, int sf, int af, int ct, int lat, int size, int lIN, string name); // an INode information setter
    void setter2(int tf, int rof, int hf, int sf, int af, int lat); // an setattr setter
	int get_reference(int referencenum); // getter of reference
	int get_IDBlock(int IDBnum); // getter of indirect block
	int get_type_flag(); // getter of type flag
	int get_read_only_flag(); // getter of read only flag
	int get_hidden_flag(); // getter of hidden flag
	int get_system_flag(); // getter of system flag
	int get_archive_flag(); // getter of archive flag
	int get_creation_time(); // getter of creation time
	int get_last_access_time(); // getter of last access time
	int get_size(); // getter of size
	void del(); // set the Inode to delete
	void set_reference(int referencenum, int loc);
	void set_last_node(int loc);
    void set_IDBlock(int IDBnum, int loc);
    void set_filesize(int size);

    // TODO: other getters and setters
};

class FileSystem {
private:
    vector<vector<string>> disks;
	Disk cur_disk;
	const size_t BlockSize = 4096; // for test
	const size_t INodeSize = 512; // for test
	INode cur_INode; // current INode
	int cur_INode_num;
	string cur_path;
    string cur_drive_letter;

public:
    logger l;
	FileSystem(); // constructor
	string ver = "0.0.1"; // version
    bool copyin(string external, string name); // copy from the real FS to the virtual FS
    bool copyout(string name, string external); // copy from the virtual FS to the real FS
	bool mount(string path, string drive_letter); // mount a disk to the file system
    bool unmount(string drive_letter); // unmount a disk from the file system
    vector<string> dir(); // dir for CLI
    vector<vector<string>> directory(); // directory for GUI
	bool md(string name); // make directory
	bool rd(string name); // remove directory
	bool cd(string name); // change directory
    bool move(string path1, string path2); // move file
    bool copy(string path1, string path2); // copy file
    string open(string name); // open file
	bool create(string name); // create file
    bool _delete(string name); // delete file
	vector<string> getattr(string name); // get attributes
    bool setattr(string name, vector<string> attrs); // set attributes
	bool format(string drive_letter); // format the disk
    bool rename(string name, string newname); // rename of entries
    bool chdisk(string drive_letter); // change the current operating disk
    bool receive(string name, string text); // receive the opened text from texteditor
    bool chkdsk(); //check disk
    vector<string> disklist(); // return the disk list

	// CLI functions
	void execute(string line);
	// shell functions
	void do_delete(vector<string> parameters, vector<int> locations);
	void do_help(vector<string> parameters, vector<int> locations);
	void do_copyin(vector<string> parameters, vector<int> locations);
    void do_copyout(vector<string> parameters, vector<int> locations);
	void do_mount(vector<string> parameters, vector<int> locations);
	void do_unmount(vector<string> parameters, vector<int> locations);
	void do_dir(vector<string> parameters, vector<int> locations);
	void do_md(vector<string> parameters, vector<int> locations);
	void do_rd(vector<string> parameters, vector<int> locations);
	void do_cd(vector<string> parameters, vector<int> locations);
	void do_copy(vector<string> parameters, vector<int> locations);
	void do_move(vector<string> parameters, vector<int> locations);
	void do_rename(vector<string> parameters, vector<int> locations);
	void do_version(vector<string> parameters, vector<int> locations);
	void do_chkdsk(vector<string> parameters, vector<int> locations);
	void do_format(vector<string> parameters, vector<int> locations);
	void do_getattr(vector<string> parameters, vector<int> locations);
	void do_setattr(vector<string> parameters, vector<int> locations);
	void do_open(vector<string> parameters, vector<int> locations);
	void do_create(vector<string> parameters, vector<int> locations);
    void do_chdisk(vector<string> parameters, vector<int> locations);

	// process functions
	void process_instruction(string line);
	void process_line(string line);
	void execute_instruction(vector<string> parameters, vector<int> locations);

};


#endif // FS_H

