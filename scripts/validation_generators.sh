[ ! -d "domain/" ] && mkdir -p "domain"
[ ! -d "domain/validation/" ] && mkdir -p "domain/validation"
[ ! -d "experiments/" ] && mkdir -p "experiments/"
[ ! -d "experiments/validation/" ] && mkdir -p "experiments/validation"

# AIJ domain
echo 'Generating Blocks Ontable validation instances...'
if [ -d "domain/validation/ontable/" ]; then
	rm domain/validation/ontable/*
else
	mkdir -p "domain/validation/ontable"
fi 
./domain/generators/ontable.py 12 31 1 domain/validation/ontable/

echo 'Generating Corridor validation instances...'
if [ -d "domain/validation/corridor/" ]; then
	rm domain/validation/corridor/*
else
	mkdir -p "domain/validation/corridor"
fi 
./domain/generators/corridor.py 12 1011 domain/validation/corridor/

echo 'Generating Fibonacci validation instances...'
if [ -d "domain/validation/fibo/" ]; then
	rm domain/validation/fibo/*
else
	mkdir -p "domain/validation/fibo"
fi 
./domain/generators/fibo.py 12 44 domain/validation/fibo/

echo 'Generating Find validation instances...'
if [ -d "domain/validation/find/" ]; then
	rm domain/validation/find/*
else
	mkdir -p "domain/validation/find"
fi 
./domain/generators/find.py 1000 100 11100 domain/validation/find/

echo 'Generating Grid validation instances...'
if [ -d "domain/validation/grid/" ]; then
	rm domain/validation/grid/*
else
	mkdir -p "domain/validation/grid"
fi 
./domain/generators/grid.py 5 66 domain/validation/grid/

echo 'Generating Gripper validation instances...'
if [ -d "domain/validation/gripper/" ]; then
	rm domain/validation/gripper/*
else
	mkdir -p "domain/validation/gripper"
fi 
./domain/generators/gripper.py 12 1011 domain/validation/gripper/

# AIJ domain
echo 'Generating Miconic validation instances...'
if [ -d "domain/validation/miconic/" ]; then
	rm domain/validation/miconic/*
else
	mkdir -p "domain/validation/miconic"
fi 
./domain/generators/miconic.py 12 31 0 domain/validation/miconic/

# AIJ domain
echo 'Generating Michalski Trains validation instances...'
if [ -d "domain/validation/mtrains/" ]; then
	rm domain/validation/mtrains/*
else
	mkdir -p "domain/validation/mtrains"
fi 
./domain/generators/mtrains.py domain/validation/mtrains/

echo 'Generating Reverse validation instances...'
if [ -d "domain/validation/reverse/" ]; then
	rm domain/validation/reverse/*
else
	mkdir -p "domain/validation/reverse"
fi 
./domain/generators/reverse.py validation 1000 100 11100 domain/validation/reverse/

# AIJ domain
echo 'Generating Satellite validation instances...'
if [ -d "domain/validation/satellite/" ]; then
	rm domain/validation/satellite/*
else
	mkdir -p "domain/validation/satellite"
fi 
./domain/generators/satellite.py 12 31 0 domain/validation/satellite/

echo 'Generating Select validation instances...'
if [ -d "domain/validation/select/" ]; then
	rm domain/validation/select/*
else
	mkdir -p "domain/validation/select"
fi 
./domain/generators/select.py validation 1000 100 11100 domain/validation/select/

# AIJ domain
echo 'Generating Sieve of Erathostenes validation instances...'
if [ -d "domain/validation/sieve/" ]; then
	rm domain/validation/sieve/*
else
	mkdir -p "domain/validation/sieve"
fi 
./domain/generators/sieve.py 12 111 domain/validation/sieve/

echo 'Generating Sorting validation instances...'
if [ -d "domain/validation/sorting/" ]; then
	rm domain/validation/sorting/*
else
	mkdir -p "domain/validation/sorting"
fi 
./domain/generators/sorting.py validation 12 1 111 domain/validation/sorting/
#./domain/generators/sorting.py validation 12 1 31 domain/validation/sorting/

# AIJ domain
echo 'Generating Spanner validation instances...'
if [ -d "domain/validation/spanner/" ]; then
	rm domain/validation/spanner/*
else
	mkdir -p "domain/validation/spanner"
fi 
./domain/generators/spanner.py 12 31 0 domain/validation/spanner/

echo 'Generating Triangular Sum validation instances...'
if [ -d "domain/validation/triangular-sum/" ]; then
	rm -rf domain/validation/triangular-sum/
	mkdir -p "domain/validation/triangular-sum"
else
	mkdir -p "domain/validation/triangular-sum"
fi 
./domain/generators/triangular-sum.py 12 44720 domain/validation/triangular-sum/

# AIJ new
echo 'Generating Visitall validation instances...'
if [ -d "domain/validation/visitall/" ]; then
	rm domain/validation/visitall/*
else
	mkdir -p "domain/validation/visitall"
fi 
./domain/generators/visitall.py 12 61 domain/validation/visitall/


