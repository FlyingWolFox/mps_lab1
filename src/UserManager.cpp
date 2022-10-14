#include "UserManager.hpp"
#include <stdexcept>

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
	if (login.empty())
		throw std::invalid_argument("Empty login");
	if (login.length() > 12)
		throw std::invalid_argument("Login too long");
	// TODO: uh, can login contain spaces/symbols?
	if (login.find_first_of("0123456789") != std::string::npos)
		throw std::invalid_argument("Login contains digits");

	if (pass.empty())
		throw std::invalid_argument("Empty password");
	if (pass.length() > 20)
		throw std::invalid_argument("Password too long");
	if (pass.length() < 8)
		throw std::invalid_argument("Password too short");
	if (pass.find_first_of("0123456789") == pass.find_last_of("0123456789"))
		throw std::invalid_argument("Password contains less than two digits");
	if (pass.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != std::string::npos)
		throw std::invalid_argument("Password contains invalid symbols");

	users.emplace(login, User(login, pass));
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
