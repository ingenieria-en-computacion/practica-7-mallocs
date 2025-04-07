#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Macro para crear listas dependiendo del tipo pasado
#define LIST_CREATE(TYPE) \
    _Generic((TYPE){0}, \
        int:    list_int_create, \
        float:  list_float_create, \
        char:   list_char_create \
    )()

// Macro para declarar estructuras de nodos y listas, así como funciones asociadas
#define DECLARE_LINKED_LIST(TYPE) \
    typedef struct Node_##TYPE { \
        TYPE data; \
        struct Node_##TYPE* next; \
    } Node_##TYPE; \
    \
    Node_##TYPE* node_##TYPE##_create(TYPE); \
    Node_##TYPE* node_##TYPE##_destroy(Node_##TYPE*); \
    \
    typedef struct { \
        Node_##TYPE* head; \
        Node_##TYPE* tail; \
        size_t length; \
    } List_##TYPE; \
    \
    List_##TYPE* list_##TYPE##_create(void); \
    void list_##TYPE##_destroy(List_##TYPE* list); \
    bool list_##TYPE##_insert(List_##TYPE* list, TYPE data, size_t pos); \
    bool list_##TYPE##_append(List_##TYPE* list, TYPE data); \
    bool list_##TYPE##_remove_at(List_##TYPE* list, size_t pos); \
    bool list_##TYPE##_get(const List_##TYPE* list, size_t pos, TYPE* out); \
    size_t list_##TYPE##_length(const List_##TYPE* list); \
    void list_##TYPE##_print(const List_##TYPE* list, void (*print_fn)(TYPE));

// Macros para destrucción y adición de elementos, aplicando _Generic según tipo de lista
#define LIST_DESTROY(list) _Generic((list), \
    List_int*:    list_int_destroy, \
    List_float*:  list_float_destroy, \
    List_char*:   list_char_destroy \
)(list)

#define LIST_APPEND(list, value) _Generic((list), \
    List_int*:    list_int_append, \
    List_float*:  list_float_append, \
    List_char*:   list_char_append \
)(list, value)

