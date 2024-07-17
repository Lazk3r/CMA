
//Añadimos el archivo de declaración
#include "searchCharacters.h";

char* searchCharacters(const char *input_Name)
{// La función recibe el nombre del personaje y retorna los datos que encuentra en la API
   char* json_data = get_characters();
    //Error en caso de que no acceda correctamente a la API
    if (!json_data) {
        fprintf(stderr, "Failed to get characters from API\n");
        return;
    }
    //Decodificar el .json y obtener los datos de la API
    json_error_t error;
    json_t *root = json_loads(json_data, 0, &error);
    free(json_data);
    //Error en decodificación
    if (!root) {
        fprintf(stderr, "Error parsing JSON: %s\n", error.text);
        return;
    }
    //Obtener los valores relacionados a results en la API
    json_t *results = json_object_get(root, "results");
    //En caso de ser NULL
    if (!json_is_array(results)) {
        fprintf(stderr, "Error: results is not an array\n");
        json_decref(root);
        return;
    }
    // Almacena las longitudes de los indices del .json
    size_t index;
    json_t *character;
    //Itera sobre cada elemento de los datos de la API
    json_array_foreach(results, index, character) {
        //Obtiene el nombre de cada uno de los personajes
        json_t *name = json_object_get(character, "name");
        //Compara con el nombre proporcionado
        if (json_is_string(name) && strcmp(json_string_value(name), input_Name) == 0) {
            //Castea de json a string los datos del personaje
            char *character_str = json_dumps(character, JSON_INDENT(4));
            //Elimina los datos del json que almacenaba en root (Libera memoria)
            json_decref(root);
            //Retorna los datos del personaje
            return character_str;
        }
    }
    //En caso de no encontrar libera memoria igualmente
    json_decref(root); 

};