#ifndef __DAEX_yahsp_plan_H__
#define __DAEX_yahsp_plan_H__
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <src/plan.h>
namespace daex
{
class Plan
{
protected:
    TimeVal _makespan;
    unsigned int _search_steps;
    bool _is_valid;
    std::string _plan_rep;
public:
    Plan( SolutionPlan * p_plan ) : _makespan(p_plan->makespan), _search_steps(0), _is_valid(true) 
      {   
        _plan_rep = plan_to_str( p_plan );
      }
      Plan() : _makespan( INT_MAX ), _search_steps(0), _is_valid(false),_plan_rep("No plan")
	{}
    void search_steps( unsigned int steps ) { _search_steps = steps; }
    unsigned int search_steps() const { return _search_steps; }
    TimeVal makespan() const { return _makespan; }
    std::string plan_to_str( SolutionPlan * p_plan )
    {        
        std::ostringstream out;
        char* buffer;
        size_t buffer_size;
        FILE* stream = open_memstream( & buffer, & buffer_size );
        if( stream == NULL ) {
            std::ostringstream msg;
            msg << "Cannot open memstream for printing Plan (" << p_plan << ")";
            throw std::runtime_error( msg.str() );
        }
        print_plan_ipc( stream, p_plan, 0.0 ); 
        fclose( stream );
        out << buffer;
        free( buffer );
        return out.str();
    }
    friend std::ostream& operator<<( std::ostream& out, Plan & plan )
    {
        out << plan._plan_rep;
	return out;
    }
};
} 
#endif 
