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

## Netowrk 
rtt:
	g++ -I ../utils -DREMOTE_IP=\"192.168.1.245\" -DREMOTE_PORT=8080 -DCPU_FREQ=2700 -o ${OUTDIR}/rtt Network/rtt.cpp ${INCL_CPP}
	./${OUTDIR}/rtt

remote_rtt:
	g++ -o ${OUTDIR}/remote_rtt Network/remote_rtt.cpp -lpthread
	./${OUTDIR}/remote_rtt

netbw:
	g++ -I ../utils -DREMOTE_IP=\"192.168.1.245\" -DREMOTE_PORT=8080 -DCPU_FREQ=2700 -o ${OUTDIR}/netbw Network/bw.cpp ${INCL_CPP}
	./${OUTDIR}/netbw

remote_netbw:
	g++ -o ${OUTDIR}/remote_netbw Network/remote_bw.cpp -lpthread
	./${OUTDIR}/remote_netbw
	
clean:
	rm -f ./${OUTDIR}/*