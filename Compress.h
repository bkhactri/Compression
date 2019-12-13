#pragma once
#include "Data.h"
#include<string>
#include <string.h>
#include<fstream>
#include<chrono>
const int size = 1024 * 1024;
const int MAX = 1024*1024*8;
void SortData(Data* data, int count);
void Find(Data* root, string path[]);
void HuffmanTree(Data* root, int count);
void Compress(char* oldDir, char* newDir);
