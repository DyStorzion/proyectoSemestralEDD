// Para la compilacion g++ test.cpp huffman.cpp -o test.out (o .exe para Windows)
// Para la ejecucion test.out <direccionArchivo.txt> (o test.exe para Windows)  

#include <iostream>
#include <string>
#include "huffman.h"
#include <fstream>
#include <chrono>

int main(int argc, char const *argv[])
{
    if(argc < 2) {
        std::cerr << "Usage: " << argv[0] << "<Texto a codificar>" << std::endl;
        exit(1);
    }
    std::ifstream archivoDeEntrada(argv[1]);
    if(!archivoDeEntrada.is_open()){
        std::cerr << "Error abriendo el archivo: " << argv[1] << std::endl;
        return 1;
    }
    std::string texto;
    std::string linea;
    while (std::getline(archivoDeEntrada, linea))
    {
        texto += linea;
    }
    archivoDeEntrada.close();

    HuffmanTree huffman;
    auto start = std::chrono::high_resolution_clock::now();
    huffman.buildHuffmanTree(texto);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();


    // Muestra los codigos generados
    huffman.mostrarCodigos();
    start = std::chrono::high_resolution_clock::now();    
    std::string codigo = huffman.codificar(texto);
    end = std::chrono::high_resolution_clock::now();
    duration += std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    
    //std::cout << "\nTexto codificado(" << codigo.length() << "bits):" << "\n" << codigo << std::endl;

    std::string decodificado = huffman.decodificar(codigo);
    //std::cout << "\nTexto decodificado(" << decodificado.length() * 8 << "bits):" << "\n" << decodificado << std::endl;

    double ahorroEspacio = 100 - ((double)(codigo.length() * 100) / (double)(texto.length()*8));
    double duracion = duration / 1000000.0;
    std::cout << "\nCon la codificacion se ahorro un " <<  ahorroEspacio << "% de datos en bits y tardo " << duracion << "s" << std::endl; 

    // Formato para el nombre del archivo sin datasets/ ni .txt
    std::string nombreArchivo = argv[1];
    std::string remover = "datasets/";
    size_t posicion = nombreArchivo.find(remover);
    if(posicion != std::string::npos) nombreArchivo.erase(posicion, remover.length());
    remover = ".txt";
    posicion = nombreArchivo.find(remover);
    if(posicion != std::string::npos) nombreArchivo.erase(posicion, remover.length());

    // Generar archivo de salida
    std::ofstream archivoDeSalida("resultados.csv", std::ios::app);
    archivoDeSalida << nombreArchivo << ";" << ahorroEspacio << ";" << duracion << std::endl;
    archivoDeSalida.close();

}
