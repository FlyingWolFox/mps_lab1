#include "UserManager.hpp"
#include "exceptions.hpp"

using namespace mps;

UserIterator &UserIterator::operator++()
{
	++it;
	return *this;
}

UserIterator UserIterator::operator++(int)
{
	UserIterator tmp(*this);
	operator++();
	return tmp;
}

bool UserIterator::operator==(const UserIterator &rhs) const { return it == rhs.it; }

bool UserIterator::operator!=(const UserIterator &rhs) const { return it != rhs.it; }

const User &UserIterator::operator*() const { return it->second; }

const User *UserIterator::operator->() const { return &it->second; }


void check_login(const std::string& login)
{
	if (login.empty())
		throw UserLoginException("Empty login", "Login cannot be empty");
	if (login.length() > 12)
		throw UserLoginException("Login too long", "Login cannot be longer than 12 characters");
	if (login.find_first_of("0123456789") != std::string::npos)
		throw UserLoginException("Login contains digits", "Login cannot contain digits");
}

void check_password(const std::string& pass)
{
	if (pass.empty())
		throw UserPasswordException("Empty password", "Password cannot be empty");
	if (pass.length() > 20)
		throw UserPasswordException("Password too long", "Password cannot be longer than 20 characters");
	if (pass.length() < 8)
		throw UserPasswordException("Password too short", "Password cannot be shorter than 8 characters");
	if (pass.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == pass.find_last_of("0123456789"))
		throw UserPasswordException("Password doesn't have a letter", "Password must contain at least a letter");
	if (pass.find_first_of("0123456789") == pass.find_last_of("0123456789"))
		throw UserPasswordException("Password contains less than two digits", "Password must contain at least two digits");
}

User& UserManager::add(const std::string &login, const std::string &pass)
{
	check_login(login);
	check_password(pass);

	auto[_it, inserted] = users.emplace(login, User(login, pass));
	if (!inserted)
		throw UserAlreadyExistsException("User already exists", "User already exists");

	this->persistence.users().emplace(login, pass); 
	return _it->second;
}

void UserManager::update(User& user, const std::string& pass)
{
	check_password(pass);
	user.pass() = pass;
	this->persistence.users().at(user.login()) = pass;
}

User& UserManager::add(const User& user)
{
	return add(user.login(), user.pass());
}

std::size_t UserManager::remove(const std::string &login)
{
	return users.erase(login);
}

User& UserManager::get(const std::string &login)
{
	try
	{
		return users.at(login);
	}
	catch (std::out_of_range& e)
	{
		throw UserNotFoundException("User not found");
	}
}

UserIterator UserManager::begin()
{
	return UserIterator(users.begin());
}

UserIterator UserManager::end()
{
	return UserIterator(users.end());
}

const UserIterator UserManager::cbegin()
{
	return UserIterator(users.begin());
}

const UserIterator UserManager::cend()
{
	return UserIterator(users.end());
}