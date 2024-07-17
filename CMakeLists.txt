cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(CMA)

# Establecer el estándar de C a usar
set(CMAKE_C_STANDARD 99)

# Buscar la librería CURL
find_package(CURL REQUIRED)

# Buscar todos los archivos .c en el directorio del proyecto
file(GLOB SOURCES "*.c")

# Añadir el ejecutable con todos los archivos fuente encontrados
add_executable(cma ${SOURCES})

# Enlazar la librería CURL al ejecutable
target_link_libraries(cma CURL::libcurl)
