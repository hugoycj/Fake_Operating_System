#include "fs.h"

using namespace std;

INode::INode() {

};

void INode::loadINode(string data) {
	this->type_flag = stoi(strip(data.substr(0, 1)));
	this->read_only_flag = stoi(strip(data.substr(1, 1)));
	this->hidden_flag = stoi(strip(data.substr(2, 1)));
	this->system_flag = stoi(strip(data.substr(3, 1)));
	this->archive_flag = stoi(strip(data.substr(4, 1)));
	this->creation_time = stoi(strip(data.substr(5, 16)));
	this->last_access_time = stoi(strip(data.substr(21, 16)));
	this->size = stoi(strip(data.substr(37, 32)));
	this->last_INode = stoi(strip(data.substr(69, 4)));
	this->reference1 = stoi(strip(data.substr(73, 8)));
	this->reference2 = stoi(strip(data.substr(81, 8)));
	this->reference3 = stoi(strip(data.substr(89, 8)));
	this->reference4 = stoi(strip(data.substr(97, 8)));
	this->reference5 = stoi(strip(data.substr(105, 8)));
	this->reference6 = stoi(strip(data.substr(113, 8)));
	this->reference7 = stoi(strip(data.substr(121, 8)));
	this->reference8 = stoi(strip(data.substr(129, 8)));
	this->IDBlock1 = stoi(strip(data.substr(137, 8)));
	this->IDBlock2 = stoi(strip(data.substr(145, 8)));
	this->name = strip(data.substr(153, 24));
};

string INode::dumpINode() {
	string data;

	data = data + add_placeholder(this->type_flag, 1);
	data = data + add_placeholder(this->read_only_flag, 1);
	data = data + add_placeholder(this->hidden_flag, 1);
	data = data + add_placeholder(this->system_flag, 1);
	data = data + add_placeholder(this->archive_flag, 1);
	data = data + add_placeholder(this->creation_time, 16);
	data = data + add_placeholder(this->last_access_time, 16);
	data = data + add_placeholder(this->size, 32);
	data = data + add_placeholder(this->last_INode, 4);
	data = data + add_placeholder(this->reference1, 8);
	data = data + add_placeholder(this->reference2, 8);
	data = data + add_placeholder(this->reference3, 8);
	data = data + add_placeholder(this->reference4, 8);
	data = data + add_placeholder(this->reference5, 8);
	data = data + add_placeholder(this->reference6, 8);
	data = data + add_placeholder(this->reference7, 8);
	data = data + add_placeholder(this->reference8, 8);
	data = data + add_placeholder(this->IDBlock1, 8);
	data = data + add_placeholder(this->IDBlock2, 8);
	data = data + add_placeholder(this->name, 24);

	return data;
};

void INode::setter(int tf, int rof, int hf, int sf, int af, int ct, int lat, int size, int lIN, string name) {
	this->type_flag = tf;
	this->read_only_flag = rof;
	this->hidden_flag = hf;
	this->system_flag = sf;
	this->archive_flag = af;
	this->creation_time = ct;
	this->last_access_time = lat;
	this->size = size;
	this->last_INode = lIN;
	this->name = name;
};

int INode::get_reference(int referencenum) {
	if (referencenum == 1) {
		return this->reference1;
	}
	else if (referencenum == 2){
		return this->reference2;
	}
	else if (referencenum == 3) {
		return this->reference3;
	}
	else if (referencenum == 4) {
		return this->reference4;
	}
	else if (referencenum == 5) {
		return this->reference5;
	}
	else if (referencenum == 6) {
		return this->reference6;
	}
	else if (referencenum == 7) {
		return this->reference7;
	}
	else if (referencenum == 8) {
		return this->reference8;
	};
};

int INode::get_IDBlock(int IDBnum) {
	if (IDBnum == 1) {
		return this->IDBlock1;
	}
	else if (IDBnum == 2) {
		return this->IDBlock2;
	};
};

void INode::del() {
	if (this->type_flag == 0) {
		this->type_flag = 2;
	}
	else if (this->type_flag == 1) {
		this->type_flag = 3;
	}
	else {
		// raise error
	};
}

void INode::set_reference(int referencenum, int loc) {
	if (referencenum == 1) {
		this->reference1 = loc;
	}
	else if (referencenum == 2) {
		this->reference2 = loc;
	}
	else if (referencenum == 3) {
		this->reference3 = loc;
	}
	else if (referencenum == 4) {
		this->reference4 = loc;
	}
	else if (referencenum == 5) {
		this->reference5 = loc;
	}
	else if (referencenum == 6) {
		this->reference6 = loc;
	}
	else if (referencenum == 7) {
		this->reference7 = loc;
	}
	else if (referencenum == 8) {
		this->reference8 = loc;
	};
};

void INode::set_last_node(int loc) {
	this->last_INode = loc;
};

// constructor
FileSystem::FileSystem() {

};

// copyin
bool FileSystem::copyin() {

	return false;
};

// copyout
bool FileSystem::copyout() {

	return false;
};

// copybetween
bool FileSystem::copybetween() {

	return false;
};

// mount
bool FileSystem::mount(string path, string drive_letter) {
	// TODO: Multidisk
	// TODO: check drive letter is only one letter
    Disk disk;
	if (this->cur_disk.open(path, drive_letter)) {
		disks.push_back(disk);
		string data;
		INode INode;
		this->cur_disk.getINode(0, data);
		INode.loadINode(data);
		this->cur_INode = INode;
		this->cur_INode_num = 0;
		return true;
	}
	else {
		return false;
	};
};

