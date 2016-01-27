#include <eo>
#include "core/decomposition.h"
namespace daex {
class CrossOver : public eoQuadOp<Decomposition>
{
public:
    bool operator()( Decomposition & decompo1, Decomposition & decompo2 )
    {
        if( decompo1.empty() || decompo2.empty() ) {
            return false;
        }
        Decomposition::iterator decompo1_middle = decompo1.begin();
        std::advance( decompo1_middle, rng.random( decompo1.size() ) );
        Decomposition::iterator decompo2_middle = decompo2.begin();
        std::advance( decompo2_middle, rng.random( decompo2.size() ) );
        TimeVal d1 = decompo1_middle->earliest_start_time();
        TimeVal d2 = decompo2_middle->earliest_start_time();
        if( d2 > d1 ) {
            decompo1.erase( decompo1_middle, decompo1.end() );
            std::copy( decompo2_middle, decompo2.end(), std::back_inserter( decompo1 ) );
        } else {
            decompo1.erase( decompo1.begin(), decompo1_middle );
            std::reverse_copy( decompo2.begin(), decompo2_middle, std::front_inserter( decompo1 ) ); 
        }
        decompo1.plans_sub_reset();
        return true;   
    }
};
class CrossOverTimeFilterHalf : public eoQuadOp<Decomposition>
{
public:
    bool operator()( Decomposition & decompo1, Decomposition & decompo2 )
    {
        if( decompo1.empty() || decompo2.empty() ) {
            return false;
        }
#ifndef NDEBUG
        eo::log << eo::debug << "C";
        eo::log.flush();
        eo::log << eo::xdebug << " Crossover:" << std::endl << "\tBefore: " << std::endl;
        eo::log << eo::xdebug << "\t\t";
        simplePrint( eo::log << eo::xdebug, decompo1 );
        eo::log << eo::xdebug << "\t\t";
        simplePrint( eo::log << eo::xdebug, decompo2 );
#endif
        Decomposition::iterator decompo1_middle = decompo1.begin();
#ifndef NDEBUG
        unsigned int i1 = rng.random( decompo1.size() );
        std::advance( decompo1_middle, i1 );
#else
        std::advance( decompo1_middle, rng.random( decompo1.size() ) );
#endif
        Decomposition::iterator decompo2_middle = decompo2.begin();
#ifndef NDEBUG
        unsigned int i2 = rng.random( decompo2.size() );
        std::advance( decompo2_middle, i2 );
#else
        std::advance( decompo2_middle, rng.random( decompo2.size() ) );
#endif
        TimeVal d1 = decompo1_middle->earliest_start_time();
        TimeVal d2 = decompo2_middle->earliest_start_time();
#ifndef NDEBUG
        eo::log << eo::xdebug << "\ti1: " << i1 << ", i2: " << i2 << std::endl;
        eo::log << eo::xdebug << "\td1: " << d1 << ", d2: " << d2 << std::endl;
#endif
        if( d2 > d1 ) {
            Decomposition::iterator decompo1_middle_next = decompo1_middle;
            decompo1_middle_next++;
            decompo1.erase( decompo1_middle_next, decompo1.end() );
            for( Decomposition::iterator igoal = decompo2_middle, iend = decompo2.end(); igoal != iend; ++igoal ) {
                if( igoal->earliest_start_time() > d1 ) {
                    decompo1.push_back( *igoal );
                }
            }
        } else {
            decompo1.erase( decompo1.begin(), decompo1_middle );
            Decomposition::iterator igoal;
            Decomposition::iterator ibegin = decompo2.begin();
            for( igoal = decompo2_middle; igoal != ibegin; --igoal ) {
                if( igoal->earliest_start_time() < d2 ) {
                    decompo1.push_front( *igoal );
                }
            }
            if( igoal->earliest_start_time() < d2 ) {
                    decompo1.push_front( *igoal );
            }
        } 
#ifndef NDEBUG
        eo::log << eo::xdebug << "\t After: " << std::endl;
        eo::log << eo::xdebug << "\t\t";
        simplePrint( eo::log << eo::xdebug, decompo1 );
#endif
        decompo1.plans_sub_reset();
        return true;   
    }
};
} 
