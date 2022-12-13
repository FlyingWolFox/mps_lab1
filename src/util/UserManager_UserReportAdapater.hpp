#ifndef USER_MANAGER___USER_REPORT_ADAPTER_HPP
#define USER_MANAGER___USER_REPORT_ADAPTER_HPP

#include "../business/control/UserManager.hpp"
#include "../business/model/User.hpp"

namespace mps
{
	class UserManager_UserReportAdapter
	{
        std::vector<std::tuple<std::string, std::string>> userPasswdVec;
	public:
		UserManager_UserReportAdapter(mps::UserManager& userManager)
		{
			std::transform(userManager.cbegin(), userManager.cend(), std::back_inserter(userPasswdVec), [](const mps::User& user) {
				return std::make_tuple(user.login(), user.pass());
			});
		}

		std::vector<std::tuple<std::string, std::string>> operator()() const
		{
			return userPasswdVec;
		}
	};
}

#endif
