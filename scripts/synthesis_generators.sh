[ ! -d "domain/" ] && mkdir -p "domain"
[ ! -d "domain/synthesis/" ] && mkdir -p "domain/synthesis"
[ ! -d "experiments/" ] && mkdir -p "experiments"
[ ! -d "experiments/synthesis/" ] && mkdir -p "experiments/synthesis"

# AIJ domain
echo 'Generating Blocks Ontable synthesis instances...'
if [ -d "domain/synthesis/ontable/" ]; then
	rm domain/synthesis/ontable/*
else
	mkdir -p "domain/synthesis/ontable"
fi 
./domain/generators/ontable.py 2 6 1 domain/synthesis/ontable/

echo 'Generating Corridor synthesis instances...'
if [ -d "domain/synthesis/corridor/" ]; then
	rm domain/synthesis/corridor/*
else
	mkdir -p "domain/synthesis/corridor"
fi 
./domain/generators/corridor.py 2 11 domain/synthesis/corridor/

echo 'Generating Fibonacci synthesis instances...'
if [ -d "domain/synthesis/fibo/" ]; then
	rm domain/synthesis/fibo/*
else
	mkdir -p "domain/synthesis/fibo"
fi 
./domain/generators/fibo.py 2 11 domain/synthesis/fibo/

echo 'Generating Find synthesis instances...'
if [ -d "domain/synthesis/find/" ]; then
	rm domain/synthesis/find/*
else
	mkdir -p "domain/synthesis/find"
fi 
./domain/generators/find.py 2 1 11 domain/synthesis/find/

echo 'Generating Grid synthesis instances...'
if [ -d "domain/synthesis/grid/" ]; then
	rm domain/synthesis/grid/*
else
	mkdir -p "domain/synthesis/grid"
fi 
./domain/generators/grid.py 2 4 domain/synthesis/grid/

echo 'Generating Gripper synthesis instances...'
if [ -d "domain/synthesis/gripper/" ]; then
	rm domain/synthesis/gripper/*
else
	mkdir -p "domain/synthesis/gripper"
fi 
./domain/generators/gripper.py 2 11 domain/synthesis/gripper/

# AIJ domain
echo 'Generating Miconic synthesis instances...'
if [ -d "domain/synthesis/miconic/" ]; then
	rm domain/synthesis/miconic/*
else
	mkdir -p "domain/synthesis/miconic"
fi 
./domain/generators/miconic.py 2 6 0 domain/synthesis/miconic/

# AIJ domain
echo 'Generating Michalski Trains synthesis instances...'
if [ -d "domain/synthesis/mtrains/" ]; then
	rm domain/synthesis/mtrains/*
else
	mkdir -p "domain/synthesis/mtrains"
fi 
./domain/generators/mtrains.py domain/synthesis/mtrains/

echo 'Generating Reverse synthesis instances...'
if [ -d "domain/synthesis/reverse/" ]; then
	rm domain/synthesis/reverse/*
else
	mkdir -p "domain/synthesis/reverse"
fi 
./domain/generators/reverse.py synthesis 2 1 11 domain/synthesis/reverse/

# AIJ domain
echo 'Generating Satellite synthesis instances...'
if [ -d "domain/synthesis/satellite/" ]; then
	rm domain/synthesis/satellite/*
else
	mkdir -p "domain/synthesis/satellite"
fi 
./domain/generators/satellite.py 2 6 0 domain/synthesis/satellite/

echo 'Generating Select synthesis instances...'
if [ -d "domain/synthesis/select/" ]; then
	rm domain/synthesis/select/*
else
	mkdir -p "domain/synthesis/select"
fi 
./domain/generators/select.py synthesis 2 1 11 domain/synthesis/select/

# AIJ domain
echo 'Generating Sieve of Erathostenes synthesis instances...'
if [ -d "domain/synthesis/sieve/" ]; then
	rm domain/synthesis/sieve/*
else
	mkdir -p "domain/synthesis/sieve"
fi 
./domain/generators/sieve.py 2 11 domain/synthesis/sieve/

echo 'Generating Sorting synthesis instances...'
if [ -d "domain/synthesis/sorting/" ]; then
	rm domain/synthesis/sorting/*
else
	mkdir -p "domain/synthesis/sorting"
fi 
./domain/generators/sorting.py synthesis 2 1 11 domain/synthesis/sorting/

# AIJ domain
echo 'Generating Spanner synthesis instances...'
if [ -d "domain/synthesis/spanner/" ]; then
	rm domain/synthesis/spanner/*
else
	mkdir -p "domain/synthesis/spanner"
fi 
./domain/generators/spanner.py 2 6 0 domain/synthesis/spanner/

echo 'Generating Triangular Sum synthesis instances...'
if [ -d "domain/synthesis/triangular-sum/" ]; then
	rm domain/synthesis/triangular-sum/*
else
	mkdir -p "domain/synthesis/triangular-sum"
fi 
./domain/generators/triangular-sum.py 2 11 domain/synthesis/triangular-sum/

# AIJ new
echo 'Generating Visitall synthesis instances...'
if [ -d "domain/synthesis/visitall/" ]; then
	rm domain/synthesis/visitall/*
else
	mkdir -p "domain/synthesis/visitall"
fi 
./domain/generators/visitall.py 2 11 domain/synthesis/visitall/
