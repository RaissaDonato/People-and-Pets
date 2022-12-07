#include "people.h"
#include "pets.h"
#include "menu.h"
int nextCodePerson()
{
    int codPerson = 0;
    
    FILE *pcodes = NULL;    
    // declaração de uma variável do tipo "FILE" e "ponteiro"
    // ponteiro do tipo FILE que aponta para uma stream que é o conteúdo de um arquivo
    
    pcodes = fopen("codesPeople.chv", "rb+"); //aqui da pra botar chv 
    // abrindo o arquivo, "nome do arquivo", "modo de abertura"
    // modo de abertura "rb+" abre um arquivo binário para leitura e escrita
    // recebe a stream do arquivo
    
    if(pcodes == NULL)    // se pcodes ainda for NULL, será escrito informações no arquivo
    {
        pcodes = fopen("codesPeople.chv", "wb+");    // w de writte
        // a extensão de arquivo CHV tem zero tipo(s) primário de arquivo e pode ser aberta com Binary Data
    }
    
    fseek(pcodes, 0, SEEK_SET);
    // quando implementamos fseek(), movemos o ponteiro em uma distância 
    // de 0 em relação ao começo do arquivo, ou seja, o ponteiro agora 
    // aponta para o começo do arquivo
    
    fread(&codPerson, sizeof(int), 1, pcodes);
    // &conteudo
    // sizeof(int)
    // número de elementos
    // ponteiro para onde os dados serão armazenados
    // lê

    codPerson++;

    fseek(pcodes, 0, SEEK_SET);
    fwrite(&codPerson, sizeof(int), 1, pcodes);
    // escreve

    fseek(pcodes, 0, SEEK_SET);
    fread(&codPerson, sizeof(int), 1, pcodes);
    // lê o que acabou de ser escrito

    fclose(pcodes);

    return codPerson;
}
int cpfExists(char *file_path, char *string)
{
    int codPerson = 0;
    
    info_person listPeople;

    FILE *peopleInfos = NULL;
    FILE *pcodes = NULL;

    peopleInfos = fopen(file_path, "rb+");
    pcodes = fopen("codesPeople.chv", "rb");

    if(peopleInfos == NULL)
    {
        peopleInfos = fopen(file_path, "wb+");
    }

    fseek(pcodes, 0, SEEK_SET);
    fread(&codPerson, sizeof(int), 1, pcodes);

    for(int i = 0; i < codPerson; i++)
    {
        fseek(peopleInfos, sizeof(info_person) * i, SEEK_SET);
        fread(&listPeople, sizeof(info_person), 1, peopleInfos);

        if(!strcmp(listPeople.cpfPerson, string))
        {
            return 1;    // cpf já cadastrado
        }
    }

    return 0;    // cpf ainda não cadastrado
}

