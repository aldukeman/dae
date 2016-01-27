#ifndef __DAEX_INIT_H__
#define __DAEX_INIT_H__
#include <map>
#include <algorithm>
#include "core/decomposition.h"
#include "utils/pddl_load.h"
#include "utils/utils.h"
namespace daex {
class Init : public eoInit<Decomposition>
{
public:
    Init( const ChronoPartition & times, unsigned int l_max_init_coef = 2, unsigned int min_nb = 1 );
    void operator()( Decomposition & decompo );
public:
    void l_max( unsigned int l ) { _l_max = l; }
    unsigned int l_max() const { return _l_max; }
protected:
    const ChronoPartition & _times;
    const unsigned int _min_nb;
    const unsigned int _l_max_init_coef;
    unsigned int _l_max;
};
} 
#endif 
