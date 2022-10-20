#include <iostream>
#include "UserManager.hpp"
#include "exceptions.hpp"

int main(int, char**) {
    mps::UserManager userManager;

    while (true)
    {
        std::cout << "Operations Available:" << std::endl;
        std::cout << "(C)reate an user" << std::endl;
        std::cout << "(R)ead an user" << std::endl;
        std::cout << "(U)pdate an user" << std::endl;
        std::cout << "(D)elete an user" << std::endl;
        std::cout << "(L)ist all users" << std::endl;
        std::cout << "(Q)uit" << std::endl;
        std::cout << "\nWhat do you want to do? (C/R/U/D/L/Q) ";
        std::cout.flush();

        char choice;
        std::cin >> choice;
        std::cin.ignore();

        std::string login;
        std::string pass;
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
            {
                for (const auto& user : userManager)
                {
                    std::cout << user.login() << std::endl;
                }
            }

            break;

            case 'q':
            case 'Q':
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
