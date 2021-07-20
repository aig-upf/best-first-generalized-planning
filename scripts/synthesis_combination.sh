domains=( "corridor" "fibo" "find" "gripper" "reverse" "select" "sorting" "triangular-sum" "visitall" )
bounds=(8 7 6 8 7 7 11 6 8)
structural_f=("h1" "h2" "h3" "h7")
performance_f=("h4" "h5" "h6" "h8" "h9")

total=${#domains[@]}
#total=1
for (( i=0; i<$(($total)); i++ ))
do
	for sf in "${structural_f[@]}"
	do
		for pf in "${performance_f[@]}"
		do
			echo "Running ${domains[i]} $sf $pf..."
			./scripts/time_memory.sh ./main.bin ${bounds[i]} "domain/synthesis/${domains[i]}/" $sf $pf &
			echo "Running ${domains[i]} $pf $sf..."
			./scripts/time_memory.sh ./main.bin ${bounds[i]} "domain/synthesis/${domains[i]}/" $pf $sf
		done
	done
    experiments_file=$experiments_file"_${argv[j]}"
done



