#pragma once
#include<iostream>
using namespace std;

class Data{
	private:
		char character;
		unsigned long long int freq;
		string path;
		Data* pLeft;
		Data* pRight;
	public:
		Data();
		~Data();
		
		void SetCharacter(char character);
		char GetCharacter();
		void SetFreq(unsigned long long int freq);
		unsigned long long int GetFreq();
		void SetPath(string path);
		void CreatePath(bool* path, int n);
		string GetPath();
		
		void SetPLeft(Data* data);
		Data* GetPLeft();
		void SetPRight(Data* data);
		Data* GetPRight();
};



