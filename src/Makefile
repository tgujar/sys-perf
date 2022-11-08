INCL_CPP= ../utils/timer.cpp ../utils/stats.cpp
OUTDIR = ../build

syscall:
	g++ -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/syscall CPU/syscall.cpp ${INCL_CPP}
	./${OUTDIR}/syscall

ctxswitch:
	g++ -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/ctxswitch CPU/ctxswitch.cpp ${INCL_CPP}
	./${OUTDIR}/ctxswitch

ctxswitchkernel:
	g++ -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/ctxswitchkernel CPU/ctxswitchkernel.cpp ${INCL_CPP}
	./${OUTDIR}/ctxswitchkernel

readTimeOverhead:
	g++ -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/readTimeOverhead CPU/readTimeOverhead.cpp ${INCL_CPP}
	./${OUTDIR}/readTimeOverhead

readTimeOverheadLoop:
	g++ -g -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/readTimeOverheadLoop CPU/readTimeOverheadLoop.cpp ${INCL_CPP}
	./${OUTDIR}/readTimeOverheadLoop

procedureCallOverhead:
	g++ -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/procedureCallOverhead CPU/procedureCallOverhead.cpp ${INCL_CPP}
	./${OUTDIR}/procedureCallOverhead

createProcess:
	g++ -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/createProcess CPU/createProcess.cpp ${INCL_CPP}
	./${OUTDIR}/createProcess

createThread:
	g++ -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/createThread CPU/createThread.cpp ${INCL_CPP}
	./${OUTDIR}/createThread

ramAccessTime:
	g++ -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/ramAccessTime Memory/ramAccessTime1.cpp ${INCL_CPP}
	./${OUTDIR}/ramAccessTime

clean:
	rm -f ./${OUTDIR}/*