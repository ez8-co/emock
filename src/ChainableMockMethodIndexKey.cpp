
#include <mockcpp/ChainableMockMethodIndexKey.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////////
ChainableMockMethodIndexKey::ChainableMockMethodIndexKey(
      unsigned int vptrIndex, unsigned int vtblIndex)
    : index(vptrIndex*MOCKCPP_MAX_VTBL_SIZE + vtblIndex)
{
}

////////////////////////////////////////////////////////////
bool ChainableMockMethodIndexKey::equals(
      const ChainableMockMethodKey* const rhs) const
{
    if(rhs == 0)
    {
       return false;
    }

    if(this == rhs)
    {
       return true;
    }

    ChainableMockMethodIndexKey* key = \
          dynamic_cast<ChainableMockMethodIndexKey*> \
             (const_cast<ChainableMockMethodKey*>(rhs));
    if(key == 0)
    {
       return 0;
    }
     
    return key->getIndex() == this->getIndex();
}

///////////////////////////////////////////////////////////
unsigned int ChainableMockMethodIndexKey::getIndex() const
{
   return index;
}

MOCKCPP_NS_END
