/*
	Motive

	1. project started in October 2nd, 2022
	2. inspired by wallpaper engine on steam

	Goal

	1. change my laptop's wallpaper image randomly

	Condition

	1. the random image must be in a certain folder so that
		this program can get access to the image's information easily
	2. if want to add another image file, need to add the image file to the directory

	Subfunctions needed

	1. function that can change wallpaper
	2. get number of image files in a certain directory
	3. get random index 

	headers needed

	iostream for logging
	windows.h for actual change of wallpaper
	time.h for random
	filesystem to read file in a directory
	
	conio.h...  do i need this?


*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <Windows.h>
#include <filesystem>
#include <time.h>
#include <fstream>

using namespace std;
using filesystem::directory_iterator;

// if needs to edit extensions, fix this vector
static const vector<string> Extensions = { ".jpg" ,".jpeg",".bmp", ".png" };
static char FileName[10001] = { 0, };

void ChangeWallpaper(wchar_t* file);

int main()
{
	srand((unsigned int)time(NULL));

	vector<filesystem::directory_entry> FileDirectory;

	// get all the files' path in a directory
	for (const auto& FilesInDirectory : directory_iterator("FileSource"))
	{
		for (unsigned int i = 0; i < Extensions.size(); i++)
		{
			if (FilesInDirectory.path().extension() == Extensions[i])
			{
				FileDirectory.push_back(FilesInDirectory);
			}
		}
	}

	if (FileDirectory.empty() == true)
	{
		return -1;
	}

	int index = rand() % FileDirectory.size();

	filesystem::directory_entry RandomFile = FileDirectory[index];
	
	cout << RandomFile.path() << endl;

	wstring wstringRandomFileName = RandomFile.path();

	const wchar_t* TargetFileName = wstringRandomFileName.c_str();

	cout << "Successfully changed wallpaper" << endl;

	ChangeWallpaper((wchar_t*)TargetFileName);

	return 0;
}

void ChangeWallpaper(wchar_t* file)
{
	SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, file, SPIF_UPDATEINIFILE);
}