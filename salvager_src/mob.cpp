#include "mob.hpp"

Mob::Mob()
{
    //
    mName = "unnamed";
    mIcon = '?';
    mDefaultBehavior = AI_NONE;

}

Mob::~Mob()
{

}

MobRef::MobRef(Mob *nref)
{
    mRef = nref;
}

MobRef::~MobRef()
{

}
