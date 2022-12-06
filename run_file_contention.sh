cd temp_files
chmod +x makeFiles.sh
./makeFiles.sh
cd ..
echo "Temp files created"
for i in {2..8}
do
    n_processes=$(($i+1))
    echo "Running for ${n_processes} processes"
    make -s N_PROCESSES=$i -C src/ fileContention
done
