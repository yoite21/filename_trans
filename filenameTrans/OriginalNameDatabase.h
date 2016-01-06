#pragma once
// 1. �����̸��˻�
// �˻��� / ����� / ����
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

	std::string mOriginalName; // ���� �̸� (���� ������ �� ���� �Է�)
	std::string mShortName;    // ����� (���� �̸��� �涧 �� ���� �Է��Ѵ�)
	std::string mSearchName;   // �˻��� �̸�
};