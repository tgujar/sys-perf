INCL_CPP= ../utils/timer.cpp ../utils/stats.cpp
OUTDIR = ../build

# CPU ops
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

# Memory OPS
ramAccessTime:
	g++ -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/ramAccessTime Memory/ramAccessTime1.cpp ${INCL_CPP}
	./${OUTDIR}/ramAccessTime
  
readBW:
	g++ -O2 -funroll-loops -g -I ../utils -DCPU_FREQ=2700 -o ${OUTDIR}/readBW Memory/readBW.cpp ${INCL_CPP}
	./${OUTDIR}/readBW

writeBW:
	g++ -O2 -funroll-loops -g -I ../utils -DCPU_FREQ=2700 -o ${OUTDIR}/writeBW Memory/writeBW.cpp ${INCL_CPP}
	./${OUTDIR}/writeBW

clean:
	rm -f ./${OUTDIR}/*

fileReadTime:
	bash Filesystem/createFile.sh
	g++ -g -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/fileReadTime_seq Filesystem/readtime_sequential.cpp ${INCL_CPP}
	g++ -g -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/fileReadTime_rand Filesystem/readtime_random.cpp ${INCL_CPP}
	./${OUTDIR}/fileReadTime_seq
	./${OUTDIR}/fileReadTime_rand
	rm Filesystem/temp/*.txt