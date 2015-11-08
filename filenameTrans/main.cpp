#include <windows.h>
#include <direct.h>
#include <string>
#include <stdio.h>
#include <tchar.h> 
#include <strsafe.h>
#include <vector>
#include <Shlwapi.h>

// db에 들어갈 내용
// 1. 원본이름검색
// 검색어 / 단축어 / 원본
// 2. 작가 db ( 나중에 )
// 작가 이름 / 작품명
// 3. 삭제 db ( 나중에 )
// 검색어
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
	OriginalNameDatabase db("db.txt");
	
	db.saveNodeToData(DatabaseNode("qwer/원문2/줄임2"));


	return 0;
}

int main()
{
#ifdef TEST_MAIN
	testMain();
#else
	// setlocale(LC_ALL,""); // 이거 용도가??

	// changeFilenameInDirectory("E:\\utorrent\\*");

#endif

	return 0;
}

void changeFilenameInDirectory(const std::string& directoryUrl)
{
	
	WIN32_FIND_DATA fileData;	// 파일 정보
	HANDLE hFind;				// 디렉토리 핸들러
	
	std::vector<std::string> str;
	std::vector<std::string> directoryVector;

	
	hFind = FindFirstFile(directoryUrl.c_str(),&fileData);
	
	
	while(FindNextFile(hFind, &fileData) != 0)
	{
		// 처음 파일은 현재 폴더를 가리키기 때문에 사용하지 않음

		if ( fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) {
			continue; // 폴더는 필요 없음
		}

		// 파일 이름을 받아 새로운 파일 이름을 만듬
		std::string newFilename = makeNewFilename(fileData.cFileName);
		
		std::string afterFileUrl(directoryUrl);
		afterFileUrl.pop_back(); // '*' 제거
		afterFileUrl.append(newFilename);

		std::string beforeFileUrl(directoryUrl);
		beforeFileUrl.pop_back(); // '*' 제거
		beforeFileUrl.append(fileData.cFileName);

		if ( PathFileExists(afterFileUrl.c_str()) )
		{
			// 나중에 처리하겠습니다.
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
	std::string retv;
	// db, 사용자의 입력을 사용하여 새 파일이름을 만들어 return할것

	return retv;
}
