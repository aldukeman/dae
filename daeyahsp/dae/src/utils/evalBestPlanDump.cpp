#include "evalBestPlanDump.h"
namespace daex {
void evalBestMakespanPlanDump::call( Decomposition & eo )
{
    if( eo.plan().makespan() < _best ) {
        _best = eo.plan().makespan();
        dump( eo );
    } 
}
void evalBestFitnessPlanDump::call( Decomposition & eo )
{
    if( eo.fitness() > _best ) {
        _best = eo.fitness();
        dump( eo );
    } 
}
} 
