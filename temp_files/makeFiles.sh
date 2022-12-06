for i in {0..11}
do
    file_name="file${i}.txt"
    # dd if=/dev/zero of=$file_name bs=64M count=1
    truncate -s 64M $file_name
done