int rgExists(char *file_path, char *string)
{
    int codPerson = 0;
    
    info_person listPeople;

    FILE *peopleInfos = NULL;
    FILE *pcodes = NULL;

    peopleInfos = fopen(file_path, "rb+");
    pcodes = fopen("codesPeople.chv", "rb");
    
    if(peopleInfos == NULL)
    {
        peopleInfos = fopen(file_path, "wb+");
    }

    fseek(pcodes, 0, SEEK_SET);
    fread(&codPerson, sizeof(int), 1, pcodes);

    register int i;

    for(i = 0; i < codPerson; i++)
    {
        fseek(peopleInfos, sizeof(info_person) * i, SEEK_SET);
        fread(&listPeople, sizeof(info_person), 1, peopleInfos);
        
        if(!strcmp(listPeople.rgPerson, string))
        {
            return 1;    // rg já cadastrado
        }
    }
    return 0;    // rg ainda não cadastrado
}
int readInfosPerson()
//limpa as strings, permitindo sua correta ocupação, possibilita a utilização de espaços entre as palavras
{
    char *name = malloc(sizeof(char) * 255);
    char *rg = malloc(sizeof(char) * 11);
    char *cpf = malloc(sizeof(char) * 11);
    char *address = malloc(sizeof(char) * 255);
    char *birth = malloc(sizeof(char) * 10);
    char *wage = malloc(sizeof(char) * 20);
    
    
    printf("############################################################################\n");
    printf("#                                                                          #\n");
    printf("#                      Digite os dados para cadastro:                      #\n");
    printf("#                                                                          #\n");
    printf("############################################################################\n");

    printf("Nome: ");
    fflush(stdin);  
    __fpurge(stdin);
    fgets(name, 255, stdin);    // variável, tamaanho, stdin

    printf("RG: ");
    fflush(stdin);
    fgets(rg, 11, stdin);

    printf("CPF: ");
    fflush(stdin);
    fgets(cpf, 11, stdin);

    printf("Endereço: ");
    fflush(stdin);
    fgets(address, 255, stdin);

    printf("Data de nascimento (dd/mm/aaaa): ");
    fflush(stdin);
    fgets(birth, 10, stdin);

    printf("Salário (R$XXXX,XX): ");
    fflush(stdin);
    fgets(wage, 20, stdin);

    if(strlen(name) > 1  && strlen(rg) > 1 && strlen(cpf) > 1 && strlen(address) > 1 && strlen(birth) > 1 && strlen(wage) > 1)
    {
        if(!cpfExists("people.bin", cpf))
        {
            if(!rgExists("people.bin", rg))
            {
                insertPersonFile("people.bin", name, rg, cpf, address, birth, wage);
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
                printf("#                  O RG digitado já existe no sistema!                     #\n");
                printf("#                                                                          #\n");
                printf("############################################################################\n");
                return 0;
            }
        }
        else
        {
            printf("############################################################################\n");
            printf("#                                                                          #\n");
            printf("#                  O CPF digitado já existe no sistema!                    #\n");
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
        return 0;
    }
}

void insertPersonFile(char *file_path, char *name, char *rg, char *cpf, char *address, char *birth, char *wage)
{
 
    info_person *infos;
    
    infos = (info_person*)malloc(sizeof(info_person));
    
    FILE *peopleInfos = NULL;
    
    peopleInfos = fopen(file_path, "rb+");

    if(peopleInfos == NULL)
    {
        peopleInfos = fopen(file_path, "wb+");
    }
    
    strcpy(infos->namePerson, name);
    strcpy(infos->rgPerson, rg);
    strcpy(infos->cpfPerson, cpf);
    strcpy(infos->addressPerson, address);
    strcpy(infos->birthPerson, birth);
    strcpy(infos->wagePerson, wage);
    infos->fileExists = 1;

    infos->codePerson = nextCodePerson();
    
    free(name);
    free(rg);
    free(cpf);
    free(address);
    free(birth);
    free(wage);

    fseek(peopleInfos, 0, SEEK_END);
    
    fwrite(infos, sizeof(info_person), 1, peopleInfos);

    fclose(peopleInfos);

    free(infos);
}

char readNewInfosPerson()
{
    int codPerson;
    char *name = malloc(sizeof(char) * 255);
    char *rg = malloc(sizeof(char) * 20);
    char *cpf = malloc(sizeof(char) * 20);
    char *address = malloc(sizeof(char) * 255);
    char *birth = malloc(sizeof(char) * 15);
    char *wage = malloc(sizeof(char) * 20);

    printf("############################################################################\n");
    printf("#                                                                          #\n");
    printf("#             Insira os dados para alteração de cadastro.                  #\n");
    printf("#                                                                          #\n");
    printf("############################################################################\n");
    
    printf("############################################################################\n");
    printf("#                                                                          #\n");
    printf("#        Digite o código do usuário que deseja alterar o cadastro.         #\n");
    printf("#                                                                          #\n");
    printf("############################################################################\n");
    scanf("%d", &codPerson);

    codPerson--;

    printf("Nome: "); 
    fflush(stdin);    // limpa
    __fpurge(stdin);
    fgets(name, 255, stdin);    // variável, tamanho, stdin

    printf("RG: ");
    fflush(stdin);
    fgets(rg, 20, stdin);

    printf("CPF: ");
    fflush(stdin);
    fgets(cpf, 20, stdin);

    printf("Endereço: ");
    fflush(stdin);
    fgets(address, 255, stdin);

    printf("Data de nascimento (dd/mm/aaaa): ");
    fflush(stdin);
    fgets(birth, 15, stdin);

    printf("Salário (R$XXXX,XX): ");
    fflush(stdin);
    fgets(wage, 20, stdin);
    
    if(strlen(name) > 1  && strlen(rg) > 1 && strlen(cpf) > 1 && strlen(address) > 1 && strlen(birth) > 1 && strlen(wage) > 1)
    {
        if(!cpfExists("people.bin", cpf))
        {
            if(!rgExists("people.bin", rg))
            {
                changeInfosPersonFile("people.bin", name, rg, cpf, address, birth, wage, codPerson);
                printf("############################################################################\n");
                printf("#                                                                          #\n");
                printf("#                    Cadastro alterado com sucesso.                        #\n");
                printf("#                                                                          #\n");
                printf("############################################################################\n");
            }
            else
            {
                printf("############################################################################\n");
                printf("#                                                                          #\n");
                printf("#                  O RG digitado já existe no sistema!                     #\n");
                printf("#                                                                          #\n");
                printf("############################################################################\n");
                return 0;
            }
        }
        else
        {
            printf("############################################################################\n");
            printf("#                                                                          #\n");
            printf("#                  O CPF digitado já existe no sistema!                    #\n");
            printf("#                                                                          #\n");
            printf("############################################################################\n");
            return 0;
        }
    }
    else
    {
        printf("############################################################################\n");
        printf("#                                                                          #\n");
        printf("#         Dados Inválidos! Não foi possivel alterar o cadastro.           #\n");
        printf("#                                                                          #\n");
        printf("############################################################################\n");
        return 0;
    }
}
}

