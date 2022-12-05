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

server:
	g++ -g -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/server Network/server.cpp ${INCL_CPP}
	./${OUTDIR}/server 8070

client_setup:
	g++ -g -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/client_setup Network/client_setup.cpp ${INCL_CPP}
	./${OUTDIR}/client_setup localhost 8070

client_teardown:
	g++ -g -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/client_teardown Network/client_teardown.cpp ${INCL_CPP}
	./${OUTDIR}/client_teardown localhost 8070

fileContention:
	g++ -g -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/fileContention FS/fileContention.cpp ${INCL_CPP}
	./${OUTDIR}/fileContention 6

clean:
	rm -f ./${OUTDIR}/*