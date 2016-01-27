#include <algorithm>
#include <ostream>
#include "delatom.h"
namespace daex {
bool MutationDelAtom::operator()( Decomposition & decompo )
{
#ifndef NDEBUG
    eo::log << eo::debug << "d";
    eo::log.flush();
    eo::log << eo::xdebug << " DelAtom:" << std::endl << "\tBefore: ";
    simplePrint( eo::log << eo::xdebug, decompo );
#endif
    if( decompo.empty() ) {
        return false;
    }
    bool is_modified;
    Decomposition::iterator igoal = decompo.begin();
    int unreach_goal = std::min( 
                static_cast<unsigned int>(decompo.size()), 
                static_cast<unsigned int>( decompo.last_reached() ) + 1 
                );
#ifndef NDEBUG
    eo::log << eo::xdebug << "\tunreached goal: " << unreach_goal << std::endl;
#endif
    int i = 0;
    while( i < unreach_goal ) {
        if( igoal->size() > 1 
              && 
            rng.flip( _proba_del_atom / decompo.size() ) 
          ) {
 #ifndef NDEBUG
            unsigned int j = rng.random( igoal->size() );
            eo::log << eo::xdebug << "\tdelete the " << j << "th atom in the " << i << "th goal" << std::endl;
            eo::log << eo::xdebug << "\t\tBefore: " << *igoal << std::endl;
            igoal->erase( igoal->iter_at( j ) );
            eo::log << eo::xdebug << "\t\t After: " << *igoal << std::endl;
#else
            igoal->erase(
                    igoal->iter_at(
                        rng.random( igoal->size() ) 
                    )
                );
#endif
            is_modified = true;
        }
        igoal++;
        i++;
    } 
#ifndef NDEBUG
        eo::log << eo::xdebug << "\t After: ";
        simplePrint( eo::log << eo::xdebug, decompo );
#endif
    return is_modified;
}
bool MutationDelOneAtom::operator()( Decomposition & decompo )
{
#ifndef NDEBUG
    eo::log << eo::debug << "d";
    eo::log.flush();
#endif
    assert( !decompo.empty() );
    int range;
    if( decompo.invalid() ) {
        range = decompo.size();
    } else {
        range = std::min( 
                static_cast<unsigned int>(decompo.size()), 
                static_cast<unsigned int>( decompo.last_reached() ) + 1 
                );
    }
    unsigned int i = rng.random( range );
    Decomposition::iterator goal_i = decompo.iter_at(i);
    if( goal_i->size() <= 1 ) {
        return false;
    } else {
        unsigned int a = rng.random( goal_i->size() );
        goal_i->erase( goal_i->iter_at( a ) );
        return true;
    } 
}
} 
