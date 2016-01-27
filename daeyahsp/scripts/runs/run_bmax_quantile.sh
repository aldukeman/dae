#!/bin/bash

# no core dump
ulimit -c 1

domain=$1
instance=$2
res=$3
quantile=$4
q=0.$quantile

r=$SGE_TASK_ID
#r=2
s=$((`date +%s`/r))

d=`echo $domain | cut -d '/' -f 7`
i=`basename $instance .pddl`

echo "----------------------------------------------------------------------"
echo "Run dae on $d : $i, run $r, b_max quantile $q" 1>&2
echo "----------------------------------------------------------------------"

cmd="./dae --max-seconds=1799 --domain=$domain --instance=$instance --seed=$s --status=$res/status/dae_status.${d}_${i}_q${q}_r$r --plan-file=$res/plans/dae_plan_${d}_${i}_q${q}_r$r --verbose=logging --bmax-quantile=${q} --runs-max=0"


echo "$cmd" 1>&2

$cmd

