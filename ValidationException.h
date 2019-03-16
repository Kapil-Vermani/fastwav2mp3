#ifndef VALIDATION_EXCEPTION_H
#define VALIDATION_EXCEPTION_H
#include <exception>
#include <string>
class CValidationException : public std::exception
{
public:
	/**
		Default constructor might be needed if we want to say create vector of validation exceptions
	*/
	CValidationException() = default;
	
	/** Constructor (C strings).
	*  @param message C-style string error message.
	*                 The string contents are copied upon construction.
	*                 Hence, responsibility for deleting the char* lies
	*                 with the caller.
	*/
	explicit CValidationException(const char* message) :msg_(message)
	{
	}

	/** Constructor (C++ STL strings).
	*  @param message The error message.
	*/
	explicit CValidationException(const std::string& message) :msg_(message)
	{
	}
	
	/**
	  Setter used for setting exception message
	  @param message The error message.
	*/
	void setExceptionMessage(const std::string& message)
	{
		msg_ = message;
	}

	virtual ~CValidationException() = default;

	/** Returns a pointer to the (constant) error description.
	*  @return A pointer to a const char*.
	*/
	virtual const char* what() const override 
	{
		return msg_.c_str();
	}

protected:
	/** Error message.
	*/
	std::string msg_;
};
#endif
