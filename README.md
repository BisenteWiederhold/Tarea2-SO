Parte I — Barrera Reutilizable

Compilacion

gcc -o barrera main.c -pthread

Ejecutar:

./barrera (Nhebras) (Etapas)

Parte II — Simulador de Memoria Virtual

Compilacion

g++ -o sim sim.cpp 

Ejecutar:

./sim Nmarcos tamaño_marco [--verbose] archivo_traza

Ejemplo:

./sim 8 4096 trace.txt



