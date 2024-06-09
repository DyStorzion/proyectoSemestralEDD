#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <queue>
#include <unordered_map>
#include <iostream>


/// @brief Clase para generar el arbol de Huffman
class HuffmanTree {
    private:
        /// @brief Struct para representar un nodo del arbol de Huffman
        struct Nodo {
            char letra;
            int frecuencia;
            Nodo* izq;
            Nodo* der;

            Nodo(char letra, int frecuencia) {
                this->letra = letra;
                this->frecuencia = frecuencia;
                izq = der = nullptr;
            }
        };

        /// @brief Struct para comparar los nodos del arbol de Huffman
        struct comp {
            bool operator()(Nodo* izq, Nodo* der) {
                return izq->frecuencia > der->frecuencia;
            }
        };

        Nodo* raiz;
        std::unordered_map<char, std::string> codigoHuffman;
        int bitsCodigo;

        /// @brief metodo privado para generar los codigos de Huffman
        /// @param raiz Nodo raiz del arbol
        /// @param codigo codigo de Huffman 
        void generarCodigos(Nodo* raiz, std::string codigo);

    public:
        /// @brief metodo para construir el arbol de Huffman
        /// @param texto texto con el que se construira el arbol de Huffman
        void buildHuffmanTree(std::string texto);

        /// @brief metodo para imprimir los codigos de Huffman
        void mostrarCodigos();

        /// @brief metodo para codificar un texto
        /// @param texto texto a codificar (debe ser el mismo texto con el que se construyo el arbol de Huffman)
        /// @return codigo de Huffman completo
        std::string codificar(std::string texto);

        /// @brief metodo para decodificar un codigo de Huffman
        /// @param codigo codigo de Huffman a decodificar
        /// @return texto decodificado
        std::string decodificar(std::string codigo);

        /// @brief metodo para decodificar un codigo de Huffman guardado en un archivo .bin
        /// @param codigo codigo de Huffman a decodificar 
        /// @return texto decodificado 
        std::string decodificarArchivo(std::string codigo);

};

#endif // HUFFMAN_H