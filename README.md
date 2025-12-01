Compilacion

cd parte1

gcc -o barrera main.c -pthread

Parte I — Barrera Reutilizable

cd parte1
make

Ejecutar:

./barrera (Nhebras) (Etapas)

Parte II — Simulador de Memoria Virtual

Compilacion

cd parte2

g++ -o sim sim.cpp 

cd parte2
make

Ejecutar:

./sim Nmarcos tamaño_marco [--verbose] archivo_traza

Ejemplo:

./sim 8 4096 trace.txt



