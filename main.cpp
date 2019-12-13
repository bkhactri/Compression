#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <string.h>
#include<cstdlib>
#include<string>
#include <process.h> 
#include <stdlib.h>
#include<fstream>
#include <bitset>
#include "dirent.h"
#include<direct.h>
#include <conio.h> 
#include<time.h>
#include "Uncompress.h"
#include "jpeg_encoder.h"
using namespace std;

void ListFile(char* path, char* compressPath, int choice){
	DIR *pDIR;
    struct dirent *entry;
    if( pDIR = opendir(path)){
        while(entry = readdir(pDIR)){
            if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 ){	
	            if(choice == 1){
	            	bool dot = false;
					for(int i = 0; i < strlen(entry->d_name); i++){
	            		if(entry->d_name[i] == '.'){
	            			dot = true;
	            			break;
						}
					}
					if(dot == false){
						char newPath[260];
						strcpy(newPath, path);
						strcat(newPath, "/");
						strcat(newPath, entry->d_name);
						
						char newCompressPath[260];
						strcpy(newCompressPath, compressPath);
						strcat(newCompressPath, "/");
						strcat(newCompressPath, entry->d_name);
						_mkdir(newCompressPath);
						ListFile(newPath, newCompressPath, choice);
					}
					else{
						char newPath[260];
						strcpy(newPath, path);
						strcat(newPath, "/");
						strcat(newPath, entry->d_name);
						
						char newCompressPath[260];
						strcpy(newCompressPath, compressPath);
						strcat(newCompressPath, "/");
						for(int i = strlen(entry->d_name) - 1; i >= 0; i--){
							if(entry->d_name[i] == '.'){
								strncat(newCompressPath, entry->d_name, i + 1);	
								break;	
							}
						}
						strcat(newCompressPath, "bin");
						Compress(newPath, newCompressPath);
					}
				}
				else{
					bool dot = false;
					for(int i = 0; i < strlen(entry->d_name); i++){
	            		if(entry->d_name[i] == '.'){
	            			dot = true;
	            			break;
						}
					}
					if(dot == false){
						char newPath[260];
						strcpy(newPath, path);
						strcat(newPath, "/");
						strcat(newPath, entry->d_name);
						
						char newCompressPath[260];
						strcpy(newCompressPath, compressPath);
						strcat(newCompressPath, "/");
						strcat(newCompressPath, entry->d_name);
						_mkdir(newCompressPath);
						ListFile(newPath, newCompressPath, choice);
					}
					else{
						char newPath[100];
						strcpy(newPath, path);
						strcat(newPath, "/");
						strcat(newPath, entry->d_name);
						
						char newCompressPath[100];
						strcpy(newCompressPath, compressPath);
						strcat(newCompressPath, "/");
						for(int i = strlen(entry->d_name) - 1; i >= 0; i--){
							if(entry->d_name[i] == '.'){
								strncat(newCompressPath, entry->d_name, i + 1);	
								break;	
							}
						}
						Uncompress(newPath, newCompressPath);
					}
				}
            	
			}
        }
        closedir(pDIR);
    }
}

int main(){	
	while(true){
		system("cls");
		int choice;
		cout << "CHUONG TRINH NEN DU LIEU\n" << endl;
		cout << "1. Nen file " << endl;
		cout << "2. Giai nen file " << endl;
		cout << "3. Nen folder " << endl;
		cout << "4. Giai nen folder" << endl;
		cout << "5. Nen anh" << endl;
		cout << "6. Thoat\n" << endl;
		cout << "Nhap lua chon: ";
		cin >>  choice;
		system("cls");
		char path[260] = "";
		char newPath[260] = "";
		cin.ignore();
		if(choice == 1){
			cout << "Nhap ten file can nen: ";	
			gets_s(path);
			for(int i = strlen(path) - 1; i >= 0; i--){
				if(path[i] == '.'){
					strncat(newPath, path, i + 1);	
					break;	
				}
			}
			strcat(newPath, "bin");
			Compress(path, newPath);  
			return 0;
		}
		else if(choice == 2){
			cout << "Nhap ten file can giai nen: ";
			gets_s(path);
			for(int i = strlen(path) - 1; i >= 0; i--){
				if(path[i] == '.'){
					strncat(newPath, path, i + 1);	
					break;	
				}
			}
			Uncompress(path, newPath);
			return 0;
		}
		else if(choice == 3){
			cout << "Nhap ten folder can nen: ";
			cin.getline(path, 260);
			cout << "Nhap ten folder moi: ";
			cin.getline(newPath, 260);
			_mkdir(newPath);
			ListFile(path, newPath, 1);
		}
		else if(choice == 4){
			cout << "Nhap ten folder can giai nen: ";
			cin.getline(path, 260);
			cout << "Nhap ten folder moi: ";
			cin.getline(newPath, 260);
			_mkdir(newPath);
			ListFile(path, newPath, 2);
		}
		else if(choice ==5){
			cout << "Nhap ten anh can nen (.bmp): ";
			gets_s(path);
			cout << "Nhap ten anh sau khi nen: ";
			gets_s(newPath);
			strcat(newPath,".jpg");
			JpegEncoder encoder;
			if(!encoder.readFromBMP(path))
			{
				cout << "Dinh dang anh can dua vo la bitmap & co the ban da nhap nhap sai" << endl;
			}
		
			if(!encoder.encodeToJPG("out.jpg", 50))
			{
				cout << "Qua trinh nen anh da xay ra loi , xin hay kiem tra lai" << endl;
			}
			cout << "Qua trinh nen anh thanh cong . Ban hay kiem tra anh sau khi nen bang file (ten anh sau khi nen).jpg" << endl;
		}
		else if(choice == 6) break;
		system("pause");
	}
	system("pause");
	return 0;
}
