// Adaptación de: https://www.geeksforgeeks.org/lzw-lempel-ziv-welch-compression-technique/
#include <iostream>
#include "lempelziv.h"

std::vector<int> lempelziv::comprimir(std::string input){  
    std::unordered_map<std::string, int> tablaCodigos; // Crear una tabla para almacenar los códigos y sus correspondientes cadenas  
    // Inicializar la tabla con los caracteres ASCII
    for (int i = 0; i <= 255; i++) { 
        std::string caracter = ""; 
        caracter += char(i); 
        tablaCodigos[caracter] = i; // Asignar a cada carácter su código ASCII
    } 
    
    // Inicializar las variables para la compresión
    std::string cadenaActual = "", cadenaSiguiente = ""; 
    cadenaActual += input[0]; // Iniciar cadenaActual con el primer carácter de la cadena
    int code = 256; // Iniciar el código para las nuevas entradas en la tabla
    std::vector<int> codigoSalida; // Vector para almacenar los códigos de salida

    // Iterar sobre la cadena de texto para comprimir
    for (int i = 0; i < input.length(); i++) { 
        // Si no estamos al final de la cadena, añadir el siguiente carácter a cadenaSiguiente
        if (i != input.length() - 1) 
            cadenaSiguiente += input[i + 1]; 
        // Si la cadena cadenaActual+cadenaSiguiente está en la tabla, actualizar cadenaActual a cadenaActual+cadenaSiguiente
        if (tablaCodigos.find(cadenaActual + cadenaSiguiente) != tablaCodigos.end()) { 
            cadenaActual = cadenaActual + cadenaSiguiente; 
        } else { 
            // Si no, añadir el código de cadenaActual a la salida y añadir cadenaActual+cadenaSiguiente a la tabla con un nuevo codigo
            codigoSalida.push_back(tablaCodigos[cadenaActual]); 
            codigos.push_back({cadenaActual, tablaCodigos[cadenaActual]});
            tablaCodigos[cadenaActual + cadenaSiguiente] = code; 
            code++; // Incrementar el código para la próxima entrada
            cadenaActual = cadenaSiguiente; // Actualizar cadenaActual a cadenaSiguiente
        } 
        cadenaSiguiente = ""; // Limpiar cadenaSiguiente para la próxima iteración
    }
    
    codigos.push_back({cadenaActual, tablaCodigos[cadenaActual]});
    codigoSalida.push_back(tablaCodigos[cadenaActual]); // Añadir el último código a la salida
    return codigoSalida; 
} 

std::string lempelziv::descomprimir(std::vector<int> codigoEntrada){
    std::unordered_map<int, std::string> tablaCadenas; // Crear una tabla para almacenar los códigos y sus correspondientes cadenas
    
    // Inicializar la tabla con los caracteres ASCII
    for (int i = 0; i <= 255; i++) { 
        std::string caracter = ""; 
        caracter += char(i); 
        tablaCadenas[i] = caracter; 
    } 
    
    // Iniciar codigoAnterior con el primer código de la entrada
    int codigoAnterior = codigoEntrada[0], codigoActual; 
    std::string cadenaActual = tablaCadenas[codigoAnterior]; 
    std::string cadenaSiguiente = ""; 
    cadenaSiguiente += cadenaActual[0]; // Iniciar cadenaSiguiente con el primer carácter de cadenaActual
    std::string resultado = cadenaActual; // Iniciar la cadena de resultado con cadenaActual
    int count = 256; // Iniciar el contador para los nuevos códigos
    
    // Iterar sobre los códigos de entrada para descomprimir
    for (int i = 0; i < codigoEntrada.size() - 1; i++) { 
        codigoActual = codigoEntrada[i + 1]; // Leer el siguiente código de la entrada
        if (tablaCadenas.find(codigoActual) == tablaCadenas.end()) { 
            cadenaActual = tablaCadenas[codigoAnterior]; 
            cadenaActual = cadenaActual + cadenaSiguiente; // Si codigoActual no está en la tabla, actualizar cadenaActual a la cadena correspondiente a codigoAnterior seguida de cadenaSiguiente
        }
        else { 
            cadenaActual = tablaCadenas[codigoActual]; // Si codigoActual está en la tabla, actualizar cadenaActual a la cadena correspondiente a codigoActual
        }
        resultado += cadenaActual; // Añadir cadenaActual a la cadena de resultado
        cadenaSiguiente = ""; 
        cadenaSiguiente += cadenaActual[0]; // Actualizar cadenaSiguiente al primer carácter de cadenaActual
        tablaCadenas[count] = tablaCadenas[codigoAnterior] + cadenaSiguiente; // Añadir a la tabla la cadena correspondiente a codigoAnterior seguida de cadenaSiguiente con un nuevo código
        count++; // Incrementar el contador para el próximo código
        codigoAnterior = codigoActual; // Actualizar codigoAnterior a codigoActual
    }
    
    return resultado; // Devolver la cadena de resultado
} 

void lempelziv::mostrarCodigos(){
    std::cout << "Codigos generados:\n";
    for (auto par : codigos) {
        std::cout << par.first << " " << par.second << std::endl;
    }
}
