#include "cpt.h"
void bindDaeCpt( daex::pddlLoad & pddl )
{
    bindDaeYahspCpt( pddl, SOLVER_CPT );
}
void daeCptEval::call( daex::Decomposition & decompo )
{
    if( ! decompo.invalid() ) {
        return;
    }
    _k = 0;
    _u = 0;
    _B = 0;
    _total_backtracks = 0;
    for( unsigned int p=0; p < plans_nb; ++p ) {
        plan_free( plans[p] );
    }
    plans_nb = 0;
    cpt_malloc( plans, _l_max );
    decompo.plans_sub_reset();
    std::copy( init_state, init_state + init_state_nb, _current_state );
    _current_state_nb = init_state_nb;
    daex::Decomposition::iterator iend = decompo.end();
    for( daex::Decomposition::iterator igoal = decompo.begin(); 
         igoal != iend;
         ++igoal ) {
        _intermediate_goal_state_nb = igoal->size();
        assert( _intermediate_goal_state_nb > 0 );
        _intermediate_goal_state = new Fluent*[_intermediate_goal_state_nb];
        unsigned int i = 0;
        for( daex::Goal::iterator iatom = igoal->begin(); iatom != igoal->end(); ++iatom ) {
            _intermediate_goal_state[i++] = (*iatom)->fluent_of<Fluent*>( "cpt" );
        } 
        _timer_subsolver.restart();
        unsigned int return_code = 
            cpt_search( _current_state, _current_state_nb, 
                        _intermediate_goal_state, _intermediate_goal_state_nb,
                        false, false, false );
        double time_subsolver = _timer_subsolver.get();
        decompo.plan().time_subsolver( decompo.plan().time_subsolver() + time_subsolver );
        if( return_code == PLAN_FOUND ) {
            if( solution_plan->steps_nb > 0 ) {
                _u++;
                _B += static_cast<unsigned int>( solution_plan->backtracks );
            }
            _k++;
            exec_plan();
            plans[plans_nb++] = solution_plan;
            decompo.plans_sub_add( convertPlanCptToDae( solution_plan ) );
            decompo.last_subplan().time_subsolver( time_subsolver );
            decompo.last_subplan().search_steps( _B );
            decompo.last_subplan().time_eval( _timer_eval.get() );
            solution_plan = NULL;
        } else {
           assert( return_code == GOALS_MUTEX      ||
                   return_code == INIT_PROP_FAILED ||
                   return_code == BACKTRACK_LIMIT  ||
                   return_code == BOUND_LIMIT      ); 
            decompo.fitness( fitness_unfeasible( decompo, state_convert(_current_state,_current_state_nb) ) );
            return;
        }
    } 
    _timer_subsolver.restart();
    unsigned int return_code = 
        cpt_search( _current_state, _current_state_nb, 
                    goal_state, goal_state_nb,
                    false, false, false );
    double time_subsolver = _timer_subsolver.get();
    if( return_code == PLAN_FOUND ) {
        if( solution_plan->steps_nb > 0 ) {
            _u++;
            _B += static_cast<unsigned int>( solution_plan->backtracks );
        }
        _k++;
        plans[plans_nb++] = solution_plan;
        decompo.plans_sub_add( convertPlanCptToDae( solution_plan ) );
        decompo.last_subplan().time_subsolver( time_subsolver );
        decompo.last_subplan().search_steps( _B );
        decompo.last_subplan().time_eval( _timer_eval.get() );
        solution_plan = NULL;
        bool cqp = opt.complete_qualprec;
        opt.complete_qualprec = true;
        _timer_subsolver.restart();
        unsigned int return_code = 
            cpt_search( _current_state, _current_state_nb, 
                        goal_state, goal_state_nb,
                        true, 
                        true, 
                        true  
                      );
        opt.complete_qualprec = cqp;
        if( return_code != PLAN_FOUND ) {
            assert( solution_plan == NULL );
            unsigned int total_steps_nb = 0;
            for( unsigned int i = 0; i < plans_nb; ++i ) {
                total_steps_nb += plans[i]->steps_nb;
            }
            solution_plan = new SolutionPlan;
            solution_plan->steps = new Step*[ total_steps_nb ];
            solution_plan->steps_nb = total_steps_nb;
            unsigned int solution_index = 0;
            for( unsigned int i = 0; i < plans_nb; ++i ) {
                std::copy( plans[i]->steps, plans[i]->steps + plans[i]->steps_nb, 
                           solution_plan->steps + solution_index );
                solution_index += plans[i]->steps_nb;
            } 
            assert( solution_index == total_steps_nb );
        } 
        decompo.plan().time_subsolver( decompo.plan().time_subsolver() + _timer_subsolver.get() );
        decompo.fitness( fitness_feasible( decompo )  );
        decompo.plan_global( convertPlanCptToDae( solution_plan ) );
        return;
    } else {
       assert( return_code == GOALS_MUTEX      ||
               return_code == INIT_PROP_FAILED ||
               return_code == BACKTRACK_LIMIT  ||
               return_code == BOUND_LIMIT      ); 
        decompo.fitness( fitness_unfeasible( decompo, state_convert(_current_state,_current_state_nb) ) );
        return;
    }
}
void daeCptEval::exec_plan()
{
    for( unsigned int s = 0; s < solution_plan->steps_nb; s++ ) {
         Step step = *(solution_plan->steps[s]);
        for( unsigned int f = 0; f < _current_state_nb; f++ ) {
            for( unsigned int d = 0; d < step.action->del_nb; d++ ) {
                if( _current_state[f] == step.action->del[d] ) {
                    _current_state[ f-- ] = _current_state[ --_current_state_nb ];
                    break;
                } 
            } 
        } 
        for( unsigned int a = 0; a < step.action->add_nb; a++ ) {
            bool found = false;
            for( unsigned int f = 0; f < _current_state_nb; f++ ) {
                if( step.action->add[a] == _current_state[f] ) {
                    found = true;
                    break;
                }
             } 
            if( ! found ) {
                _current_state[ _current_state_nb++ ] = step.action->add[a];
            }
        } 
    } 
}
BitArray daeCptEval::state_convert( Fluent * * & f_state, unsigned int f_state_nb )
{
    BitArray state = bitarray_create( fluents_nb );
    for( unsigned int i = 0; i < f_state_nb; ++i ) {
        bitarray_set( state, f_state[i] );
    } 
   return state;
}
