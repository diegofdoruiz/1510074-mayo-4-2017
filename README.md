# Práctica utilizando hilos en c, 1510074-mayo-4-2017

En el archivo PracticaSoHilos.c se inplementan m hilos que ingresan como
parámetro al main, y lo que se obtiene como salida es: hola n, donde n es 
id correspondiente al hilo creado.

```
gcc -pthread PracticaSoHilos.c -o PracticaSoHilos
```
```
./PracticaSoHilos
```

# Modificación del programa Riemann_Scheme.c
Se completó el programa Riemann_Scheme.c el cual sirve para calcular de
forma aproximada el área bajo la curva de una función en un intervalo
específico

```
gcc -pthread Riemann_Scheme.c -o Riemann_Scheme
```
```
./Riemann_Scheme
```
