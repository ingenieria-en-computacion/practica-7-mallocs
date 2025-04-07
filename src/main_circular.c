#define LINKED_LIST_IMPLEMENTATION
#include "linked_list_circular.h"
#include <stdio.h>
#include <assert.h>

// Función para imprimir un entero
void print_int(int value) {
    printf("%d", value);
}

// Función para imprimir un carácter
void print_char(char value) {
    printf("%c", value);
}

// Función auxiliar para verificar si la lista es circular
void verify_circularity_int(List_int* list) {
    if (!list || !list->head) {
        printf("La lista esta vacia.\n");
        return;
    }

    printf("[VERIFICACION] Tail->next apunta a Head => %s\n", 
           (list->tail->next == list->head) ? "Si " : "No ");
}

int main() {
    // -----------------------
    // Prueba con lista de enteros
    // -----------------------
    List_int* nums = list_int_create();

    // Agregar elementos
    list_int_append(nums, 100);
    list_int_append(nums, 200);
    list_int_append(nums, 300);

    // Mostrar contenido
    printf("Lista Circular de Enteros:\n");
    list_int_print(nums, print_int); // Esperado: 100 -> 200 -> 300 (head)

    // Verificar que sea circular
    verify_circularity_int(nums);    // Esperado: Sí 

    // Liberar memoria con macro
    LIST_DESTROY(nums);

    // -----------------------
    // Prueba con lista de caracteres
    // -----------------------
    List_char* chars = list_char_create();

    // Agregar elementos
    LIST_APPEND(chars, 'A');
    LIST_APPEND(chars, 'B');
    LIST_APPEND(chars, 'C');
    LIST_APPEND(chars, 'D');

    // Mostrar contenido
    printf("\nLista Circular de Caracteres:\n");
    list_char_print(chars, print_char); // Esperado: A -> B -> C -> D (head)

    // Nota: No se verifica circularidad explícita aquí, pero está garantizada por implementación

    // Liberar memoria con macro
    LIST_DESTROY(chars);

    return 0;
}
