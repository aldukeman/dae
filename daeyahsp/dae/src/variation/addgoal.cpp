#include <algorithm>
#include <sstream>
#include <iomanip>
#include "addgoal.h"
namespace daex {
bool MutationAddGoal::operator() ( Decomposition & decompo )
{
#ifndef NDEBUG
    eo::log << eo::debug << "A";
    eo::log.flush();
#endif
        assert( ! decompo.empty() );
            int last_reached = decompo.last_reached();
#ifndef NDEBUG
                eo::log << eo::xdebug << " AddGoal:" << std::endl;
                eo::log << eo::xdebug << "\tbefore: ";
                simplePrint( eo::log << eo::xdebug, decompo );
                eo::log << eo::xdebug << "\tlast reached: " << last_reached << std::endl;
#endif
            if( last_reached == -1 ) {
#ifndef NDEBUG
                eo::log << eo::xdebug << "\tgenerate random goal in ] " << 0 << ", " << decompo.iter_at( 0 )->earliest_start_time() << " ]" << std::endl;
#endif
                Goal new_goal = random_goal(
                            0, 
                            decompo.iter_at( 0 )->earliest_start_time()
                        );
#ifndef NDEBUG
                eo::log << eo::xdebug << "\tgoal: " << new_goal.earliest_start_time() << "(" << new_goal.size() << ")" << std::endl;
                eo::log << eo::xdebug << "\tpush front" << std::endl;
#endif
                decompo.push_front( new_goal );
            } else {
                unsigned int range = last_reached + 1;
                unsigned int j = rng.random( range );
#ifndef NDEBUG
                eo::log << eo::xdebug << "\tgoal index chosen: " << j << std::endl;
#endif
                TimeVal t1;
                TimeVal t2;
                if( j == 0 ) {
                    t1 = decompo.iter_at( j )->earliest_start_time();
#ifndef NDEBUG
                    eo::log << eo::xdebug << "\tgenerate random goal in ] " << 0 << ", " << t1 << " ]" << std::endl;
#endif
                    Goal new_goal = random_goal( 0, t1 );
#ifndef NDEBUG
                    eo::log << eo::xdebug << "\tgoal: " << new_goal.earliest_start_time() << "(" << new_goal.size() << ")" << std::endl;
                    eo::log << eo::xdebug << "\tpush front" << std::endl;
#endif
                    decompo.push_front( new_goal );
                } else if(  j < decompo.size() ) {
                    t1 = decompo.iter_at( j - 1 )->earliest_start_time();
                    t2 = decompo.iter_at( j )->earliest_start_time(); 
                    if( t1 >= t2 ) {
#ifndef NDEBUG
                        eo::log << eo::xdebug << "\t" << t1 << ">=" << t2 << ", no insertion" << std::endl << std::endl;
#endif
                        return false;
                    }
#ifndef NDEBUG
                    eo::log << eo::xdebug << "\tgenerate random goal in ] " << t1 << ", " << t2 << " ]" << std::endl;
#endif
                    Goal new_goal = random_goal( t1, t2 );
#ifndef NDEBUG
                    eo::log << eo::xdebug << "\tgoal: " << new_goal.earliest_start_time() << "(" << new_goal.size() << ")" << std::endl;
                    eo::log << eo::xdebug << "\tinsert before index: " << j << std::endl;
#endif
                    decompo.insert( decompo.iter_at( j ), new_goal );
                } else { 
                    t1 = decompo.back().earliest_start_time();
                    ChronoPartition::const_iterator it1 = _times.find(t1);
                    assert( it1 != _times.end() );
                    assert( it1 != _times.begin());
                    ChronoPartition::const_iterator it0 = it1;
                    std::advance( it0, -1 );
                    TimeVal t0 = it0->first;
                    t2 = _times.rbegin()->first;
#ifndef NDEBUG
                    eo::log << eo::xdebug << "\tgenerate random goal in ] " << t0 << " ([ " << t1 << "), " << t2 << " ]" << std::endl;
#endif
                    Goal new_goal = random_goal( t0, t2 );
#ifndef NDEBUG
                    eo::log << eo::xdebug << "\tgoal: " << new_goal.earliest_start_time() << "(" << new_goal.size() << ")" << std::endl;
                    eo::log << eo::xdebug << "\tpush back" << std::endl;
#endif
                    decompo.push_back( new_goal );
                }
            } 
#ifndef NDEBUG
    eo::log << eo::xdebug << "\tafter:  ";
    simplePrint( eo::log << eo::xdebug, decompo );
    eo::log << eo::xdebug << std::endl;
#endif
    return true;
}
Goal MutationAddGoal::random_goal(  TimeVal t1, TimeVal t2 )
{
#ifndef NDEBUG
    eo::log << eo::xdebug << "\t\trandom goal: in ]" << t1 << "," << t2 << "]";
#endif
    assert( t1 <= t2 );
    assert( t1 != t2 );
    assert( _times.count(t1) == 1 );
    assert( _times.count(t2) == 1 );
    assert( _times.find(t1) != _times.end() );
    assert( _times.find(t2) != _times.end() );
    assert( _times.find(t1)->second.size() > 0 );
    assert( _times.find(t2)->second.size() > 0 );
    std::vector<TimeVal> candidate_dates;
    candidate_dates.reserve( _times.size() );
    ChronoPartition::const_iterator it1 = _times.find(t1);
    ChronoPartition::const_iterator it2 = _times.find(t2);
    do {it1++;
        candidate_dates.push_back(it1->first);}
    while(it1 != it2);
    assert( candidate_dates.size() != 0 );
    TimeVal date = candidate_dates[rng.random(candidate_dates.size())];
#ifndef NDEBUG
    eo::log << eo::xdebug << ", considering " << candidate_dates.size() << " candidate dates" 
                          << ", chosen one: " << date;
#endif
    assert( _times.count( date ) > 0 );
    std::list<Atom*> candidate_atoms;
    ChronoPartition::const_iterator it = _times.find(date);
    it--;
    unsigned int j=_radius;
    while ( j != 0 && it != _times.begin()){ 
      std::copy(it->second.begin(), it->second.end(), std::back_inserter(candidate_atoms));
      it--; j--;
    }
    it = _times.find(date); j=_radius+1; 
    while (j != 0 && it != _times.end()){
      std::copy(it->second.begin(), it->second.end(), std::back_inserter(candidate_atoms));
      it++; j--;
    }
#ifndef NDEBUG
    eo::log << eo::xdebug << ", with a radius: " << _radius << ", have " << candidate_atoms.size() << " candidate atoms";
#endif
    assert( candidate_atoms.size() != 0 );
#ifndef NDEBUG
    std::list<Atom*> nomutex_atoms = nomutex( candidate_atoms );
    assert( nomutex_atoms.size() > 0 );
    eo::log << eo::xdebug << ", of which " << nomutex_atoms.size() << " are nomutex";
    Goal result= random_subset( nomutex_atoms );
    eo::log << eo::xdebug << ", final goal: " << result.earliest_start_time() << "(" << result.size() << ")" << std::endl;
    return result;
#else
    return random_subset( nomutex( candidate_atoms ) );
#endif
}
} 
