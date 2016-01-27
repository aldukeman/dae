#include "delgoal.h"
namespace daex {
bool MutationDelGoal::operator()( Decomposition & decompo )
{
    if( decompo.size() <= 1 ) {
        return false;
    } else {
#ifndef NDEBUG
        eo::log << eo::debug << "D";
        eo::log.flush();
        eo::log << eo::xdebug << " DelGoal:" << std::endl << "\tBefore: ";
        simplePrint( eo::log << eo::xdebug, decompo );
#endif
        unsigned int i = rng.random( std::min( static_cast<unsigned int>(decompo.size()), static_cast<unsigned int>(decompo.last_reached() + 1) ) );
        decompo.erase( decompo.iter_at( i ) );
#ifndef NDEBUG
        eo::log << eo::xdebug << "\tdelete the " << i << "th goal" << std::endl;
        eo::log << eo::xdebug << "\tAfter: ";
        simplePrint( eo::log << eo::xdebug, decompo );
#endif
        return true;
    }
}
} 
