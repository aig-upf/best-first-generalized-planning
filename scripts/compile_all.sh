echo 'Generating folders...'
[ ! -d "domain/" ] && mkdir -p "domain"

[ ! -d "domain/synthesis/" ] && mkdir -p "domain/synthesis"

[ ! -d "domain/synthesis/corridor/" ] && mkdir -p "domain/synthesis/corridor"
[ ! -d "domain/synthesis/fibo/" ] && mkdir -p "domain/synthesis/fibo"
[ ! -d "domain/synthesis/find/" ] && mkdir -p "domain/synthesis/find"
[ ! -d "domain/synthesis/grid/" ] && mkdir -p "domain/synthesis/grid"
[ ! -d "domain/synthesis/gripper/" ] && mkdir -p "domain/synthesis/gripper"
[ ! -d "domain/synthesis/miconic/" ] && mkdir -p "domain/synthesis/miconic"
[ ! -d "domain/synthesis/mtrains/" ] && mkdir -p "domain/synthesis/mtrains"
[ ! -d "domain/synthesis/ontable/" ] && mkdir -p "domain/synthesis/ontable"
[ ! -d "domain/synthesis/reverse/" ] && mkdir -p "domain/synthesis/reverse"
[ ! -d "domain/synthesis/satellite/" ] && mkdir -p "domain/synthesis/satellite"
[ ! -d "domain/synthesis/select/" ] && mkdir -p "domain/synthesis/select"
[ ! -d "domain/synthesis/sorting/" ] && mkdir -p "domain/synthesis/sorting"
[ ! -d "domain/synthesis/spanner/" ] && mkdir -p "domain/synthesis/spanner"
[ ! -d "domain/synthesis/triangular-sum/" ] && mkdir -p "domain/synthesis/triangular-sum"
[ ! -d "domain/synthesis/visitall/" ] && mkdir -p "domain/synthesis/visitall"

[ ! -d "domain/validation/" ] && mkdir -p "domain/validation"

[ ! -d "domain/validation/corridor/" ] && mkdir -p "domain/validation/corridor"
[ ! -d "domain/validation/fibo/" ] && mkdir -p "domain/validation/fibo"
[ ! -d "domain/validation/find/" ] && mkdir -p "domain/validation/find"
[ ! -d "domain/validation/grid/" ] && mkdir -p "domain/validation/grid"
[ ! -d "domain/validation/gripper/" ] && mkdir -p "domain/validation/gripper"
[ ! -d "domain/validation/miconic/" ] && mkdir -p "domain/validation/miconic"
[ ! -d "domain/validation/mtrains/" ] && mkdir -p "domain/validation/mtrains"
[ ! -d "domain/validation/ontable/" ] && mkdir -p "domain/validation/ontable"
[ ! -d "domain/validation/reverse/" ] && mkdir -p "domain/validation/reverse"
[ ! -d "domain/validation/satellite/" ] && mkdir -p "domain/validation/satellite"
[ ! -d "domain/validation/select/" ] && mkdir -p "domain/validation/select"
[ ! -d "domain/validation/sorting/" ] && mkdir -p "domain/validation/sorting"
[ ! -d "domain/validation/spanner/" ] && mkdir -p "domain/validation/spanner"
[ ! -d "domain/validation/triangular-sum/" ] && mkdir -p "domain/validation/triangular-sum"
[ ! -d "domain/validation/visitall/" ] && mkdir -p "domain/validation/visitall"

[ ! -d "experiments/" ] && mkdir -p "experiments"
[ ! -d "experiments/synthesis/" ] && mkdir -p "experiments/synthesis"
[ ! -d "experiments/validation/" ] && mkdir -p "experiments/validation"

echo 'Compiling the main project...'
./scripts/compile_main.sh
echo 'Compiling the validator...'
./scripts/compile_validator.sh
