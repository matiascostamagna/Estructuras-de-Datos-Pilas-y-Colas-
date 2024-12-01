# AyEd-P1-2024
Realizar un programa que evalue un archivo de formato JSON-AYED.

Una expresion de este tipo es una expresion delimitada por llaves que internamente tiene subexpresiones separadas por coma, donde una subexpresion es alguna de las siguientes:

Un par (llave : valor), ambos strings delimitados por comillas dobles (”nombre”: “Carlos”)
Un par (”llave”: lista) de strings separados por coma y delimitados por corchetes ([”string1”,..,”stringX”])
Un par (llave : subexpresion) recursivamente definida delimitada por llaves ({})

Un ejemplo de esto es:
{
"nombre":‘‘Carlos",
"apellido":‘‘Garciarena",
"domicilio": 	{
		‘‘calle":"San martin",
		‘‘altura":‘‘33",
		‘‘cuidad":‘‘Jujuy",
		"telefonos":["351-4555666","351-5012789"]
		},

"conyuge":"Ana Castro",
"hijos":["Ana Garciarena","Lucas Garciarena"]
}

Ud. debera desarrollar un programa que lea un archivo de texto que tenga una sola expresion JSON-AYED, validar que sea correctamente escrita, e imprimirla en otro archivo eliminando los espacios entre expresiones, saltos de linea y tab que tenga el archivo de entrada, o bien, si no es correcta la expresion de entrada, indicar donde se produjo el error en la expresion de entrada.
Para el desarrollo debe basarse en los siguientes lineamientos:
Debe leer los caracteres del archivo de entrada uno a uno.
Debe utilizar estructuras de pilas y colas con ciertas especificaciones.
El archivo de salida no tiene espacios, tabs ni saltos de linea.
Debe utilizar una clase para cada tipo de componente de una expresion
JSON-AYED:
1. Expresion entre llaves (expresion JSON-AYED)
2. Expresion llave : valor
3. Expresion llave : expresion JSON-AYED
4. Expresion llave : expresion lista de strings

Cada uno de estos componentes debe tener una pila que se utilice en la evaluacion de la correctitud de la expresion. Adicionalmente la lista de strings debe tener una cola donde se almacenen los valores que tiene dicha expresion.
Para evaluar la expresion de entrada, al ir leyendo uno a uno los caracteres del archivo se entran en ciertos “modos” de avance del proceso que definen la validez del proximo caracter a leer, por ejemplo, el validador de la expresion JSON-AYED tiene una pila que esta vacıa al inicio de la lectura, por lo cuanto sabe que el proximo caracter debe ser una llave que abre, y cuando lee una llave que cierra determina que la expresion termino y tiene la pila vacıa. Otro ejemplo es para leer un string, que comienza con una comilla doble, siguen
caracteres alfanumericos y espacios y debe terminar con otra comilla doble.
Se aconseja que cada ”modo” tenga su propia pila para evaluacion. Al cambiar de modo se activa su tipo de pila de evaluacion y al volver al modo anterior se restablece el de llamada.

Cada clase a su vez debe tener un buffer de almacenamiento donde guardar el contenido que tiene cada instancia de la respectiva clase y que se utiliza luego al hacer la impresion de la expresion leıda por medio de un metodo print que llame a los print de los objetos almacenados en el buffer.
Debera codificar la solucion usando Clases de C++, con metodos que respeten el comportamiento definido en esta especificacion. Lo que no esta especificado aquı es de libre eleccion. Podra utilizar el codigo dado en clases practicas ajustando el tipo de dato contenido en cada estructura al tipo respectivo a la clase a la cual pertenece.
