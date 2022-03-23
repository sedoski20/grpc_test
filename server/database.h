#ifndef DATABASE_H
#define DATABASE_H

#include "string"
    
class User
{
    public:
    User(std::string name, 
        std::string cpf,
        std::string email,
        std::string address);

    
    std::string name;
    std::string cpf;
    std::string email;
    std::string address;
};

 const static User users[10] = 
{
    User("Marcelo", "001", "abc@abc.com", "Stree A, 01 - Brazil"),
    User("Anna",    "002", "abc@abc.com", "Stree A, 01 - Brazil"),
    User("Joaquim", "003", "abc@abc.com", "Stree A, 01 - Brazil"),
    User("Jose",    "004", "abc@abc.com", "Stree A, 01 - Brazil"),
    User("Pedro",   "005", "abc@abc.com", "Stree A, 01 - Brazil"),
    User("Bruna",   "006", "abc@abc.com", "Stree A, 01 - Brazil"),
    User("Thais",   "007", "abc@abc.com", "Stree A, 01 - Brazil"),
    User("Rafael",  "008", "abc@abc.com", "Stree A, 01 - Brazil"),
    User("Ricardo", "009", "abc@abc.com", "Stree A, 01 - Brazil"),
    User("Andrea",  "010", "abc@abc.com", "Stree A, 01 - Brazil")
};

#endif // DATABASE_H
