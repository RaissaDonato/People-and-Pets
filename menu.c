#include "menu.h" 
#include "people.h"
#include "pets.h"


void mainMenu()
{
    int optionMain;
    enum optionsMain {people = 1, pets};

    printf("############################################################################\n");
    printf("#                                                                          #\n");
    printf("#        Bem-vindo(a) ao programa de cadastro de pessoas e de pets!        #\n");
    printf("#                                                                          #\n");
    printf("############################################################################\n");
    printf("\nDigite a opção que você deseja executar.\n\n");
    printf("############################################################################\n\n");
    printf("#  1: Funcionalidades para pessoas.\n");
    printf("#  2: Funcionalidades para pets.\n");
    printf("############################################################################\n\n");
    scanf("%d",&optionMain);

    switch(optionMain)
    {
        case (people):
        {
            peopleMenu();
            break;
        }

        case (pets):
        {
            petsMenu();
            break;
        }
    }
}

void peopleMenu()
{
    int optionPeople, codPeople, codPets, answer, final;
    enum optionsPeople {addPeople = 1, changePeople, deletePeople, showByCode, showByPet, list_people, alphabeticalOrder, exitPeopleMenu};
    
    printf("############################################################################\n");
    printf("#                                                                          #\n");
    printf("#      Menu de Pessoas selecionado: Digite a opção que deseja executar.    #\n");
    printf("#                                                                          #\n");
    printf("############################################################################\n");
    printf("1: Inserir uma nova pessoa.\n");
    printf("2: Alterar uma pessoa existente.\n");
    printf("3: Excluir uma pessoa.\n");
    printf("4: Mostrar/imprimir dados de uma pessoa com base no código.\n");
    printf("5: Mostrar/imprimir dados de pessoas que tenham um tipo de pet (cão, por exemplo).\n");
    printf("6: Mostrar/imprimir todas as pessoas.\n");
    printf("7: Mostrar/imprimir todas as pessoas om ordem alfabética pelo nome.\n");
    printf("8: Voltar para o menu principal.\n");
    printf("############################################################################\n\n");
    scanf("%d", &optionPeople);

    switch(optionPeople)
    {
        case (addPeople):
        {
            readInfosPerson();
            final = 1;
            break;
        }

        case (changePeople):
        {
            readNewInfosPerson();
            final = 1;
            break;
        }

        case (deletePeople):
        {
            int codPerson;
            printf("############################################################################\n");
            printf("#                                                                          #\n");
            printf("#        Digite o código do usuário que deseja excluir do sistema.         #\n");
            printf("#                                                                          #\n");
            printf("############################################################################\n");
            scanf("%d", &codPerson);
            
            deletePerson("people.bin", codPerson);
            final = 1;
            break;
        }

        case (list_people):
        {
            listPeople("people.bin");
            final = 1;
            break;
        }

        case (showByCode):
        {
            int codPerson;
            printf("############################################################################\n");
            printf("#                                                                          #\n");
            printf("#            Digite o código do usuário que deseja consultar.              #\n");
            printf("#                                                                          #\n");
            printf("############################################################################\n");
            scanf("%d",&codPerson);
            listCodePerson("people.bin", codPerson);
            final = 1;
            break;
        }

        case (showByPet):
        {
            char Type[15];
            printf("############################################################################\n");
            printf("#                                                                          #\n");
            printf("#              Digite o tipo do pet que deseja consultar.                  #\n");
            printf("#                                                                          #\n");
            printf("############################################################################\n"); 
            fflush(stdin);
            fgets(Type, 15 ,stdin);  
            listOwnerTypePet("pets.bin", Type);
            final = 1;
            break;
        }

        case (alphabeticalOrder):
        {
            sortAlphabeticallyPeople("people.bin");
            final = 1;
            break;
        }

        case (exitPeopleMenu):
        {
            final = 1;
            break;
        }

        default:
        {
            
            printf("############################################################################\n");
            printf("#                                                                          #\n");
            printf("#  Opção Inválida. Digite '1' para voltar para o menu ou '0' para sair:    #\n");
            printf("#                                                                          #\n");
            printf("############################################################################\n\n");
            scanf("%d", &answer);
            if (answer > 1 || answer <= 0) 
            {
                system("cls"); // Limpa a tela do usuário.
                printf("############################################################################\n");
                printf("#                                                                          #\n");
                printf("#                        O programa será encerrado.                        #\n");
                printf("#                                                                          #\n");
                printf("############################################################################\n\n");
                final = 0;
            } else {
                peopleMenu();
            }
            break;
        }
    }

    if (final == 1)
    {
        printf("############################################################################\n");
        printf("#                                                                          #\n");
        printf("#Deseja voltar ao menu do programa? Digite '1' para 'Sim' e '0' para 'Não':#\n");
        printf("#                                                                          #\n");
        printf("############################################################################\n\n");
        
        scanf("%d", &answer);
        if (answer == 1)
        {
            mainMenu();
        }
        else
        {
            
            printf("############################################################################\n");
            printf("#                                                                          #\n");
            printf("#                        O programa será encerrado.                        #\n");
            printf("#                                                                          #\n");
            printf("############################################################################\n\n");
            final = 0;
        }
    }
}

