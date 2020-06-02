#include "disk.h"
#include "fs.h"
#include "math.h"

using namespace std;    

Disk::Disk() {

};

Disk::~Disk() {
    this->writeDiskInfo();
    this->diskimg.close();
};

void Disk::loadDiskInfo() {
	string data;
	this->getBlock(0, data);

	// Magic Number
    string MagNum = data.substr(0, 16);
	if (MagNum == this->magic_number) {
		// Disk Name
		string DiskName = strip(data.substr(16, 256));
		DiskName = this->disk_name;

		// BlockSize
		int BlockSize = stoi(strip(data.substr(272, 4)));

		// Number of Blocks
		int NumBlocks = stoi(strip(data.substr(276, 8)));
		this->Blocks = NumBlocks;

		// Used Space
		int UsedSpace = stoi(strip(data.substr(284, 32)));
		this->used_space = UsedSpace;

		// Total Space
		int TotalSpace = stoi(strip(data.substr(316, 32)));
		this->total_space = TotalSpace;

		// INode Bitmap Location
		int INBLoc = stoi(strip(data.substr(348, 4)));
		this->inode_bitmap_location = INBLoc;

		// Block Bitmap Location
		int BBLoc = stoi(strip(data.substr(352, 4)));
		this->block_bitmap_location = BBLoc;

		// Inode Location
		int INodeLoc = stoi(strip(data.substr(356, 4)));
		this->inode_location = INodeLoc;
	}
    else {
        cout << "disk has been broken" << endl;
	};
};

void Disk::writeDiskInfo() {
	string data;
	// Magic Number
	data = data + add_placeholder(this->magic_number, 16);

	// Disk Name
	data = data + add_placeholder(this->disk_name, 256);

	// Block Size
	data = data + add_placeholder(to_string(this->BlockSize), 4);

	// Number of Blocks
	data = data + add_placeholder(to_string(this->Blocks), 8);

	// Used Space
	data = data + add_placeholder(to_string(this->used_space), 32);

	// Total Space
	data = data + add_placeholder(to_string(this->total_space), 32);

	// INode Bitmap Location
	data = data + add_placeholder(to_string(this->inode_bitmap_location), 4);

	// Block Bitmap Location
	data = data + add_placeholder(to_string(this->block_bitmap_location), 4);
	
	// Inode Location
	data = data + add_placeholder(to_string(this->inode_location), 4);

	this->putBlock(0, data);
}

bool Disk::open(string filepath, string drive_letter) {
    if (file_exist(filepath)) {
        this->diskimg.open(filepath, ios::in|ios::out);
        this->loadDiskInfo();
		return true;
	}
	else {
		// create a new disk
        this->diskimg.open(filepath, ios::in|ios::out|ios::trunc);
		// TODO: get user input for how many blocks to be created
		for (int i = 0; i < 169918464/* Maximum Size */; i++) {
			// put enough "\0" into the disk
            this->diskimg.write(" ", 1);
		};

		this->disk_name = "New Disk";
		this->Blocks = 41484;
		this->used_space = 0;
		this->total_space = 169918464;
		this->inode_bitmap_location = 1;
		this->block_bitmap_location = 2;
		this->inode_location = 12;

        this->writeDiskInfo();

		// initiallize bitmaps
		string emptybitmap = string(4096, '0');

		this->putBlock(1, emptybitmap);
		this->putBlock(2, emptybitmap);
		this->putBlock(3, emptybitmap);
		this->putBlock(4, emptybitmap);
		this->putBlock(5, emptybitmap);
		this->putBlock(6, emptybitmap);
		this->putBlock(7, emptybitmap);
		this->putBlock(8, emptybitmap);
		this->putBlock(9, emptybitmap);
		this->putBlock(10, emptybitmap);
		this->putBlock(11, emptybitmap);

		// write root directory INode
		INode root;
        root.setter(1, 0, 0, 1, 0, 0, 0, 0, -1, "/");
		root.set_reference(1, 524);
		root.set_last_node(0);
		string data;
		data = root.dumpINode();
		// cout << data << endl;
		this->putINode(0, data);

		// write root directory block
		string rootdata = add_placeholder(0, 8) + add_placeholder("..", 24) + add_placeholder(0, 8) + add_placeholder(".", 24);
		this->putBlock(524, rootdata);

		// update bitmap
		this->changeBitmap(1, 0);
		this->changeBitmap(2, 0);

		cout << "New disk created successfully" << endl;
		return true;
    };
	return false;
};

