#include <iostream>
#include <algorithm>
#include "UserManager.hpp"
#include "TradeManager.hpp"
#include "exceptions.hpp"
#include "business/report/Report.hpp"

int main(int, char**) {
    mps::UserManager& userManager = mps::UserManager::getInstance();
    mps::TradeManager& tradeManager = mps::TradeManager::getInstance();

    while (true)
    {
        std::cout << "Operate on: " << std::endl;
        std::cout << "(U)ser" << std::endl;
        std::cout << "(T)rade" << std::endl;
        std::cout << "(R)eport" << std::endl;
        std::cout << "(Q)uit" << std::endl;
        std::cout << "\nWhat do you want to operate on? (U/T/R/Q) ";
        std::cout.flush();

        char choice;
        std::cin >> choice;
        std::cin.ignore();

        std::string login;
        std::string pass;
        std::vector<std::tuple<std::string, std::string>> userPasswdVec;
        std::vector<std::byte> report_bytes;
        std::string report_str;

        switch (choice)
        {
        case 'U':
        case 'u':
            std::cout << "Operations Available:" << std::endl;
            std::cout << "(C)reate an user" << std::endl;
            std::cout << "(R)ead an user" << std::endl;
            std::cout << "(U)pdate an user" << std::endl;
            std::cout << "(D)elete an user" << std::endl;
            std::cout << "(L)ist all users" << std::endl;
            std::cout << "\nWhat do you want to do? (C/R/U/D/L) ";
            std::cout.flush();

            std::cin >> choice;
            std::cin.ignore();

            switch (choice)
            {
                case 'c':
                case 'C':
                    while (true)
                    {
                        std::cout << "Enter login: ";
                        std::cin >> login;
                        std::cin.ignore();

                        std::cout << "Enter password: ";
                        std::cin >> pass;
                        std::cin.ignore();

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
                    std::cout << "Enter login: ";
                    std::cin >> login;
                    std::cin.ignore();

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
                    std::cout << "Enter login: ";
                    std::cin >> login;
                    std::cin.ignore();

                    while (true) {
                        try
                        {
                            auto& user = userManager.get(login);
                            std::cout << "Enter new password: ";
                            std::cin >> pass;
                            std::cin.ignore();
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
                    std::cout << "Enter login: ";
                    std::cin >> login;
                    std::cin.ignore();

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
            std::cout << "Operations Available:" << std::endl;
            std::cout << "(C)reate a trade" << std::endl;
            std::cout << "(R)ead a trade" << std::endl;
            std::cout << "(L)ist all trades" << std::endl;
            std::cout << "\nWhat do you want to do? (C/R/L) ";
            std::cout.flush();

            std::cin >> choice;
            std::cin.ignore();

            switch (choice)
            {
                case 'c':
                case 'C':
                    std::cout << "Enter amount (without commas): ";
                    int amount;
                    std::cin >> amount;
                    std::cin.ignore();

                    std::cout << "Enter type (B/S): ";
                    char type;
                    std::cin >> type;
                    std::cin.ignore();

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
                    size_t index;
                    std::cout << "Enter index: ";
                    std::cin >> index;
                    std::cin.ignore();


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
            std::cout << "Choose a format to print:" << std::endl;
            std::cout << "(C)SV" << std::endl;
            std::cout << "(H)TML" << std::endl;
            std::cout << "\nYour choice? (C/H) ";
            std::cout.flush();

            std::cin >> choice;
            std::cin.ignore();

            switch (choice)
            {
                case 'c':
                case 'C':
                    std::transform(userManager.begin(), userManager.end(), std::back_inserter(userPasswdVec), [](const mps::User& user) {
                        return std::make_tuple(user.login(), user.pass());
                    });

                    report_bytes = mps::UserReportCSV(userPasswdVec)();
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
                    std::transform(userManager.begin(), userManager.end(), std::back_inserter(userPasswdVec), [](const mps::User& user) {
                        return std::make_tuple(user.login(), user.pass());
                    });

                    report_bytes = mps::UserReportHTML(userPasswdVec)();
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

        std::cout << "\n<Press Enter to continue> ";
        std::cout.flush();
        std::cin.ignore();
    }
}
