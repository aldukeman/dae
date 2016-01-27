#ifndef __DAEX_MUTATION_ADDGOAL_H__
#define __DAEX_MUTATION_ADDGOAL_H__
#include <eo>
#include "utils/pddl_load.h"
#include "core/decomposition.h"
#include "utils/utils.h"
namespace daex {
class MutationAddGoal: public eoMonOp<Decomposition>
{
public:
    MutationAddGoal(
            const ChronoPartition & times,
            unsigned int radius = 1
    ) : _times(times), _radius( radius ) {}
    bool operator()( Decomposition & decompo );
protected:
    Goal random_goal(  TimeVal t1, TimeVal t2 );
    const ChronoPartition & _times;
    unsigned int _radius;
};
} 
#endif 
