#include "DatalogProgram.h"


DatalogProgram::DatalogProgram()
{
}

void DatalogProgram::FillDomain() {
	for (unsigned int i = 0; i < facts.size(); i++) {
		for (unsigned int j = 0; j < facts[i].params.size(); j++) {
			domain.insert(facts[i].params[j].ToString());
		}
	}
};

void DatalogProgram::ToString()
{
	cout << "Schemes(" << schemes.size() << "):" << endl;
	for (unsigned int i = 0; i < schemes.size(); i++) {
		cout << "  " << schemes[i].ToString() << endl;
	}


	cout << "Facts(" << facts.size() << "):" << endl;
	for (unsigned int i = 0; i < facts.size(); i++) {
		cout << "  " << facts[i].ToString() << "." << endl;
	}


	cout << "Rules(" << rules.size() << "):\n";
	for (unsigned int i = 0; i < rules.size(); i++) {
		cout << "  " << rules[i].ToString() << ".\n";
	}


	cout << "Queries(" << queries.size() << "):\n";
	for (unsigned int i = 0; i < queries.size(); i++) {
		cout << "  " << queries[i].ToString() << "?\n";
	}


	FillDomain();
	cout << "Domain(" << domain.size() << "):\n";
	for (auto ptr = domain.begin(); ptr != domain.end(); ptr++) {
		cout << "  " << *ptr << endl;
	}
;
}


