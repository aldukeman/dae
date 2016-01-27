#ifndef DEA_H
#define DAE_H
#ifdef __cplusplus
extern "C"
{
#endif 
typedef struct Fluent * CPTFluent;
typedef struct SolutionPlan * CPTSolutionPlan;
typedef struct PDDLPredicate * CPTPredicate;
typedef struct PDDLTerm * CPTTerm;
typedef struct CPTFluentArray CPTFluentArray;
typedef struct CPTPredicateArray CPTPredicateArray;
typedef struct CPTTermArray CPTTermArray;
typedef struct CPTCostArray CPTCostArray;
typedef struct AttributeSpace AttributeSpace;
struct AttributeSpace {
  PDDLPredicate *predicate;
  long position;
  VECTOR(PDDLTerm *, constants);
};
EVECTOR(AttributeSpace *, att_spaces);
void create_attribute_spaces();
struct CPTFluentArray {
  CPTFluent *elems;
  int nb;
};
struct CPTPredicateArray {
  CPTPredicate *elems;
  int nb;
};
struct CPTTermArray {
  CPTTerm *elems;
  int nb;
};
struct CPTCostArray {
  long *elems;
  int nb;
};
extern void cptMakeProblem(char *cmd_line);
extern CPTFluentArray cptGetInit(void);
extern CPTFluentArray cptGetGoal(void);
extern char *cptGetFluentName(CPTFluent fluent);
extern int cptGetIndexFromFluent(CPTFluent fluent);
extern CPTFluent cptGetFluentFromIndex(int index);
extern CPTPredicateArray cptGetPredicates(void);
extern CPTPredicate cptGetPredicate(CPTFluent fluent);
extern CPTTermArray cptGetTerms(CPTFluent fluent);
extern int cptGetArity(CPTPredicate predicate);
extern const char * cptGetPredicateName(CPTPredicate predicate);
extern CPTTermArray cptGetPossibleTerms(CPTPredicate predicate, int position);
extern const char * cptGetTermName(CPTTerm term);
extern CPTFluent cptGetFluent(CPTPredicate predicate, CPTTermArray terms);
extern CPTFluent cptGetFluentFromName(char *name);
extern CPTFluentArray cptGetFluentArrayFromNames(char **names, int names_nb);
extern CPTFluentArray cptGetAllFluents(void);
extern int cptMutex(CPTFluent fluent1, CPTFluent fluent2);
extern void cptResetSearch(void);
extern CPTSolutionPlan cptSolveNext(CPTFluentArray goal);
extern CPTSolutionPlan cptCompressSolution(bool compress_causals, bool compress_orderings);
extern void cptPrintSolutionPlan(FILE *out, CPTSolutionPlan solution_plan);
extern void cptFreeSolutionPlan(CPTSolutionPlan solution_plan);
extern long cptGetMakespan(CPTSolutionPlan plan);
extern int cptGetLength(CPTSolutionPlan plan);
extern long cptGetBacktracks(CPTSolutionPlan plan);
extern double cptGetSearchTime(CPTSolutionPlan plan);
extern double cptGetTotalTime(CPTSolutionPlan plan);
extern double cptGetPreprocessingTime(CPTSolutionPlan plan);
extern void cptSetMaxBacktracks(long backtracks);
#define CPT_PLAN_FOUND 0	
#define CPT_GOALS_MUTEX 1	
#define CPT_INIT_PROP_FAILED 2	
#define CPT_BACKTRACK_LIMIT 3	
#define CPT_BOUND_LIMIT 4	
#define CPT_NO_PLAN 5		
extern int cptGetReturnCode(void);
extern CPTCostArray cptGetCosts();
extern CPTFluentArray cptGetFluentsByCost(long cost);
extern char cptGetFluentDifficulty(CPTFluent f1, CPTFluent f2);
extern long cptGetPGCD();
extern long cptGetPPCM();
extern void cptSetPDDL21(char *precision);
#ifdef __cplusplus
}
#endif 
#endif 