void petsMenu()
{
    int optionPets, codPeople, codPets, answer, final,codPetOwner;
    enum optionsPets {addPets = 1, changePets, deletePets, showByCodePets, showByCodePeople, alphabeticalOrderPets, exitPetsMenu};
    
    printf("############################################################################\n");
    printf("#                                                                          #\n");
    printf("#      Menu de Pets selecionado: Digite a opção que deseja executar.    #\n");
    printf("#                                                                          #\n");
    printf("############################################################################\n");
    printf("1: Inserir um novo pet.\n");
    printf("2: Alterar um pet existente.\n");
    printf("3: Excluir um pet.\n");
    printf("4: Mostrar/imprimir dados de um pet com base no código.\n");
    printf("5: Mostrar/imprimir todos os pets de uma pessoa com base no código da pessoa.\n");
    printf("6: Mostrar/imprimir todas os pets em ordem alfabética pelo nome.\n");
    printf("7: Voltar para o menu principal.\n");
    printf("############################################################################\n\n");
    scanf("%d", &optionPets);

    switch(optionPets)
    {
        case (addPets):
        {
            readInfosPet();
            final = 1;
            break;
        }

        case (changePets):
        {
            readNewInfosPet();
            final = 1;
            break;
        }

        case (deletePets):
        {
            printf("############################################################################\n");
            printf("#                                                                          #\n");
            printf("#        Digite o código do pet que deseja excluir do sistema.             #\n");
            printf("#                                                                          #\n");
            printf("############################################################################\n");
            scanf("%d", &codPets);
            deletePet("pets.bin",codPets);
            final = 1;
            break;
        }

        case (showByCodePets):
        {
            printf("############################################################################\n");
            printf("#                                                                          #\n");
            printf("#            Digite o código do pet que deseja consultar.                  #\n");
            printf("#                                                                          #\n");
            printf("############################################################################\n");
            scanf("%d",&codPets);
            showbyCodePet("pets.bin",codPets);
            final = 1;
            break;
        }

        case (showByCodePeople):
        {
            printf("############################################################################\n");
            printf("#                                                                          #\n");
            printf("#     Digite o código do dono que deseja consultar seus pets.              #\n");
            printf("#                                                                          #\n");
            printf("############################################################################\n");
            scanf("%d",&codPetOwner);
            listPetsCodeOwner("pets.bin",codPetOwner);
            final = 1;
            break;
        }

        case (alphabeticalOrderPets):
        {
            sortAlphabeticallyPet("pets.bin");
            final = 1;
            break;
        }

        case (exitPetsMenu):
        {
            //exitpetsmenu();
            final = 1;
            break;
        }

        default:
        {
            
            printf("############################################################################\n");
            printf("#                                                                          #\n");
            printf("#  Opção Inválida. Digite '1' para voltar para o menu ou '0' para sair:    #\n");
            printf("#                                                                          #\n");
            printf("############################################################################\n\n");
            scanf("%d", &answer);
            if (answer > 1 || answer <= 0) 
            {
                system("cls"); // Limpa a tela do usuário.
                printf("############################################################################\n");
                printf("#                                                                          #\n");
                printf("#                        O programa será encerrado.                        #\n");
                printf("#                                                                          #\n");
                printf("############################################################################\n\n");
                final = 0;
            } else {
                petsMenu();
            }
            break;
        }
    }

    if (final == 1)
    {
        
        printf("############################################################################\n");
        printf("#                                                                          #\n");
        printf("#Deseja voltar ao menu do programa? Digite '1' para 'Sim' e '0' para 'Não':#\n");
        printf("#                                                                          #\n");
        printf("############################################################################\n\n");
        scanf("%d", &answer);
        if (answer == 1)
        {
            mainMenu();
        }
        else
        {
            
            printf("############################################################################\n");
            printf("#                                                                          #\n");
            printf("#                        O programa será encerrado.                        #\n");
            printf("#                                                                          #\n");
            printf("############################################################################\n\n");
            final = 0;
        }
    }
}