#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#define MAX_STR_LEN 100;
/*

    Message body(text)
    ammount paid
*/
#include <string>

class Message {
private:
    std::string msg, athr;
    int paid;
public:
    Message(int ammount, std::string message, std::string author): msg(message), athr(author), paid(ammount){}
    
    std::string getText() {return msg;}
    std::string getAuthor() {return athr;}
    int getAmmount() {return paid;}


};

#endif /* ifndef MESSAGE_HPP */