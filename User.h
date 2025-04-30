#pragma once

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

    void write(std::string text)
    {
        if(!authenticate(Role::Espectator)){
            std::cout << "Error: User not authenticated.\n";
            return;
        }
        std::cout << text << '\n';
    }

    void rollDice(unsigned short num_sides)
    {
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

    void show_list_of_players()
    {
        if(!authenticate(Role::GameMaster)){
            std::cout << "Error: User not authenticated.\n";
            return;
        }

        if(list_of_players == nullptr){
            std::cout << "Error: list_of_players is null.\n";
            return;
        }

        std::cout << "List of players:\n";
        for(const auto& player : *list_of_players)
            std::cout << player << '\n';
    }

    bool authenticate(Role required_role = Role::GameMaster)
    {
        if(this->role <= required_role)
            return true;
        else
            return false;
    }
};
