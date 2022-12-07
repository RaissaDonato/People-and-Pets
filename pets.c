#include "people.h"
#include "pets.h"
#include "menu.h"

int nextCodePet()
{
    int codPet = 0;

    FILE *pcodesPets = NULL;
    // declaração de uma variável do tipo "FILE" e "ponteiro"
    // ponteiro do tipo FILE que aponta para uma stream que é o conteúdo de um arquivo

    pcodesPets = fopen("codesPets.chv", "rb+");
    // abrindo o arquivo, "nome do arquivo", "modo de abertura"
    // modo de abertura "rb+" abre um arquivo binário para leitura e escrita
    // recebe a stream do arquivo

    if (pcodesPets == NULL) // se pcodes ainda for NULL, será escrito informações no arquivo
    {
        pcodesPets = fopen("codesPets.chv", "wb+"); // w de writte
    }

    fseek(pcodesPets, 0, SEEK_SET);
    // quando implementamos fseek(), movemos o ponteiro em uma distância
    // de 0 em relação ao começo do arquivo, ou seja, o ponteiro agora
    // aponta para o começo do arquivo

    fread(&codPet, sizeof(int), 1, pcodesPets);
    // &condeudo
    // sizeof(int)
    // número de elementos
    // ponteiro para onde os dados serão armazenados
    // lê

    codPet++;

    fseek(pcodesPets, 0, SEEK_SET);
    fwrite(&codPet, sizeof(int), 1, pcodesPets);
    // escreve

    fseek(pcodesPets, 0, SEEK_SET);
    fread(&codPet, sizeof(int), 1, pcodesPets);
    // lê o que acabou de ser escrito

    fclose(pcodesPets);

    return codPet;
}

int readInfosPet()
// limpa as strings, permitindo sua correta ocupação, possibilita a utilização de espaços entre as palavras
{
    char *petName = malloc(sizeof(char) * 255);
    char *petSpecies = malloc(sizeof(char) * 20);
    char *petBirth = malloc(sizeof(char) * 15);
    int codPetOwner;

    printf("Nome do pet: ");
    fflush(stdin);              // limpa
    fgets(petName, 255, stdin); // variável, tamanho, stdin

    printf("Espécie do pet: ");
    fflush(stdin);
    fgets(petSpecies, 20, stdin);

    printf("Data de nascimento do pet (dd/mm/aaaa): ");
    fflush(stdin);
    fgets(petBirth, 15, stdin);

    printf("Código do dono: ");
    fflush(stdin);
    scanf("%d",&codPetOwner);

    if (strlen(petName) > 1 && strlen(petSpecies) > 1 && strlen(petBirth) > 1)
    {
        if (!checkCodeOwner("codesPeople.chv", codPetOwner))
        {
            insertPetFile( "pets.bin" , petName , petSpecies , petBirth , codPetOwner );
            printf("############################################################################\n");
            printf("#                                                                          #\n");
            printf("#                    Cadastro realizado com sucesso.                       #\n");
            printf("#                                                                          #\n");
            printf("############################################################################\n");
        }
        else
        {
            printf("############################################################################\n");
            printf("#                                                                          #\n");
            printf("#       Não existe nenhuma pessoa cadastrada com ess código.               #\n");
            printf("#                                                                          #\n");
            printf("############################################################################\n");
            return 0;
        }
    }
    else
    {
        printf("############################################################################\n");
        printf("#                                                                          #\n");
        printf("#         Dados Inválidos! Não foi possivel realizar o cadastro.           #\n");
        printf("#                                                                          #\n");
        printf("############################################################################\n");
    }
}

int checkCodeOwner(char *file_path, int codPetOwner)
{
    int codPerson = 0;
    FILE *pcodes = NULL;
    pcodes = fopen(file_path,"rb");

    fseek(pcodes,0,SEEK_SET);
    fread(&codPerson,sizeof(int),1,pcodes);

    for(int i = 0; i < codPerson; i++){

        if(codPetOwner==i+1){
            return 0;  // existe o código
        }
    }
    return 1;  // não existe o código do dono
}

void insertPetFile(char *file_path, char *petName, char *petSpecies, char *petBirth,int codPetOwner)
{

    info_pet *infosPets;

    infosPets = (info_pet*)malloc(sizeof(info_pet));

    FILE *petInfos = NULL;

    petInfos = fopen(file_path, "rb+");

    if (petInfos == NULL)
    {
        petInfos = fopen(file_path, "wb+");
    }

    strcpy(infosPets->namePet , petName);
    strcpy(infosPets->birthPet , petBirth);
    strcpy(infosPets->speciesPet , petSpecies);
    infosPets->fileExistsPet = 1;

    infosPets->codePet = nextCodePet();
    infosPets->codePetOwner = codPetOwner;
    printf("%d",infosPets->codePetOwner);

    free(petName);
    free(petBirth);
    free(petSpecies);

    fseek(petInfos, 0, SEEK_END);

    fwrite(infosPets, sizeof(info_pet), 1, petInfos);

    fclose(petInfos);

    free(infosPets);
}


