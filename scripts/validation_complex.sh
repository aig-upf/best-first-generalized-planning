echo 'Validation with INFINITE detection...'

echo 'Random BLOCKS ONTABLE...'
./scripts/time_memory.sh ./validator.bin solutions/ontable.prog domain/validation/ontable/ INF

echo 'Random GRID...'
./scripts/time_memory.sh ./validator.bin solutions/grid.prog domain/validation/grid/ INF

echo 'Random MICONIC...'
./scripts/time_memory.sh ./validator.bin solutions/miconic.prog domain/validation/miconic/ INF

echo 'Random MICHALSKI TRAINS...'
./scripts/time_memory.sh ./validator.bin solutions/mtrains.prog domain/validation/mtrains/ INF

echo 'Random SATELLITE...'
./scripts/time_memory.sh ./validator.bin solutions/satellite.prog domain/validation/satellite/ INF

echo 'Random SIEVE OF ERATHOSTENES...'
./scripts/time_memory.sh ./validator.bin solutions/sieve.prog domain/validation/sieve/ INF

echo 'Random SPANNER...'
./scripts/time_memory.sh ./validator.bin solutions/spanner.prog domain/validation/spanner/ INF


echo 'Validation without INFINITE detection...'

echo 'Random BLOCKS ONTABLE...'
./scripts/time_memory.sh ./validator.bin solutions/ontable.prog domain/validation/ontable/ NOINF

echo 'Random GRID...'
./scripts/time_memory.sh ./validator.bin solutions/grid.prog domain/validation/grid/ NOINF

echo 'Random MICONIC...'
./scripts/time_memory.sh ./validator.bin solutions/miconic.prog domain/validation/miconic/ NOINF

echo 'Random MICHALSKI TRAINS...'
./scripts/time_memory.sh ./validator.bin solutions/mtrains.prog domain/validation/mtrains/ NOINF

echo 'Random SATELLITE...'
./scripts/time_memory.sh ./validator.bin solutions/satellite.prog domain/validation/satellite/ NOINF

echo 'Random SIEVE OF ERATHOSTENES...'
./scripts/time_memory.sh ./validator.bin solutions/sieve.prog domain/validation/sieve/ NOINF

echo 'Random SPANNER...'
./scripts/time_memory.sh ./validator.bin solutions/spanner.prog domain/validation/spanner/ NOINF
