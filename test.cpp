// Para la compilacion g++ test.cpp huffman.cpp lempelziv.cpp -o test.out (o .exe para Windows)
// Para la ejecucion test.out <direccionArchivo.txt> (o test.exe para Windows)  

#include <iostream>
#include <string>
#include "huffman.h"
#include <fstream>
#include <chrono>
#include <vector>
#include "lempelziv.h"

/// @brief metodo para guardar el codigo de Huffman en un archivo binario
/// @param code codigo de Huffman a guardar
/// @param filename nombre del archivo donde se guardara el codigo (debe tener extension .bin)
void saveHuffmanCode(const std::string code, const std::string& filename) {
    std::ofstream outFile(filename, std::ios::binary);
    if (outFile.is_open()) {
        char buffer = 0; // Buffer para almacenar los bits
        int count = 0; // Contador de bits escritos en el buffer

        for (char c : code) {
            buffer = (buffer << 1) | (c - '0'); // Desplazar el buffer y agregar el nuevo bit
            count++;

            if (count == 8) { // Si el buffer está lleno, escribirlo en el archivo
                outFile.write(&buffer, sizeof(char));
                buffer = 0; // Reiniciar el buffer
                count = 0;
            }
        }

        // Si hay bits restantes en el buffer, escribirlos
        if (count > 0) {
            buffer <<= (8 - count);
            outFile.write(&buffer, sizeof(char));
        }

        outFile.close();
    } else {
        std::cerr << "Error al abrir el archivo para escribir.\n";
    }
}

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

    // Huffman
    HuffmanTree huffman;
    auto start = std::chrono::high_resolution_clock::now();
    huffman.buildHuffmanTree(texto);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();


    // Muestra los codigos generados
    start = std::chrono::high_resolution_clock::now();    
    std::string codigo = huffman.codificar(texto);
    end = std::chrono::high_resolution_clock::now();
    duration += std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
    
    saveHuffmanCode(codigo, "codificado.bin");
    // Decodificacion

    start = std::chrono::high_resolution_clock::now();    
    std::string decodificado = huffman.decodificarArchivo("codificado.bin");
    end = std::chrono::high_resolution_clock::now();
    auto durationDecode = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();

    double ahorroEspacio = 100 - ((double)(codigo.length() * 100) / (double)(texto.length()*8));
    double duracion = duration / 1000000.0;
    double duracionDecode = durationDecode / 1000000.0;
    
    // Formato para el nombre del archivo sin datasets/ ni .txt
    std::string nombreArchivo = argv[1];
    std::string remover = "datasets\\"; // Cambiar por datasets/ en Linux
    size_t posicion = nombreArchivo.find(remover);
    if(posicion != std::string::npos) {
        nombreArchivo = nombreArchivo.substr(posicion + remover.length());
    }
    remover = ".txt";
    posicion = nombreArchivo.find(remover);
    if(posicion != std::string::npos) nombreArchivo.erase(posicion, remover.length());

    // Generar archivo de salida
    std::ofstream archivoDeSalida("resultadosHuffman.csv", std::ios::app);
    archivoDeSalida << "codificacion;" << nombreArchivo << ";" << ahorroEspacio << ";" << duracion << std::endl;
    archivoDeSalida << "decodificacion" << nombreArchivo << ";" << duracionDecode << std::endl;
    archivoDeSalida.close();


    // Lempel-Ziv
    lempelziv lz;

    start = std::chrono::high_resolution_clock::now();
    std::vector<int> codigoLZ = lz.comprimir(texto);
    end = std::chrono::high_resolution_clock::now();
    auto durationLZ = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    size_t tamañoCodigoLZ = 0;
    for (int codigo: codigoLZ) tamañoCodigoLZ += std::to_string(codigo).length() * 4;

    start = std::chrono::high_resolution_clock::now();
    std::string decodificadoLZ = lz.descomprimir(codigoLZ);
    end = std::chrono::high_resolution_clock::now();
    auto durationDescomprimir = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    ahorroEspacio = 100 - ((double)(tamañoCodigoLZ * 100) / (double)(texto.length()*8));
    long double duracionLZ = durationLZ / 1000000.0;
    auto duracionDescomprimir = durationDescomprimir / 1000000.0;

    // Generar archivo de salida
    archivoDeSalida.open("resultadosLempelZiv.csv", std::ios::app);
    archivoDeSalida << "compresion;" << nombreArchivo << ";" << ahorroEspacio << ";" << duracionLZ << std::endl;
    archivoDeSalida << "descompresion;" << nombreArchivo << ";" << duracionDescomprimir << std::endl;
    archivoDeSalida.close();
    return 0;
}
