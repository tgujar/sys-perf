# sys-perf

Experiments to characterize and understand a system's performance.

## Running experiments
`cd src` and then follow the commands below
### CPU, Scheduling, and OS Services
- Measurement overhead
- Procedure call overhead:
- System call overhead: `make syscall`
- Task creation time:
- Context switch time(process switch): `make ctxswitch`
- Context switch time(kenel thread switch): `make ctxswitchkernel`

### Memory
- RAM access time
- RAM bandwidth(read): `make readBW`
- RAM bandwidth(write): `make writeBW` 
- Page fault service time

### Network
- Round trip time(remote and loopback): 
    1. On remote machine: `make remote_rtt`. 
    2. On primary machine: `make rtt`. You will need to modify the ip address specified in the make file for the `rtt` rule.
- Peak bandwidth(remote and loopback):
    1. On remote machine: `make remote_netbw`. 
    2. On primary machine: `make netbw`. You will need to modify the ip address specified in the make file for the `netbw` rule.
- Connection overhead

### File System
- Size of file cache
- File read time
- Remote file read time: 
    1. Create an NFS directory on the remote. [REF](https://bluexp.netapp.com/blog/azure-anf-blg-linux-nfs-server-how-to-set-up-server-and-client)
    2. Mount the directory on the `temp` folder in `src/Filesystem/temp` using the command `sudo mount -t nfs -o noac,lookupcache=none XXX.XX.XX.XX:/{remote_nfs_dir} Filesystem/temp`
    3. `make remote_fileReadTime`
- Contention