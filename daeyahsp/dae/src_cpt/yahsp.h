#ifndef YAHSP_H
#define YAHSP_H
extern void yahsp_init();
extern int yahsp_main();
extern void yahsp_reset();
extern int yahsp_search(Fluent **init, long init_nb, Fluent **goals, long goals_nb);
extern int yahsp_compress_plans();
BitArray * get_current_state();
#endif 
