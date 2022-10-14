#ifndef USER_MPS_HPP
#define USER_MPS_HPP

#include <string>

namespace mps
{
	class User
	{
		std::string _login;
		std::string _pass;
	public:
		User(const std::string& login, const std::string& pass) : _login(login), _pass(pass) {};

		std::string& login() { return _login; }
		const std::string& login() const { return _login; }
		std::string& pass() { return _pass; }
		const std::string& pass() const { return _pass; }
	};

	class StandardUser : public User
	{
	public:
		StandardUser(std::string login, std::string pass) : User(login, pass) {};
	};

	class AdminUser : public User
	{
	public:
		AdminUser(std::string login, std::string pass) : User(login, pass) {};
	};
}

#endif
