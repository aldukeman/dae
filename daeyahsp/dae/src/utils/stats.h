#ifndef __stats_h__
#define __stats_h__
#include <eo>
template< class EOT >
class eoBestIndividualStat : public eoSortedStat<EOT, std::string> 
{
public:
    using eoSortedStat<EOT, std::string>::value;
    eoBestIndividualStat( std::string description = "Best individual" ) : 
        eoSortedStat<EOT, std::string>("", description) 
    {}
    void operator()(const std::vector<const EOT*>& pop)  {
        std::ostringstream os;
        os << *(pop[0]);
        value() = os.str();
    }
};
template< class EOT >
class eoBestPlanStat : public eoBestIndividualStat<EOT> 
{
public: 
    using eoSortedStat<EOT, std::string>::value;
    eoBestPlanStat( std::string description = "Best plan" ) : 
        eoBestIndividualStat<EOT>( description ) 
    {}
    void operator()(const std::vector<const EOT*>& pop)  {
        std::ostringstream os;
        daex::Plan plan = (*(pop[0])).plan_copy(); 
        os << plan;
        value() = os.str();
    }
};
template< class EOT >
class eoBestPlanImprovedStat : public eoBestPlanStat< EOT >
{
public:
    typedef typename EOT::Fitness FitnessT;
    using eoSortedStat<EOT, std::string>::value;
    eoBestPlanImprovedStat( FitnessT worst_fitness, std::string description = "Best improved plan" ) : 
        _best_fitness( worst_fitness ), 
        eoBestPlanStat<EOT>( description ) 
    {}
    void operator()(const std::vector<const EOT*>& pop)  
    {
        daex::Decomposition best_decompo = *( pop[0] );
        if( best_decompo.fitness() > _best_fitness ) {
            _best_fitness = best_decompo.fitness();
            std::ostringstream os;
            daex::Plan plan = best_decompo.plan_copy(); 
            os << plan;
            value() = os.str();
        }
    }
protected:
    FitnessT _best_fitness;
};
#endif 
