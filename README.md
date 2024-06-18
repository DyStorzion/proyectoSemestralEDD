# Proyecto semestral de Estructura de datos

## Nombre integrantes del grupo
- Benjamin Alonso Espinoza Henriquez
- Sofia Ignacia Lopez Aguilera
- Nicolas Francisco Alexis Lopez Cid
---
## Instrucciones para la ejecucion
Si se desea probar la experimentación en su dispositivo en Windows, se dispone en este proyecto un 
archivo .bat en el que se pueden modificar el numero de iteraciones por las que se desea ejecutar
el código. En la terminal ubicada en la ruta del archivo, ejecutar:

`.\experimentacion.bat`

Esto dará como resultado los archivos .csv resultadosLempelZiv.csv y resultadosHuffman.csv. Se puede modificar
el dataset con distintos archivos .txt, esto no generará problemas porque se itera para todos los ficheros con esta
terminación que se encuentren dentro de la carpeta *datasets* de este repositorio. Los ficheros deben contener
colecciones de strings, donde sus caracteres deben ser parte de la tabla ASCII.

---

## Descripción general del proyecto
Este repositorio contiene implementación de las técnicas de codificación de Huffman y compresión
de Lempel-Ziv, aplicadas para codificar, descodificar, comprimir y descomprimir strings, con el 
fin de experimentar sobre estos métodos para compararlos en términos de tiempo de ejecución y tamaño.
