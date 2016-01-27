#ifndef __DECOMPOSITION_H__
#define __DECOMPOSITION_H__
#include <iterator>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <functional>
#include <eo>
#include "decomposition.h"
#include "goal.h"
#include "plan.h"
namespace daex
{
class Decomposition : public std::list<Goal>, public EO< eoMinimizingDualFitness >
{
public:
    void invalidate();
    Plan plan_copy() const
    {
        return _plan_global;
    }
    Plan & plan()
    {
        return _plan_global;
    }
    Plan & subplan(unsigned int i)
    {
        return _plans_sub[i];
    }
    std::vector<Plan> & subplans()
    {
        return _plans_sub;
    }
    Plan & last_subplan()
    {
        return *(_plans_sub.end() - 1 );
    }
    unsigned int subplans_size() const
    {
        return _plans_sub.size();
    }
    int last_reached() const
    {
        return static_cast<int>( subplans_size() ) - 1;
    }
    unsigned int last_reached_safe() const
    {
      if ( subplans_size() == 0 ) return 0;
      if ( subplans_size() > this->size()) return this->size() - 1;
      return subplans_size() - 1 ;
    }
    void plan_global( Plan p );
    void plans_sub_add( Plan p );
    void plans_sub_reset();
     void printOn( std::ostream & out ) const;
    Decomposition::iterator iter_at( unsigned int i );
protected:
    Plan _plan_global;
    std::vector< Plan > _plans_sub;
}; 
void simplePrint( std::ostream & out, Decomposition & decompo );
} 
#endif
