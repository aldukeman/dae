#ifndef __DAE_BIND_YAHSP_CPT_H__
#define __DAE_BIND_YAHSP_CPT_H__
#include <string>
#include <eo>
#include "utils/pddl_load.h"
#include "core/decomposition.h"
#include "utils/posix_timer.h"
#include <src/structs.h>
#include <src/plan.h>
std::string timeValToString( TimeVal x );
void bindDaeYahspCpt( daex::pddlLoad & pddl, std::string solver = SOLVER_YAHSP );
bool operator==( const Fluent * fluent, const daex::Atom & atom );
bool operator!=( const PDDLTerm & term, const daex::pddlObject & object );
class daeCptYahspEval : public eoEvalFunc<daex::Decomposition>
{
public:
  daeCptYahspEval( unsigned int l_max_ = 20, unsigned int b_max_in = 10, unsigned int b_max_last = 30, double fitness_weight = 10, double fitness_penalty = 1e60, bool sequential = false ) : _l_max( l_max_ ), _b_max_in(b_max_in),_b_max_last( b_max_last),_unknown_parameter(fitness_weight),_fitness_penalty( fitness_penalty ),_sequential( sequential )
    {
        b_max( b_max_in );
    }
    virtual ~daeCptYahspEval() {}
public:
    unsigned int l_max() const { return _l_max; }
    void l_max( unsigned int l ) { _l_max = l; }
    unsigned int b_max() const { return _b_max; }
    void b_max( unsigned int b ) 
    { 
        _b_max = b;
        opt.max_backtracks = b;
    }
public:
     void operator() ( daex::Decomposition & decompo ) 
    {
        pre_call( decompo );
        call( decompo );
        post_call( decompo );
    }
    virtual void call( daex::Decomposition & decompo ) = 0;
protected:
     void pre_call( daex::Decomposition &  ) 
    {}
     void post_call( daex::Decomposition & decompo )
    {
        decompo.plan().search_steps( _B );
    }
protected:
    unsigned int distance_to_goal_Hamming( BitArray state );
    double fitness_feasible( daex::Decomposition & decompo );
    double fitness_unfeasible( daex::Decomposition & decompo, BitArray state );
    double fitness_unfeasible_too_long( );
    double fitness_unfeasible_intermediate( );
    double fitness_unfeasible_final( );
protected:
    unsigned int _l_max;
    unsigned int _b_max;
    unsigned int _b_max_in;
    unsigned int _b_max_last;
    double _unknown_parameter;
    double _fitness_penalty;
protected:
    bool _sequential;
protected:
    unsigned int _k;
    unsigned int _u;
    unsigned int _B;
}; 
#endif 
