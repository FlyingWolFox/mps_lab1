#ifndef PERSISTENCE_MPS_HPP
#define PERSISTENCE_MPS_HPP

#include <string>
#include <unordered_map>
#include <vector>

namespace mps {
	class Persistence
	{
		std::unordered_map<std::string, std::string> _users;
	public:
		std::unordered_map<std::string, std::string>& users() { return _users; }
		const std::unordered_map<std::string, std::string>& users() const { return _users; }
	};

	class TradePersistance
	{
		std::vector<std::tuple<uintmax_t, intmax_t>> _trades;
	public:
		std::vector<std::tuple<uintmax_t, intmax_t>>& trades() { return _trades; }
		const std::vector<std::tuple<uintmax_t, intmax_t>>& trades() const { return _trades; }
	};

}

#endif
