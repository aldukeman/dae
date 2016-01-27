#include <sys/time.h>
#include <sys/resource.h>
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <cfloat>
#include <eo>
#include <ga.h>
#include <utils/eoParserLogger.h>
#include <utils/eoLogger.h>
#include <utils/eoFeasibleRatioStat.h>
#include "daex.h"
#include "evaluation/yahsp.h"
#include "utils/evalBestPlanDump.h"
#include "evaluation/cpt-yahsp.h"
#define LOG_FILL ' '
#define FORMAT_LEFT_FILL_WIDTH(width) "\t" << std::left << std::setfill(LOG_FILL) << std::setw(width) 
#define FORMAT_LEFT_FILL_W_PARAM FORMAT_LEFT_FILL_WIDTH(20)
bool testDirRes(std::string _dirName, bool _erase);
void print_results( eoPop<daex::Decomposition> pop, time_t time_start )
{
    (void) time_start;
#ifndef NDEBUG
    struct rusage usage;
    getrusage(RUSAGE_SELF,&usage);
    eo::log << eo::warnings << "OS statistics:" << std::endl;
    eo::log << eo::warnings << FORMAT_LEFT_FILL_WIDTH(30) << "user time used"               << usage.ru_utime.tv_sec << "." << usage.ru_utime.tv_usec << " s." << std::endl;
    eo::log << eo::warnings << FORMAT_LEFT_FILL_WIDTH(30) << "system time used"             << usage.ru_stime.tv_sec << "." << usage.ru_stime.tv_usec << " s." << std::endl;
    eo::log << eo::warnings << FORMAT_LEFT_FILL_WIDTH(30) << "page reclaims * page size"   << usage.ru_minflt * getpagesize() << " b." 
                                         << " (~ " << std::setprecision(2) << usage.ru_minflt * getpagesize() / 1048576 << " Mb.)" << std::endl; 
    eo::log << eo::warnings << FORMAT_LEFT_FILL_WIDTH(30) << "page reclaims"                << usage.ru_minflt               << std::endl;
    eo::log << eo::warnings << std::endl;
    eo::log << eo::warnings << FORMAT_LEFT_FILL_WIDTH(30) << "page faults"                  << usage.ru_majflt               << std::endl;
    eo::log << eo::warnings << FORMAT_LEFT_FILL_WIDTH(30) << "maximum resident set size"    << usage.ru_maxrss               << " b." << std::endl;
    eo::log << eo::warnings << FORMAT_LEFT_FILL_WIDTH(30) << "integral shared memory size"  << usage.ru_ixrss                << " b." << std::endl;
    eo::log << eo::warnings << FORMAT_LEFT_FILL_WIDTH(30) << "integral unshared data size"  << usage.ru_idrss                << " b." << std::endl;
    eo::log << eo::warnings << FORMAT_LEFT_FILL_WIDTH(30) << "integral unshared stack size" << usage.ru_isrss                << " b." << std::endl;
    eo::log << eo::warnings << FORMAT_LEFT_FILL_WIDTH(30) << "swaps"                        << usage.ru_nswap                << std::endl;
    eo::log << eo::warnings << FORMAT_LEFT_FILL_WIDTH(30) << "block input operations"       << usage.ru_inblock              << std::endl;
    eo::log << eo::warnings << FORMAT_LEFT_FILL_WIDTH(30) << "block output operations"      << usage.ru_oublock              << std::endl;
    eo::log << eo::warnings << FORMAT_LEFT_FILL_WIDTH(30) << "messages sent"                << usage.ru_msgsnd               << std::endl;
    eo::log << eo::warnings << FORMAT_LEFT_FILL_WIDTH(30) << "messages received"            << usage.ru_msgrcv               << std::endl;
    eo::log << eo::warnings << FORMAT_LEFT_FILL_WIDTH(30) << "signals received"             << usage.ru_nsignals             << std::endl;
    eo::log << eo::warnings << FORMAT_LEFT_FILL_WIDTH(30) << "voluntary context switches"   << usage.ru_nvcsw                << std::endl;
    eo::log << eo::warnings << FORMAT_LEFT_FILL_WIDTH(30) << "involuntary context switches" << usage.ru_nivcsw               << std::endl;
    unsigned int subsolver_steps = 0;
    for( unsigned int i=0; i < pop.size(); i++ ) {
        for( unsigned int j=0; j < pop[i].subplans().size(); j++ ) {
             subsolver_steps += pop[i].subplan(j).search_steps();
        }
    }
    eo::log << eo::progress << "DAEx sub-solver steps " << subsolver_steps << std::endl;
    eo::log << eo::progress << "DAEx user time " << usage.ru_utime.tv_sec << "." << usage.ru_utime.tv_usec << " (seconds of user time in CPU)" << std::endl;
    eo::log << eo::progress << "DAEx wallclock time " << std::difftime( std::time(NULL), time_start )  << " (seconds)" << std::endl;
#endif
    pop.sort();
#ifndef NDEBUG
    std::cout << IPC_PLAN_COMMENT << pop.front() << std::endl;
#endif
    std::cout << pop.front().plan() << std::endl;
}
int main ( int argc, char* argv[] )
{
    time_t time_start = std::time(NULL);
    eoParserLogger parser(argc, argv);
    make_verbose(parser);
#ifndef NDEBUG
    struct rlimit limit;
    getrlimit(RLIMIT_AS, &limit);
    eo::log << eo::logging << "Maximum size of the process virtual memory (soft,hard)=" << limit.rlim_cur << ", " << limit.rlim_max << std::endl;
    getrlimit(RLIMIT_DATA, &limit);
    eo::log << eo::logging << "Maximum size of the process   data segment (soft,hard)=" << limit.rlim_cur << ", " << limit.rlim_max << std::endl;
#endif
    eo::log << eo::logging << "Parameters:" << std::endl;
    std::string domain = parser.createParam( (std::string)"domain-zeno-time.pddl", "domain", "PDDL domain file", 'D', "Problem", true ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "domain" << domain << std::endl;
    std::string instance = parser.createParam( (std::string)"zeno10.pddl", "instance", "PDDL instance file", 'I', "Problem", true ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "instance" << instance << std::endl;
    unsigned int pop_size = parser.createParam( (unsigned int)100, "popSize", "Population Size", 'P', "Evolution Engine").value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "pop_size" << pop_size << std::endl;
    eoValueParam<unsigned int> & param_seed = parser.createParam( (unsigned int)0, "seed", "Random number seed", 'S' );
    if ( param_seed.value() == 0) {
      param_seed.value()=time(0); 
    }
    unsigned int seed = param_seed.value();
    rng.reseed( seed );
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "seed" << seed << std::endl;
    unsigned int l_max_init_coef = parser.createParam( (unsigned int)2, "lmax-initcoef", 
            "l_max will be set to the size of the chrono partition * this coefficient", 'C', "Initialization" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "l_max_init_coef" << l_max_init_coef << std::endl;
    unsigned int l_min = parser.createParam( (unsigned int)1, "lmin", 
            "Minimum number of goals in a decomposition", 'l', "Initialization" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "l_min" << l_min << std::endl;
    unsigned int toursize = parser.createParam( (unsigned int)5, "tournament", 
            "Size of the deterministic tournament for the selection", 't', "Selection" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "toursize" << toursize << std::endl;
    double offsprings = parser.createParam( (double)700, "offsprings", 
            "Number of offsprings to produces", 'f', "Selection" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "offsprings" << offsprings << std::endl;
    unsigned int fitness_weight = parser.createParam( (unsigned int)10, "fitness-weight", 
            "Unknown weight in the feasible and unfeasible fitness computation", 'W', "Evaluation" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "fitness_weight" << fitness_weight << std::endl;
    unsigned int fitness_penalty = parser.createParam( (unsigned int)2, "fitness-penalty", 
            "Penalty in the unfeasible fitnesses computation", 'w', "Evaluation" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "fitness_penalty" << fitness_penalty << std::endl;
    unsigned int b_max_init = parser.createParam( (unsigned int)1e4, "bmax-init", "Number of allowed expanded nodes for the initial computation of b_max", 'B', "Evaluation" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "b_max_init" << b_max_init << std::endl;
    unsigned int b_max_fixed = parser.createParam( (unsigned int)0, "bmax-fixed", "Fixed number of allowed expanded nodes. Overrides bmaxinit if != 0", 'b', "Evaluation" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "b_max_fixed" << b_max_fixed << std::endl;
    double b_max_last_weight = parser.createParam( (double)3, "bmax-last-weight",
            "Weighting for the b_max used during the last search towards the end goal (must be strictly positive)", 'T', "Evaluation" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "b_max_last_weight" << b_max_last_weight << std::endl;
    if( b_max_last_weight <= 0 ) {
        std::cout << "bmax-last-weight must be strictly positive (=" << b_max_last_weight << ") type --help for usage." << std::endl;
        exit(1);
    }
    double b_max_ratio = parser.createParam( 0.01, "bmax-ratio","Satisfying proportion of feasible individuals for the computation of b_max", 'J', "Evaluation" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "b_max_ratio" << b_max_ratio << std::endl;
    double b_max_increase_coef = parser.createParam( (double)2, "bmax-increase-coef", "Multiplier increment for the computation of b_max", 'K', "Evaluation" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "b_max_increase_coef" << b_max_increase_coef << std::endl;
    unsigned int maxtry_candidate = 0; 
    unsigned int maxtry_mutex = 0;     
    std::string plan_file = parser.createParam( (std::string)"plan.soln", "plan-file", "Plan file backup", 'F', "Misc" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "plan-file" << plan_file << std::endl;
    unsigned int radius = parser.createParam( (unsigned int)2, "radius", 
            "Number of neighbour goals to consider for the addGoal mutation", 'R', "Variation" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "radius" << radius << std::endl;
    double proba_change = parser.createParam( (double)0.8, "proba-change", 
            "Probability to change an atom for the changeAtom mutation", 'c', "Variation" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "proba_change" << proba_change << std::endl;
    double proba_del_atom = parser.createParam( (double)0.8, "proba-del-atom", 
            "Average probability to delete an atom for the delAtom mutation", 'd', "Variation" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "proba_del_atom" << proba_del_atom << std::endl;
    double w_delgoal = parser.createParam( (double)1, "w-delgoal", 
            "Relative weight defining the probability to call the delGoal mutation", 'a', "Variation" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "w_delgoal" << w_delgoal << std::endl;
    double w_addgoal = parser.createParam( (double)3, "w-addgoal", 
            "Relative weight defining the probability to call the addGoal mutation", 'A', "Variation" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "w_addgoal" << w_addgoal << std::endl;
    double w_delatom = parser.createParam( (double)1, "w-delatom", 
            "Relative weight defining the probability to call the delAtom mutation", 'g', "Variation" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "w_delatom" << w_delatom << std::endl;
    double w_addatom = parser.createParam( (double)1, "w-addatom", 
            "Relative weight defining the probability to call the addAtom mutation", 'G', "Variation" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "w_addatom" << w_addatom << std::endl;
    double proba_cross = parser.createParam( (double)0.2, "proba-cross", 
            "Probability to apply a cross-over", 'c', "Variation" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "proba_cross" << proba_cross << std::endl;
    double proba_mut = parser.createParam( (double)0.8, "proba-mut", 
            "Probability to apply one of the mutation", 'm', "Variation" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "proba_mut" << proba_mut << std::endl;
    unsigned int max_seconds = parser.createParam( (unsigned int)0, "max-seconds", 
            "Maximum number of user seconds in CPU for the whole search, set it to 0 to deactivate (1800 = 30 minutes)", 'i', "Stopping criterions" ).value(); 
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "max_seconds" << max_seconds << std::endl;
    unsigned int mingen = parser.createParam( (unsigned int)10, "gen-min", 
            "Minimum number of iterations", 'n', "Stopping criterions" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "mingen" << mingen << std::endl;
    unsigned int steadygen = parser.createParam( (unsigned int)50, "gen-steady", 
            "Number of iterations without improvement", 's', "Stopping criterions" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "steadygen" << steadygen << std::endl;
    unsigned int maxgens = parser.createParam( (unsigned int)1000, "gen-max", 
            "Maximum number of iterations", 'x', "Stopping criterions" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "maxgens" << maxgens << std::endl;
    unsigned int maxruns = parser.createParam( (unsigned int)0, "runs-max", 
            "Maximum number of runs, if x==0: unlimited multi-starts, if x>1: will do <x> multi-start", 'r', "Stopping criterions" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "maxruns" << maxruns << std::endl;
#ifndef NDEBUG
    eoValueParam<std::string>& dirNameParam =  parser.createParam(std::string("Res"), "resDir", "Directory to store DISK outputs", '\0', "Output - Disk");
    eoValueParam<bool>& eraseParam = parser.createParam(true, "eraseDir", "erase files in dirName if any", '\0', "Output - Disk");
    eoValueParam<unsigned>& saveFrequencyParam = parser.createParam(unsigned(0), "saveFrequency", "Save every F generation (0 = only final state, absent = never)", '\0', "Persistence" );
#endif
    std::string plusOrComma =  parser.createParam(std::string("Comma"), "plusOrComma", "Plus (parents+offspring) or Comma (only offspring) for replacement", '\0', "Evolution Engine").value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "plusOrComma" << plusOrComma << std::endl;
    unsigned replaceTourSize = parser.createParam(unsigned(1), "replaceTourSize", "Size of Replacement Tournament (1->deterministic (hum, pas logique ;-(", '\0', "Evolution Engine" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "replaceTourSize" << replaceTourSize << std::endl;
    bool removeDuplicates = parser.createParam(false, "removeDuplicates", "Does not allow duplicates in replacement (if possible)", '\0', "Evolution Engine").value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "removeDuplicates" << removeDuplicates << std::endl;
    bool weakElitism = parser.createParam(true, "weakElitism", "Weak Elitism in replacement", '\0', "Evolution Engine").value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "weakElitism" << weakElitism << std::endl;
    make_help( parser );
#ifndef NDEBUG
    eo::log << eo::progress << "Load the instance..." << std::endl;
    eo::log.flush();
#endif
    daex::pddlLoad pddl( domain, instance, SOLVER_YAHSP, HEURISTIC_H1 );
#ifndef NDEBUG
    eo::log << eo::progress << "Load the instance...OK" << std::endl;
    eo::log << eo::progress << "Initialization...";
    eo::log.flush();
#endif
    daex::Init init( pddl.chronoPartitionAtom(), l_max_init_coef, l_min );
#ifndef NDEBUG
    eo::log << eo::logging << std::endl;
    eo::log << eo::logging << "\tChrono partition size: " << pddl.chronoPartitionAtom().size() << std::endl;
    eo::log << eo::logging << "\tl_max: " << init.l_max() << std::endl;
    eo::log << eo::debug << "\tChrono partition dates(#atoms): ";
    for( daex::ChronoPartition::const_iterator it = pddl.chronoPartitionAtom().begin(), end = pddl.chronoPartitionAtom().end(); it != end; ++it ) {
         eo::log << eo::debug << it->first << "(" << it->second.size() << ") ";
    }
    eo::log << eo::debug << std::endl;
#endif
    eoPop<daex::Decomposition> pop = eoPop<daex::Decomposition>( pop_size, init );
    unsigned int b_max_in=1, b_max_last, goodguys=0, popsize = pop.size();
#ifndef NDEBUG
    unsigned int eval_count = 0;
#endif
    TimeVal best_makespan = INT_MAX; 
    std::string dump_sep = ".";
    unsigned int dump_file_count = 1;
    std::string metadata = "domain " + domain + "\n" + IPC_PLAN_COMMENT + "instance " + instance;
    daex::Decomposition empty_decompo;
    bool found = false;
    if( b_max_fixed == 0 ) {
#ifndef NDEBUG
        eo::log << eo::progress << "Apply an incremental computation strategy to fix bmax:" << std::endl;
#endif
	while( (((double)goodguys/(double)popsize) < b_max_ratio) && (b_max_in < b_max_init) ) {
	    goodguys=0;
            b_max_last = static_cast<unsigned int>( std::floor( b_max_in * b_max_last_weight ) );
            daeYahspEval eval_yahsp( init.l_max(), b_max_in, b_max_last, fitness_weight, fitness_penalty );
            daex::evalBestMakespanPlanDump eval_bestfile( eval_yahsp, plan_file, best_makespan, false, dump_sep, dump_file_count, metadata );
#ifndef NDEBUG
            eoEvalFuncCounter<daex::Decomposition> eval_counter( eval_bestfile, "Eval.\t" );
            eval_counter.value( eval_count );
            eoPopLoopEval<daex::Decomposition> eval_y( eval_counter );
#else
            eoPopLoopEval<daex::Decomposition> eval_y( eval_bestfile );
#endif
            eval_y( pop, pop );
#ifndef NDEBUG
	    eoBestFitnessStat<daex::Decomposition> best_statTEST("Best");
	    best_statTEST(pop);
	    eo::log << eo::logging << "\tbest_fitness " << best_statTEST.value();
#endif
            for (size_t i = 0; i < popsize; ++i) {
                if (pop[i].fitness().is_feasible()) goodguys++;
                else pop[i].invalidate();
            }
            if ((goodguys == 0) && (!found)) {
                empty_decompo.invalidate();
#ifndef NDEBUG
                eval_counter(empty_decompo);
#else
                eval_bestfile(empty_decompo);
#endif
                if (empty_decompo.fitness().is_feasible()){
                    found = true;
                }
            } 
            best_makespan = eval_bestfile.best();
            dump_file_count = eval_bestfile.file_count();
#ifndef NDEBUG
            eo::log << eo::logging << "\tb_max_in "   << b_max_in << "\tfeasible_ratio " <<  ((double)goodguys/(double)popsize);
            eo::log << "\tbest_makespan " << best_makespan;
            if(found) {
                eo::log << "\tfeasible empty decomposition";
            }
            eo::log << std::endl;
            eval_count = eval_counter.value();
#endif
            b_max_fixed = b_max_in;
            b_max_in = (unsigned int)ceil(b_max_in*b_max_increase_coef);
        } 
    } 
    b_max_in = b_max_fixed;
    b_max_last = static_cast<unsigned int>( std::floor( b_max_in * b_max_last_weight ) );
    daeYahspEval eval_yahsp( init.l_max(), b_max_in, b_max_last, fitness_weight, fitness_penalty );
    eoPopLoopEval<daex::Decomposition> eval_y( eval_yahsp );
    eval_y( pop, pop );
#ifndef NDEBUG
    eo::log << eo::logging << std::endl << "\tb_max for intermediate goals, b_max_in: "   << b_max_in   << std::endl;
    eo::log << eo::logging              << "\tb_max for        final goal,  b_max_last: " << b_max_last << std::endl;
    eo::log << eo::progress << "OK" << std::endl;
    eo::log << eo::progress << "Creating evaluators...";
    eo::log.flush();
#endif
    eoEvalFunc<daex::Decomposition> * p_eval;
    daex::evalBestMakespanPlanDump eval_bestfile( eval_yahsp, plan_file, best_makespan, false, dump_sep, dump_file_count, metadata );
#ifndef NDEBUG
    eoEvalFuncCounter<daex::Decomposition> eval_counter( eval_bestfile, "Eval.\t" );
    eval_counter.value( eval_count );
#endif
    if( max_seconds == 0 ) {
#ifndef NDEBUG
        p_eval = & eval_counter;
#else
        p_eval = & eval_bestfile;
#endif
    } else {
        eoEvalUserTimeThrowException<daex::Decomposition> * p_eval_maxtime
#ifndef NDEBUG
            = new eoEvalUserTimeThrowException<daex::Decomposition>( eval_counter, max_seconds );
#else
            = new eoEvalUserTimeThrowException<daex::Decomposition>( eval_bestfile, max_seconds );
#endif
        p_eval = p_eval_maxtime;
    }
#ifndef NDEBUG
    eo::log << eo::progress << "OK" << std::endl;
#endif
#ifndef NDEBUG
    eo::log << eo::progress << "Algorithm instanciation...";
    eo::log.flush();
#endif
    eoSteadyFitContinue<daex::Decomposition> steadyfit( mingen, steadygen );
    eoGenContinue<daex::Decomposition> maxgen( maxgens );
    eoCombinedContinue<daex::Decomposition> continuator( steadyfit );
    continuator.add(maxgen);
    eoCheckPoint<daex::Decomposition> checkpoint( continuator );
#ifndef NDEBUG
    eoOStreamMonitor clog_monitor( std::clog, "\t", 10, ' '); 
    eoBestFitnessStat<daex::Decomposition> best_stat("Best");
    eoInterquartileRangeStat<daex::Decomposition> iqr_f( std::make_pair(0.0,false), "IQR_f" );
    eoInterquartileRangeStat<daex::Decomposition> iqr_uf( std::make_pair(0.0,false), "IQR_uf" );
    eoDualStatSwitch<daex::Decomposition,eoInterquartileRangeStat<daex::Decomposition> > dual_iqr( iqr_f, iqr_uf, "\t" );
    eoNthElementFitnessStat<daex::Decomposition> median_stat( pop.size() / 2, "Median" ); 
    eoFeasibleRatioStat<daex::Decomposition> feasible_stat( "F.Ratio" );
    eoAverageSizeStat<daex::Decomposition> asize_stat( "Av.Size" );
    if( eo::log.getLevelSelected() >= eo::progress ) {
        checkpoint.add( best_stat );
        checkpoint.add( feasible_stat );
        checkpoint.add( asize_stat );
        checkpoint.add( median_stat );
        checkpoint.add( dual_iqr );
        clog_monitor.add( eval_counter );
        clog_monitor.add( best_stat );
        clog_monitor.add( asize_stat );
        clog_monitor.add( feasible_stat );
        clog_monitor.add( median_stat );
        clog_monitor.add( dual_iqr );
        checkpoint.add( clog_monitor );
    }
    eoState state;
    state.registerObject(parser);
    state.registerObject(pop);
    state.registerObject(eo::rng);
    bool dirOK = false;
    if (parser.isItThere(saveFrequencyParam)) {
      if (! dirOK ) {
	dirOK = testDirRes(dirNameParam.value(), eraseParam.value());
    eo::log << eo::progress << "TESTRESDIR" << std::endl;
      }
    }
    unsigned freq = (saveFrequencyParam.value()>0 ? saveFrequencyParam.value() : UINT_MAX );
    std::string stmp = dirNameParam.value() + "/generations";
    eoCountedStateSaver stateSaver1 (freq, state, stmp);
    checkpoint.add(stateSaver1);
#endif 
    eoSelectOne<daex::Decomposition> * p_selectone;
    if ( toursize == 1 ) {
      p_selectone = (eoSelectOne<daex::Decomposition> *) ( new eoSequentialSelect<daex::Decomposition> ( true ) );
    }
    else {
      p_selectone = (eoSelectOne<daex::Decomposition> *) ( new eoDetTournamentSelect<daex::Decomposition> ( toursize ) );
    }
    daex::MutationDelGoal delgoal;
    daex::MutationDelAtom delatom( proba_del_atom );
    daex::MutationAddGoal addgoal( pddl.chronoPartitionAtom(), radius  );
    daex::MutationChangeAddAtom addatom( pddl.chronoPartitionAtom(), proba_change, maxtry_candidate, maxtry_mutex );
    eoPropCombinedMonOp<daex::Decomposition> mutator( delgoal, w_delgoal );
    mutator.add( delatom, w_delatom );
    mutator.add( addgoal, w_addgoal );
    mutator.add( addatom, w_addatom );
    daex::CrossOverTimeFilterHalf crossover;
    eoSGAGenOp<daex::Decomposition> variator( crossover, proba_cross, mutator, proba_mut);
    eoGeneralBreeder<daex::Decomposition> breed( *p_selectone, variator, offsprings, false ); 
    eoReplacement<daex::Decomposition> * pt_replace;
    eoMerge<daex::Decomposition> * pt_merge;
    if (plusOrComma == "Comma") {
      pt_merge = (eoMerge<daex::Decomposition> *) (new eoNoElitism<daex::Decomposition>);
    } else { 
      pt_merge = (eoMerge<daex::Decomposition> *) (new eoPlus<daex::Decomposition>);
    }
    eoReduce<daex::Decomposition> * pt_reduce;
    if (replaceTourSize == 1) {
      pt_reduce = (eoReduce<daex::Decomposition> *) (new eoTruncate<daex::Decomposition>);
    } else {
      pt_reduce = (eoReduce<daex::Decomposition> *) (new eoDetTournamentTruncate<daex::Decomposition> ( replaceTourSize ));
    }
    eoMergeReduce<daex::Decomposition> mergeReduce (*pt_merge, *pt_reduce);
    if (weakElitism) {
	pt_replace = (eoReplacement<daex::Decomposition> *) (new eoWeakElitistReplacement<daex::Decomposition> ( mergeReduce ) );
      } else {
	pt_replace = &mergeReduce;
      }
    eoEasyEA<daex::Decomposition> dae( checkpoint, *p_eval, breed, (*pt_replace) );
#ifndef NDEBUG
    eo::log << eo::progress << "OK" << std::endl;
    eo::log << eo::progress << "Note: dual fitness is printed as two numbers: a value followed by a boolean (0=unfeasible, 1=feasible)" << std::endl;
    eo::log.flush();
    eo::log << eo::debug << "Legend: \n\t- already valid, no eval\n\tx plan not found\n\t* plan found\n\ta add atom\n\tA add goal\n\td delete atom\n\tD delete goal\n\tC crossover" << std::endl;
#endif
    daex::Decomposition best = pop.best_element();
    unsigned int run = 1;
    try { 
        while( true ) {
#ifndef NDEBUG
            eo::log << eo::progress << "Start the " << run << "th run..." << std::endl;
            checkpoint( pop );
#endif
            dae( pop );
            daex::Decomposition best_of_run = pop.best_element();
            if( best_of_run.fitness() > best.fitness() ) { 
               best = best_of_run;
            }
            run++;
            if( run >= maxruns && maxruns != 0 ) {
                break;
            }
            pop = eoPop<daex::Decomposition>( pop_size, init );
            eoPopLoopEval<daex::Decomposition> pop_eval( *p_eval );
            pop_eval( pop, pop );
            steadyfit.totalGenerations( mingen, steadygen );
            maxgen.totalGenerations( maxgens );
        }
    } catch( std::exception& e ) {
#ifndef NDEBUG
        eo::log << eo::warnings << "STOP: " << e.what() << std::endl;
        eo::log << eo::progress << "... premature end of search, current result:" << std::endl;
#endif
        pop.push_back( best );
#ifndef NDEBUG
        checkpoint( pop );
#endif
        pop.push_back( empty_decompo );
        print_results( pop, time_start );
        return 0;
    }
#ifndef NDEBUG
    eo::log << eo::progress << "... end of search" << std::endl;
#endif
    pop.push_back( empty_decompo );
    pop.push_back( best );
    print_results( pop, time_start );
    return 0;
}
