#include <iostream>

#include "User.h"

void choose_user(User*& currentUser, User& gameMaster, User& player, User& espectator);

int main()
{
    // Initialize users for example
    User gameMaster{"Jao", "1@3$J", "jao@mail.com", Role::GameMaster};
    User player{"Gabriela", "1@3$G", "gabriela@mail.com", Role::Player};
    User espectator{"Sara", "1@3$S", "sara@mail.com", Role::Espectator};
    User* currentUser = nullptr;
    
    unsigned short command;
    while(true)
    {
        // If currentUser is nullptr, prompt to choose a user
        if(currentUser == nullptr)
            choose_user(currentUser, gameMaster, player, espectator);
        
        // If currentUser persists as nullptr, skip the loop
        if(currentUser == nullptr)
            continue;
        
        std::cout << "\nEnter a command: " << 
        "\n(1) Write"                    << 
        "\n(2) Roll Dice"                << 
        "\n(3) Show List of Players"     << 
        "\n(4) Include Player\n"         << 
        "(5) Exclude Player"             << 
        "\n(6) Change User"              << 
        "\n(7) Exit\n\n";
        std::cin >> command;
        
        switch(command)
        {
        case 1:
            currentUser->write();
            break;
        case 2:
            currentUser->rollDice();
            break;
        case 3:
            currentUser->show_list_of_players();
            break;
        case 4:
            currentUser->include_player();
            break;
        case 5:
            currentUser->exclude_player();
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

/**
 * @brief Function to choose a user
 */
void choose_user(User*& currentUser, User& gameMaster, User& player, User& espectator)
{
    std::cout << "Select a user:" << 
    "\n(1) " << gameMaster.name   << 
    "\n(2) " << player.name       << 
    "\n(3) " << espectator.name   << "\n";

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
