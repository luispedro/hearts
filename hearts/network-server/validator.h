#ifndef VALIDATOR_H
#define VALIDATOR_H

/** An API to validate a username/password combination */
class Validator {
	public:
		virtual bool validate( const char*, const char* ) = 0;
};
#endif // VALIDATOR_H

