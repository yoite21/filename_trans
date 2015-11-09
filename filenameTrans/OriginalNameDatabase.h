#pragma once
// 1. �����̸��˻�
// �˻��� / ����� / ����
#include <vector>
#include <string>

class DatabaseNode;

class OriginalNameDatabase {
public:
	static OriginalNameDatabase* getInstance();
	
		
	std::string getOriginalName(const std::string& writtenString) const;
	void saveNodeToData(const DatabaseNode& node);
private:
	OriginalNameDatabase(const char* fileUrl);
	~OriginalNameDatabase();
	void loadFileToData();
	
	void saveNodeToFile(const DatabaseNode& node);
	void saveToFile();
	
private:
	OriginalNameDatabase* mInstance;
	std::string mDatabaseFileUrl;
	std::vector<DatabaseNode> mData;

};

class DatabaseNode {
public:
	DatabaseNode();
	DatabaseNode(const std::string& str);
	DatabaseNode(const char* searchName, const char* originalName, const char* shortName = "");

	std::string mOriginalName; // ���� �̸� (���� ������ �� ���� �Է�)
	std::string mShortName;    // ����� (���� �̸��� �涧 �� ���� �Է��Ѵ�)
	std::string mSearchName;   // �˻��� �̸�
};