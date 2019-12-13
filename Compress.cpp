#include "Compress.h"

void SortData(Data* data, int count){
	for(int i = 0; i < count - 1; i++){
		for(int j = i + 1; j < count; j++){
			if(data[i].GetFreq() < data[j].GetFreq()){
				Data tmp = data[i];
				data[i] = data[j];
				data[j] = tmp;
			}
		}
	}
}

void Find(Data* root, string path[]){
	static string trace;
	if(root->GetPLeft() == NULL && root->GetPRight() == NULL){
		int tmp = int(root->GetCharacter());
		if(tmp < 0) tmp += 256;
		path[tmp] = trace;
		int l = trace.length();
 	}
	else{
		if(root->GetPLeft() != NULL ) {
			trace += "0";
			Find(root->GetPLeft(), path);
			trace.erase(trace.end() - 1);
		}
		if(root->GetPRight() != NULL ) {
			trace += "1";
			Find(root->GetPRight(), path);	
			trace.erase(trace.end() - 1);
		}
	}
}

void HuffmanTree(Data* root, int count){
	while(count > 1){
		Data* tmp = new Data;
		tmp->SetCharacter(root[count - 2].GetCharacter());
		tmp->SetFreq(root[count - 2].GetFreq());
		tmp->SetPLeft(root[count - 2].GetPLeft());
		tmp->SetPRight(root[count-2].GetPRight());
		root[count - 2].SetPRight(&root[count - 1]);
		root[count - 2].SetPLeft(tmp);
		root[count - 2].SetFreq(root[count - 2].GetPRight()->GetFreq() + root[count - 2].GetPLeft()->GetFreq());
		root[count - 2].SetCharacter(0);
		count--;	
		SortData(root, count);
	}
}

void Compress(char* oldDir, char* newDir){
	auto start = chrono::high_resolution_clock::now();
	string fileType;
	for(int j = strlen(oldDir) - 1; j >= 0; j--){
		if(oldDir[j] == '.'){
			int l = strlen(oldDir);
			for(int k = j + 1; k < l; k++){
				fileType += oldDir[k];
			}
			break;
		}
	}
	
	cout << "Compressing: " << oldDir << endl;
	unsigned long long int freq[256];
	for(int i = 0; i< 256; i++) freq[i] = 0;
	
	fstream input;
	const int size = 1024 * 1024;
	input.open(oldDir, ios::in | ios::binary);
	unsigned char* c = new unsigned char[size];
	while(!input.eof()){
		input.read((char*)c, size);
		int l = input.gcount();
		for(int i = 0; i < l; i++){
			freq[c[i]]++;
	 	}  

	}
	input.close();
	int count = 0;
	Data* root = new Data[256];
	for(int i = 0; i < 256; i++){
		root[i].SetCharacter(i);
		root[i].SetFreq(freq[i]);
		if(freq[i] != 0){
			count++;
		}
	}
	
	for(int i = 0; i < 256 - 1; i++){
		for(int j = i + 1; j < 256; j++){
			if(root[i].GetFreq() < root[j].GetFreq()){
				Data tmp = root[i];
				root[i] = root[j];
				root[j] = tmp;
			}
		}
	}
	
	fstream output;
	output.open(newDir, ios::out | ios::binary);
	output << char(10);
	for(int i = 0; i < fileType.length(); i++){
		output.write(&fileType[i], 1);
	}
	output << char(10);
	output << count << char(10);
	for(int i = 0 ; i < count; i++){
		 if(int(root[i].GetCharacter()) != 10) output << root[i].GetCharacter() << root[i].GetFreq() << char(10);
		else output << 10 << root[i].GetFreq() << char(10);
	}
	HuffmanTree(root, count);	
	string path[256];
	Find(&root[0], path);
	
	string encode = "";
	char* buff = new char[size];
	int buffCount = 0;
	input.open(oldDir, ios::in | ios::binary);
	
	while(!input.eof()){
		input.read((char*)c, size);
		int l = input.gcount();
		for(int i = 0; i < l; i++){
			encode += path[c[i]];
			if(encode.length() >= MAX){
				for(int j = 0; j < MAX; j+=8){
					buff[buffCount] = char((encode[j]-48) << 7 | (encode[j + 1]-48) << 6 | (encode[j+2]-48) << 5 | (encode[j+3]-48) << 4 | (encode[j+4]-48) << 3 | (encode[j+5]-48) << 2 | (encode[j+6]-48) << 1 | (encode[j+7]-48) << 0);
					buffCount++;
					if(buffCount == size){
						output.write(buff, size);
						buffCount = 0;
					}
				}
				encode = encode.substr(MAX);
			}
		}		
	}
	
	int n = 8 - encode.length()%8;
	if(n != 8){
		for(int i = 0; i < n; i++){
			encode += "0";
		}
	}
	for(int j = 0; j < encode.length(); j+=8){
		buff[buffCount] = char((encode[j]-48) << 7 | (encode[j + 1]-48) << 6 | (encode[j+2]-48) << 5 | (encode[j+3]-48) << 4 | (encode[j+4]-48) << 3 | (encode[j+5]-48) << 2 | (encode[j+6]-48) << 1 | (encode[j+7]-48) << 0);
		buffCount++;
		if(buffCount == size){
			output.write(buff, size);
			buffCount = 0;

		}
	}
	output.write(buff, buffCount);
	delete[] buff;
	delete[] c;
	output.seekg(0, ios::beg);
	output << n;
	output.close();
	input.close();
	cout << "Compressed to: " << newDir << endl;
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
	cout << "Time: " << duration.count() / 1000.0 << "s" << endl;
}
