#include <iomanip>
#include <algorithm>
#include "init.h"
namespace daex {
    Init::Init( const ChronoPartition & times, unsigned int l_max_init_coef , unsigned int min_nb  ) : _times(times), _min_nb(min_nb), _l_max_init_coef(l_max_init_coef), _l_max( 20 )
    {
        assert( ! _times.empty() );
        _l_max = times.size() * _l_max_init_coef;
    }
void Init::operator()( Decomposition & decompo )
{
    decompo.clear();
    std::list<TimeVal> _times_tmp;
    ChronoPartition::const_iterator it, begin = _times.begin();
    std::advance( begin, 1); 
    for( it = begin; it != _times.end(); it++) {
        _times_tmp.push_back( it->first );
    }
    unsigned int decompo_nb = std::min( 
            _min_nb + rng.random( _times_tmp.size() + 1 - _min_nb ),
            _l_max 
        );
    std::vector<TimeVal> t_candidates;
    t_candidates.reserve( decompo_nb );
    for( unsigned int i = 0; i < decompo_nb; ++i ) {
        std::list<TimeVal>::iterator it = _times_tmp.begin();
        std::advance( it, rng.random( _times_tmp.size() ) );
        t_candidates.push_back(*it); 
        _times_tmp.erase( it );
    }
    std::sort( t_candidates.begin(), t_candidates.end() );
#ifndef NDEBUG
    assert( t_candidates.front() < t_candidates.back() || t_candidates.front() == t_candidates.back() );
    eo::log << eo::xdebug << "\t\tDecomposition on " << std::right << std::setfill(' ') << std::setw(3) << t_candidates.size() << " partition dates, date(#atoms):";
    unsigned int nb_goals = 0;
#endif
    for( std::vector<TimeVal>::iterator idate = t_candidates.begin(), iend = t_candidates.end(); 
            idate != iend; idate++ ) {
        assert( _times.at( *idate ).size() > 0 );
        Goal goal = random_subset( nomutex( _times.at( *idate ) ) );
#ifndef NDEBUG
        eo::log << eo::xdebug
            << "\t" << std::right << std::setfill(' ') << std::setw(3) 
            << *idate 
            << "(" 
            << goal.size() 
            << ")";
        nb_goals++;
        eo::log << eo::xdebug << std::endl << "Check atom's earliest start times consistency...";
        eo::log.flush();
        for( Goal::iterator iatom = goal.begin(), end = goal.end(); iatom != end; ++iatom ) {
            assert( (*iatom)->fluent()->init == goal.earliest_start_time() );
        }
        eo::log << eo::xdebug << "OK" << std::endl;
#endif
        decompo.push_back( goal );
    } 
    decompo.invalidate();
} 
} 
