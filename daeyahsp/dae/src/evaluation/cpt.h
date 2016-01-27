#ifndef __DAEX_EVAL_CPT_H__
#define __DAEX_EVAL_CPT_H__
#include <iostream>
#include <algorithm>
#include <eo>
#include "utils/pddl.h"
#include "utils/pddl_load.h"
#include "core/decomposition.h"
#include "cpt-yahsp.h"
#include <src/globs.h>
#include <src/plan.h>
#include <src/yahsp.h>
#include <src/cpt.h>
#include <src/trace.h>
#include <src/options.h>
void bindDaeCpt( daex::pddlLoad & pddl );
class daeCptEval : public daeCptYahspEval
{
public:
    daeCptEval( unsigned int l_max_ = 20, unsigned int b_max_ = 100000  ) :
        daeCptYahspEval(l_max_,b_max_),
        _current_state( NULL )
    {
        _current_state = new Fluent*[ fluents_nb ];
    }
    ~daeCptEval()
    {
        assert( _current_state != NULL );
        delete[] _current_state;
    }
public:
    void call( daex::Decomposition & decompo );
protected:
    void exec_plan();
    BitArray state_convert( Fluent * * & f_state, unsigned int f_state_nb );
protected:
    Fluent * * _current_state;
    unsigned int _current_state_nb;
    unsigned int _total_backtracks;
    Fluent * * _intermediate_goal_state;
    unsigned int _intermediate_goal_state_nb;
};
#endif 
