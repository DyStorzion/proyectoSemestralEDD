// Implementacion adptada de https://gist.github.com/pwxcoo/72d7d3c5c3698371c21e486722f9b34b y https://www.techiedelight.com/huffman-coding/ 
#include <string>
#include <queue>
#include <unordered_map>
#include <iostream>
#include "huffman.h"

void HuffmanTree::buildHuffmanTree(std::string texto) {
    codigoHuffman.clear();
    std::unordered_map<char, int> frecuencia;
    // Contar la frecuencia de cada caracter para guardarlo en un mapa como (caracter, frecuencia)
    for (char c : texto) {
        frecuencia[c]++;
    }

    // Crear una cola de prioridad para los nodos del arbol de Huffman
    std::priority_queue<Nodo*, std::vector<Nodo*>, comp> pq;

    // Insertar los nodos hoja en la cola de prioridad
    for (std::pair<char, int> par : frecuencia) {
        pq.push(new Nodo(par.first, par.second));
    }

    // Construir el arbol de Huffman
    while (pq.size() > 1) {
        // Sacar los dos nodos con menor frecuencia (mayor prioridad)
        Nodo* izq = pq.top();
        pq.pop();
        Nodo* der = pq.top();
        pq.pop();

        // Crear un nuevo nodo con el caracter vacio y la suma de las frecuencias de los dos nodos anteriores
        Nodo* nuevoNodo = new Nodo('\0', izq->frecuencia + der->frecuencia);
        nuevoNodo->izq = izq;
        nuevoNodo->der = der;

        pq.push(nuevoNodo);
    }

    // Guardar la raiz del arbol 
    raiz = pq.top();
    generarCodigos(raiz, "");
}

void HuffmanTree::mostrarCodigos() {
    for (std::pair<char, std::string> par : codigoHuffman) {
        std::cout << par.first << " " << par.second << std::endl;
    }
}

void HuffmanTree::generarCodigos(Nodo* raiz, std::string codigo) {
    // Caso base para la recursion
    if (raiz == nullptr) return;

    // Si el nodo es una hoja, entonces es un caracter
    if (!raiz->izq && !raiz->der) {
        //Guardar el codigo de Huffman en el mapa como (letra, codigo)
        codigoHuffman[raiz->letra] = codigo;
    }

    // Recorrer el arbol recursivamente
    generarCodigos(raiz->izq, codigo + "0");
    generarCodigos(raiz->der, codigo + "1");
}

std::string HuffmanTree::codificar(std::string texto) {
    std::string codigo = "";
    for (char c : texto) {
        codigo += codigoHuffman[c];
    }
    return codigo;
}

std::string HuffmanTree::decodificar(std::string codigo) {
    if(raiz == nullptr) return "";

    std::string texto = "";
    Nodo* actual = raiz;

    for (char c : codigo) {
        // Si el caracter es 0, ir al hijo izquierdo, si es 1, ir al hijo derecho
        if (c == '0') {
            actual = actual->izq;
        } else {
            actual = actual->der;
        }

        // Si el nodo actual es una hoja, entonces es un caracter
        if (!actual->izq && !actual->der) {
            texto += actual->letra;
            // Volver al nodo raiz
            actual = raiz;
        }
    }
    return texto;
}