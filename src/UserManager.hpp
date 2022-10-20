#ifndef USER_MANAGER_MPS_HPP
#define USER_MANAGER_MPS_HPP

#include <string>
#include <unordered_map>
#include "User.hpp"
#include "Persistence.hpp"

namespace mps {
	class UserIterator
	{
		std::unordered_map<std::string, User>::iterator it;
	public:
		UserIterator(const std::unordered_map<std::string, User>::iterator& it) : it(it) {};

		UserIterator& operator++();
		UserIterator operator++(int);
		bool operator==(const UserIterator& rhs) const;
		bool operator!=(const UserIterator& rhs) const;
		const User& operator*() const;
		const User* operator->() const;
	};

	class UserManager {
		std::unordered_map<std::string, User> users;
		Persistence& persistence;
	public:
		UserManager(Persistence& persistence);

		User& add(const std::string& login, const std::string& pass);
		User& add(const User& user);
		void update(User& user, const std::string& pass);
		std::size_t remove(const std::string& login);
		User& get(const std::string& login);
		UserIterator begin();
		UserIterator end();
		const UserIterator cbegin();
		const UserIterator cend();
	};

}


#endif
