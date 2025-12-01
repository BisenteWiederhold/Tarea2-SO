Compilacion
cd parte1
gcc -o barrera main.c barrier.c -pthread

cd parte2
g++ -o sim sim.cpp -std=c++17

Parte I — Barrera Reutilizable
cd parte1
make
Ejecutar:
./barrera (Nhebras) (Etapas)

Parte II — Simulador de Memoria Virtual
cd parte2
make
Ejecutar:
./sim Nmarcos tamaño_marco [--verbose] archivo_traza

Ejemplos:
./sim 8 4096 traces/trace2.txt
./sim 16 8 --verbose traces/trace1.txt
