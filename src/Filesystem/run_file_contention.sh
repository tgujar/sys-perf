cd Filesystem
chmod +x makeFiles.sh
./makeFiles.sh
echo "Temp files created"
cd ..
for i in {1..8}
do
    n_processes=$(($i+1))
    echo "Running for ${n_processes} processes"
    make -s N_PROCESSES=$i fileContention
    echo $'\n'
done
rm Filesystem/temp/file*.txt
