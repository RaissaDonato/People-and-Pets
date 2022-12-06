#ifndef PETS_H
#define PETS_H

#include <stdio.h> // Biblioteca padrão para todo programa em C para input/output de informações.
#include <stdlib.h> // Biblioteca utilizada para alocações de memória e outros processos.
#include <string.h> // Biblioteca utilizada para C para manipulação de cadeias de caracteres e regiões de memória.


typedef struct    // create a struct to store a person's data
{
    int codePet;
    int codePetOwner;
    char namePet[255];
    char speciesPet[20];
    char birthPet[15];
    int fileExistsPet;
}info_pet;    // defines the name of the new type created

int nextCodePet();

int readInfosPet();

int checkCodeOwner(char *file_path, int codPetOwner);

void insertPetFile(char *file_path, char *petName, char *petSpecies, char *petBirth, int codPetOwner);

int readNewInfosPet();

void deletePetByCodeOwner(char *file_path,int codOwner);

void changeInfosPetsFile(char *file_path, char *petName, char *petSpecies, char *petBirth,int codOwner,int codePet);

void deletePet(char *file_path, int codPet);

void deletePetByCodeOwner();

void showbyCodePet(char *file_path,int codePet);

int listPetsCodeOwner(char *file_path, int codPetOwner);

void sortAlphabeticallyPet(char *file_path);

#endif