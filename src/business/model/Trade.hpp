#include <cinttypes>
#include <string>

namespace mps {
	class Trade
	{
	protected:
		intmax_t _amount;
		std::string trade_name;
	
	public:
		Trade(intmax_t amount, std::string trade_name) : _amount(amount), trade_name(trade_name) {};
		Trade(const Trade& other) : _amount(other._amount), trade_name(other.trade_name) {};
	
		intmax_t amount() const { return _amount; }
		virtual uintmax_t typeId() const { return -1; };
		std::string name() const { return trade_name; };
	};

	class Buy : public Trade
	{
	public:
		Buy(intmax_t amount) : Trade(amount, "Buy") {};
		uintmax_t typeId() const override { return 0; }

	};

	class Sell : public Trade
	{
	public:
		Sell(intmax_t amount) : Trade(amount, "Sell") {};
		uintmax_t typeId() const override { return 1; }
	};

}