bool Disk::close() {
    this->writeDiskInfo();
    this->diskimg.close();
    return true;
};

bool Disk::clear() {
    this->writeDiskInfo();
    this->diskimg.close();
    this->diskimg.clear();
    return true;
};

bool Disk::format() {
    for (int i = 0; i < 169918464/* Maximum Size */; i++) {
        // put enough "\0" into the disk
        this->diskimg.write(" ", 1);
    };

    this->disk_name = "New Disk";
    this->Blocks = 41484;
    this->used_space = 0;
    this->total_space = 169918464;
    this->inode_bitmap_location = 1;
    this->block_bitmap_location = 2;
    this->inode_location = 12;

    this->writeDiskInfo();

    // initiallize bitmaps
    string emptybitmap = string(4096, '0');

    this->putBlock(1, emptybitmap);
    this->putBlock(2, emptybitmap);
    this->putBlock(3, emptybitmap);
    this->putBlock(4, emptybitmap);
    this->putBlock(5, emptybitmap);
    this->putBlock(6, emptybitmap);
    this->putBlock(7, emptybitmap);
    this->putBlock(8, emptybitmap);
    this->putBlock(9, emptybitmap);
    this->putBlock(10, emptybitmap);
    this->putBlock(11, emptybitmap);

    // write root directory INode
    INode root;
    root.setter(1, 0, 0, 1, 0, 0, 0, 0, -1, "/");
    root.set_reference(1, 524);
    root.set_last_node(0);
    string data;
    data = root.dumpINode();
    // cout << data << endl;
    this->putINode(0, data);

    // write root directory block
    string rootdata = add_placeholder(0, 8) + add_placeholder("..", 24) + add_placeholder(0, 8) + add_placeholder(".", 24);
    this->putBlock(524, rootdata);

    // update bitmap
    this->changeBitmap(1, 0);
    this->changeBitmap(2, 0);

    cout << "Disk formated successfully" << endl;
    return true;
}

bool Disk::getBlock(int blocknum, string &data) {
    if (blocknum <= (int)Blocks) {
        this->diskimg.seekg(blocknum*4096, ios::beg);
        char cdata[4096];
        this->diskimg.read(cdata, 4096);
		string temp = chartostring(cdata, 4096);
        data = temp;
		return true;
    };
	return false;
};

bool Disk::putBlock(int blocknum, string &data) {
	// TODO: check data size smaller than blocksize, if larger, return to the above level
    if (blocknum <= (int)Blocks) {
        if (data.size() != 0) {
            this->diskimg.seekp(blocknum*4096, ios::beg);
			//int len = strlen(data.c_str())+1;
			int len = strlen(data.c_str());
            this->diskimg.write(data.c_str(), len);
        };
        return true;
    };
	return false;
};

bool Disk::getINode(int nodenum, string &data) {
	// TODO: Verification
	int blocknum = nodenum / 8 + 12;
	int offset = nodenum % 8;
	string blockdata;
	this->getBlock(blocknum, blockdata);
	data = blockdata.substr(512*offset, 512);
	return true;
};

bool Disk::putINode(int nodenum, string &data) {
	int blocknum = nodenum / 8 + 12;
	int offset = nodenum % 8;
	string blockdata;
	this->getBlock(blocknum, blockdata);
	blockdata.replace(512*offset, 512, data);

	// cout << blockdata << endl;
	this->putBlock(blocknum, blockdata);
	return true;
};

bool Disk::getBitmap(int nodenum, int position) {
	string data;
	// TODO: Verification
	this->getBlock(nodenum, data);
	if (data[position] == '0') {
		return false;
	}
	else if (data[position] == '1') {
		return true;
	}
	else {
		// TODO: raise error
		return false;
	};
};

void Disk::changeBitmap(int nodenum, int position) {
	string data;
	// TODO: Verification
	this->getBlock(nodenum, data);
	if (data[position] == '0') {
		data[position] = '1';
		this->putBlock(nodenum, data);
	}
	else if (data[position] == '1') {
		data[position] = '0';
		this->putBlock(nodenum, data);
	}
};

