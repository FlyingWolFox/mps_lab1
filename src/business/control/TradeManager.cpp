#include "TradeManager.hpp"

using namespace mps;

TradeIterator& TradeIterator::operator++()
{
	++it;
	return *this;
}

TradeIterator TradeIterator::operator++(int)
{
	TradeIterator tmp(*this);
	operator++();
	return tmp;
}

bool TradeIterator::operator==(const TradeIterator& rhs) const { return it == rhs.it; }

bool TradeIterator::operator!=(const TradeIterator& rhs) const { return it != rhs.it; }

const Trade& TradeIterator::operator*() const { return *it; }

const Trade* TradeIterator::operator->() const { return &(*it); }



void TradeManager::add(const Trade& trade)
{
	trades.push_back({trade});
	this->persistence.trades().emplace_back(trade.typeId(), trade.amount());
}

Trade& TradeManager::get(const std::size_t& index)
{
	return trades.at(index);
}

TradeIterator TradeManager::begin() { return TradeIterator(trades.begin()); }

TradeIterator TradeManager::end() { return TradeIterator(trades.end()); }

const TradeIterator TradeManager::cbegin() { return TradeIterator(trades.begin()); }

const TradeIterator TradeManager::cend() { return TradeIterator(trades.end()); }

