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

void INode::setter2(int tf, int rof, int hf, int sf, int af, int lat) {
    this->type_flag = tf;
    this->read_only_flag = rof;
    this->hidden_flag = hf;
    this->system_flag = sf;
    this->archive_flag = af;
    this->last_access_time = lat;
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

int INode::get_type_flag() {
	return this->type_flag;
};

int INode::get_read_only_flag() {
	return this->read_only_flag;
};

int INode::get_hidden_flag() {
	return this->hidden_flag;
};

int INode::get_system_flag() {
	return this->system_flag;
};

int INode::get_archive_flag() {
	return this->archive_flag;
};

int INode::get_creation_time() {
	return this->creation_time;
};

int INode::get_last_access_time() {
	return this->last_access_time;
};

int INode::get_size() {
	return this->size;
};

void INode::set_IDBlock(int IDBnum, int loc) {
    if (IDBnum == 1) {
        this->IDBlock1 = loc;
    } else if (IDBnum == 2) {
        this->IDBlock2 = loc;
    } else {
        // raise error
    };
};

void INode::set_filesize(int size) {
    this->size = size;
};

// constructor
FileSystem::FileSystem() {

};

void FileSystem::execute(string line) {
	if (!line.empty())
	{
        // Maybe put this part in GUI control?
        if (line == "exit" || line == "quit") {
            this->l.out("The File System is shutdowned");
            // call the destructor
        } else {
            this->process_line(line);
        };
	};
};

// copyin
bool FileSystem::copyin(string external, string name) {
    string out = " > copyin " + name + " " + external;
    this->l.out(out);
    fstream file(external, ios::in);
    this->create(name);
    file.seekg(ios::end);
    int length = file.tellg();
    file.seekg(ios::beg);
    char* cdata = new char[length];
    file.read(cdata, length);
    string data = chartostring(cdata, length);
    this->receive(name, data);
	return false;
};

// copyout
bool FileSystem::copyout(string name, string external) {
    string out = " > copyout " + name + " " + external;
    this->l.out(out);
    fstream file(external, ios::out | ios::trunc);
    string data = this->open(name);
    file.write(data.c_str(), data.length());
	return false;
};

// mount
bool FileSystem::mount(string path, string drive_letter) {
    string out = " > mount " + path + " " + drive_letter;
    this->l.out(out);
    if (this->disks.empty()) {
        if (this->cur_disk.open(path, drive_letter)) {
            string data;
            INode inode;
            this->cur_disk.getINode(0, data);
            inode.loadINode(data);
            this->cur_INode = inode;
            this->cur_INode_num = 0;
            vector<string> disk_vec;
            disk_vec.push_back(drive_letter);
            disk_vec.push_back(path);
            this->disks.push_back(disk_vec);
            this->cur_drive_letter = drive_letter;
            return true;
        }
        else {
            return false;
        };
    } else {
        this->cur_disk.clear();
        if (this->cur_disk.open(path, drive_letter)) {
            string data;
            INode inode;
            this->cur_disk.getINode(0, data);
            inode.loadINode(data);
            this->cur_INode = inode;
            this->cur_INode_num = 0;
            vector<string> disk_vec;
            disk_vec.push_back(drive_letter);
            disk_vec.push_back(path);
            this->disks.push_back(disk_vec);
            this->cur_drive_letter = drive_letter;
            return true;
        }
        else {
            return false;
        };
    };
};

// unmount
bool FileSystem::unmount(string drive_letter) {
    string out = " > unmount " + drive_letter;
    this->l.out(out);
    if (drive_letter != this->cur_drive_letter) {
        for (size_t i = 0; i < this->disks.size(); i++) {
            if (this->disks[i][0] == drive_letter) {
                this->disks.erase(this->disks.begin()+i);
                break;
            };
        }
    } else {
        for (size_t i = 0; i < this->disks.size(); i++) {
            if (this->disks[i][0] == drive_letter) {
                this->disks.erase(this->disks.begin()+i);
                break;
            };
        };
        if (!this->disks.empty()){
            string path = this->disks[0][1];
            string driveletter = this->disks[0][0];
            this->cur_disk.clear();
            if (this->cur_disk.open(path, driveletter)) {
                string data;
                INode inode;
                this->cur_disk.getINode(0, data);
                inode.loadINode(data);
                this->cur_INode = inode;
                this->cur_INode_num = 0;
                vector<string> disk_vec;
                disk_vec.push_back(driveletter);
                disk_vec.push_back(path);
                this->disks.push_back(disk_vec);
                this->cur_drive_letter = driveletter;
            };
        };
    };
	return true;
};


// dir
vector<string> FileSystem::dir() {
    this->l.out(" > dir");
	vector<string> entries = this->cur_disk.loadDirEntries(this->cur_INode.get_reference(1));
	return entries;
};

vector<vector<string>> FileSystem::directory() {
    this->l.out(" > dir");
    vector<string> entries = this->cur_disk.loadDirEntries(this->cur_INode.get_reference(1));
	vector<vector<string>> directories;
	for (size_t i = 0; i != entries.size(); i++) {
		vector<string> directory;
		int INodenum;
		string name;
        loadDirEntry(INodenum, name, entries[i]);
		INode entry;
		string data;
		this->cur_disk.getINode(INodenum, data);
		entry.loadINode(data);
        int tf = entry.get_type_flag();
		if (tf == 0) { // file
			directory.push_back("FILE");
            directory.push_back(name);
            directories.push_back(directory);
		}
		else if (tf == 1){ // directory
			directory.push_back("DIR");
            directory.push_back(name);
			directories.push_back(directory);
		}
		else { // deleted files and directories
			// raise error
		};
	};
    return directories;
}

// make directory
bool FileSystem::md(string name) {
    string out = " > md " + name;
    this->l.out(out);
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
    string out = " > rd " + name;
    this->l.out(out);
    // TODO: Verification whether such a directory exist

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
    string out = " > cd " + name;
    this->l.out(out);
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
    string out = " > copy " + path1 + " " + path2;
    this->l.out(out);
    this->l.out("copy is not supported in this version");
	return true;
};

// move
bool FileSystem::move(string path1, string path2) {
    string out = " > move " + path1 + " " + path2;
    this->l.out(out);
    this->l.out("move is not supported in this version");
	return true;
};

string FileSystem::open(string name) {
    string out = " > open " + name;
    this->l.out(out);
    cout << "open " << name << endl;
    string text;

    // get dir entries
    vector<string> entries = this->cur_disk.loadDirEntries(this->cur_INode.get_reference(1));

    // search for the file to be opened
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
    INode file;
    string data;
    this->cur_disk.getINode(INode_num, data);
    file.loadINode(data);

    // concat blocks
    for (int i=0; i < 8; i++) {
        // get referenced block
        string blockdata;
        int blocknum = file.get_reference(i+1);
        if (blocknum != -1) {
            this->cur_disk.getBlock(blocknum, blockdata);
            text = text + blockdata;
        } else {
            break;
        };
        if (i == 7) {
            for (int j=1; j<=2; j++) {
                // get Indirect Block
                int IDBnum = file.get_IDBlock(j);
                if (IDBnum != -1) {
                    string IDBdata;
                    this->cur_disk.getBlock(IDBnum, IDBdata);
                    for (int k=0; k<512;k++) {
                        string substr = IDBdata.substr(k*8, 8);
                        if (!all_placeholder(substr)) {
                            blocknum = stoi(strip(substr));
                            string IDdata;
                            this->cur_disk.getBlock(blocknum, IDdata);
                            text = text + IDdata;
                        } else {
                            break;
                        };
                    };
                } else {
                    break;
                };
            };
        };
    };
    return text;
};

bool FileSystem::create(string name) {
    string out = " > create " + name;
    this->l.out(out);
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
    newdir.setter(0, 0, 0, 0, 0, get_cur_time(), get_cur_time(), 0, this->cur_INode_num, name);
	newdir.set_last_node(this->cur_INode_num);
	newdir.set_reference(1, new_Block);
	string INodedata = newdir.dumpINode();
	this->cur_disk.putINode(new_INode, INodedata);

	// change bitmap
	this->cur_disk.changeBitmap(1, new_INode);
	this->cur_disk.changeBitmap((new_Block - 524) / 4096 + 2, (new_Block - 524) % 4096);

	return true;
};

vector<string> FileSystem::getattr(string name) {
    string out = " > getattr " + name;
    this->l.out(out);
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
	INode entry;
	string data;
	this->cur_disk.getINode(INode_num, data);
	entry.loadINode(data);

	// construct vector
	vector<string> attrs;
	attrs.push_back(entry.name);
	attrs.push_back(to_string(entry.get_type_flag()));
	attrs.push_back(to_string(entry.get_read_only_flag()));
	attrs.push_back(to_string(entry.get_hidden_flag()));
	attrs.push_back(to_string(entry.get_system_flag()));
	attrs.push_back(to_string(entry.get_archive_flag()));
	attrs.push_back(to_string(entry.get_creation_time()));
	attrs.push_back(to_string(entry.get_last_access_time()));
	attrs.push_back(to_string(entry.get_size()));
	
	return attrs;
};

bool FileSystem::setattr(string name, vector<string> attrs) {
    string out = " > setattr " + name;
    this->l.out(out);
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
    INode entry;
    string data;
    this->cur_disk.getINode(INode_num, data);
    entry.loadINode(data);

    entry.setter2(stoi(attrs[1]), stoi(attrs[2]), stoi(attrs[3]), stoi(attrs[4]), stoi(attrs[5]), stoi(attrs[6]));
    string INodedata = entry.dumpINode();
    this->cur_disk.putINode(INode_num, INodedata);

    this->rename(attrs[7], attrs[0]);

	return true;
};

bool FileSystem::format(string drive_letter) {
    string out = " > format " + drive_letter;
    this->l.out(out);
    this->chdisk(drive_letter);
    this->cur_disk.format();
    return true;
};

bool FileSystem::chdisk(string drive_letter) {
    string out = " > chdisk " + drive_letter;
    this->l.out(out);
    int index;
    for (size_t i = 0; i < this->disks.size(); i++) {
        if (this->disks[i][0] == drive_letter) {
            index = i;
            break;
        };
    };
    if (!this->disks.empty()){
        string path = this->disks[index][1];
        string driveletter = this->disks[index][0];
        this->cur_disk.clear();
        if (this->cur_disk.open(path, driveletter)) {
            string data;
            INode inode;
            this->cur_disk.getINode(0, data);
            inode.loadINode(data);
            this->cur_INode = inode;
            this->cur_INode_num = 0;
            this->cur_drive_letter = driveletter;
        };
    };
    return true;
};

bool FileSystem::rename(string name, string newname) {
    string out = " > rename " + name + " " + newname;
    this->l.out(out);
    // get dir entries
    vector<string> entries = this->cur_disk.loadDirEntries(this->cur_INode.get_reference(1));

    // search for the entry to be renamed
    int INode_num;
    size_t index;

    for (size_t i = 0; i != entries.size(); i++) {
        int INodenum;
        string entryname;
        loadDirEntry(INodenum, entryname, entries[i]);
        if (entryname == name) {
            INode_num = INodenum;
            index = i;
        };
    };

    // load INode
    INode rn;
    string data;
    this->cur_disk.getINode(INode_num, data);
    rn.loadINode(data);

    string new_name = dumpDirEntry(INode_num, newname);
    rn.name = newname;
    entries[index] = new_name;
    this->cur_disk.dumpDirEntries(this->cur_INode.get_reference(1), entries);

    return true;
};

bool FileSystem::receive(string name, string text) {
    // get dir entries
    vector<string> entries = this->cur_disk.loadDirEntries(this->cur_INode.get_reference(1));

    // search for the entry to be removed
    int INode_num;
    size_t index;

    for (size_t i = 0; i != entries.size(); i++) {
        int INodenum;
        string filename;
        loadDirEntry(INodenum, filename, entries[i]);
        if (filename == name) {
            INode_num = INodenum;
            index = i;
        };
    };

    // load file's INode
    INode file;
    string data;
    this->cur_disk.getINode(INode_num, data);
    file.loadINode(data);

    // set bitmaps(delete)
    this->cur_disk.changeBitmap(1, INode_num);
    for (int i=0; i < 8; i++) {
        // delete referenced block
        int blocknum = file.get_reference(i+1);
        if (blocknum != -1) {
            this->cur_disk.changeBitmap((blocknum - 524) / 4096 + 2, (blocknum - 524) % 4096);
        } else {
            break;
        };
        if (i == 7) {
            for (int j=1; j<=2; j++) {
                // delete Indirect Block
                int IDBnum = file.get_IDBlock(j);
                if (IDBnum != -1) {
                    string IDBdata;
                    this->cur_disk.getBlock(IDBnum, IDBdata);
                    this->cur_disk.changeBitmap((IDBnum - 524) / 4096 + 2, (IDBnum - 524) % 4096);
                    for (int k=0; k<512;k++) {
                        string substr = IDBdata.substr(k*8, 8);
                        if (!all_placeholder(substr)) {
                            blocknum = stoi(strip(substr));
                            this->cur_disk.changeBitmap((blocknum - 524) / 4096 + 2, (blocknum - 524) % 4096);
                        } else {
                            break;
                        };
                    };
                } else {
                    break;
                };
            };
        };
    };

    size_t cursor = 0;

    // receive blocks(create)
    for (int i=1; i<=8; i++) {
        if (cursor+4096 <= text.length()) {
            string blockdata = text.substr(cursor, 4096);
            int blocknum = this->cur_disk.searchBitmap(1);
            this->cur_disk.putBlock(blocknum, blockdata);
            file.set_reference(i, blocknum);
        } else if (cursor + 4096 > text.length() && text.length()> cursor){
            string blockdata = add_placeholder(text.substr(cursor, text.length()-cursor), 4096);
            int blocknum = this->cur_disk.searchBitmap(1);
            this->cur_disk.putBlock(blocknum, blockdata);
            file.set_reference(i, blocknum);
        } else {
            file.set_reference(i, -1);
        };
        cursor = cursor + 4096;
    };
    file.set_IDBlock(1, -1);
    file.set_IDBlock(2, -1);
    // Indirect Block 1
    if (cursor > text.length()) {
        string IDBdata;
        int IDB = this->cur_disk.searchBitmap(1);
        file.set_IDBlock(1, IDB);
        for(int i=0; i<512; i++) {
            if (cursor+4096 <= text.length()) {
                string blockdata = text.substr(cursor, 4096);
                int blocknum = this->cur_disk.searchBitmap(1);
                this->cur_disk.putBlock(blocknum, blockdata);
                IDBdata = IDBdata + add_placeholder(blocknum, 8);
            } else if (cursor + 4096 > text.length() && text.length()> cursor){
                string blockdata = add_placeholder(text.substr(cursor, text.length()-cursor), 4096);
                int blocknum = this->cur_disk.searchBitmap(1);
                this->cur_disk.putBlock(blocknum, blockdata);
                IDBdata = IDBdata + add_placeholder(blocknum, 8);
            } else {
                break;
            };
        };
        IDBdata = add_placeholder(IDBdata, 4096);
        this->cur_disk.putBlock(IDB, IDBdata);
    };
    // Indirect Block 2
    if (cursor > text.length()) {
        string IDBdata;
        int IDB = this->cur_disk.searchBitmap(1);
        file.set_IDBlock(2, IDB);
        for(int i=0; i<512; i++) {
            if (cursor+4096 <= text.length()) {
                string blockdata = text.substr(cursor, 4096);
                int blocknum = this->cur_disk.searchBitmap(1);
                this->cur_disk.putBlock(blocknum, blockdata);
                IDBdata = IDBdata + add_placeholder(blocknum, 8);
            } else if (cursor + 4096 > text.length() && text.length()> cursor){
                string blockdata = add_placeholder(text.substr(cursor, text.length()-cursor), 4096);
                int blocknum = this->cur_disk.searchBitmap(1);
                this->cur_disk.putBlock(blocknum, blockdata);
                IDBdata = IDBdata + add_placeholder(blocknum, 8);
            } else {
                break;
            };
        };
        IDBdata = add_placeholder(IDBdata, 4096);
        this->cur_disk.putBlock(IDB, IDBdata);
    };
    // INode
    string INodedata = file.dumpINode();
    this->cur_disk.putINode(INode_num, INodedata);

    return true;
};

bool FileSystem::_delete(string name) {
    string out = " > delete " + name;
    this->l.out(out);
    // get dir entries
    vector<string> entries = this->cur_disk.loadDirEntries(this->cur_INode.get_reference(1));

    // search for the entry to be removed
    int INode_num;
    size_t index;

    for (size_t i = 0; i != entries.size(); i++) {
        int INodenum;
        string filename;
        loadDirEntry(INodenum, filename, entries[i]);
        if (filename == name) {
            INode_num = INodenum;
            index = i;
        };
    };

    // put the entries back
    entries.erase(entries.begin() + index);
    this->cur_disk.dumpDirEntries(this->cur_INode.get_reference(1), entries);

    // load file's INode
    INode file;
    string data;
    this->cur_disk.getINode(INode_num, data);
    file.loadINode(data);
    file.del();

    string deldata = file.dumpINode();
    this->cur_disk.putINode(INode_num, deldata);

    // set bitmaps
    this->cur_disk.changeBitmap(1, INode_num);
    for (int i=0; i < 8; i++) {
        // delete referenced block
        int blocknum = file.get_reference(i+1);
        if (blocknum != -1) {
            this->cur_disk.changeBitmap((blocknum - 524) / 4096 + 2, (blocknum - 524) % 4096);
        } else {
            break;
        };
        if (i == 7) {
            for (int j=1; j<=2; j++) {
                // delete Indirect Block
                int IDBnum = file.get_IDBlock(j);
                if (IDBnum != -1) {
                    string IDBdata;
                    this->cur_disk.getBlock(IDBnum, IDBdata);
                    this->cur_disk.changeBitmap((IDBnum - 524) / 4096 + 2, (IDBnum - 524) % 4096);
                    for (int k=0; k<512;k++) {
                        string substr = IDBdata.substr(k*8, 8);
                        if (!all_placeholder(substr)) {
                            blocknum = stoi(strip(substr));
                            this->cur_disk.changeBitmap((blocknum - 524) / 4096 + 2, (blocknum - 524) % 4096);
                        } else {
                            break;
                        };
                    };
                } else {
                    break;
                };
            };
        };
    };
    return true;
};

bool FileSystem::chkdsk() {
    string out = " > chkdsk ";
    this->l.out(out);
    this->l.out("chkdsk is not supported in this version");
    return true;
};

vector<string> FileSystem::disklist() {
    vector<string> dl;
    for (size_t i=0; i<this->disks.size(); i++) {
        dl.push_back(this->disks[i][0]);
    };
    return dl;
};

// CLI functions

// delete
void FileSystem::do_delete(vector<string> parameters, vector<int> locations) {
    this->_delete(parameters[1]);
};

// help
void FileSystem::do_help(vector<string> parameters, vector<int> locations) {
	if (parameters.size() == 1) {
        this->l.out("Usage: help [instruction you want to know]");
	};
};

// copyin
void FileSystem::do_copyin(vector<string> parameters, vector<int> locations) {
    this->copyin(parameters[1], parameters[2]);
};

// copyout
void FileSystem::do_copyout(vector<string> parameters, vector<int> locations) {
    this->copyout(parameters[1], parameters[2]);
};

// mount
void FileSystem::do_mount(vector<string> parameters, vector<int> locations) {
	// @parameter mount
	// @parameter drive letter
	// @parameter real path

	// TODO: Verification
	string path = parameters[1];
    string drive_letter = parameters[2];
    if (this->mount(path, drive_letter)) {
        this->l.out("Disk mounted successfully");
    }
    else {
        this->l.out("Disk mounted fail");
    };
};

// unmount
void FileSystem::do_unmount(vector<string> parameters, vector<int> locations) {
	// TODO: check unmount reliability
	// @parameter unmount
	// @parameter drive letter

	// TODO: Verification
	string drive_letter = parameters[1];
	this->unmount(drive_letter);
};

// dir
void FileSystem::do_dir(vector<string> parameters, vector<int> locations) {
	// TODO: different mode
	// TODO: problems in it
	vector<string> dir = this->dir();
	for (size_t i = 0; i != dir.size(); i++) {
		int INodenum;
		string name;
		loadDirEntry(INodenum, name, dir[i]);
        this->l.out(name);
	};
};

// make directory
void FileSystem::do_md(vector<string> parameters, vector<int> locations) {
	if (!this->md(parameters[1])) {
        this->l.out("make fail");
	};
};

// remove directory
void FileSystem::do_rd(vector<string> parameters, vector<int> locations) {
	if (!this->rd(parameters[1])) {
        this->l.out("remove fail");
	};
};

// change directory
void FileSystem::do_cd(vector<string> parameters, vector<int> locations) {
	if (!this->cd(parameters[1])) {
        this->l.out("no such directory");
	};
};

// copy
void FileSystem::do_copy(vector<string> parameters, vector<int> locations) {

};

// move
void FileSystem::do_move(vector<string> parameters, vector<int> locations) {

};

// rename
void FileSystem::do_rename(vector<string> parameters, vector<int> locations) {
    this->rename(parameters[1], parameters[2]);
};

// version
void FileSystem::do_version(vector<string> parameters, vector<int> locations) {
    this->l.out(this->ver);
};

// check disk
void FileSystem::do_chkdsk(vector<string> parameters, vector<int> locations) {
    this->chkdsk();
};

// format
void FileSystem::do_format(vector<string> parameters, vector<int> locations) {
    this->format(parameters[1]);
};

// get attribute
void FileSystem::do_getattr(vector<string> parameters, vector<int> locations) {
    vector<string> attrs = this->getattr(parameters[1]);
    this->l.out("name: " + attrs[0]);
    this->l.out("type flag: " + attrs[1]);
    this->l.out("read only flag: " + attrs[2]);
    this->l.out("hidden flag: " + attrs[3]);
    this->l.out("system flag: " + attrs[4]);
    this->l.out("archive flag: " + attrs[5]);
    this->l.out("creation time: " + attrs[6]);
    this->l.out("last access time: " + attrs[7]);
    this->l.out("size: " + attrs[8]);
};

// set attribute
void FileSystem::do_setattr(vector<string> parameters, vector<int> locations) {
    // this->setattr(parameters[1]);
    this->l.out("setattr is not supported in the CLI mode, please use GUI mode \"preperties\"");
};

// open
void FileSystem::do_open(vector<string> parameters, vector<int> locations) {
    this->l.out("This function is forbidden on CLI mide, please use GUI to complete it");
};

// create
void FileSystem::do_create(vector<string> parameters, vector<int> locations) {
	string name;
	this->create(name);
};

// change disk
void FileSystem::do_chdisk(vector<string> parameters, vector<int> locations) {
    this->chdisk(parameters[0]);
};

// process functions

void FileSystem::process_instruction(string line) {
	vector<string> parameters = extract_part(line, " ");
	vector<int> locations = locate_parameter(parameters);
	this->execute_instruction(parameters, locations);
};

void FileSystem::process_line(string line) {
	vector<string> instructions = extract_part(line, "&&");
	for (size_t i = 0; i < instructions.size(); i++) {
		string temp = strip(instructions[i]);
		this->process_instruction(temp);
	};
};

void FileSystem::execute_instruction(vector<string> parameters, vector<int> locations) {
    string Instructions[29] = { "dir", "md", "mkdir", "rd", "rmdir", "cd", "chdir", "copy", "cp", "del", "move", "mv",
        "ren", "rename", "chkdsk", "setdsk", "ver", "version", "format", "getattr", "setattr", "open", "copyin", "copyout",
        "mount", "unmount", "help", "create", "chdisk"};
	int index = getindex(parameters[0], Instructions, 29/*the length of the Instructions*/);
	if (index != -1) {
		if (parameters[0] == "dir") {
			this->do_dir(parameters, locations);
		}
		else if (parameters[0] == "md" || parameters[0] == "mkdir") {
			this->do_md(parameters, locations);
		}
		else if (parameters[0] == "rd" || parameters[0] == "rmdir") {
			this->do_rd(parameters, locations);
		}
		else if (parameters[0] == "cd" || parameters[0] == "chdir") {
			this->do_cd(parameters, locations);
		}
		else if (parameters[0] == "del") {
			this->do_delete(parameters, locations);
		}
		else if (parameters[0] == "help") {
			this->do_help(parameters, locations);
		}
		else if (parameters[0] == "copyin") {
			this->do_copyin(parameters, locations);
		}
		else if (parameters[0] == "copyout") {
			this->do_copyout(parameters, locations);
		}
		else if (parameters[0] == "mount") {
			this->do_mount(parameters, locations);
		}
		else if (parameters[0] == "unmount") {
			this->do_unmount(parameters, locations);
		}
		else if (parameters[0] == "cp" || parameters[0] == "copy") {
			this->do_copy(parameters, locations);
		}
		else if (parameters[0] == "mv" || parameters[0] == "move") {
			this->do_move(parameters, locations);
		}
		else if (parameters[0] == "ren" || parameters[0] == "rename") {
			this->do_rename(parameters, locations);
		}
		else if (parameters[0] == "ver" || parameters[0] == "version") {
			this->do_version(parameters, locations);
		}
		else if (parameters[0] == "chkdsk") {
			this->do_chkdsk(parameters, locations);
		}
		else if (parameters[0] == "format") {
			this->do_format(parameters, locations);
		}
		else if (parameters[0] == "getattr") {
			this->do_getattr(parameters, locations);
		}
		else if (parameters[0] == "setattr") {
			this->do_setattr(parameters, locations);
		}
		else if (parameters[0] == "open") {
			this->do_open(parameters, locations);
		}
		else if (parameters[0] == "creare") {
			this->do_create(parameters, locations);
        }
        else if (parameters[0] == "chdisk") {
            this->do_chdisk(parameters, locations);
        };
	};
};

