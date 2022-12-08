#ifndef RELATORY_MPS_HPP
#define RELATORY_MPS_HPP

#include <cstddef>
#include <vector>
#include <string>

namespace mps {
	class UserReport
	{
	public:
		using byteVector = std::vector<std::byte>;
		UserReport(std::vector<std::tuple<std::string, std::string>> userPasswdVector) : userPasswdVector(userPasswdVector) {};
		byteVector operator()();
	protected:
		std::vector<std::tuple<std::string, std::string>> userPasswdVector;
		byteVector wipReport;

		virtual void writeHeader() = 0;
		virtual void writeBody() = 0;
		virtual void writeFooter() = 0;
	};

	class UserReportCSV : public UserReport
	{
	public:
		UserReportCSV(std::vector<std::tuple<std::string, std::string>> userPasswdVector) : UserReport(userPasswdVector) {};
	protected:
		void writeHeader() override;
		void writeBody() override;
		void writeFooter() override;
	};

	class UserReportHTML : public UserReport
	{
	public:
		UserReportHTML(std::vector<std::tuple<std::string, std::string>> userPasswdVector) : UserReport(userPasswdVector) {};
	protected:
		void writeHeader() override;
		void writeBody() override;
		void writeFooter() override;
	};

}

#endif
