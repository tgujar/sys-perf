INCL_CPP= ../utils/timer.cpp ../utils/stats.cpp ../utils/csvfile.h
OUTDIR = ../build

syscall:
	g++ -g -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/syscall CPU/syscall.cpp ${INCL_CPP}
	./${OUTDIR}/syscall

ctxswitch:
	g++ -g -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/ctxswitch CPU/ctxswitch.cpp ${INCL_CPP}
	./${OUTDIR}/ctxswitch
ctxswitchkernel:
	g++ -g -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/ctxswitchkernel CPU/ctxswitchkernel.cpp ${INCL_CPP}
	./${OUTDIR}/ctxswitchkernel

readTimeOverhead:
	g++ -g -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/readTimeOverhead CPU/readTimeOverhead.cpp ${INCL_CPP}
	./${OUTDIR}/readTimeOverhead

readTimeOverheadLoop:
	g++ -g -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/readTimeOverheadLoop CPU/readTimeOverheadLoop.cpp ${INCL_CPP}
	./${OUTDIR}/readTimeOverheadLoop

procedureCallOverhead:
	g++ -g -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/procedureCallOverhead CPU/procedureCallOverhead.cpp ${INCL_CPP}
	./${OUTDIR}/procedureCallOverhead

createProcess:
	g++ -g -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/createProcess CPU/createProcess.cpp ${INCL_CPP}
	./${OUTDIR}/createProcess

createThread:
	g++ -g -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/createThread CPU/createThread.cpp ${INCL_CPP}
	./${OUTDIR}/createThread

pageFault:
	bash Memory/createFile.sh
	g++ -g -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/pageFault Memory/pageFault.cpp ${INCL_CPP}
	./${OUTDIR}/pageFault

clean:
	rm -f ./${OUTDIR}/*