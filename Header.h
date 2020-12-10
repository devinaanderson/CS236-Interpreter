#pragma once
#include <iostream>
#include <vector>

using namespace std;


class Header
{
private:
public:
	vector<string> attributes;

	Header();
	Header(vector<string> attr) {
		attributes = attr;
	};
	Header(vector<Parameter> params) {
		for (Parameter p : params) {
			attributes.push_back(p.ToString());
		}
	};
	~Header();
	void AddAttr(string s) {
		attributes.push_back(s);
	};
	void ToString() {
		for (string s : attributes) {
			cout << s << ", ";
		}
		cout << endl;
	}
};



Header::Header()
{
}


Header::~Header()
{
}
