#include <windows.h>
#include <direct.h>
#include <string>
#include <stdio.h>
#include <tchar.h> 
#include <strsafe.h>
#include <vector>
#include <Shlwapi.h>
#include <algorithm>

// db�� �� ����
// 1. �����̸��˻�
// �˻��� / ����� / ����
// 2. �۰� db ( ���߿� )
// �۰� �̸� / ��ǰ��
// 3. ���� db ( ���߿� )
// �˻���
#include "OriginalNameDatabase.h"

#pragma comment(lib, "User32.lib")
#pragma comment(lib, "shlwapi.lib")

#define TEST_MAIN


void changeFilenameInDirectory(const std::string& directoryUrl);

std::string makeNewFilename(const char* filename);
bool isExistFilename(const std::string& fileUrl);
void makeExistFilename(std::string& filename);

int testMain()
{
	
	OriginalNameDatabase::getInstance()->saveNodeToData(DatabaseNode("qwer/����2/����2"));


	return 0;
}

int main()
{
#ifdef TEST_MAIN
	testMain();
#else
	// setlocale(LC_ALL,""); // �̰� �뵵��??

	// changeFilenameInDirectory("E:\\utorrent\\*");

#endif

	return 0;
}

void changeFilenameInDirectory(const std::string& directoryUrl)
{
	
	WIN32_FIND_DATA fileData;	// ���� ����
	HANDLE hFind;				// ���丮 �ڵ鷯
	
	std::vector<std::string> str;
	std::vector<std::string> directoryVector;

	
	hFind = FindFirstFile(directoryUrl.c_str(),&fileData);
	
	
	while(FindNextFile(hFind, &fileData) != 0)
	{
		// ó�� ������ ���� ������ ����Ű�� ������ ������� ����

		if ( fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) {
			continue; // ������ �ʿ� ����
		}

		// ���� �̸��� �޾� ���ο� ���� �̸��� ����
		std::string newFilename = makeNewFilename(fileData.cFileName);
		
		std::string afterFileUrl(directoryUrl);
		afterFileUrl.pop_back(); // '*' ����
		afterFileUrl.append(newFilename);

		std::string beforeFileUrl(directoryUrl);
		beforeFileUrl.pop_back(); // '*' ����
		beforeFileUrl.append(fileData.cFileName);

		if ( PathFileExists(afterFileUrl.c_str()) )
		{
			// ���߿� ó���ϰڽ��ϴ�.
			/*
			int errno;
			if ( errno = rename(beforeFileUrl.c_str(), afterFileUrl.c_str()) )
			{
				switch ( errno ) {
				case EACCES:
					printf("already exists or could not be created.\n");
					break;
				case ENOENT:
					printf("oldname not found.\n");
					break;
				case EINVAL:
					printf("invalid characters.\n");
					break;
				default:
					perror("rename");
				}
			}
			*/
		}
	}
	FindClose(hFind);
}



std::string makeNewFilename(const char* filename)
{
	// db, ������� �Է��� ����Ͽ� �� �����̸��� ����� return�Ұ�
	// �Է� ���� : (asdf)[fghj]qwer(asdf)[qwer]
	std::string str(filename);
	int sectionStartIndex = 0;
	while(1)
	{
		// (), [] ���� ���� �κ� ã��
		int roundBracketLeftIndex = str.find("(",sectionStartIndex);
		int squareBracketLeftIndex = str.find("[",sectionStartIndex);
		

		// ������ġ���� ó�� parenthese�� �����ϴ� ��ġ���̿�
		// ������ ������ �ش� ������ section ���� ����
		// ������ ��ȣ������ section �� �������� �����ؼ� ������ ã��
		
		// round, square �� ���� npos �� ��츦 �����ؾ� �ϰ�
		// ���⼭ round, square ����� ������ ã�°͵� ������
		std::string tmp(str.substr(sectionStartIndex,roundBracketLeftIndex<squareBracketLeftIndex?roundBracketLeftIndex:squareBracketLeftIndex));
		tmp.erase(std::remove(tmp.begin(),tmp.end()," "));

		int sectionEndIndex;
		if ( tmp.empty() )
		{
			sectionStartIndex = roundBracketLeftIndex<squareBracketLeftIndex?roundBracketLeftIndex:squareBracketLeftIndex;

			int roundBracketRightIndex = std::string::npos;
			int squareBracketRightIndex = std::string::npos;
			if ( roundBracketLeftIndex != std::string::npos )
			{
				roundBracketRightIndex = str.find(")",sectionStartIndex);
			}
			if ( squareBracketLeftIndex != std::string::npos )
			{
				squareBracketRightIndex = str.find("]",sectionStartIndex);
			}

			int parentheseEndIndex;
			if ( roundBracketLeftIndex == std::string::npos )
			{
				if ( squareBracketLeftIndex == std::string::npos )
				{
					//
					break;
				}
				else
				{
					parentheseEndIndex = roundBracketRightIndex;

				}
			}
			else
			{
				if ( squareBracketLeftIndex == std::string::npos )
				{
				
				}
				else
				{

				}
			}
		}
		else
		{
			sectionEndIndex = roundBracketLeftIndex<squareBracketLeftIndex?roundBracketLeftIndex:squareBracketLeftIndex - 1;
		}
		
		// section start index, section end index �� �� ���̰��� ����
		// ���� �ذ��� �ؼ� retv�� ����
		
	}

	std::string retv;
	return retv;
}
