#ifndef COMMAND_MPS_HPP
#define COMMAND_MPS_HPP

#include <string>
#include <initializer_list>

namespace mps {
	template <typename ReturnType = void>
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual ReturnType operator()() = 0;
	};

	template <typename ReturnType>
	class FormattedInputCommand : public Command<ReturnType>
	{
	public:
		ReturnType operator()() override
		{
			ReturnType c;
			std::cin >> c;
			std::cin.ignore();
			return c;
		}
	};

	template <typename OutputType>
	class FormattedOutputCommand : public Command<void>
	{
		OutputType output;
	public:
		FormattedOutputCommand(const OutputType& output) : output(output) {}
		void operator()() override
		{
			std::cout << output;
			std::cout.flush();
		}
	};

	class PrintOptionsCommand : public Command<void>
	{
		std::string header;
		std::vector<char> optionsInitials;
		std::vector<std::string> optionsNoInitials;
	public:
		PrintOptionsCommand(const std::string& header, const std::initializer_list<std::string>& options) : header(header)
		{
			for (const auto& option : options)
			{
				optionsInitials.push_back(option[0]);
				optionsNoInitials.emplace_back(option.begin() + 1, option.end());
			}
		}
		void operator()() override
		{
			std::cout << header << std::endl;
			for (size_t i = 0; i < optionsInitials.size(); ++i)
				std::cout << "(" << optionsInitials[i] << ")" << optionsNoInitials[i] << std::endl;
			std::cout << "\nYour choice? (";
			std::cout << optionsInitials[0];
			for (size_t i = 1; i < optionsInitials.size(); ++i)
				std::cout << '/' << optionsInitials[i];
			std::cout << ") ";
			std::cout.flush();
		}
	};
}

#endif
