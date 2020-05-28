#include "disk.h"
#include "fs.h"
#include "math.h"

using namespace std;    

Disk::Disk() {

};

Disk::~Disk() {
    if (diskimg != NULL) {
		this->writeDiskInfo();
        fclose(this->diskimg);
    };
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
        this->diskimg = fopen(filepath.c_str(), "rb+");
		this->loadDiskInfo();
		return true;
	}
	else {
		// create a new disk
		this->diskimg = fopen(filepath.c_str(), "wb+");
		// TODO: get user input for how many blocks to be created
		for (int i = 0; i < 169918464/* Maximum Size */; i++) {
			// put enough "\0" into the disk
			fputc(32, this->diskimg); // put empty space in
		};

		this->disk_name = "New Disk";
		this->Blocks = 41484;
		this->used_space = 0;
		this->total_space = 169918464;
		this->inode_bitmap_location = 1;
		this->block_bitmap_location = 2;
		this->inode_location = 12;

		this->writeDiskInfo();
		cout << "write disk info success" << endl;

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
		root.setter(2, 0, 0, 1, 0, 0, 0, 0, -1, "/");
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
    if (diskimg != NULL) {
		this->writeDiskInfo();
        fclose(this->diskimg);
		return true;
    };
	return false;
};

bool Disk::getBlock(int blocknum, string &data) {
    if (blocknum <= (int)Blocks) {
        fseek(diskimg, blocknum*BlockSize, SEEK_SET);
        char cdata[4096];
        fgets(cdata, BlockSize, diskimg);
		string temp = chartostring(cdata, 4096);
		data = temp;
        // cout << data << endl; // for test
		return true;
    };
	return false;
};

bool Disk::putBlock(int blocknum, string &data) {
	// TODO: check data size smaller than blocksize, if larger, return to the above level
    if (blocknum <= (int)Blocks) {
        if (data.size() != 0) {
            fseek(diskimg, blocknum*BlockSize, SEEK_SET);
			//int len = strlen(data.c_str())+1;
			int len = strlen(data.c_str());
			if (fwrite(data.c_str(), 1, len, diskimg) == len) {
				// cout << "write operation success" << endl;
				return true;
			}
			else {
				// cout << "write operation failed" << endl;
				return false;
			};
        };
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

