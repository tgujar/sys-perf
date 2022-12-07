cd FS
chmod +x makeFiles.sh
./makeFiles.sh
echo "Temp files created"
cd ..
for i in {2..8}
do
    n_processes=$(($i+1))
    echo "Running for ${n_processes} processes"
    make -s N_PROCESSES=$i fileContention
    echo $'\n'
done
rm -rf FS/temp