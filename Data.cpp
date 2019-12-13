#include "Data.h"

Data::Data(){
	character = char(0);
	freq = 0;
	pLeft = pRight = NULL;
	path = "";
}

Data::~Data(){

}

void Data::SetCharacter(char character){
	this->character = character;	
}

char Data::GetCharacter(){
	return character;
}

void Data::SetFreq(unsigned long long int freq){
	this->freq = freq;
}

unsigned long long int Data::GetFreq(){
	return freq;
}

void Data::SetPath(string path){
	this->path = path;
}

string Data::GetPath(){
	return path;
}

void Data::CreatePath(bool path[], int n){
	for(int i = 0; i < n; i++){
		if(path[i] == 1) this->path += "1";
		else this->path += "0";
	}	
}

void Data::SetPLeft(Data* data){
	pLeft = data;
}

Data* Data::GetPLeft(){
	return pLeft;
}

void Data::SetPRight(Data* data){
	pRight = data;
}

Data* Data::GetPRight(){
	return pRight;
}
