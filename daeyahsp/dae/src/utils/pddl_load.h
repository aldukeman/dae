#ifndef __PDDL_LOAD_H_
#define __PDDL_LOAD_H_
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <map>
#include <gmpxx.h>
#include <src/cpt.h>
#include <src/options.h>
#include <src/structs.h>
#include <src/problem.h>
#include <src/solve.h>
#include <src/globs.h>
#include "core/atom.h"
#define SOLVER_YAHSP "yahsp"
#define SOLVER_CPT   "cpt"
#define HEURISTIC_NO 0
#define HEURISTIC_H1 1
#define HEURISTIC_H2 2
namespace daex
{
class ChronoPartition : public std::map<TimeVal, std::vector< daex::Atom*> > 
{
public:
    ChronoPartition() : _goal_max_date(0) {}
    TimeVal goal_max_date() const { return _goal_max_date; }
    void compute_goal_max_date()
    {
        for( unsigned int i=0; i < goal_state_nb; ++i ) {
            _goal_max_date = std::max( _goal_max_date, goal_state[i]->init );
        } 
    }
protected:
    TimeVal _goal_max_date;
};
class pddlLoad
{
public:
    pddlLoad( std::string domain, std::string problem, std::string solver = SOLVER_YAHSP, unsigned int heuristic_start_times = HEURISTIC_H1,  std::vector<std::string> solver_args = std::vector<std::string>());
    ~pddlLoad();
    void load_pddl( std::string solver = SOLVER_YAHSP, unsigned int heuristic_start_times = HEURISTIC_H1,  std::vector<std::string> solver_args = std::vector<std::string>() );
    void compute_chrono_partition();
    std::vector< daex::Atom*> atoms() const { return this->_atoms; }
    const ChronoPartition & chronoPartitionAtom() { return this->_chrono_partition_atom; }
public:
    std::vector< daex::Atom*> _atoms;
protected:
    std::string _domain;
    std::string _problem;
    ChronoPartition _chrono_partition_atom;
};
} 
#endif 
