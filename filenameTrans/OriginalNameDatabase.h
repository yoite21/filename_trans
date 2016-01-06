#pragma once
// 1. 원본이름검색
// 검색어 / 단축어 / 원본
#include <vector>
#include <string>

class OriginalNameDatabaseNode;

class OriginalNameDatabase {
public:
	static OriginalNameDatabase* getInstance();
	
		
	std::string getOriginalName(const std::string& writtenString) const;
	void saveNodeToData(const OriginalNameDatabaseNode& node);
private:
	OriginalNameDatabase(const char* fileUrl);
	~OriginalNameDatabase();
	void loadFileToData();
	
	void saveNodeToFile(const OriginalNameDatabaseNode& node);
	void saveToFile();
	
private:
	static OriginalNameDatabase* mInstance;
	std::string mDatabaseFileUrl;
	std::vector<OriginalNameDatabaseNode> mData;

};

class OriginalNameDatabaseNode {
public:
	OriginalNameDatabaseNode();
	OriginalNameDatabaseNode(const std::string& str);
	OriginalNameDatabaseNode(const char* searchName, const char* originalName, const char* shortName = "");

	std::string mOriginalName; // 원본 이름 (단축어가 없으면 이 값을 입력)
	std::string mShortName;    // 단축어 (원본 이름이 길때 이 단축어를 입력한다)
	std::string mSearchName;   // 검색할 이름
};