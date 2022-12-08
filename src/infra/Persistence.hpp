#ifndef PERSISTENCE_MPS_HPP
#define PERSISTENCE_MPS_HPP

#include <string>
#include <unordered_map>
#include <vector>

namespace mps {

	template <typename Structure>
	class Persistance
	{
		Structure _structure;
	public:
		Structure& structure() { return _structure; }
		const Structure& structure() const { return _structure; }
	};


	class PersistanceFactory
	{
	public:
		using UserPersistance = Persistance<std::unordered_map<std::string, std::string>>;
		using TradePersistance = Persistance<std::vector<std::tuple<uintmax_t, intmax_t>>>;
	};
}

#endif
