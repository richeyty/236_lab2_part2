#ifndef PLAIN_PARAMETER_H
#define PLAIN_PARAMETER_H
#include "Parameter.h"
#include <string>
class PlainParameter : public Parameter {
private:
	string stringOrId;
public:
	PlainParameter() {}
	PlainParameter(string inputString) {
		this->stringOrId = inputString;
	}
	string toString() {
		return stringOrId;
	}
};

#endif // PLAIN_PARAMETER_H

