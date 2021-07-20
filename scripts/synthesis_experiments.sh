domains=( "corridor" "fibo" "find" "gripper" "reverse" "select" "sorting" "triangular-sum" "visitall" )
bounds=(8 7 6 8 7 7 11 6 8)
heuristics=("h1" "h2" "h3" "h4" "h5" "h6" "h7" "h8" "h9" "h5 h1" )

total=${#domains[@]}
#total=1
for (( i=0; i<$(($total)); i++ ))
do
	for h in "${heuristics[@]}"
	do
		./scripts/time_memory.sh ./main.bin ${bounds[i]} "domain/synthesis/${domains[i]}/" $h
	done
    experiments_file=$experiments_file"_${argv[j]}"
done


