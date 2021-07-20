<!-- [![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.4600833.svg)](https://doi.org/10.5281/zenodo.4600833) -->

# Best First Generalized Planning
Heuristic and evaluation techniques for searching programs that generally solve a set of planning problems.
This framework uses a domain specific language for planning with pointers and functions over pointers.
It starts with a short tutorial, and later explains every step in more detail.

## Short Tutorial

1. Generate folders and compile the project.
```shell
./scripts/compile_all.sh
```
2. Generate synthesis and validation instances of Fibonacci.
```shell
./domain/generators/fibo.py 2 11 domain/synthesis/fibo/
./domain/generators/fibo.py 12 44 domain/validation/fibo/
```
3. Search a program that solves Fibonacci
```shell
./main.bin 7 domain/synthesis/fibo/
```
The resulting program, saved in ```experiments/synthesis/fibo_h5_h7.prog```, should looks as follows:
```shell
0. vector-add(a,b)
1. dec(b)
2. vector-add(a,b)
3. set(b,a)
4. inc(a)
5. goto(0,!(( zf = 1 )( cf = 0 )))
6. end
```
4. Validate the output program, with and without infinite error detection.
```shell
./validator.bin experiments/synthesis/fibo_h5_h7.prog domain/validation/fibo/ INF
./validator.bin experiments/synthesis/fibo_h5_h7.prog domain/validation/fibo/ NOINF
```
Both validations should finish with an `[INFO] GOAL ACHIEVED!`

## Long Tutorial
### Required folders and project compilation
The next command is used to generate required folders and compile the project:

```shell
./scripts/compile_all.sh
```
The compilation will generate a ```main.bin``` and ```validator.bin``` executables file in the root folder.

### Generating random inputs

The inputs are randomly generated from a high-level specification.
The next are the examples used in the project to generate the original domains and instances:

```shell
./domain/generators/corridor.py 2 11 domain/synthesis/corridor/
./domain/generators/fibo.py 2 11 domain/synthesis/fibo/
./domain/generators/find.py 2 1 11 domain/synthesis/find/
./domain/generators/gripper.py 2 11 domain/synthesis/gripper/
./domain/generators/reverse.py synthesis 2 1 11 domain/synthesis/reverse/
./domain/generators/select.py synthesis 2 1 11 domain/synthesis/select/
./domain/generators/sorting.py synthesis 2 1 11 domain/synthesis/sorting/
./domain/generators/triangular-sum.py 2 11 domain/synthesis/triangular-sum/
./domain/generators/visitall.py 2 11 domain/synthesis/visitall/
```

### Searching a program
Here we show few examples which load (f5,f7) evaluation functions by default:

```shell
./main.bin 8 domain/synthesis/corridor/
./main.bin 7 domain/synthesis/fibo/
./main.bin 6 domain/synthesis/find/
./main.bin 8 domain/synthesis/gripper/
./main.bin 7 domain/synthesis/reverse/
./main.bin 7 domain/synthesis/select/
./main.bin 11 domain/synthesis/sorting/
./main.bin 6 domain/synthesis/triangular-sum/
./main.bin 8 domain/synthesis/visitall/
```

Explicit load of another function should be appended to the arguments as follows:
```shell
./main.bin 7 domain/synthesis/select/ h2
```

Or a list of functions:
```shell
./main.bin 7 domain/synthesis/reverse/ h3 h5 h1
```

### Validating a program

Generating validation instances in some ```[folder]```, where default folder destinations can be found in the script ```validation_generators.sh```:
```shell
./domain/generators/corridor.py 12 1011 [folder]
```

Other instance generators:
```shell
./domain/generators/find.py 1000 100 11100 [folder]
./domain/generators/gripper.py 12 1011 [folder]
./domain/generators/reverse.py validation 1000 100 11100 [folder]
./domain/generators/select.py validation 1000 100 11100 [folder]
./domain/generators/sorting.py validation 12 1 111 [folder]
./domain/generators/triangular-sum.py 12 44720 [folder]
./domain/generators/visitall.py 12 61 [folder]
```

Generators of more complex domains (some require to install tarski module, e.g. ```pip install tarski```):
```shell
./domain/generators/ontable.py 12 31 1 [folder]
./domain/generators/grid.py 5 66 [folder]
./domain/generators/miconic.py 12 31 0 [folder]
./domain/generators/mtrains.py [folder]
./domain/generators/satellite.py 12 31 0 [folder]
./domain/generators/sieve.py 12 111 [folder]
./domain/generators/spanner.py 12 31 0 [folder]
```

Validating a specific program with infinite program detection by default, where validation instances are in the folder ```domain/validation/fibo/```:
```shell
./validator.bin solutions/fibo.prog domain/validation/fibo/
```

Explicit validation with/out infinite program detection:
```shell
./validator.bin solutions/fibo.prog domain/validation/fibo/ INF
./validator.bin solutions/fibo.prog domain/validation/fibo/ NOINF
```

### Reproducing AIJ Experiments

> This is a remainder that some experiments may take days of computation, e.g. ```synthesis_combination.sh```, and may exhaust your computer resources, e.g. validations with infinite detection.

In order to reproduce AIJ experiments simply run:
```shell
./scripts/aij_experiments.sh
```

This script consist of the following commands which should succeed (given the paper settings):
```shell
./scripts/compile_all.sh
./scripts/synthesis_generators.sh
./scripts/synthesis_experiments.sh
./scripts/synthesis_combination.sh
./scripts/validation_generators.sh
./scripts/validation_experiments.sh
./scripts/validation_complex.sh
```
