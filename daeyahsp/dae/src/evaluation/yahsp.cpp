#include <sys/time.h>
#include <sys/resource.h>
#include <utility>
#include <sstream>
#include <stdexcept>
#include <numeric>
#include "yahsp.h"
#include "utils/utils.h"
std::ostream & operator<<( std::ostream & out, BitArray bitarray )
{
    for( unsigned int i = 1; i < fluents_nb; ++i ) {
        unsigned long bit = bitarray_get( bitarray, fluents[i] );
        if( bit != 0 ) {
            out << " " << fluent_name(fluents[i]);
        }
    }
    return out;
}
daeYahspEval::daeYahspEval( 
            unsigned int l_max_ , 
            unsigned int b_max_in , 
            unsigned int b_max_last , 
            double fitness_weight ,
            double fitness_penalty 
        ) :
        daeCptYahspEval( l_max_,b_max_in, b_max_last, fitness_weight, fitness_penalty ),
        _previous_state( NULL ), _intermediate_goal_state(NULL), _intermediate_goal_state_nb(0)
{
    _previous_state = bitarray_create( fluents_nb );
    _intermediate_goal_state = (Fluent**) malloc( fluents_nb * sizeof( Fluent* ) );
    if( _intermediate_goal_state == NULL ) {
        std::ostringstream msg;
        msg << "Error: cannot allocate an intermediate goal state of size " << fluents_nb << std::endl;
        throw std::runtime_error( msg.str().c_str() );
    }
}
daeYahspEval::~daeYahspEval()
{
    free( _previous_state );
    free( _intermediate_goal_state );
}
unsigned int daeYahspEval::solve_next( daex::Decomposition & decompo, Fluent** next_state, unsigned int next_state_nb )
{
    bitarray_copy( _previous_state, *get_current_state(), fluents_nb );
                                 #ifndef NDEBUG
                                     eo::log << eo::xdebug << "ok" << std::endl;
                                     eo::log << eo::xdebug << "\t\tcall the solver...";
                                     eo::log.flush();
                                 #endif
    unsigned int return_code = cpt_search( init_state, init_state_nb, next_state, next_state_nb, false, false, false );
                                 #ifndef NDEBUG
                                     eo::log << eo::xdebug << "ok" << std::endl;
                                     eo::log << eo::xdebug << "\t\treturn code: " << return_code << " ";
                                     eo::log.flush();
                                 #endif
    if( return_code == NO_PLAN || return_code == GOALS_MUTEX ) {
        step_recorder_fail();
                                 #ifndef NDEBUG
                                         eo::log << eo::debug << "x";
                                         eo::log.flush();
                                         eo::log << eo::xdebug << std::endl;
                                 #endif
    } else if( return_code == PLAN_FOUND ) { assert( solution_plan != NULL );
        if( solution_plan->steps_nb > 0 )  {
            _u++; 
            _B += static_cast<unsigned int>( solution_plan->backtracks );
        }
        _k++; 
        plans[plans_nb] = solution_plan;
        plans_nb++;
        decompo.plans_sub_add( daex::Plan() ); 
        decompo.last_subplan().search_steps( _B );
                                 #ifndef NDEBUG
                                         eo::log << eo::xdebug << "ok" << std::endl;
                                         eo::log << eo::xdebug << "\t\trecord steps...";
                                         eo::log.flush();
                                 #endif
        step_recorder();
        solution_plan = NULL; 
                                 #ifndef NDEBUG
                                         eo::log << eo::xdebug << "ok" << std::endl;
                                 #endif
    }
    return return_code;
}
void daeYahspEval::compress( daex::Decomposition & decompo )
{
                                 #ifndef NDEBUG
                                         eo::log << eo::xdebug << "\t\tcompression...";
                                         eo::log.flush();
                                 #endif
        yahsp_compress_plans();
                                         assert(solution_plan != NULL);
                                         assert(solution_plan->makespan > 0);
                                 #ifndef NDEBUG
                                         eo::log << eo::xdebug << "ok" << std::endl;
                                         eo::log << eo::xdebug << "\t\tsave compressed plan and fitness...";
                                         eo::log.flush();
                                 #endif
        decompo.plan_global( daex::Plan( solution_plan ) ); 
        decompo.last_subplan().search_steps( _B );
                                 #ifndef NDEBUG
                                         eo::log << eo::xdebug << "ok" << std::endl;
                                 #endif
}
void daeYahspEval::call( daex::Decomposition & decompo ) 
{
                                 #ifndef NDEBUG
                                     eo::log << eo::xdebug << "decompo.size=" << decompo.size() << std::endl;
                                 #endif
                                 #ifndef NDEBUG
                                     eo::log << eo::xdebug << "Check goal consistency" << std::endl;
                                     for( daex::Decomposition::iterator igoal = decompo.begin(), goal_end = decompo.end(); igoal != goal_end; ++igoal ) {
                                         assert_noduplicate( igoal->begin(), igoal->end() );
                                         assert_nomutex(     igoal->begin(), igoal->end() );
                                     }
                                 #endif
    if( ! decompo.invalid() ) { 
                                 #ifndef NDEBUG
                                         eo::log << eo::debug << "-";
                                         eo::log.flush();
                                 #endif
    } else { 
#ifndef PAPERVERSION
        if( decompo.size() > _l_max ) {
           decompo.fitness( std::make_pair( fitness_unfeasible_too_long(), false ) );
        } else 
                                 #endif
	  {
                                 #ifndef NDEBUG
                                         eo::log << eo::xdebug << "malloc plans...";
                                         eo::log.flush();
                                 #endif
        cpt_malloc( plans, decompo.size()+1 ); 
        plans_nb = 0;
                                 #ifndef NDEBUG
                                         eo::log << eo::xdebug << "ok" << std::endl;
                                         eo::log << eo::xdebug << "yahsp reset...";
                                         eo::log.flush();
                                 #endif
        yahsp_reset();
                                 #ifndef NDEBUG
                                         eo::log << eo::xdebug << "ok" << std::endl;
                                 #endif
        _k = 0; 
        _u = 0; 
        _B = 0; 
                                 #ifndef NDEBUG
                                         eo::log << eo::xdebug << "for each goal:" << std::endl;
                                 #endif
        unsigned int code = 0; 
        b_max( _b_max_in ); 
        for( daex::Decomposition::iterator igoal = decompo.begin(), iend = decompo.end(); igoal != iend; ++igoal ) {
                                 #ifndef NDEBUG
                                             eo::log << eo::xdebug << "\t\tcopy of states and fluents...";
                                             eo::log.flush();
                                 #endif
                                             assert( igoal->size() > 0 );
            unsigned int i = 0;
            for( daex::Goal::iterator iatom = igoal->begin(); iatom != igoal->end(); ++iatom ) {
                _intermediate_goal_state[i] =  (*iatom)->fluent();
                i++;
            }
                                             assert( i ==  igoal->size());
            code = solve_next( decompo, _intermediate_goal_state, igoal->size() );
            if( code != PLAN_FOUND ) {
#ifdef PAPERVERSION
              decompo.fitness( std::make_pair( fitness_unfeasible(decompo, _previous_state), false ) );
#else
              decompo.fitness( std::make_pair( fitness_unfeasible_intermediate(), false ) );
#endif 
              break;
            }
        } 
        if((decompo.size() == 0) || (code == PLAN_FOUND)) {
            b_max( _b_max_last );
            unsigned int code = solve_next( decompo, goal_state, goal_state_nb  );
            if( code == PLAN_FOUND ) {
                compress( decompo );
                decompo.fitness( std::make_pair( fitness_feasible( decompo ), true ) );
                                 #ifndef NDEBUG
                                                 eo::log << eo::debug << "*";
                                                 eo::log.flush();
                                 #endif
            } else {
#ifdef PAPERVERSION
                decompo.fitness( std::make_pair( fitness_unfeasible(decompo, _previous_state), false ) );
#else
                decompo.fitness( std::make_pair( fitness_unfeasible_final(), false ) );
#endif 
            } 
        } 
      } 
    } 
    free_yahsp_structures();
}
void daeYahspEval::free_yahsp_structures()
{
                                 #ifndef NDEBUG
                                     eo::log << eo::xdebug << "\t\tfree plans...";
                                     eo::log.flush();
                                 #endif
    for( unsigned int p=0; p < plans_nb; ++p ) {
      plan_free( plans[p] );
    }
    plans_nb = 0;
    cpt_free( plans );
    if( solution_plan != NULL ) {
        plan_free( solution_plan );
	solution_plan = NULL;
    }
                                 #ifndef NDEBUG
                                     eo::log << eo::xdebug << "ok" << std::endl;
                                 #endif
}
void daeYahspEvalInit::call( daex::Decomposition & decompo ) 
{
#ifndef NDEBUG
    eo::log << eo::logging << std::endl << "init decompo nodes nb: ";
    eo::log.flush();
    int prev = std::accumulate( node_numbers.begin(), node_numbers.end(), 0 );
#endif
    daeYahspEval::call( decompo );
#ifndef NDEBUG
    int next = std::accumulate( node_numbers.begin(), node_numbers.end(), 0 );
    eo::log << eo::logging << "     (" << next - prev << ")";
#endif
}
void daeYahspEvalInit::step_recorder() {
    node_numbers.push_back( static_cast<int>( solution_plan->backtracks ) ); 
#ifndef NDEBUG
    eo::log << eo::logging << " " << node_numbers.back();
    eo::log.flush();
#endif
}
void daeYahspEvalInit::step_recorder_fail() {
      node_numbers.push_back(stats.evaluated_nodes);
#ifndef NDEBUG
    eo::log << eo::logging << " " << node_numbers.back();
    eo::log.flush();
#endif
}
unsigned int daeYahspEvalInit::estimate_b_max( double quantile  )
{
    assert( node_numbers.size() > 0 );
    unsigned int nth = static_cast<unsigned int>( ceil( static_cast<double>( node_numbers.size() ) * quantile ) );
#ifndef NDEBUG
    if( nth == 0 || nth == node_numbers.size()-1 ) {
        eo::log << eo::warnings << "WARNING: while estimating the b_max, the quantile at " << quantile << " returns the " << nth << "th element (size=" << node_numbers.size() << ")" << std::endl;
    }
#endif
    if( node_numbers.size() % 2 != 0 ) { 
        std::nth_element( node_numbers.begin(), node_numbers.begin() + nth,  node_numbers.end() );
        return node_numbers[nth];
    } else { 
        unsigned int m1, m2;
        std::nth_element( node_numbers.begin(), node_numbers.begin() + nth,  node_numbers.end() );
        m1 = node_numbers[nth];
        std::nth_element( node_numbers.begin(), node_numbers.begin() + nth - 1,  node_numbers.end() );
        m2 = node_numbers[nth-1];
        return static_cast<unsigned int>( ceil( static_cast<double>( m1 + m2 ) / 2.0 ) );
    } 
}
