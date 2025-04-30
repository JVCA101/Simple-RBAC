#include <iostream>

#include "User.h"

void choose_user(User*& currentUser, User& gameMaster, User& player, User& espectator);

int main()
{
    User gameMaster{"Jao", "1@3$J", "jao@mail.com", Role::GameMaster};
    User player{"Gabriela", "1@3$G", "gabriela@mail.com", Role::Player};
    User espectator{"Sara", "1@3$S", "sara@mail.com", Role::Espectator};
    User* currentUser = nullptr;
    
    unsigned short command;
    std::string text, new_player;
    while(true)
    {
        choose_user(currentUser, gameMaster, player, espectator);
        if(currentUser == nullptr)
            continue;
        
        std::cout << "Enter a command: \n(1) Write\n(2) Roll Dice\n(3) Show List of Players\n(4) Include Player\n" << 
        "(5) Exclude Player\n(6) Change User\n(7) Exit\n";
        std::cin >> command;
        
        text.clear();
        new_player.clear();
        switch(command)
        {
        case 1:
            std::cout << "Enter text to write: ";
            std::cin.ignore();
            std::getline(std::cin, text);
            currentUser->write(text);
            break;
        case 2:
            std::cout << "Enter number of sides for the dice: ";
            unsigned short num_sides;
            std::cin >> num_sides;
            currentUser->rollDice(num_sides);
            break;
        case 3:
            std::cout << "Showing list of players:\n";
            currentUser->show_list_of_players();
            break;
        case 4:
            std::cout << "Enter player name to include: ";
            std::cin >> new_player;
            currentUser->include_player(new_player);
            break;
        case 5:
            std::cout << "Enter player name to exclude: ";
            std::cin >> new_player;
            currentUser->exclude_player(new_player);
            break;
        case 6:
            std::cout << "Changing user...\n";
            currentUser = nullptr;
            break;
        case 7:
            std::cout << "Exiting...\n";
            return 0;
        default:
            std::cout << "Invalid command.\n";
            break;
        }
    }
    return 0;
}

void choose_user(User*& currentUser, User& gameMaster, User& player, User& espectator)
{
    if(currentUser == nullptr)
    {
        std::cout << "Select a user:\n(1) " << gameMaster.name << "\n(2) " << player.name << "\n(3) " << espectator.name << "\n";
        unsigned short user;
        std::cin >> user;
        switch(user)
        {
            case 1:
            currentUser = &gameMaster;
            break;
            case 2:
            currentUser = &player;
            break;
            case 3:
            currentUser = &espectator;
            break;
            default:
            std::cout << "Invalid user.\n";
            break;
        };
    }
}
