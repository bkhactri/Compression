#define _CRT_SECURE_NO_WARNINGS
#include "Uncompress.h"

void Uncompress(char* oldDir, char* newDir){
	auto start = chrono::high_resolution_clock::now();
	fstream input;
	input.open(oldDir, ios::in | ios::binary);
	int redundant;
	input >> redundant;
	string tail;
	getline(input, tail);
	strcat(newDir, tail.c_str());
	cout << "Uncompressing: " << oldDir << endl ;
	int cCount;
	input >> cCount;
	Data* map = new Data[cCount];
	string tmp;
	getline(input, tmp);
	for(int i = 0; i < cCount; i++){
		getline(input, tmp);
		if(tmp[1] == '0') {	
			map[i].SetCharacter(char(10));
			map[i].SetFreq(atoi((tmp.substr(2)).c_str()));
		}
		else{
			map[i].SetCharacter(tmp[0]);
			map[i].SetFreq(atoi((tmp.substr(1)).c_str()));
		}
	}
	HuffmanTree(map, cCount);
	string path[256];
	Find(&map[0], path);

	fstream output;
	const int size = 1024 * 1024;
	output.open(newDir, ios::out | ios::binary);
	Data* root = &map[0];
	char* buff = new char[size];
	int buffCount = 0;
	unsigned char* c = new unsigned char[size];
	string binString = "";
	while(!input.eof()){
		input.read((char*)c, size);
		int l = input.gcount();

		int end = 0;
		for (int i = 0; i < l; i++) {
			bitset<8> b(c[i]);
			if (i == l - 1 && input.eof()) end = redundant;
			for (int j = 7; j >= end; j--) {

				if (b[j] == 0) root = root->GetPLeft();
				else root = root->GetPRight();
				if(root->GetPLeft() == NULL && root->GetPRight() == NULL){
					buff[buffCount] = root->GetCharacter();	
					buffCount++;
					if(buffCount == size){
						output.write(buff, size);
						buffCount = 0;			
					}
					root = &map[0];
				}
			}
		}
	}
	output.write(buff, buffCount);
 	delete[] buff;
 	delete[] map;
	output.close();
 	cout << "Uncompressed to: "<< newDir << endl;
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
	cout << "Time: " << duration.count() / 1000.0 << "s" << endl;
}
