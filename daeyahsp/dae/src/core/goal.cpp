#include "goal.h"
namespace daex
{
Goal::iterator Goal::iter_at( unsigned int i )
{
    if( i >= this->size() ) {
        std::ostringstream msg;
        msg << "asked for element " << i << " but size of the Goal is " << this->size();
        throw( std::out_of_range( msg.str() ) );
    }
    Goal::iterator it = this->begin();
    std::advance(it,i);
    return it;
}
} 
