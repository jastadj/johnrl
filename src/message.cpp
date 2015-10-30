#include "message.hpp"
#include "engine.hpp"

Message::Message(std::string nmsg)
{
    m_Message = nmsg;
    m_MsgTime = 4;
}

Message::~Message()
{

}

bool Message::decayTime()
{
    if(m_MsgTime > 0)
    {
        m_MsgTime--;
        return true;
    }
    else return false;
}

//////////////////////////////////////////////////////////////
MessageManager::MessageManager()
{

}

MessageManager::~MessageManager()
{
    //delete all messages
    for(int i = 0; i < int(m_MessageHistory.size()); i++) delete m_MessageHistory[i];
    m_MessageHistory.clear();
    for(int i = 0; i < int(m_MessageQue.size()); i++) delete m_MessageQue[i];
    m_MessageQue.clear();
}

void MessageManager::update()
{
    for(int i = int(m_MessageQue.size()); i >= 0; i --)
    {
        //if message time is 0, remove from que and move to message history
        if( !m_MessageQue[i]->decayTime() )
        {
            m_MessageHistory.push_back( m_MessageQue[i]);
            m_MessageQue.erase( m_MessageQue.begin() + i);
        }
    }
}

void MessageManager::addMessage(std::string nmsg)
{
    m_MessageQue.push_back(new Message(nmsg));
}
