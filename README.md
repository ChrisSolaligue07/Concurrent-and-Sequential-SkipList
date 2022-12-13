# Concurrent-and-Sequential-SkipList
> Para el ingreso de argumentos:
> [help]   : Brinda todos los comandos para el testeo.
> [helpC]  : Caracteristicas por defecto que lleva el testeo.
# help
[--th]                    -> Testeo secuencial contra concurrente con la cantidad maxima de threads [Threads=default, Elementos=default].
[--th] [n]                -> Testeo secuencial contra concurrente con una cantidad n de threads [Elementos=default].
[--th] [n] [m]            -> Testeo secuencial contra concurrente con una cantidad n de threads y una cantidad m de elementos.
[--th] [n] [m] [m] ...    -> Testeo secuencial contra concurrente con una cantidad n de threads y m casos de x de elementos.

[--thU]                       -> Testeo concurrente con la cantidad maxima de threads.
[--thU] [n]                   -> Testeo concurrente con una cantidad n de threads.
[--thU] [n] [m]               -> Testeo concurrente con una cantidad n de threads y una cantidad m de elementos.
[--thU] [n] [m] [m] [m] ...   -> Testeo concurrente con una cantidad n de threads y una cantidad de m casos de x elementos.

[--thCsv] [n] [m] [s] -> Testeo secuencial contra concurrente con una cantidad n de threads, m elementos con s pruebas del mismo caso. [Promedio]

[--s]             -> Testeo secuencial [Elementos=default].
[--s] [m]         -> Testeo secuencial con m elementos.
[--s] [m] [m] ... -> Testeo secuencial con n casos de m elementos.
# helpC
Cantidad de threads: MAX
Testeo Secuencial: True
Testeo Concurrente: True
Cantidad de elementos: 1000000
