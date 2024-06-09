#ifndef LEMPELZIV_H
#define LEMPELZIV_H

#include <string>
#include <vector>
#include <unordered_map>

class lempelziv {
    private:
        std::vector<std::pair<std::string, int>> codigos; // Vector para almacenar los códigos generados
    public:
        /// @brief  metodo para comprimir una cadena de texto utilizando el algoritmo de Lempel-Ziv
        /// @param input texto a comprimir
        /// @return vector con los codigos de la cadena comprimida
        std::vector<int> comprimir(std::string input);

        /// @brief metodo para descomprimir una cadena de texto comprimida utilizando el algoritmo de Lempel-Ziv
        /// @param op vector con los codigos de la cadena comprimida
        /// @return texto descomprimido
        std::string descomprimir(std::vector<int> op);

        /// @brief metodo para mostrar los codigos generados
        void mostrarCodigos();
};

#endif // LEMPELZIV_H