void changeInfosPersonFile(char *file_path, char *name, char *rg, char *cpf, char *address, char *birth, char *wage, int codePerson)
{
    FILE *peopleInfos = NULL;
    peopleInfos = fopen(file_path, "rb+");

    if(peopleInfos == NULL)
    {
        peopleInfos = fopen(file_path, "wb+");
    }

    info_person *newInfos;

    newInfos = (info_person*)malloc(sizeof(info_person));

    strcpy(newInfos->namePerson, name);
    strcpy(newInfos->rgPerson, rg);
    strcpy(newInfos->cpfPerson, cpf);
    strcpy(newInfos->addressPerson, address);
    strcpy(newInfos->birthPerson, birth);
    strcpy(newInfos->wagePerson, wage);

    newInfos->codePerson= codePerson + 1;

    newInfos->fileExists = 1;

    free(name);
    free(rg);
    free(cpf);
    free(address);
    free(birth);
    free(wage);
    
    fseek(peopleInfos, sizeof(info_person)*codePerson, SEEK_SET);
    fwrite(newInfos, sizeof(info_person), 1, peopleInfos);
    
    fclose(peopleInfos);
    
    free(newInfos);
}

void listPeople(char *file_path)
{
    info_person listPerson;
    int cod = 0;
    int i;
    FILE *peopleInfos;
    FILE *pcodes=NULL;

    peopleInfos = fopen(file_path,"rb");
    pcodes = fopen("codesPeople.chv","rb");

    fseek(pcodes, 0, SEEK_SET);
    fread(&cod, sizeof(int), 1, pcodes);
     
    for(i = 0; i < cod; i++)
    {
        fseek(peopleInfos, sizeof(info_person) * i, SEEK_SET);
        fread(&listPerson, sizeof(info_person), 1, peopleInfos);
        
        if(listPerson.fileExists == 1)
        {
            printf("############################################################################\n");
            printf("Código: %d\n", listPerson.codePerson);
            printf("Nome: %s\n", listPerson.namePerson);
            printf("Rg: %s\n", listPerson.rgPerson);
            printf("CPF: %s\n", listPerson.cpfPerson);
            printf("Endereço: %s\n", listPerson.addressPerson);
            printf("Data de nascimento: %s\n", listPerson.birthPerson);
            printf("Rendimento: %s\n", listPerson.wagePerson);
            printf("############################################################################\n");
        }
    }   
    fclose(peopleInfos);
}


void listCodePerson(char *file_path, int codPerson)
{
    codPerson--;
    FILE *peopleInfos = NULL;
    info_person listPerson;

    peopleInfos = fopen(file_path, "rb");

    fseek(peopleInfos, sizeof(info_person) * codPerson, SEEK_SET);
    fread(&listPerson, sizeof(info_person), 1, peopleInfos);

    if(listPerson.fileExists == 1) 
    {
        printf("############################################################################\n");
        printf("#  *Código: %d\n", listPerson.codePerson);
        printf("#  *Nome: %s\n", listPerson.namePerson);
        printf("#  *RG: %s\n", listPerson.rgPerson);
        printf("#  *CPF: %s\n", listPerson.cpfPerson);
        printf("#  *Endereço: %s\n", listPerson.addressPerson);
        printf("#  *Data de nascimento: %s\n", listPerson.birthPerson);
        printf("#  *Rendimento: %s\n", listPerson.wagePerson);
        printf("############################################################################\n");
    }
    else
    {
        printf("############################################################################\n");
        printf("#                                                                          #\n");
        printf("#               Não há usuário cadastrado com esse código.                 #\n");
        printf("#                                                                          #\n");
        printf("############################################################################\n");
    }
}

