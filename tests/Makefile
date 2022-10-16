INCL_CPP= ../utils/timer.cpp ../utils/stats.cpp
OUTDIR = ../build

timer-check:
	g++ -g -I ../utils -DCPU_FREQ=2700 -o ${OUTDIR}/timer timer_check.cpp ${INCL_CPP}
	./${OUTDIR}/timer

clean:
	rm ${OUTDIR}/timer
