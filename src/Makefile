INCL_CPP= ../utils/timer.cpp ../utils/stats.cpp
OUTDIR = ../build

syscall:
	g++ -g -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/syscall CPU/syscall.cpp ${INCL_CPP}
	./${OUTDIR}/syscall
clean:
	rm ./${OUTDIR}/syscall