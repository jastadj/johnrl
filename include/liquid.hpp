#ifndef CLASS_LIQUID
#define CLASS_LIQUID

#include <string>
#include "defs.hpp"

class Liquid
{
private:

    std::string m_Name;

    int m_Color;

    int m_LiquidID; // do not change

public:
    Liquid();
    ~Liquid();
    int getLiquidID() { return m_LiquidID;}
    void setLiquidID(int nid) { m_LiquidID = nid;} // do not use

    std::string getName() { return m_Name;}
    void setName(std::string nname) { m_Name = nname;}

    int getColor() { return m_Color;}
    void setColor(int ncolor);

};
#endif // CLASS_LIQUID
