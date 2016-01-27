#ifndef __DAEX_UTILS_H__
#define __DAEX_UTILS_H__
#include "core/atom.h"
#include <src/structs.h>
namespace daex {
template<class T>
  bool has_one_mutex_in( Atom* const& candidate, T const first, T const last)
{
  for( T it=first; it!=last; ++it  ) {
        Atom* a = *it;
        if( candidate == a 
            || 
            fmutex( candidate->fluent(),
                            a->fluent() ) ) {
            return true;
        }
    }
    return false;
}
template< class T1, class T2 >
typename T1::const_iterator draw_until_mutex_if( T1 const& applicants, T2 const goal_first, T2 const goal_last, unsigned int maxtry, bool search_mutex )
{
    assert( maxtry <= applicants.size() );
    typedef std::list< typename T1::const_iterator > IterList;
    IterList candidates;
    for( std::vector<Atom*>::const_iterator it = applicants.begin(), end = applicants.end(); it != end; ++it ) {
        candidates.push_back( it );
    }
    while( maxtry > 0 ) {
        typename IterList::iterator itapp;
        itapp = candidates.begin();
        std::advance( itapp, rng.random( candidates.size() ) );
        if(   search_mutex &&  has_one_mutex_in( **itapp, goal_first, goal_last )
           ||
             !search_mutex && !has_one_mutex_in( **itapp, goal_first, goal_last ) ) {
#ifndef NDEBUG
            if( !search_mutex ) {
                for( T2 iatom = goal_first; iatom != goal_last; ++iatom ) {
                     assert( **itapp != *iatom );
                }
            }
#endif
            return *itapp;
        } else {
            maxtry--;
            candidates.erase( itapp );
        }
    } 
    return applicants.end();
}
template< class T1, class T2 >
typename T1::const_iterator draw_until_nomutex( T1 const& applicants, T2 const goal_first, T2 const goal_last, unsigned int maxtry = 0 )
{
    if( maxtry == 0 ) { maxtry = applicants.size(); }
    return draw_until_mutex_if( applicants, goal_first, goal_last, maxtry, false );
}
template< class T >
T nomutex( T const& candidates )
{
    std::list<Atom*> candidate_atoms;
    std::copy( candidates.begin(), candidates.end(), std::back_inserter( candidate_atoms ) );
    assert( candidate_atoms.size() > 0 );
    T nomutex_atoms;
    while( candidate_atoms.size() > 0 ) {
        std::list<Atom*>::iterator ca_it = candidate_atoms.begin();
        std::advance(ca_it, rng.random( candidate_atoms.size() ) );
        if( candidate_atoms.size() > 1 ) {
            typedef std::vector< std::list<Atom*>::iterator > ItersVec;
            ItersVec iters_to_erase;
            iters_to_erase.reserve( candidate_atoms.size() );
            for( std::list<Atom*>::iterator it = candidate_atoms.begin(), end = candidate_atoms.end(); it != end; ++it ) {
                if( ca_it != it ) {
                    Atom* ca = *ca_it;
                    Atom* a = *it;
                    assert( ca != a );
                    assert( ca->fluent() != a->fluent() );
                    if( fmutex(
                                ca->fluent(), 
                                a->fluent() 
                              )
                      ) {
                        iters_to_erase.push_back( it );
                    } 
                } 
            } 
            for( typename ItersVec::iterator itte = iters_to_erase.begin(), iend = iters_to_erase.end(); itte != iend; ++itte ) {
                candidate_atoms.erase( *itte );
            }
            iters_to_erase.clear();
        } 
        nomutex_atoms.push_back( *ca_it );
        candidate_atoms.erase( ca_it );
    } 
    return nomutex_atoms;
}
template< class T>
Goal random_subset( T candidate_atoms )
{
#ifndef NDEBUG
    eo::log << eo::xdebug << "\t\trandom_subset of " << candidate_atoms.size() << " candidates:";
#endif
    Goal goal(0);
    TimeVal goaldate = 0;
    unsigned int N = 1 + rng.random( candidate_atoms.size() );
#ifndef NDEBUG
    eo::log << eo::xdebug << " " << N << " atoms chosen, ";
#endif
    unsigned int i = 0;
    do {
        unsigned int j = rng.random( candidate_atoms.size() );
        typename T::iterator it = candidate_atoms.begin();
        std::advance(it,j);
        goal.push_back(*it);
        goaldate = std::max( (*it)->earliest_start_time(), goaldate );
        assert(goaldate != 0);
        candidate_atoms.erase( it );
        i++;
    } while( i < N );
    goal.earliest_start_time(goaldate);
#ifndef NDEBUG
	eo::log << eo::xdebug << "goal final date: " << goal.earliest_start_time();
    eo::log << eo::xdebug << std::endl;
#endif
    return goal;
}
template<class T>
void assert_nomutex( T begin, T end ) 
{
    T iend = end;
    iend--;
    for( T iatom  = begin; iatom != iend;  ++iatom  ) {
        T begin2 = iatom;
        begin2++;
        for( T iatom2 = begin2; iatom2 != end; ++iatom2 ) {
            Atom* a = *iatom;
            Atom* b = *iatom2;
            assert( ! fmutex( a->fluent(), b->fluent() ) );
        }
    }
}
template<class T>
void assert_noduplicate( T begin, T end ) 
{
    T atom_end = end;
    atom_end--;
    for( T iatom = begin; iatom != atom_end; ++iatom ) {
        T jatom = iatom;
        jatom++;
        for( T iatom2 = jatom; iatom2 != end; ++iatom2 ) {
            assert( *iatom != *iatom2 );
        }
    }
}
} 
#endif 
