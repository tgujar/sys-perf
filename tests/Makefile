INCL_CPP= ../utils/timer.cpp ../utils/stats.cpp
OUTDIR = ../build

timer-check:
	g++ -I ../utils -DCPU_FREQ=2700 -o ${OUTDIR}/timer timer_check.cpp ${INCL_CPP}
	./${OUTDIR}/timer

test-csv:
	g++ -I ../utils -o ${OUTDIR}/csv test_csv.cpp ${INCL_CPP}
	./${OUTDIR}/csv

clean:
	rm -f ${OUTDIR}/timer
	rm -f ${OUTDIR}/csv