// Macro para implementar funciones para un tipo específico
#define IMPLEMENT_LINKED_LIST(TYPE) \
    /* Crear un nuevo nodo con el valor */ \
    Node_##TYPE* node_##TYPE##_create(TYPE data) { \
        Node_##TYPE* new_node = malloc(sizeof(Node_##TYPE)); \
        new_node->data = data; \
        new_node->next = NULL; \
        return new_node; \
    } \
    \
    /* Destruir un nodo si es el último */ \
    Node_##TYPE* node_##TYPE##_destroy(Node_##TYPE* node) { \
        if (node->next == NULL) { \
            free(node); \
            return NULL; \
        } \
        return node; \
    } \
    \
    /* Crear una lista vacía */ \
    List_##TYPE* list_##TYPE##_create(void) { \
        List_##TYPE* list = malloc(sizeof(List_##TYPE)); \
        if (!list) return NULL; \
        list->head = list->tail = NULL; \
        list->length = 0; \
        return list; \
    } \
    \
    /* Liberar todos los nodos de la lista */ \
    void list_##TYPE##_destroy(List_##TYPE* list) { \
        if (!list) return; \
        Node_##TYPE* current = list->head; \
        while (current) { \
            Node_##TYPE* temp = current; \
            current = current->next; \
            free(temp); \
        } \
        free(list); \
    } \
    \
    /* Insertar un nuevo elemento en una posición específica */ \
    bool list_##TYPE##_insert(List_##TYPE* list, TYPE data, size_t pos) { \
        if (!list || pos > list->length) return false; \
        Node_##TYPE* new_node = node_##TYPE##_create(data); \
        if (!new_node) return false; \
        \
        if (pos == 0) { \
            new_node->next = list->head; \
            list->head = new_node; \
            if (!list->tail) list->tail = new_node; \
        } else if (pos == list->length) { \
            new_node->next = NULL; \
            list->tail->next = new_node; \
            list->tail = new_node; \
        } else { \
            Node_##TYPE* current = list->head; \
            for (size_t i = 0; i < pos - 1; ++i) { \
                current = current->next; \
            } \
            new_node->next = current->next; \
            current->next = new_node; \
        } \
        list->length++; \
        return true; \
    } \
    \
    /* Agregar elemento al final de la lista */ \
    bool list_##TYPE##_append(List_##TYPE* list, TYPE data) { \
        return list_##TYPE##_insert(list, data, list->length); \
    } \
    \
    /* Eliminar un nodo en una posición específica */ \
    bool list_##TYPE##_remove_at(List_##TYPE* list, size_t pos) { \
        if (!list || pos >= list->length) return false; \
        Node_##TYPE* to_delete = NULL; \
        \
        if (pos == 0) { \
            to_delete = list->head; \
            list->head = list->head->next; \
            if (!list->head) list->tail = NULL; \
        } else { \
            Node_##TYPE* current = list->head; \
            for (size_t i = 0; i < pos - 1; ++i) { \
                current = current->next; \
            } \
            to_delete = current->next; \
            current->next = to_delete->next; \
            if (pos == list->length - 1) list->tail = current; \
        } \
        \
        free(to_delete); \
        list->length--; \
        return true; \
    } \
    \
    /* Obtener el valor en una posición específica */ \
    bool list_##TYPE##_get(const List_##TYPE* list, size_t pos, TYPE* out) { \
        if (!list || !out || pos >= list->length) return false; \
        Node_##TYPE* current = list->head; \
        for (size_t i = 0; i < pos; ++i) current = current->next; \
        *out = current->data; \
        return true; \
    } \
    \
    /* Obtener la longitud de la lista */ \
    size_t list_##TYPE##_length(const List_##TYPE* list) { \
        return list ? list->length : 0; \
    } \
    \
    /* Verificar si la lista está vacía */ \
    bool list_##TYPE##_is_empty(const List_##TYPE* list) { \
        return list ? (list->length == 0) : true; \
    } \
    \
    /* Eliminar todos los elementos de la lista */ \
    void list_##TYPE##_clear(List_##TYPE* list) { \
        if (!list) return; \
        Node_##TYPE* current = list->head; \
        while (current) { \
            Node_##TYPE* temp = current; \
            current = current->next; \
            free(temp); \
        } \
        list->head = list->tail = NULL; \
        list->length = 0; \
    } \
    \
    /* Imprimir todos los elementos de la lista */ \
    void list_##TYPE##_print(const List_##TYPE* list, void (*print_fn)(TYPE)) { \
        if (!list || !print_fn) return; \
        printf("["); \
        Node_##TYPE* current = list->head; \
        while (current) { \
            print_fn(current->data); \
            if (current->next) printf(", "); \
            current = current->next; \
        } \
        printf("]\n"); \
    } \
    \
    /* Verificar si la lista contiene un valor */ \
    bool list_##TYPE##_contains(const List_##TYPE* list, TYPE data) { \
        if (!list) return false; \
        Node_##TYPE* current = list->head; \
        while (current) { \
            if (current->data == data) return true; \
            current = current->next; \
        } \
        return false; \
    } \
    \
    /* Eliminar el primer nodo con un valor específico */ \
    bool list_##TYPE##_remove(List_##TYPE* list, TYPE data) { \
        if (!list) return false; \
        Node_##TYPE* prev = NULL; \
        Node_##TYPE* current = list->head; \
        \
        while (current) { \
            if (current->data == data) { \
                if (prev) { \
                    prev->next = current->next; \
                    if (!current->next) list->tail = prev; \
                } else { \
                    list->head = current->next; \
                    if (!list->head) list->tail = NULL; \
                } \
                free(current); \
                list->length--; \
                return true; \
            } \
            prev = current; \
            current = current->next; \
        } \
        return false; \
    }

// Declaración de listas para tipos concretos
DECLARE_LINKED_LIST(int)
DECLARE_LINKED_LIST(char)
DECLARE_LINKED_LIST(float)

#ifdef LINKED_LIST_IMPLEMENTATION
IMPLEMENT_LINKED_LIST(int)
IMPLEMENT_LINKED_LIST(char)
IMPLEMENT_LINKED_LIST(float)
#endif
