#ifndef MESSAGE_HPP
#define MESSAGE_HPP

/*

    Message body(text)
    ammount paid
*/
#include <string>

class Message {
private:
    std::string msg;
    int paid;
public:
    Message(int ammount, std::string message): msg(message), paid(ammount){}
    
    std::string getText() {return msg;}
    int getAmmount() {return paid;}

};

#endif /* ifndef MESSAGE_HPP */