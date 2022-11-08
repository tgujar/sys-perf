dd if=/dev/urandom of=sample.txt bs=1G count=1
for i in {1..2}; do cat sample.txt sample.txt > sample2.txt && mv sample2.txt sample.txt; done
