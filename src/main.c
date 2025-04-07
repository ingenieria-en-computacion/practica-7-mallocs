#define LINKED_LIST_IMPLEMENTATION
#include "linked_list.h"
#include <stdio.h>

// Función de impresión para enteros
void print_int(int value) {
    printf("%d", value);
}

// Función de comparación para enteros (opcional, no usada)
bool int_cmp(int a, int b) {
    return a == b;
}

// Función de impresión para caracteres
void print_char(char value) {
    printf("%c", value);
}

// Función de comparación para caracteres (opcional, no usada)
bool char_cmp(char a, char b) {
    return a == b;
}

int main() {
    // Crear lista de enteros y agregar elementos
    List_int* nums = list_int_create();
    list_int_append(nums, 1);
    list_int_append(nums, 2);
    list_int_append(nums, 3);
    list_int_append(nums, 4);
    list_int_append(nums, 5);

    printf("Lista de numeros enteros: ");
    list_int_print(nums, print_int);

    // Liberar lista de enteros
    LIST_DESTROY(nums);

    // Crear lista de caracteres y agregar elementos
    List_char *chars = list_char_create();
    LIST_APPEND(chars, 'l');
    LIST_APPEND(chars, 'i');
    LIST_APPEND(chars, 's');
    LIST_APPEND(chars, 't');
    LIST_APPEND(chars, 'a');

    printf("Lista de caracteres: ");
    list_char_print(chars, print_char);

    // Liberar lista de caracteres
    LIST_DESTROY(chars);

    return 0;
}
