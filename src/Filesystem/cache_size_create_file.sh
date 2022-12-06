# dd if=/dev/urandom of=Filesystem/temp/file256M.txt bs=1M count=256
# dd if=/dev/urandom of=Filesystem/temp/file512M.txt bs=1M count=512
# dd if=/dev/urandom of=Filesystem/temp/file1G.txt bs=1G count=1
# dd if=/dev/urandom of=Filesystem/temp/file2G.txt bs=1G count=2
# cat Filesystem/temp/file2G.txt Filesystem/temp/file2G.txt > Filesystem/temp/file4G.txt
# cat Filesystem/temp/file4G.txt Filesystem/temp/file256M.txt > Filesystem/temp/file42G.txt
# cat Filesystem/temp/file4G.txt Filesystem/temp/file512M.txt > Filesystem/temp/file45G.txt
cat Filesystem/temp/file45G.txt Filesystem/temp/file256M.txt > Filesystem/temp/file47G.txt
# cat Filesystem/temp/file4G.txt Filesystem/temp/file1G.txt > Filesystem/temp/file5G.txt
# cat Filesystem/temp/file5G.txt Filesystem/temp/file1G.txt > Filesystem/temp/file6G.txt
# cat Filesystem/temp/file4G.txt Filesystem/temp/file4G.txt > Filesystem/temp/file8G.txt