#include <cinttypes>

namespace mps {
	class Trade
	{
	protected:
		intmax_t _amount;
	
	public:
		Trade(intmax_t amount) : _amount(amount) {};
		Trade(const Trade& other) : _amount(other._amount) {};
		virtual ~Trade() = default;
	
		intmax_t amount() const { return _amount; }
		virtual uintmax_t typeId() const { return -1; };
	};

	class Buy : public Trade
	{
	public:
		Buy(intmax_t amount) : Trade(amount) {};
		uintmax_t typeId() const override { return 0; }
	};

	class Sell : public Trade
	{
	public:
		Sell(intmax_t amount) : Trade(amount) {};
		uintmax_t typeId() const override { return 1; }
	};

}
