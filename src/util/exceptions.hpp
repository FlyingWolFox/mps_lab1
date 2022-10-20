#ifndef EXCEPTIONS_MPS_HPP
#define EXCEPTIONS_MPS_HPP

#include <stdexcept>
#include <string>

namespace mps {
	class UserCreationException : public std::invalid_argument
	{
		const std::string _display_msg;
	public:
		UserCreationException(const std::string &msg, const std::string& display_msg) : std::invalid_argument(msg), _display_msg(display_msg) {}
		const std::string& display_msg() const { return _display_msg; }
	};

	class UserLoginException : public UserCreationException
	{
		using UserCreationException::UserCreationException;
	};

	class UserPasswordException : public UserCreationException
	{
		using UserCreationException::UserCreationException;
	};

	class UserAlreadyExistsException : public UserCreationException
	{
		using UserCreationException::UserCreationException;
	};


	class UserNotFoundException : public std::out_of_range
	{
		using std::out_of_range::out_of_range;
	};

}

#endif