int readNewInfosPet()
{
    int codPets, codPetOwner;
    char *petName = malloc(sizeof(char) * 255);
    char *petSpecies = malloc(sizeof(char) * 20);
    char *petBirth = malloc(sizeof(char) * 15);
    printf("############################################################################\n");
    printf("#                                                                          #\n");
    printf("#        Digite o código do pet que deseja alterar o cadastro.         #\n");
    printf("#                                                                          #\n");
    printf("############################################################################\n");
    scanf("%d", &codPets);
    codPets--;

    printf("############################################################################\n");
    printf("#                                                                          #\n");
    printf("#         Insira os dados do pet para alteração de cadastro.               #\n");
    printf("#                                                                          #\n");
    printf("############################################################################\n");

    printf("Nome do pet: ");
    fflush(stdin);              // limpa
    fgets(petName, 255, stdin); // variável, tamanho, stdin

    printf("Data de nascimento (dd/mm/aaaa): ");
    fflush(stdin);
    fgets(petSpecies, 20, stdin);

    printf("Data de nascimento (dd/mm/aaaa): ");
    fflush(stdin);
    fgets(petBirth, 15, stdin);

    printf("Código do dono: ");
    fflush(stdin);
    scanf("%d",&codPetOwner);

    if (strlen(petName) > 1 && strlen(petSpecies) > 1 && strlen(petBirth) > 1)
    {
        if (!checkCodeOwner("codesPeople.chv", codPetOwner))
        {
            changeInfosPetsFile("pets.bin", petName, petSpecies, petBirth, codPetOwner,codPets);
            printf("############################################################################\n");
            printf("#                                                                          #\n");
            printf("#                     Cadastro alterado com sucesso.                       #\n");
            printf("#                                                                          #\n");
            printf("############################################################################\n");
        }
        else
        {
            printf("############################################################################\n");
            printf("#                                                                          #\n");
            printf("#       Não existe nenhuma pessoa cadastrada com ess código.               #\n");
            printf("#                                                                          #\n");
            printf("############################################################################\n");
            return 0;
        }
    }
    else
    {
        printf("############################################################################\n");
        printf("#                                                                          #\n");
        printf("#         Dados inválidos! Não foi possível cadastrar no sistema.          #\n");
        printf("#                                                                          #\n");
        printf("############################################################################\n");
    }
}

void changeInfosPetsFile(char *file_path, char *petName, char *petSpecies, char *petBirth, int codOwner,int codePet)
{

    FILE *petInfos = NULL;
    petInfos = fopen(file_path, "rb+");

    if (petInfos == NULL)
    {
        petInfos = fopen(file_path, "wb+");
    }

    info_pet newInfosPets;

    strcpy(newInfosPets.namePet, petName);
    strcpy(newInfosPets.speciesPet, petSpecies);
    strcpy(newInfosPets.birthPet, petBirth);

    newInfosPets.codePet = codePet + 1;
    newInfosPets.codePetOwner = codOwner;

    newInfosPets.fileExistsPet = 1;

    free(petName);
    free(petSpecies);
    free(petBirth);

    fseek(petInfos, sizeof(info_pet) * codePet, SEEK_SET);
    fwrite(&newInfosPets, sizeof(info_pet), 1, petInfos);

    fclose(petInfos);
}

int compareNamePet (const void *a, const void *b) 
{
    return strcmp (((info_pet *)a)->namePet,((info_pet *)b)->namePet);
}

void sortAlphabeticallyPet(char *file_path)
{
    info_pet listPets;
    int codPet = 0;

    FILE *petsInfos;
    FILE *pcodesPets;

    petsInfos = fopen(file_path,"rb");
    pcodesPets = fopen("codesPets.chv","rb");

    fread(&codPet,sizeof(int),1,pcodesPets);

    int auxCodPet = codPet;
    info_pet allPets[codPet-1];
    
    for(int i = 0; i < codPet; i++) 
    {
        fseek(petsInfos, sizeof(info_pet) * i, SEEK_SET);
        fread(&listPets,sizeof(info_pet),1,petsInfos);
        
        strcpy(allPets[i].namePet,listPets.namePet);
        strcpy(allPets[i].speciesPet,listPets.speciesPet);
        strcpy(allPets[i].birthPet,listPets.birthPet);
        
        allPets[i].codePet=listPets.codePet;
        allPets[i].codePetOwner=listPets.codePetOwner;
        allPets[i].fileExistsPet=listPets.fileExistsPet;
    }

    qsort(allPets, codPet, sizeof(info_pet), compareNamePet);
    
    for(int i = 0; i < auxCodPet; i++) 
    {
        if (allPets[i].fileExistsPet == 1) 
        {
            printf("############################################################################\n");
            printf("Lista de pessoas ordenadas alfabeticamente:\n");
            printf("#  *Código: %d\n", allPets[i].codePet);
            printf("#  *Código do dono: %d\n", allPets[i].codePetOwner);
            printf("#  *Nome: %s", allPets[i].namePet);
            printf("#  *Data de nascimento: %s", allPets[i].birthPet);
            printf("#  *Espécie: %s", allPets[i].speciesPet);
            printf("############################################################################\n");
        }
    }
}