// unmount
bool FileSystem::unmount(string drive_letter) {
    // TODO: Multidisk
    cur_disk.close();
	return true;

};

// change current disk
bool FileSystem::change_cur_disk() {

	return true;
};

// return current disk
// string FileSystem::cur_disk() {

// };

// dir
vector<string> FileSystem::dir() {
	vector<string> entries = this->cur_disk.loadDirEntries(this->cur_INode.get_reference(1));
	return entries;
};

// make directory
bool FileSystem::md(string name) {
	// get dir entries
	vector<string> entries = this->cur_disk.loadDirEntries(this->cur_INode.get_reference(1));

	// allocate a block and an inode
	int new_INode = this->cur_disk.searchBitmap(0);
	int new_Block = this->cur_disk.searchBitmap(1);

	// update directory entry
	entries.push_back(dumpDirEntry(new_INode, name));
	this->cur_disk.dumpDirEntries(this->cur_INode.get_reference(1), entries);

	// put INode to block
	INode newdir;
	newdir.setter(1, 0, 0, 0, 0, get_cur_time(), get_cur_time(), 0, this->cur_INode_num, name);
	newdir.set_last_node(this->cur_INode_num);
	newdir.set_reference(1, new_Block);
	string INodedata = newdir.dumpINode();
	this->cur_disk.putINode(new_INode, INodedata);

	// write directory entry to block
	string blockdata = add_placeholder(this->cur_INode_num, 8) + add_placeholder("..", 24) + add_placeholder(new_INode, 8) + add_placeholder(".", 24);
	this->cur_disk.putBlock(new_Block, blockdata);

	// change bitmap
	this->cur_disk.changeBitmap(1, new_INode);
	this->cur_disk.changeBitmap((new_Block-524) / 4096 + 2, (new_Block-524) % 4096); 

	return true;
};

// remove directory
bool FileSystem::rd(string name) {
	// TODO: Verification whether such a directory exist
	// TODO: delete every folder repeatedly

	// get dir entries
	vector<string> entries = this->cur_disk.loadDirEntries(this->cur_INode.get_reference(1));

	// search for the entry to be removed
	int INode_num;
	size_t index;

	for (size_t i = 0; i != entries.size(); i++) {
		int INodenum;
		string dirname;
		loadDirEntry(INodenum, dirname, entries[i]);
		if (dirname == name) {
			INode_num = INodenum;
			index = i;
		};
	};
	
	// put the entries back
	entries.erase(entries.begin() + index);
	this->cur_disk.dumpDirEntries(this->cur_INode.get_reference(1), entries);

	// load rmdir's INode
	INode rmdir;
	string data;
	cout << INode_num << endl;
	this->cur_disk.getINode(INode_num, data);
	rmdir.loadINode(data);
	rmdir.del();

	string deldata = rmdir.dumpINode();
	this->cur_disk.putINode(INode_num, deldata);

	// set two bitmaps
	this->cur_disk.changeBitmap(1, INode_num);
	int blocknum = rmdir.get_reference(1);
	this->cur_disk.changeBitmap((blocknum - 524) / 4096 + 2, (blocknum - 524) % 4096);

	return true;
};

// change directory
bool FileSystem::cd(string name) {
	// TODO: Verification

	// get dir entries
	vector<string> entries = this->cur_disk.loadDirEntries(this->cur_INode.get_reference(1));

	// search for the entry to be changed
	int INode_num;
	size_t index;

	for (size_t i = 0; i != entries.size(); i++) {
		int INodenum;
		string dirname;
		loadDirEntry(INodenum, dirname, entries[i]);
		if (dirname == name) {
			INode_num = INodenum;
			index = i;
		};
	};

	// load INode
	INode chdir;
	string data;
	this->cur_disk.getINode(INode_num, data);
	chdir.loadINode(data);

	this->cur_INode = chdir;
	this->cur_INode_num = INode_num;

	return true;
}

// copy
bool FileSystem::copy(string path1, string path2) {
	// TODO: complete
	return true;
};

// move
bool FileSystem::move(string path1, string path2) {
	// TODO: complete
	return true;
};

bool FileSystem::open(string name) {
	// TODO: complete
	

	return true;
};

bool FileSystem::create(string name) {
	// TODO: modify to adapt create
	// get dir entries
	vector<string> entries = this->cur_disk.loadDirEntries(this->cur_INode.get_reference(1));

	// allocate a block and an inode
	int new_INode = this->cur_disk.searchBitmap(0);
	int new_Block = this->cur_disk.searchBitmap(1);

	// update directory entry
	entries.push_back(dumpDirEntry(new_INode, name));
	this->cur_disk.dumpDirEntries(this->cur_INode.get_reference(1), entries);

	// put INode to block
	INode newdir;
	newdir.setter(1, 0, 0, 0, 0, get_cur_time(), get_cur_time(), 0, this->cur_INode_num, name);
	newdir.set_last_node(this->cur_INode_num);
	newdir.set_reference(1, new_Block);
	string INodedata = newdir.dumpINode();
	this->cur_disk.putINode(new_INode, INodedata);

	// write directory entry to block
	string blockdata = add_placeholder(this->cur_INode_num, 8) + add_placeholder("..", 24) + add_placeholder(new_INode, 8) + add_placeholder(".", 24);
	this->cur_disk.putBlock(new_Block, blockdata);

	// change bitmap
	this->cur_disk.changeBitmap(1, new_INode);
	this->cur_disk.changeBitmap((new_Block - 524) / 4096 + 2, (new_Block - 524) % 4096);

	return true;
};


