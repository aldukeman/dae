#!/bin/bash

# no core dump
ulimit -c 1

domain=$1
instance=$2
res=$3
seq=$4

r=$SGE_TASK_ID
#r=2
s=$((`date +%s`/r))

i=`basename $instance .PDDL`

echo "Run dae: $i, run $r, out $res" 1>&2

cmd="./dae --max-seconds=1799 --domain=$domain --instance=$instance --seed=$s --status=$res/status/dae_status_${i}_r$r --plan-file=$res/plans/dae_plan_${i}_r$r --runs-max=1"

echo "  $cmd" 1>&2

$cmd

filename="$res/plans/dae_plan_${d}_${i}_r$r"
lastfile=`ls -1 -v $filename* | tail -n 1`
cp $lastfile ${filename}.soln

if [ "$seq" = 0 ] ; then 
    cmd="./validate -t 0.00001 $domain $instance $filename"
else 
    cmd="./validate $domain $instance $filename"
fi

echo "  $cmd" 1>&2

$cmd
