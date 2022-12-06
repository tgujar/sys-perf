dd if=/dev/urandom of=Filesystem/temp/file512M.txt bs=1M count=512
dd if=/dev/urandom of=Filesystem/temp/file1G.txt bs=1G count=1
dd if=/dev/urandom of=Filesystem/temp/file2G.txt bs=1G count=2
cat Filesystem/temp/file2G.txt Filesystem/temp/file2G.txt > Filesystem/temp/file4G.txt
cat Filesystem/temp/file4G.txt Filesystem/temp/file1G.txt > Filesystem/temp/file5G.txt
cat Filesystem/temp/file5G.txt Filesystem/temp/file1G.txt > Filesystem/temp/file6G.txt
cat Filesystem/temp/file4G.txt Filesystem/temp/file4G.txt > Filesystem/temp/file8G.txt