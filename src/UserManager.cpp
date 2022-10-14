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

bool UserIterator::operator==(const UserIterator &rhs) { return it == rhs.it; }

bool UserIterator::operator!=(const UserIterator &rhs) { return it != rhs.it; }

const User &UserIterator::operator*() { return it->second; }

const User *UserIterator::operator->() { return &it->second; }


UserManager::UserManager(Persistence& persistence) : users(), persistence(persistence)
{
	for (auto& user : persistence.users())
	{
		users.insert_or_assign(user.first, User(user.first, user.second));
	}
}

void UserManager::add(const std::string &login, const std::string &pass)
{
	// TODO: should we use just one message instead of two?
	if (login.empty())
		throw UserLoginException("Empty login", "Login cannot be empty");
	if (login.length() > 12)
		throw UserLoginException("Login too long", "Login cannot be longer than 12 characters");
	// TODO: uh, can login contain spaces/symbols?
	if (login.find_first_of("0123456789") != std::string::npos)
		throw UserLoginException("Login contains digits", "Login cannot contain digits");

	if (pass.empty())
		throw UserPasswordException("Empty password", "Password cannot be empty");
	if (pass.length() > 20)
		throw UserPasswordException("Password too long", "Password cannot be longer than 20 characters");
	if (pass.length() < 8)
		throw UserPasswordException("Password too short", "Password cannot be shorter than 8 characters");
	if (pass.find_first_of("0123456789") == pass.find_last_of("0123456789"))
		throw UserPasswordException("Password contains less than two digits", "Password must contain at least two digits");
	if (pass.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != std::string::npos)
		throw UserPasswordException("Password contains invalid symbols", "Password can only contain letters and digits");

	auto[_it, inserted] = users.emplace(login, User(login, pass));
	if (!inserted)
		throw UserAlreadyExistsException("User already exists", "User already exists");
}

void UserManager::remove(const std::string &login)
{
	users.erase(login);
}

User& UserManager::get(const std::string &login)
{
	return users.at(login);
}

UserIterator UserManager::getAll()
{
	return UserIterator(users.begin());
}
