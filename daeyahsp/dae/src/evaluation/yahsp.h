#ifndef __DAEX_EVAL_YAHSP_H__
#define __DAEX_EVAL_YAHSP_H__
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include "utils/pddl.h"
#include "core/decomposition.h"
#include "core/plan.h"
#include "cpt-yahsp.h"
#include <src/globs.h>
#include <src/plan.h>
#include <src/yahsp.h>
#include <src/cpt.h>
#include <src/trace.h>
#include <src/options.h>
void bindDaeYahsp( daex::pddlLoad & pddl );
std::ostream & operator<<( std::ostream & out, BitArray bitarray );
class daeYahspEval : public daeCptYahspEval
{
 public: daeYahspEval( unsigned int l_max_ = 20, unsigned int b_max_in = 10, unsigned int b_max_last = 30, double fitness_weight = 10, double fitness_penalty = 1e6 );
    virtual ~daeYahspEval();
public:
    virtual void step_recorder() {}
    virtual void step_recorder_fail() {}
public:
    void call( daex::Decomposition & decompo ); 
protected:
    unsigned int solve_next( daex::Decomposition & decompo, Fluent** next_state, unsigned int next_state_nb );
    void compress( daex::Decomposition & decompo );
    void free_yahsp_structures();
    BitArray _previous_state;
    Fluent * * _intermediate_goal_state;
    unsigned int _intermediate_goal_state_nb;
};
class daeYahspEvalInit : public daeYahspEval
{
public:
    daeYahspEvalInit( 
            unsigned int pop_size, 
            unsigned int l_max, 
            unsigned int b_max_in = 10000, 
            unsigned int b_max_last = 30000, 
            double fitness_weight = 10,
	    double fitness_penalty = 1e6
	    ) : daeYahspEval( l_max, b_max_in, b_max_last, fitness_weight, fitness_penalty ) 
    {
      node_numbers.reserve( pop_size * l_max );
    }
    void call( daex::Decomposition & decompo );
    void step_recorder();
    void step_recorder_fail();
    unsigned int estimate_b_max( double quantile = 0.5 );
protected:
    std::vector<unsigned int> node_numbers;
};
#endif 
