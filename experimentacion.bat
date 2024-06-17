@echo off
setlocal enabledelayedexpansion

REM Instruccion para compilar
g++ -o test.exe test.cpp huffman.cpp lempelziv.cpp

REM Verificar si la compilación fue exitosa
if %errorlevel% neq 0 (
    echo Error durante la compilación.
    exit /b %errorlevel%
)
REM Directorio de los archivos de base de datos
set database_dir=datasets
set iterations=20

REM Ejecutar el programa para cada archivo de base de datos
for /R "%database_dir%" %%f in (*.txt) do (
    for /L %%i in (1, 1, %iterations%) do (
        echo Iteration %%i of %iterations% for database file "%%f"
        test.exe "%%f"
    )
)
echo Todas las ejecuciones se completaron.