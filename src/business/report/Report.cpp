#include "Report.hpp"

#include <algorithm>

using namespace mps;

void UserReportCSV::writeHeader()
{
	std::string header = "User,Password\n";
	wipReport.reserve(header.size());
	std::transform(header.begin(), header.end(), std::back_inserter(wipReport), [](char c) { return std::byte(c); });
}

void UserReportCSV::writeBody()
{
	for (auto& [user, passwd] : userPasswdVector)
	{
		std::string line = user + "," + passwd + "\n";
		wipReport.reserve(wipReport.size() + line.size());
		std::transform(line.begin(), line.end(), std::back_inserter(wipReport), [](char c) { return std::byte(c); });
	}
}

void UserReportCSV::writeFooter()
{
}

void UserReportHTML::writeHeader()
{
	std::string header = "<html><head><title>Users</title></head><body><table><tr><th>User</th><th>Password</th></tr>\n";
	wipReport.reserve(header.size());
	std::transform(header.begin(), header.end(), std::back_inserter(wipReport), [](char c) { return std::byte(c); });
}

void UserReportHTML::writeBody()
{
	for (auto& [user, passwd] : userPasswdVector)
	{
		std::string line = "<tr><td>" + user + "</td><td>" + passwd + "</td></tr>\n";
		wipReport.reserve(wipReport.size() + line.size());
		std::transform(line.begin(), line.end(), std::back_inserter(wipReport), [](char c) { return std::byte(c); });
	}
}

void UserReportHTML::writeFooter()
{
	std::string footer = "</table></body></html>\n";
	wipReport.reserve(wipReport.size() + footer.size());
	std::transform(footer.begin(), footer.end(), std::back_inserter(wipReport), [](char c) { return std::byte(c); });
}

UserReport::byteVector UserReport::operator()()
{
	writeHeader();
	writeBody();
	writeFooter();
	return wipReport;
}
