#ifndef PEOPLE_H
#define PEOPLE_H

#include <stdio.h> // Biblioteca padrão para todo programa em C para input/output de informações.
#include <stdlib.h> // Biblioteca utilizada para alocações de memória e outros processos.
#include <string.h> // Biblioteca utilizada para C para manipulação de cadeias de caracteres e regiões de memória.


typedef struct     // create a struct to store a person's data
 {
    int codePerson;
    char namePerson[255];
    char rgPerson[20];
    char cpfPerson[20];
    char addressPerson[255];
    char birthPerson[15];
    char wagePerson[20];
    int fileExists;
}info_person;    // defines the name of the new type created

int nextCodePerson();    
// gera um novo código

//void startPeople(char *name, char *rg, char *cpf, char *address, char *birth, char *wage);    
// malloc (memory allocation) aloca espaço para um 
// bloco de bytes consecutivos na memória RAM do computador e devolve
// o endereço desse bloco 

int cpfExists(char *file_path, char *string);

int rgExists(char *file_path, char *string);

int readInfosPerson();

void insertPersonFile(char *file_path, char *name, char *rg, char *cpf, char *address, char *birth, char *wage);

char readNewInfosPerson();

void changeInfosPersonFile(char *file_path, char *name, char *rg, char *cpf, char *address, char *birth, char *wage, int codePerson);

void deletePerson(char *file_path, int codPerson);

void listCodePerson(char *file_path, int codPerson);

void listOwnerTypePet(char *file_path, char *Type);

void listPeople(char *file_path);

int compareName (const void *a, const void *b);

void sortAlphabeticallyPeople();
#endif
