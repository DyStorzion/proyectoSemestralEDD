#include <iostream>
#include <string>
#include "huffman.h"

int main(int argc, char const *argv[])
{
    std::string texto = "hola mundo";
    HuffmanTree huffman;
    huffman.buildHuffmanTree(texto);
    huffman.mostrarCodigos();

    std::string codigo = huffman.codificar(texto);
    std::cout << "Texto codificado: " << codigo << std::endl;

    std::string decodificado = huffman.decodificar(codigo);
    std::cout << "Texto decodificado: " << decodificado << std::endl;

    texto = "tangananica y tanganana";
    huffman.buildHuffmanTree(texto);
    huffman.mostrarCodigos();

    codigo = huffman.codificar(texto);
    std::cout << "Texto codificado: " << codigo << std::endl;

    decodificado = huffman.decodificar(codigo);
    std::cout << "Texto decodificado: " << decodificado << std::endl;
    return 0;
}
