#ifndef PERSISTENCE_MPS_HPP
#define PERSISTENCE_MPS_HPP

#include <string>
#include <unordered_map>

namespace mps {
	class Persistence
	{
		std::unordered_map<std::string, std::string> _users;
	public:
		std::unordered_map<std::string, std::string>& users() { return _users; }
		const std::unordered_map<std::string, std::string>& users() const { return _users; }
	};

}

#endif
