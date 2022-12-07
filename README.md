# sys-perf

Experiments to characterize and understand a system's performance.

## Running experiments
`cd src` and then follow the commands below
### CPU, Scheduling, and OS Services
- Measurement overhead:
    1. Overhead of reading time: `make readTimeOverhead`
    2. Overhead of using a loop: `make readTimeOverheadLoop`
- Procedure call overhead: `make procedureCallOverhead`
- System call overhead: `make syscall`
- Task creation time: 
    1. Time to create a process: `make createProcess` 
    2. Time to create a thread: `make createThread`
- Context switch time(process switch): `make ctxswitch`. The data is output in in `data/CPU/ctxswitch.csv`.
- Context switch time(kenel thread switch): `make ctxswitchkernel`. The data is output in in `data/CPU/ctxswitchkernel.csv`.

### Memory
- RAM access time: `make ramAccessTime`
- RAM bandwidth(read): `make readBW`
- RAM bandwidth(write): `make writeBW` 
- Page fault service time: 
    1. First install cgroups using `apt install cgroup-tools`
    2. Then `make pageFault`

### Network
- Round trip time(remote and loopback): 
    1. On remote machine: `make remote_rtt`. 
    2. On primary machine: `make rtt`. You will need to modify the ip address specified in the make file for the `rtt` rule.
- Peak bandwidth(remote and loopback):
    1. On remote machine: `make remote_netbw`. 
    2. On primary machine: `make netbw`. You will need to modify the ip address specified in the make file for the `netbw` rule.
- Connection overhead:
    Loopback connection setup
    1. On primary machine (server): `make server`
    2. On primary machine (client): `make loopback_client_setup`

    Loopback connection teardown
    1. On primary machine (server): `make server`
    2. On primary machine (client): `make loopback_client_teardown`

    Remote connection setup
    1. On remote machine (server): `make server`
    2. On primary machine (client): `make remote_client_setup`. You will need to modify the ip address specified in the make file for the `remote_client_setup` rule.

    Remote connection teardown
    1. On remote machine (server): `make server`
    2. On primary machine (client): `make remote_client_teardown`. You will need to modify the ip address specified in the make file for the `remote_client_teardown` rule.   
    

### File System
- Size of file cache: `make fscacheSize`
- File read time: `make fileReadTime`
- Remote file read time: 
    1. Create an NFS directory on the remote. [REF](https://bluexp.netapp.com/blog/azure-anf-blg-linux-nfs-server-how-to-set-up-server-and-client)
    2. Mount the directory on the `temp` folder in `src/Filesystem/temp` using the command `sudo mount -t nfs -o noac,lookupcache=none XXX.XX.XX.XX:/{remote_nfs_dir} Filesystem/temp`
    3. `make remote_fileReadTime`
- Contention: `make fileContentionCompleteRun`
