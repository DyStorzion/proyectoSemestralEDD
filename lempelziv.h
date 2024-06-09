#ifndef LEMPELZIV_H
#define LEMPELZIV_H

#include <string>
#include <vector>

class lempelziv {
    public:
        // Función para comprimir una cadena de texto utilizando el algoritmo de Lempel-Ziv
        std::string comprimir(const std::string& input);

        // Función para descomprimir una cadena de texto comprimida utilizando el algoritmo de Lempel-Ziv
        std::string descomprimir(std::vector<int> op);
};

#endif // LEMPELZIV_H