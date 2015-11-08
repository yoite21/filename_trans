#pragma once
// 1. 원본이름검색
// 검색어 / 단축어 / 원본
#include <vector>
#include <string>

class DatabaseNode;

class OriginalNameDatabase {
public:
	OriginalNameDatabase(const char* fileUrl);
		
	std::string getOriginalName(const std::string& writtenString) const;
	void saveNodeToData(const DatabaseNode& node);
private:
	void loadFileToData();
	
	void saveNodeToFile(const DatabaseNode& node);
	void saveToFile();
	
private:
	std::string mDatabaseFileUrl;
	std::vector<DatabaseNode> mData;

};

class DatabaseNode {
public:
	DatabaseNode();
	DatabaseNode(const std::string& str);
	DatabaseNode(const char* searchName, const char* originalName, const char* shortName = "");

	std::string mOriginalName; // 원본 이름 (단축어가 없으면 이 값을 입력)
	std::string mShortName;    // 단축어 (원본 이름이 길때 이 단축어를 입력한다)
	std::string mSearchName;   // 검색할 이름
};