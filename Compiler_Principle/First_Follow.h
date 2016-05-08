#pragma once
class CFirst_Follow
{
public:
	CFirst_Follow();
	~CFirst_Follow();
private:
	vector<string> m_First[22];
	vector<string> m_Follow[22];

public:
	void Init();
	bool Search_First(const int&ID,const string& ptr);
	bool Search_Follow(const int&ID, const string& ptr);
	void vec_clear();
};