void deletePet(char *file_path, int codPet)
{
    info_pet infosPets;
    codPet--;

    FILE *petInfos = NULL;

    petInfos = fopen(file_path, "rb+");

    if (petInfos == NULL)
    {
        petInfos = fopen(file_path, "wb+");
    }

    infosPets.fileExistsPet = 0;

    fseek(petInfos, sizeof(info_pet) * codPet, SEEK_SET);
    fwrite(&infosPets, sizeof(info_pet), 1, petInfos);

    fseek(petInfos, sizeof(info_pet) * codPet, SEEK_SET);
    fread(&infosPets, sizeof(info_pet), 1, petInfos);

}

void showbyCodePet(char *file_path, int codPet) 
{
    codPet--;
    FILE *petsInfo = NULL;
    FILE *people;
    info_pet listPets;
    info_person listPeople;
    petsInfo = fopen(file_path, "rb");
    people= fopen("people.bin","rb");
    

    fseek(petsInfo, sizeof(info_pet) * codPet, SEEK_SET);
    fread(&listPets, sizeof(info_pet), 1, petsInfo);
    
    fseek(people, sizeof(info_person) * codPet, SEEK_SET);
    fread(&listPeople, sizeof(info_person), 1,people);

    if (listPets.fileExistsPet==1 && listPeople.fileExists==1) 
    {
        printf("\n#-----------------------------------------#");
        printf("\n Código: %d                               #", listPets.codePet);
        printf("\n#-----------------------------------------#");
        printf("\n Nome do pet: %s", listPets.namePet);
        printf(" > Data de nascimento do pet: %s", listPets.birthPet);
        printf(" > Tipo do pet: %s", listPets.speciesPet);
        printf(" > Código do dono: %d\n", listPets.codePetOwner);
    }
    else
    {
        printf("\n#-----------------------------------------#");
        printf("\n|       CADASTRO  NAO ENCONTRADO          |");
        printf("\n#-----------------------------------------#");
    }
}

int listPetsCodeOwner(char *file_path, int codPetOwner)
{
    FILE *petsInfos;
    FILE *pcodesPets;
    
    int codPet = 0, countPets = 0;
    
    info_pet listPets;

    petsInfos = fopen(file_path,"rb");
    pcodesPets = fopen("codesPets.chv","rb");

    fseek(pcodesPets,0,SEEK_SET);
    fread(&codPet,sizeof(int),1,pcodesPets);

    for(int j = 0; j < codPet; j++) 
    {
        fseek(petsInfos, sizeof(info_pet) * j, SEEK_SET);
        fread(&listPets, sizeof(info_pet), 1, petsInfos);
        if (listPets.codePetOwner == codPetOwner && listPets.fileExistsPet==1) 
        {
            printf("\n#-----------------------------------------#");
            printf("\n# Código: %d                              #", listPets.codePet);
            printf("\n#-----------------------------------------#");
            printf("\n Nome do pet: %s", listPets.namePet);
            printf(" Data de nascimento do pet: %s", listPets.birthPet);
            printf(" Tipo do pet: %s", listPets.speciesPet);
            printf(" Código do usuario: %.3d", listPets.codePetOwner);
            countPets++;
        }
    }
    if(countPets==0) {
        printf("\n#--------------------------------------------------------------#");
        printf("\n#           ESSA PESSOA NÃO TEM NENHUM PET CADASTRADO!         #");
        printf("\n#--------------------------------------------------------------#");
        return 0;
    }
}

void deletePetByCodeOwner(char *file_path,int codOwner)
{
    int codPerson = 0;
    int i;
    
    FILE *petsInfo;
    FILE *pcodes;
    info_pet listPets;
    petsInfo = fopen(file_path,"rb+");
    pcodes = fopen("codesPeople.chv","rb");
    fseek(pcodes,0,SEEK_SET);
    fread(&codPerson,sizeof(int),1,pcodes);

    for(i = 0; i < codPerson; i++)
    {
        fseek(petsInfo,sizeof(info_pet)*i,SEEK_SET);
        fread(&listPets,sizeof(info_pet),1,petsInfo);

        if(listPets.codePetOwner==codOwner){
            listPets.fileExistsPet=0;   
             
            fseek(petsInfo,sizeof(info_pet)*i,SEEK_SET);
            fwrite(&listPets,sizeof(info_pet),1,petsInfo);
        }
    }
}
