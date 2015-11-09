#include <windows.h>
#include <direct.h>
#include <string>
#include <stdio.h>
#include <tchar.h> 
#include <strsafe.h>
#include <vector>
#include <Shlwapi.h>
#include <algorithm>

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
	
	OriginalNameDatabase::getInstance()->saveNodeToData(DatabaseNode("qwer/원문2/줄임2"));


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
	// db, 사용자의 입력을 사용하여 새 파일이름을 만들어 return할것
	// 입력 예제 : (asdf)[fghj]qwer(asdf)[qwer]
	std::string str(filename);
	int sectionStartIndex = 0;
	while(1)
	{
		// (), [] 으로 감싼 부분 찾기
		int roundBracketLeftIndex = str.find("(",sectionStartIndex);
		int squareBracketLeftIndex = str.find("[",sectionStartIndex);
		

		// 시작위치부터 처음 parenthese가 시작하는 위치사이에
		// 내용이 있으면 해당 구역을 section 으로 생각
		// 없으면 괄호시작을 section 의 시작으로 생각해서 끝지점 찾기
		
		// round, square 의 값이 npos 일 경우를 생각해야 하고
		// 여기서 round, square 어떤것이 앞인지 찾는것도 좋을듯
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
		
		// section start index, section end index 로 그 사이값을 통해
		// 묻고 해결을 해서 retv에 저장
		
	}

	std::string retv;
	return retv;
}