void listOwnerTypePet(char *file_path, char *Type)
{
    int codPet = 0;

    FILE *filePets;
    FILE *filePeople;
    FILE *codesPets;

    info_pet listPets;
    info_person listPeople;

    filePets = fopen(file_path, "rb");
    filePeople = fopen("people.bin", "rb");
    codesPets = fopen("codesPets.chv", "rb");

    fseek(codesPets, 0, SEEK_SET);
    fread(&codPet, sizeof(int), 1, codesPets);

    for(int i = 0; i < codPet; i++)
    {
        fseek(filePets, sizeof(info_pet) * i, SEEK_SET);
        fread(&listPets, sizeof(info_pet), 1, filePets);

        if(!strcmp(listPets.speciesPet, Type))
        {
            fseek(filePeople, sizeof(info_person) * i, SEEK_SET);
            fread(&listPeople, sizeof(info_person), 1, filePeople);

            printf("############################################################################\n");
            printf("\tCadastro das pessoas que possuem como pet o tipo %s:\n", listPets.speciesPet);
            printf("############################################################################\n");
            printf("#  *Código: %d\n", listPeople.codePerson);
            printf("#  *Nome: %s\n", listPeople.namePerson);
            printf("#  *RG: %s\n", listPeople.rgPerson);
            printf("#  *CPF: %s\n", listPeople.cpfPerson);
            printf("#  *Endereço: %s\n", listPeople.addressPerson);
            printf("#  *Data de nascimento: %s\n", listPeople.birthPerson);
            printf("#  *Rendimento: %s\n", listPeople.wagePerson);
            printf("############################################################################\n");
        }
    }
}

int compareName (const void *a, const void *b) 
{
    return strcmp (((info_person *)a)->namePerson,((info_person *)b)->namePerson);
}

void sortAlphabeticallyPeople(char *file_path)
{
    info_person listPersons;
    int codPerson=0;

    FILE *peopleInfos;
    FILE *pcodes;

    peopleInfos = fopen(file_path,"rb");
    pcodes = fopen("codesPeople.chv","rb");

    fread(&codPerson,sizeof(int),1,pcodes);

    int auxCod = codPerson;
    info_person allPersons[codPerson-1];
    
    for(int i = 0; i < codPerson; i++) 
    {
        fseek(peopleInfos, sizeof(info_person) * i, SEEK_SET);
        fread(&listPersons,sizeof(info_person),1,peopleInfos);
        
        strcpy(allPersons[i].namePerson,listPersons.namePerson);
        strcpy(allPersons[i].rgPerson,listPersons.rgPerson);
        strcpy(allPersons[i].cpfPerson,listPersons.cpfPerson);
        strcpy(allPersons[i].addressPerson,listPersons.addressPerson);
        strcpy(allPersons[i].birthPerson,listPersons.birthPerson);
        strcpy(allPersons[i].wagePerson,listPersons.wagePerson);
        
        allPersons[i].codePerson=listPersons.codePerson;
        allPersons[i].fileExists=listPersons.fileExists;
    }

    qsort(allPersons, codPerson, sizeof(info_person), compareName);
    
    for(int i = 0; i < auxCod; i++) 
    {
        if (allPersons[i].fileExists == 1) 
        {
            printf("############################################################################\n");
            printf("Lista de pessoas ordenadas alfabeticamente:\n");
            printf("#  *Código: %d\n", allPersons[i].codePerson);
            printf("#  *Nome: %s", allPersons[i].namePerson);
            printf("#  *Cpf: %s", allPersons[i].cpfPerson);
            printf("#  *Endereco: %s", allPersons[i].addressPerson);
            printf("#  *Data de nascimento: %s", allPersons[i].birthPerson);
            printf("#  *Salário: %s", allPersons[i].wagePerson);
            printf("############################################################################\n");
            
        }
    }
}

void deletePerson(char *file_path, int codPerson)
{    
    info_person infos;
    codPerson--;
    
    FILE *peopleInfos = NULL;

    peopleInfos = fopen(file_path, "rb+");

    if(peopleInfos == NULL)
    {
        peopleInfos = fopen(file_path, "wb+");
    }

    infos.fileExists = 0;

    deletePetByCodeOwner("pets.bin", codPerson);

    fseek(peopleInfos, sizeof(info_person) * codPerson, SEEK_SET);
    fwrite(&infos, sizeof(info_person), 1, peopleInfos);

    fseek(peopleInfos, sizeof(info_person) * codPerson, SEEK_SET);
    fread(&infos, sizeof(info_person), 1, peopleInfos);
    printf("%s",infos.namePerson);
    printf("%d",infos.fileExists);

}
