#ifndef LAB1_236_HEADER_H
#define LAB1_236_HEADER_H
#include <vector>
#include <string>

using namespace std;
class Header
{
private:
	vector<string> names;
public:
	Header() {}
	Header(vector<string> inputNames) {
		for (unsigned int i = 0; i < inputNames.size(); ++i) {
			names.push_back(inputNames.at(i));
		}
	}
	vector<string> toString() {
		return names;
	}

};

#endif // HEADER_H