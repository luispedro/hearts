#ifndef SUREVALIDATOR_H
#define SUREVALIDATOR_H
#include "validator.h"

class SureValidator : public Validator {
	public:
		bool validate( const char*, const char* ) { return true; }
};

#endif // SUREVALIDATOR_H
