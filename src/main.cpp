#include <iostream>
#include <algorithm>
#include "UserManager.hpp"
#include "TradeManager.hpp"
#include "exceptions.hpp"
#include "business/report/Report.hpp"
#include "util/UserManager_UserReportAdapater.hpp"
#include "util/command.hpp"

using namespace std::string_literals;

int main(int, char**) {
    mps::UserManager& userManager = mps::UserManager::getInstance();
    mps::TradeManager& tradeManager = mps::TradeManager::getInstance();

    while (true)
    {
        mps::PrintOptionsCommand{"Operate on:", {"User", "Trade", "Report", "Quit"}}();
        char choice = mps::FormattedInputCommand<char>()();

        std::string login;
        std::string pass;

        std::vector<std::byte> report_bytes;
        std::string report_str;

        switch (choice)
        {
        case 'U':
        case 'u':
            mps::PrintOptionsCommand{
                "Operations Available:", {
                    "Create an user",
                    "Read an user",
                    "Update an user",
                    "Delete an user",
                    "List all users"
                }}();
            choice = mps::FormattedInputCommand<char>()();

            switch (choice)
            {
                case 'c':
                case 'C':
                    while (true)
                    {
                        mps::FormattedOutputCommand("Enter login: "s)();
                        login = mps::FormattedInputCommand<std::string>()();

                        mps::FormattedOutputCommand("Enter password: "s)();
                        pass = mps::FormattedInputCommand<std::string>()();

                        try
                        {
                            userManager.add(login, pass);
                            std::cout << "User created successfully" << std::endl;
                            break;
                        }
                        catch (const mps::UserCreationException& e)
                        {
                            std::cout << "User creation failed: " << e.display_msg() << "\n" << std::endl;
                        }
                    }

                break;

                case 'r':
                case 'R':
                    mps::FormattedOutputCommand("Enter login: "s)();
                    login = mps::FormattedInputCommand<std::string>()();

                    try
                    {
                        mps::User& user = userManager.get(login);
                        std::cout << "User found: \nLogin: " << user.login() << "\nPassword: " << user.pass() << std::endl;
                    }
                    catch (const mps::UserNotFoundException& e)
                    {
                        std::cout << "User not found." << std::endl;
                    }

                break;

                case 'u':
                case 'U':
                    mps::FormattedOutputCommand("Enter login: "s)();
                    login = mps::FormattedInputCommand<std::string>()();

                    while (true) {
                        try
                        {
                            auto& user = userManager.get(login);
                            mps::FormattedOutputCommand("Enter new password: "s)();
                            pass = mps::FormattedInputCommand<std::string>()();
                            userManager.update(user, pass);
                            std::cout << "User updated successfully" << std::endl;
                            break;
                        }
                        catch(const mps::UserNotFoundException& e)
                        {
                            std::cout << "User not found." << std::endl;
                            std::cout << std::endl;
                            break;
                        }
                        catch(const mps::UserPasswordException& e)
                        {
                            std::cout << "User update failed: " << e.display_msg() << std::endl;
                            std::cout << std::endl;
                        }
                    }

                break;

                case 'd':
                case 'D':
                    mps::FormattedOutputCommand("Enter login: "s)();
                    login = mps::FormattedInputCommand<std::string>()();

                    if(userManager.remove(login) == 0)
                    {
                        std::cout << "User not found." << std::endl;
                        continue;
                    }

                    std::cout << "User deleted successfully" << std::endl;

                break;

                case 'l':
                case 'L':
                    for (const auto& user : userManager)
                    {
                        std::cout << user.login() << std::endl;
                    }

                break;

                default:
                    std::cout << "Invalid choice" << std::endl;
                    break;
            }
            break;

        case 'T':
        case 't':
            mps::PrintOptionsCommand{
                "Operations Available:", {
                    "Create a trade",
                    "Read a trade",
                    "List all trades"
                }}();
            choice = mps::FormattedInputCommand<char>()();

            switch (choice)
            {
                case 'c':
                case 'C':
                    mps::FormattedOutputCommand("Enter amount (without commas): "s)();
                    int amount;
                    amount = mps::FormattedInputCommand<int>()();

                    mps::FormattedOutputCommand("Enter type (B/S): "s)();
                    char type;
                    type = mps::FormattedInputCommand<char>()();

                    switch(type)
                    {
                        case 'B':
                        case 'b':
                            tradeManager.add(mps::Buy(amount));
                            break;
                        case 'S':
                        case 's':
                            tradeManager.add(mps::Sell(amount));
                            break;
                        default:
                            std::cout << "Invalid type" << std::endl;
                            continue;
                            break;
                    }

                    std::cout << "Trade created successfully" << std::endl;

                break;

                case 'r':
                case 'R':
                    mps::FormattedOutputCommand("Enter index: "s)();
                    size_t index;
                    index = mps::FormattedInputCommand<size_t>()();

                    try
                    {
                        const mps::Trade& trade = tradeManager.get(index);
                        std::cout << "Trade found: \nType: " << trade.name() << "\nAmount: " << trade.amount() << std::endl;
                    }
                    catch (const std::out_of_range& e)
                    {
                        std::cout << "Trade not found." << std::endl;
                    }
                break;

                case 'l':
                case 'L':
                    for (auto it = tradeManager.begin(); it != tradeManager.end(); ++it)
                    {
                        std::cout << it->name() << " " << it->amount() << std::endl;
                    }
                break;
            }

            break;
        
        case 'R':
        case 'r':
            mps::PrintOptionsCommand{
                "Choose a format to print:", {
                    "CSV",
                    "HTML",
                }}();
            choice = mps::FormattedInputCommand<char>()();

            switch (choice)
            {
                case 'c':
                case 'C':
                    report_bytes = mps::UserReportCSV(mps::UserManager_UserReportAdapter(userManager)())();
                    report_str.reserve(report_bytes.size());
                    std::transform(report_bytes.begin(), report_bytes.end(), std::back_inserter(report_str), [](const std::byte& c) {
                        return (char)c;
                    });

                    std::cout << "START OF FILE" << std::endl;
                    std::cout << report_str << std::endl;
                    std::cout << "END OF FILE" << std::endl;
                    break;

                case 'h':
                case 'H':
                    report_bytes = mps::UserReportHTML(mps::UserManager_UserReportAdapter(userManager)())();
                    report_str.reserve(report_bytes.size());
                    std::transform(report_bytes.begin(), report_bytes.end(), std::back_inserter(report_str), [](const std::byte& c) {
                        return (char)c;
                    });

                    std::cout << "START OF FILE" << std::endl;
                    std::cout << report_str << std::endl;
                    std::cout << "END OF FILE" << std::endl;
                    break;
            }

            break;

        case 'Q':
        case 'q':
            return 0;
        
        default:
            std::cout << "Invalid choice" << std::endl;
            break;
        }

        mps::FormattedOutputCommand("<Press Enter to continue>"s)();
        std::cin.ignore();
    }
}
