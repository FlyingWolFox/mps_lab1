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
		UserIterator(std::unordered_map<std::string, User>::iterator it) : it(it) {};

		UserIterator& operator++();
		UserIterator operator++(int);
		bool operator==(const UserIterator& rhs);
		bool operator!=(const UserIterator& rhs);
		const User& operator*();
		const User* operator->();
	};

	class UserManager {
		std::unordered_map<std::string, User> users;
		Persistence& persistence;
	public:
		UserManager(Persistence& persistence);

		void add(const std::string& login, const std::string& pass);
		void remove(const std::string& login);
		User& get(const std::string& login);
		UserIterator getAll();
	};

}


#endif
