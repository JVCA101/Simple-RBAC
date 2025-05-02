#pragma once

#include <iostream>
#include <memory>
#include <random>
#include <vector>
#include <algorithm>

// the lower the number, the higher the priority
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

    /**
     * * @brief Function to authenticate the user
     * * @details This function checks if the user has the required role to perform an action.
     * * @param required_role Minimal role required to perform the action. Default is GameMaster.
     * * @return true if the user has the required role, false otherwise.
     */
    bool authenticate(Role required_role = Role::GameMaster)
    {
        if(this->role <= required_role)
            return true;
        else
            return false;
    }
    
public:
    std::string name{};

    User(std::string name, std::string password, std::string email, Role role) : 
    name(name), password(password), email(email), role(role) {
        if (role == Role::GameMaster)
            list_of_players = std::make_unique<std::vector<std::string>>();
    }

    /**
     * * @brief Function to write a message
     * * @details This function allows the user to write a message. The message must be between 0 and 100 characters. Everyone can write.
     */
    void write()
    {
        // Authenticate the user using RBAC
        if(!authenticate(Role::Espectator)){
            std::cout << "Error: User not authenticated.\n";
            return;
        }
        std::string text;
        std::cout << "Write text between 1 and 100 characters: ";
        std::cin.ignore();
        std::getline(std::cin, text);

        // Check if the text is empty or exceeds 100 characters
        if(text.empty()){
            std::cout << "Error: Text cannot be empty.\n";
            return;
        }
        if(text.length() > 100){
            std::cout << "Error: Text length exceeds 100 characters.\n";
            return;
        }

        // Print the message
        std::cout << this->name << ": " << text << '\n';
    }

    /**
     * * @brief Function to roll a dice
     * * @details This function allows the user to roll a dice. The number of sides must be greater than 0 and lower than 100. Espectators cannot roll the dice.
     */
    void rollDice()
    {
        // Authenticate the user using RBAC
        if(!authenticate(Role::Player)){
            std::cout << "Error: User not authenticated.\n";
            return;
        }

        // User input for number of sides
        short num_sides;
        std::cout << "Enter number of sides for the dice (2-100): ";
        std::cin >> num_sides;

        // Check if the number of sides is valid
        if(num_sides <= 1 || num_sides > 100){
            std::cout << "Error: Number of sides must be between 2 and 100.\n";
            return;
        }

        // Randomize the number
        short num = (std::rand() % (num_sides-1)) + 1;
        std::cout << "Rolled a d" << num_sides << " and got: " << num << '\n';
    }

    /**
     * * @brief Function to include a player
     * * @details This function allows the GameMaster to include a player in the game. The player must not be already in the game.
     */
    void include_player()
    {
        // Authenticate the user using RBAC
        if(!authenticate(Role::GameMaster)){
            std::cout << "Error: User not authenticated.\n";
            return;
        }

        // Check if the list of players is null
        if(list_of_players == nullptr){
            std::cout << "Error: list_of_players is null.\n";
            return;
        }

        // User input for new player name
        std::string new_player;
        std::cout << "Enter player name to include: ";
        std::cin.ignore();
        std::getline(std::cin, new_player);

        // Check if the new player name is empty
        if(new_player.empty()){
            std::cout << "Error: Player name cannot be empty.\n";
            return;
        }

        // Check if the new player is already in the game
        // if the player is not in the game, it will return an iterator to the end of the vector
        auto it = std::find(list_of_players->begin(), list_of_players->end(), new_player);
        
        if(it == list_of_players->end()){
            list_of_players->push_back(new_player);
            std::cout << new_player << " included in the game.\n";
        }
        else
            std::cout << new_player << " is already in the game.\n";
    }

    /**
     * * @brief Function to exclude a player
     * * @details This function allows the GameMaster to exclude a player from the game. The player must be already in the game.
     */
    void exclude_player()
    {
        // Authenticate the user using RBAC
        if(!authenticate(Role::GameMaster)){
            std::cout << "Error: User not authenticated.\n";
            return;
        }

        // Check if the list of players is null
        if(list_of_players == nullptr){
            std::cout << "Error: list_of_players is null.\n";
            return;
        }

        // User input for player name to exclude
        std::string player;
        std::cout << "Enter player name to exclude: ";
        std::cin.ignore();
        std::getline(std::cin, player);

        // Check if the player name is empty
        if(player.empty()){
            std::cout << "Error: Player name cannot be empty.\n";
            return;
        }

        // Check if the player is in the game
        // if the player is not in the game, it will return an iterator to the end of the vector
        auto it = std::find(list_of_players->begin(), list_of_players->end(), player);

        if(it != list_of_players->end()){
            list_of_players->erase(it);
            std::cout << player << " excluded from the game.\n";
        }
        else
            std::cout << player << " is not in the game.\n";
    }

    /**
     * * @brief Function to show the list of players
     * * @details This function shows the list of players in the game. The GameMaster can see the list of players.
     */
    void show_list_of_players()
    {
        // Authenticate the user using RBAC
        if(!authenticate(Role::GameMaster)){
            std::cout << "Error: User not authenticated.\n";
            return;
        }

        // Check if the list of players is null
        if(list_of_players == nullptr){
            std::cout << "Error: list_of_players is null.\n";
            return;
        }

        // Check if the list of players is empty
        if(list_of_players->empty()){
            std::cout << "Error: list_of_players is empty.\n";
            return;
        }

        // Print the list of players
        std::cout << "List of players:\n";
        for(const auto& player : *list_of_players)
            std::cout << player << '\n';
    }
};
