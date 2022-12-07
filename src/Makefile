INCL_CPP= ../utils/timer.cpp ../utils/stats.cpp
OUTDIR = ../build
NFSDIR = /mnt/files

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
	g++ -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/ramAccessTime Memory/ramAccessTime.cpp ${INCL_CPP}
	./${OUTDIR}/ramAccessTime
  
readBW:
	g++ -O2 -funroll-loops -g -I ../utils -DCPU_FREQ=2700 -o ${OUTDIR}/readBW Memory/readBW.cpp ${INCL_CPP}
	./${OUTDIR}/readBW

writeBW:
	g++ -O2 -funroll-loops -g -I ../utils -DCPU_FREQ=2700 -o ${OUTDIR}/writeBW Memory/writeBW.cpp ${INCL_CPP}
	./${OUTDIR}/writeBW

pageFault:
	bash Memory/createFile.sh
	g++ -g -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/pageFault Memory/pageFault.cpp ${INCL_CPP}
	cgexec -g memory:cgTeams  ./${OUTDIR}/pageFault
	rm sample.txt

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
	
# Filesystem 

fscacheSize:
	bash Filesystem/cache_size_create_file.sh
	g++ -g -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/cacheSize Filesystem/cache_size.cpp ${INCL_CPP}
	./${OUTDIR}/cacheSize
	rm Filesystem/temp/*.txt

fileReadTime:
	bash Filesystem/createFile.sh
	g++ -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/fileReadTime_seq Filesystem/readtime_sequential.cpp ${INCL_CPP}
	g++ -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/fileReadTime_rand Filesystem/readtime_random.cpp ${INCL_CPP}
	sudo ./${OUTDIR}/fileReadTime_seq
	sudo ./${OUTDIR}/fileReadTime_rand
	rm Filesystem/temp/*.txt

remote_fileReadTime:
	sudo mount -t nfs -o noac,lookupcache=none 192.168.1.245:${NFSDIR} Filesystem/temp
	bash Filesystem/remote_createFile.sh
	g++ -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/remote_fileReadTime_seq Filesystem/remote_readtime_sequential.cpp ${INCL_CPP}
	g++ -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/remote_fileReadTime_rand Filesystem/remote_readtime_random.cpp ${INCL_CPP}
	sudo ./${OUTDIR}/remote_fileReadTime_seq
	sudo ./${OUTDIR}/remote_fileReadTime_rand
	rm Filesystem/temp/f*.txt
	sudo umount Filesystem/temp

server:
	g++ -g -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/server Network/server.cpp ${INCL_CPP}
	./${OUTDIR}/server 8080

loopback_client_setup:
	g++ -g -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/client_setup Network/client_setup.cpp ${INCL_CPP}
	./${OUTDIR}/client_setup localhost 8080

loopback_client_teardown:
	g++ -g -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/client_teardown Network/client_teardown.cpp ${INCL_CPP}
	./${OUTDIR}/client_teardown localhost 8080

remote_client_setup:
	g++ -g -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/client_setup Network/client_setup.cpp ${INCL_CPP}
	./${OUTDIR}/client_setup "192.168.1.245" 8070

remote_client_teardown:
	g++ -g -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/client_teardown Network/client_teardown.cpp ${INCL_CPP}
	./${OUTDIR}/client_teardown "192.168.1.245" 8070

fileContention:
	g++ -g -I ../utils -DCPU_FREQ=2700  -o ${OUTDIR}/fileContention Filesystem/fileContention.cpp ${INCL_CPP}
	sudo ./${OUTDIR}/fileContention $(N_PROCESSES)

fileContentionCompleteRun:
	sudo bash Filesystem/run_file_contention.sh

clean:
	rm -f ./${OUTDIR}/*


