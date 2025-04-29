#include <iostream>
#include <memory>
#include <random>

enum class Role
{
    GameMaster, // have access to write, roll dice and include/exclude player
    Player,     // have access to write and roll dice
    Espectator  // have access to write
};

class User
{
private:
    std::string password{};
    std::string email{};
    Role role{};
    std::string name{};
    std::unique_ptr<std::vector<std::string>> list_of_players{nullptr};

public:
    User(std::string name, std::string password, std::string email, Role role) : 
    name(name), password(password), email(email), role(role) {
        if (role == Role::GameMaster)
            list_of_players = std::make_unique<std::vector<std::string>>();
    }

    void write(std::string text)
    {
        std::cout << text << '\n';
    }

    void rollDice(unsigned short num_sides)
    {
        unsigned short num = (std::rand() % (num_sides-1)) + 1;
        std::cout << "Rolled a d" << num_sides << " and got: " << num << '\n';
    }

    void include_player(std::string new_player)
    {
        
    }
};

int main()
{

    return 0;
}