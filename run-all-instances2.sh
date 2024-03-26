#!/bin/bash
ALGO=$1
LS=$2

if [[ $LS == "" ]]; then
	LS=3
fi 

DIFF=30
ITERATIONS=5
GPROF_FILE="gmon.out"
FLAG_D=0
FLAG_W=0
SCRIPT_MESSAGE="SCRIPT_MESSAGE "
#make clean
#make clean_log
#make

mkdir logs_gprof/$ALGO
mkdir logs_perf/$ALGO

function print(){
	echo "$SCRIPT_MESSAGE $1"
}

function moveGprofFile(){
		mv $GPROF_FILE "gmon_$1.out"
		mv "gmon_$1.out" logs_gprof/$ALGO/$FILE/
}

function execute(){
		#./main -f $FILE -i $i -a $ALGO -s $SC -l $LS -w 1
		#-e bpf-output
		print "ROUND $1"
		PERF_FILE="logs_perf/$ALGO/$FILE/$1.perf"
		perf stat -e branch-instructions -e branch-misses -e bus-cycles -e cache-misses -e cache-references -e cpu-cycles -e instructions -e ref-cycles -e stalled-cycles-frontend -e alignment-faults -e context-switches -e cpu-clock -e cpu-migrations -e dummy -e emulation-faults -e major-faults -e minor-faults -e page-faults -e task-clock -o $PERF_FILE ./main -f $FILE -i $1 -a $ALGO -l $LS -d $FLAG_D -w $FLAG_W
}

function trataErro(){
  print "Ocorreu uma falha de segmentação na iteração <<$1>>, vou executar novamente ..."

	from="$FILE"
	from+="_"
  	from+="$1"

  	to=$from
  	to+="_"
  	to+="SEGFAULT"

	mv "logs/$ALGO/$from/" "logs/$ALGO/$to/"
  	#mv "logs_gprof/$ALGO/$FILE/gmon_$1.out" "logs_gprof/$ALGO/$FILE/gmon_$1_SEGFAULT.out"

  	execute $1
}

function func1() {
   print "File: $FILE..."
   print "Stop Criteria: $SC"
   for ((i = 1; i <= $ITERATIONS; i++ ))
	do  
		START=$(date +%s)

		if [ $i == 1 ]; then
			cd logs_gprof/$ALGO/
			mkdir $FILE
			cd ../../

			cd logs_perf/$ALGO/
			mkdir $FILE
			cd ../../
		fi

		execute $i
		trap 'trataErro $i' SIGTERM SIGINT

		END=$(date +%s)
		DIFF=$(( $END - $START ))
		
		moveGprofFile $i
	done
}

A_START=$(date +%s)

#files=("V_TCCC130" "V_TCCC251" "V_TCCC412" "V_TCCC512" "V_TCCC761" "V_TCCC1000" "V_TCCC1253" "V_TCCC1517" "V_TCCC2010" "V_TCCC2313" "V_TCCC3478") 
#for ((j = 0; j < 2; j++ ))
#do
#	FILE=${files[$j]}

#	mkdir logs_gprof/$ALGO/$FILE
#	mkdir logs_perf/$ALGO/$FILE

#	print "File: $FILE..."
#	SC=10120
#	func1
#done


#FILE=V_TCCC130
#SC=10120
#func1

#FILE=V_TCCC251
#SC=10120
#func1

FILE=V_TCCC412
#SC=10120
func1

#FILE=V_TCCC512
#SC=10120
#func1

#FILE=V_TCCC761
#SC=10120
#func1

#FILE=V_TCCC1000
#SC=10120
#func1

#FILE=V_TCCC1253
#SC=10120
#func1

#FILE=V_TCCC1517
#SC=10120
#func1

#FILE=V_TCCC2010
#SC=10120
#func1

FILE=V_TCCC2313
#SC=10120
func1

FILE=V_TCCC3478
#SC=10120
func1


A_END=$(date +%s)
A_DIFF=$(( $A_END - $A_START ))
a_h=$(( $A_DIFF / 3600))

print "Time to run all instances $ITERATIONS times is: $a_h h ($A_DIFF s)"
