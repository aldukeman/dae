#include "utils/pddl_load.h"
#include <utils/eoLogger.h>
namespace daex
{
void pddlLoad::load_pddl( std::string solver , 
                          unsigned int heuristic_start_times ,
                          std::vector<std::string> solver_args   
        )
{
    assert( solver == SOLVER_YAHSP || solver == SOLVER_CPT );
    assert( heuristic_start_times == HEURISTIC_H1 || heuristic_start_times == HEURISTIC_H2 );
    std::vector<std::string> cpt_call;
    cpt_call.push_back( "cpt" );
    cpt_call.push_back( "-dae" );
    cpt_call.push_back( "-ops" );
        cpt_call.push_back( (char *) _domain.c_str() );
    cpt_call.push_back( "-facts" ); 
        cpt_call.push_back( (char *) _problem.c_str() );
    if( solver == SOLVER_YAHSP ) {
        cpt_call.push_back( "-yahsp" );
        cpt_call.push_back( "64" ); 
	cpt_call.push_back( "-K" ); 
	cpt_call.push_back( "0.01,0.01" ); 
	cpt_call.push_back( "-fluent-mutexes" );
        cpt_call.push_back( "-max-backtracks" ); 
        cpt_call.push_back( "0" );
        cpt_call.push_back( "-initial-heuristic" );
        if( heuristic_start_times == HEURISTIC_H1 ) {
            cpt_call.push_back( "1" );
        } else if( heuristic_start_times == HEURISTIC_H2 ) {
            cpt_call.push_back( "2" );
        } else {
            cpt_call.push_back( "0" );
        }
    } else if( solver == SOLVER_CPT ) {
        cpt_call.push_back( "-initial-heuristic" );
        if( heuristic_start_times == HEURISTIC_H1 ) {
            cpt_call.push_back( "1" );
        } else if( heuristic_start_times == HEURISTIC_H2 ) {
            cpt_call.push_back( "2" );
        } else {
            cpt_call.push_back( "0" );
        }
        cpt_call.push_back( "-give-suboptimal" );
        cpt_call.push_back( "-max-backtracks" );
            cpt_call.push_back( "1000000" ); 
    } 
    cpt_call.insert( cpt_call.end(), solver_args.begin(), solver_args.end() );
    const char** params = (const char**) calloc( cpt_call.size(), sizeof(const char*) );
    if( params == NULL ) {
        throw( std::runtime_error( "Parameter array allocation error" ) );
    }
    for( unsigned int i = 0; i < cpt_call.size(); ++i ) {
        params[i] = (const char*) cpt_call[i].c_str();
    }
#ifndef NDEBUG
    eo::log << eo::debug << "\tcpt_main options: ";
    std::copy( cpt_call.begin(), cpt_call.end(), std::ostream_iterator<std::string>( eo::log << eo::debug, " " ) );
    eo::log << eo::debug << std::endl;
#endif
    cpt_main( cpt_call.size(), params );
    for( unsigned int i=0; i < fluents_nb; ++i) {
        daex::Atom * atom = new daex::Atom( fluents[i]->init, fluents[i] );
        _atoms.push_back( atom );
    } 
}
void pddlLoad::compute_chrono_partition()
{
    assert( _atoms.size() != 0 );
    std::vector<daex::Atom*>::iterator it_atom = _atoms.begin();
    while( it_atom != _atoms.end() ) {
        TimeVal start_time = (*it_atom)->earliest_start_time();
        _chrono_partition_atom[ start_time ].push_back( *it_atom );
        it_atom++;
    }
    assert( _chrono_partition_atom.count( 0 ) != 0 );
    _chrono_partition_atom.compute_goal_max_date();
}
pddlLoad::pddlLoad( 
          std::string domain, 
          std::string problem, 
          std::string solver , 
          unsigned int heuristic_start_times ,
          std::vector<std::string> solver_args 
        ) : _domain(domain), _problem(problem)
{
    load_pddl( solver, heuristic_start_times,  solver_args );
    compute_chrono_partition();
}
pddlLoad::~pddlLoad()
{
    for( unsigned int i=0; i<_atoms.size(); ++i) {
        delete _atoms[i];
    }
}
} 
