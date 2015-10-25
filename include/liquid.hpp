#ifndef CLASS_LIQUID
#define CLASS_LIQUID

#include <string>
#include "defs.hpp"

class Liquid
{
private:

    std::string m_Name;

    int m_Color;

public:
    Liquid();
    ~Liquid();

    std::string getName() { return m_Name;}
    void setName(std::string nname) { m_Name = nname;}

    int getColor() { return m_Color;}
    void setColor(int ncolor);

};
#endif // CLASS_LIQUID
