#include "OriginalNameDatabase.h"

#include <cstdio>
#include <algorithm>
#include <cerrno>


OriginalNameDatabase::OriginalNameDatabase(const char* fileUrl)
	:mDatabaseFileUrl(fileUrl)
{
	loadFileToData();	

}

std::string OriginalNameDatabase::getOriginalName(const std::string& writtenString) const
{
	
	// 공백(" ")을 기준으로 나눠서 2개 이상으로 나눠지면 2번째
	// 그 외에는 첫번째로 검색해서
	// 존재하면 shortname을 전달
	// 만약 값이 없으면 빈 문자열을 리턴

	std::string searchingWord;
	std::size_t index = writtenString.find(" ");
	if ( index == std::string::npos )
	{
		searchingWord = writtenString;
	}
	else 
	{
		std::size_t nextIndex = writtenString.find(" ",index+1);
		if ( nextIndex == std::string::npos )
		{
			searchingWord = writtenString.substr(index+1);
		}
		else
		{
			searchingWord = writtenString.substr(index+1, nextIndex-index-1);
		}
	}

	for(int i = 0; i < mData.size(); i++)
	{
		if ( mData[i].mSearchName.find(searchingWord) == std::string::npos )
		{
			if ( mData[i].mShortName.empty() )
				return mData[i].mOriginalName;
			else
				return mData[i].mShortName;
		}
	}

	return std::string("");
}

void OriginalNameDatabase::loadFileToData()
{
	FILE* fp;
	fp = fopen(mDatabaseFileUrl.c_str(), "r");
	if ( fp == NULL && errno == ENOENT )
	{
		// 아마 파일이 없는경우?
		fp = fopen(mDatabaseFileUrl.c_str(), "w");
		fclose(fp);
		return;
	}

	char buffer[8192];

	while ( fscanf(fp, "%s\n", buffer) != EOF )
	{
		std::string bufString(buffer);

		if ( !bufString.empty() )
		{
			mData.push_back(DatabaseNode(bufString));
		}
	}
	
	fclose(fp);
}

void OriginalNameDatabase::saveNodeToData(const DatabaseNode& node)
{
	mData.push_back(node);
	saveNodeToFile(node);
}
void OriginalNameDatabase::saveNodeToFile(const DatabaseNode& node)
{
	FILE* fp = fopen(mDatabaseFileUrl.c_str(), "a");
	fprintf(fp, "%s/%s/%s\n",node.mSearchName.c_str(), node.mShortName.c_str(), node.mOriginalName.c_str());

	fclose(fp);
}

void OriginalNameDatabase::saveToFile()
{
	// TODO
	// 지금상태이면 자료 하나 넘어올때마다 매번 기록을 하게 되니 수정이 필요함
	// 어느정도 모았다가 저장하게 변경?

	// 입력 포맷
	// 검색어 / 단축 이름 / 원본 이름
	// 구분자는 "/"

	FILE* fp = fopen(mDatabaseFileUrl.c_str(), "w");
	for(int i = 0; i < mData.size(); i++)
	{
		fprintf(fp, "%s/%s/%s\n",mData[i].mSearchName.c_str(), mData[i].mShortName.c_str(), mData[i].mOriginalName.c_str());
	}

	fclose(fp);
}


// DatabaseNode

DatabaseNode::DatabaseNode()
{
}

DatabaseNode::DatabaseNode(const std::string& str)
{
	// 구분자는 / 임
	int index[2];
	index[0] = str.find("/");
	index[1] = str.find("/",index[0]+1);

	// 입력 포맷
	// 검색어 / 단축 이름 / 원본 이름
	mSearchName = str.substr(0, index[0]);
	mShortName = str.substr(index[0]+1, index[1]-index[0]-1);
	mOriginalName = str.substr(index[1]+1);
}

DatabaseNode::DatabaseNode(const char* searchName, const char* originalName, const char* shortName)
	: mOriginalName(originalName),
	mShortName(shortName),
	mSearchName(searchName)
{
}