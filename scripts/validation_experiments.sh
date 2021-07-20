echo 'Validation with INFINITE detection...'

echo 'Random CORRIDOR...'
./scripts/time_memory.sh ./validator.bin experiments/synthesis/corridor_h5.prog domain/validation/corridor/ INF

echo 'Random FIBO...'
./scripts/time_memory.sh ./validator.bin experiments/synthesis/fibo_h5.prog domain/validation/fibo/ INF

echo 'Random FIND...'
./scripts/time_memory.sh ./validator.bin experiments/synthesis/find_h5.prog domain/validation/find/ INF

echo 'Random GRIPPER...'
./scripts/time_memory.sh ./validator.bin experiments/synthesis/gripper_h5.prog domain/validation/gripper/ INF

echo 'Random REVERSE...'
./scripts/time_memory.sh ./validator.bin experiments/synthesis/reverse_h5.prog domain/validation/reverse/ INF

echo 'Random SELECT...'
./scripts/time_memory.sh ./validator.bin experiments/synthesis/select_h5.prog domain/validation/select/ INF

echo 'Random SORTING...'
./scripts/time_memory.sh ./validator.bin experiments/synthesis/sorting_h5.prog domain/validation/sorting/ INF

echo 'Random TRIANGULAR-SUM...'
./scripts/time_memory.sh ./validator.bin experiments/synthesis/triangular-sum_h5.prog domain/validation/triangular-sum/ INF

echo 'Random VISITALL...'
./scripts/time_memory.sh ./validator.bin experiments/synthesis/visitall_h5.prog domain/validation/visitall/ INF



echo 'Validation without INFINITE detection...'

echo 'Random CORRIDOR...'
./scripts/time_memory.sh ./validator.bin experiments/synthesis/corridor_h5.prog domain/validation/corridor/ NOINF

echo 'Random FIBO...'
./scripts/time_memory.sh ./validator.bin experiments/synthesis/fibo_h5.prog domain/validation/fibo/ NOINF

echo 'Random FIND...'
./scripts/time_memory.sh ./validator.bin experiments/synthesis/find_h5.prog domain/validation/find/ NOINF

echo 'Random GRIPPER...'
./scripts/time_memory.sh ./validator.bin experiments/synthesis/gripper_h5.prog domain/validation/gripper/ NOINF

echo 'Random REVERSE...'
./scripts/time_memory.sh ./validator.bin experiments/synthesis/reverse_h5.prog domain/validation/reverse/ NOINF

echo 'Random SELECT...'
./scripts/time_memory.sh ./validator.bin experiments/synthesis/select_h5.prog domain/validation/select/ NOINF

echo 'Random SORTING...'
./scripts/time_memory.sh ./validator.bin experiments/synthesis/sorting_h5.prog domain/validation/sorting/ NOINF

echo 'Random TRIANGULAR-SUM...'
./scripts/time_memory.sh ./validator.bin experiments/synthesis/triangular-sum_h5.prog domain/validation/triangular-sum/ NOINF

echo 'Random VISITALL...'
./scripts/time_memory.sh ./validator.bin experiments/synthesis/visitall_h5.prog domain/validation/visitall/ NOINF
