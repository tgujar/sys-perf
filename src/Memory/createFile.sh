sudo cgcreate -t ${USER}:${USER} -a ${USER}:${USER} -g memory:/cgTeams
echo $(( 16 * 1024 * 1024 )) | sudo tee /sys/fs/cgroup/memory/cgTeams/memory.limit_in_bytes
echo $(( 4 * 2049 * 1024 * 1024 )) | sudo tee /sys/fs/cgroup/memory/cgTeams/memory.memsw.limit_in_bytes
dd if=/dev/urandom of=sample.txt bs=1G count=1
for i in {1..2}; do cat sample.txt sample.txt > sample2.txt && mv sample2.txt sample.txt; done