#include <iostream>
#include <memory>
#include <random>
#include <vector>
#include <algorithm>

enum class Role
{
    GameMaster=0, // have access to write, roll dice and include/exclude player
    Player=1,     // have access to write and roll dice
    Espectator=2  // have access to write
};

class User
{
private:
    std::string password{};
    std::string email{};
    Role role{};
    std::unique_ptr<std::vector<std::string>> list_of_players{nullptr};
    
public:
    std::string name{};

    User(std::string name, std::string password, std::string email, Role role) : 
    name(name), password(password), email(email), role(role) {
        if (role == Role::GameMaster)
            list_of_players = std::make_unique<std::vector<std::string>>();
    }

    void write(std::string text){
        if(!authenticate(Role::Espectator)){
            std::cout << "Error: User not authenticated.\n";
            return;
        }
        std::cout << text << '\n';
    }

    void rollDice(unsigned short num_sides){
        if(!authenticate(Role::Player)){
            std::cout << "Error: User not authenticated.\n";
            return;
        }
        unsigned short num = (std::rand() % (num_sides-1)) + 1;
        std::cout << "Rolled a d" << num_sides << " and got: " << num << '\n';
    }

    void include_player(std::string new_player)
    {
        if(!authenticate(Role::GameMaster)){
            std::cout << "Error: User not authenticated.\n";
            return;
        }

        if(list_of_players == nullptr){
            std::cout << "Error: list_of_players is null.\n";
            return;
        }

        if(new_player.empty()){
            std::cout << "Error: Player name cannot be empty.\n";
            return;
        }

        auto it = std::find(list_of_players->begin(), list_of_players->end(), new_player);
        if(it == list_of_players->end()){
            list_of_players->push_back(new_player);
            std::cout << new_player << " included in the game.\n";
        }
        else
            std::cout << new_player << " is already in the game.\n";
    }

    void exclude_player(std::string player)
    {
        if(!authenticate(Role::GameMaster)){
            std::cout << "Error: User not authenticated.\n";
            return;
        }

        if(list_of_players == nullptr){
            std::cout << "Error: list_of_players is null.\n";
            return;
        }

        auto it = std::find(list_of_players->begin(), list_of_players->end(), player);
        if(it != list_of_players->end()){
            list_of_players->erase(it);
            std::cout << player << " excluded from the game.\n";
        }
        else
            std::cout << player << " is not in the game.\n";
    }

    bool authenticate(Role required_role = Role::GameMaster)
    {
        if(this->role <= required_role)
            return true;
        else
            return false;
    }
};

void choose_user(User*& currentUser, User& gameMaster, User& player, User& espectator);

int main()
{
    User gameMaster{"Jao", "1@3$J", "jao@mail.com", Role::GameMaster};
    User player{"Gabriela", "1@3$G", "gabriela@mail.com", Role::Player};
    User espectator{"Sara", "1@3$S", "sara@mail.com", Role::Espectator};
    User* currentUser = nullptr;
    
    while(true)
    {
        choose_user(currentUser, gameMaster, player, espectator);
        if(currentUser == nullptr)
            continue;
        
        std::cout << "Enter a command: \n(1) Write\n(2) Roll Dice\n(3) Include Player\n(4) Exclude Player\n(5) Change User\n(6) Exit\n";
        unsigned short command;
        std::cin >> command;
        
        std::string text, new_player;
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
            std::cout << "Enter player name to include: ";
            std::cin >> new_player;
            currentUser->include_player(new_player);
            break;
        case 4:
            std::cout << "Enter player name to exclude: ";
            std::cin >> new_player;
            currentUser->exclude_player(new_player);
            break;
        case 5:
            std::cout << "Changing user...\n";
            currentUser = nullptr;
            break;
        case 6:
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