int Disk::searchBitmap(int type) {
	// type 0 for INodes
	// type 1 for data blocks
	// TODO: exceptions when bitmap is full
	string data;
	if (type == 0) {
		this->getBlock(1, data);
		for (int i = 0; i < 4096; i++) {
			if (data[i] == '0') {
				return i;
			};
		};
	}
	else if (type == 1) {
		for (int i = 2; i < 12; i++) {
			this->getBlock(i, data);
			for (int j = 0; j < 4096; j++) {
				if (data[j] == '0') {
					return j + 4096*(i-2) + 524;
				};
			};
		};
	}
	else {
		// raise error
	};
};

vector<string> Disk::loadDirEntries(int nodenum) {
	string data;
	this->getBlock(nodenum, data);
	vector<string> entries;
	for (int i = 0; i<128; i++) {
		string temp = data.substr(32 * i, 32);
		if (!all_placeholder(temp)) {
			entries.push_back(temp);
		};
	};
	return entries;
};

void Disk::dumpDirEntries(int nodenum, vector<string> raw) {
	string entries;
	for (size_t i = 0; i != raw.size(); i++) {
		entries = entries + raw[i];
	};
	string data = add_placeholder(entries, 4096);
	this->putBlock(nodenum, data);
};

void loadDirEntry(int &INodenum, string &name, string raw) {
	string INode = raw.substr(0, 8);
	INodenum = stoi(strip(INode));
	name = strip(raw.substr(8, 24));
};

string dumpDirEntry(int INodenum, string name) {
	return add_placeholder(INodenum, 8) + add_placeholder(name, 24);
};

// tool functions
string strip(string str) {
	string new_str = str;

	// get rid of the white spaces
	new_str.erase(0, new_str.find_first_not_of(" "));
	new_str.erase(new_str.find_last_not_of(" ") + 1);

	// get rid of the tabs
	new_str.erase(0, new_str.find_first_not_of("\t"));
	new_str.erase(new_str.find_last_not_of("\t") + 1);

	return new_str;
};

int getindex(string element, string array[], int length) {
	int index = -1;
	for (int i = 0; i < length; i++) {
		if (element == array[i]) {
			index = i;
			break;
		};
	};
	return index;
};

bool file_exist(string filename) {
	if (FILE *file = fopen(filename.c_str(), "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
};

vector<string> process_path(string raw) {
	// TODO: not comlete
	vector<string> path;
	return path;
};

string slash_trans(string raw) {
	// TODO: not complete
	return raw;
};

string add_placeholder(string raw, int length) {
	for (size_t i = raw.length(); i < length; i++) {
		raw = raw + ' ';
	};
	return raw;
};

string add_placeholder(int raw, int length) {
	string data = to_string(raw);
	return add_placeholder(data, length);
};

string chartostring(char* raw, int size) {
	string str;
	for (int i = 0; i < size; i++) {
		str = str + raw[i];
	};
	return str;
};

bool all_placeholder(string raw) {
	// not perfect
	if (raw.find_first_not_of(" ") != std::string::npos)
	{
		// TODO: verify whether the following is useful or not
		bool flag = true;
		for (int i = 0; i < raw.length(); i++) {
			if (raw[i] == '\0') {
				flag = false;
			};
			char one = raw[i];
		};
		if (!flag) {
			return true;
		}
		else {
			return false;
		};
		return false;
	}
	else {
		return true;
	};
};

int get_cur_time() {
	time_t t = std::time(0);
	return t;
};

vector<string> extract_part(string line, string seperator)
{
	size_t pos1, pos2;
	vector<string> parameters;
	pos2 = line.find(seperator);
	pos1 = 0;
	while (pos2 != string::npos)
	{
		parameters.push_back(line.substr(pos1, pos2 - pos1));

		pos1 = pos2 + seperator.length();
		pos2 = line.find(seperator, pos1);
	}
	if (pos1 != line.length()) {
		parameters.push_back(line.substr(pos1));
	}
	return parameters;
};

vector<int> locate_parameter(vector<string> parameters) {
	vector<int> location;
	for (int i = 0; i < parameters.size(); i++) {
		if (&parameters[i][0] == "-") {
			location.push_back(i);
		};
	};
	return location;
};
