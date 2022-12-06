#ifndef TRADE_MANAGER_MPS_HPP
#define TRADE_MANAGER_MPS_HPP

#include <vector>
#include "../model/Trade.hpp"
#include "Persistence.hpp"

namespace mps {

	class TradeIterator
	{
		std::vector<Trade>::iterator it;
	public:
		TradeIterator(const std::vector<Trade>::iterator& it) : it(it) {};

		TradeIterator& operator++();
		TradeIterator operator++(int);
		bool operator==(const TradeIterator& rhs) const;
		bool operator!=(const TradeIterator& rhs) const;
		const Trade& operator*() const;
		const Trade* operator->() const;
	};

	class TradeManager
	{
		std::vector<Trade> trades;
		TradePersistance persistence;
	public:
		TradeManager() = default;
		~TradeManager() = default;

		void add(const Trade& trade);
		Trade& get(const std::size_t& index);
		TradeIterator begin();
		TradeIterator end();
		const TradeIterator cbegin();
		const TradeIterator cend();
	};
}

#endif
