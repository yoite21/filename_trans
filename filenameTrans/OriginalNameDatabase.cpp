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
	
	// ����(" ")�� �������� ������ 2�� �̻����� �������� 2��°
	// �� �ܿ��� ù��°�� �˻��ؼ�
	// �����ϸ� shortname�� ����
	// ���� ���� ������ �� ���ڿ��� ����

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
		// �Ƹ� ������ ���°��?
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
	// ���ݻ����̸� �ڷ� �ϳ� �Ѿ�ö����� �Ź� ����� �ϰ� �Ǵ� ������ �ʿ���
	// ������� ��Ҵٰ� �����ϰ� ����?

	// �Է� ����
	// �˻��� / ���� �̸� / ���� �̸�
	// �����ڴ� "/"

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
	// �����ڴ� / ��
	int index[2];
	index[0] = str.find("/");
	index[1] = str.find("/",index[0]+1);

	// �Է� ����
	// �˻��� / ���� �̸� / ���� �̸�
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