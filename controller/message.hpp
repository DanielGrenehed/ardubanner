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
    std::string message, author;
    int paid;
public:
    Message(int ammount, std::string aMessage, std::string author): message(aMessage), author(author), paid(ammount){}
    
    std::string getText() {return message;}
    std::string getAuthor() {return author;}
    int getAmmount() {return paid;}


};

#endif /* ifndef MESSAGE_HPP */