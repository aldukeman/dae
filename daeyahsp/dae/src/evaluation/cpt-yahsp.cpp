#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include "cpt-yahsp.h"
std::string timeValToString( TimeVal x )
{
    char* buffer;
    size_t buffer_size;
    FILE* stream = open_memstream( & buffer, & buffer_size );
    if( stream == NULL ) {
        std::ostringstream msg;
        msg << "Cannot open memstream for printing TimeVal (" << x << ")";
        throw std::runtime_error( msg.str() );
    }
    print_time( stream, x );
    fclose( stream );
    std::string res( buffer );
    return res;
}
double daeCptYahspEval::fitness_feasible( daex::Decomposition & decompo )
{
  double Q = (double) decompo.plan().makespan() * pddl_domain->time_gcd / pddl_domain->time_lcm;
    assert( Q > 0 );
    return Q + ( (double)decompo.size() - (double)_u + 1.0 ) / Q + (double)_B / ( (double)_l_max * (double)_b_max );
}
double daeCptYahspEval::fitness_unfeasible( daex::Decomposition & decompo, BitArray state )
{
    return  (double)_unknown_parameter *  (double)distance_to_goal_Hamming( state ) + (double)decompo.size() - (double)_u; 
}
double daeCptYahspEval::fitness_unfeasible_too_long( )
{
  return _fitness_penalty * ((double)_l_max + 1.0) * (double)_l_max * (double)_unknown_parameter * 2;
}
double daeCptYahspEval::fitness_unfeasible_intermediate( )
{
  return _fitness_penalty * ((double)_l_max - (double)_u + 1.0) * (double)_l_max * (double)_unknown_parameter;
}
double daeCptYahspEval::fitness_unfeasible_final( )
{
  return _fitness_penalty * ((double)_l_max - (double)_u + 1.0);
}
unsigned int daeCptYahspEval::distance_to_goal_Hamming( BitArray state )
{
    unsigned int nb = goal_state_nb;
    for( unsigned int i = 0; i < goal_state_nb; ++i ) {
        if ( bitarray_get( state, goal_state[i] ) != 0 ) {
            nb--;
        }
    }
    return nb;
}
