cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(CMA)

# Establecer el estándar de C a usar
set(CMAKE_C_STANDARD 99)

# Buscar la librería CURL
find_package(CURL REQUIRED)

# Añadir el ejecutable con ambos archivos fuente
add_executable(cma main.c getCharacters.c)

# Enlazar la librería CURL al ejecutable
target_link_libraries(cma CURL::libcurl)
