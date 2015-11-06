#ifndef CLASS_MESSAGE
#define CLASS_MESSAGE

#include <string>
#include <vector>

class Message
{
private:
    std:: string m_Message;
    int m_MsgTime;
public:
    Message(std::string nmsg);
    ~Message();

    bool decayTime();
    std::string getString() { return m_Message;}

};

class MessageManager
{
private:
    std::vector<Message*> m_MessageQue;
    std::vector<Message*> m_MessageHistory;

public:
    MessageManager();
    ~MessageManager();

    void addMessage(std::string nmsg);
    void update();

    std::vector<Message*> *getMessageQue() { return &m_MessageQue;}


};

#endif // CLASS_MESSAGE
