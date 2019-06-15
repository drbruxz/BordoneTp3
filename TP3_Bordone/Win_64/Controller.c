#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <strings.h>
#include "LinkedList.h"
#include "Employee.h"
#include "inputsBordone.h"
#include "controller.h"

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
    FILE* pFile;
    Employee* pEmpleado;
    Node* pNode = NULL;

    char v1[128],v2[128],v3[128],v4[128];
    int i = 0,returnValue = -1,read,validate = 1;
    pArrayListEmployee->pFirstNode = malloc(sizeof(Node));
    char pregunta;
    pFile = fopen(path,"r");
    if(pFile!=NULL){
        pNode = pArrayListEmployee->pFirstNode;
        pNode->pNextNode = malloc(sizeof(Node));
        if(pNode != NULL){
            do{
                validate = getAB(&pregunta,"La primera fila es nombre de campos? [S/N]","Input invalido[S/N]",'S','N');
            }while(validate == 1);
            if(pregunta == 'S'){
                read = fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",v1,v2,v3,v4);
            }
            while(!feof(pFile)){
                read = fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",v1,v2,v3,v4);
                if(read == 4){
                    pEmpleado = malloc(sizeof(Employee));
                    pNode->pElement = pEmpleado;
                    pEmpleado->id = atoi(v1);
                    strcpy(pEmpleado->nombre,v2);
                    pEmpleado->horasTrabajadas = atoi(v3);
                    pEmpleado->sueldo = atoi(v4);

                    pNode->pNextNode = malloc(sizeof(Node));
                    pNode = pNode->pNextNode;
                    pArrayListEmployee->size = i+1;
                    returnValue = pArrayListEmployee->size;
                    i++;
                }
            }
       }
    }
    fclose(pFile);
    free(pNode);
    free(pEmpleado);
    return returnValue;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee){
    FILE* pFile;
    pFile = fopen(path,"rb");
    Node* pNode;
    int i = 1;
    //Node* pNextNode;
    Employee* pEmployee;
    int r;




    if(pFile == NULL){
        printf("Error, puntero a nulo");
        getch();
    }
    if(pFile != NULL){
        pNode = malloc(sizeof(Node));
        pArrayListEmployee->pFirstNode = pNode;

        while(!feof(pFile)){

            pEmployee = malloc(sizeof(Employee));
            pNode->pElement = pEmployee;

            r = fread(pEmployee,sizeof(Employee),1,pFile);
            if(r==1){
              //    printf("Entre");
                    pArrayListEmployee->size = i+1;
                    pNode->pNextNode = malloc(sizeof(Node));
                    pNode = pNode->pNextNode;
                    i++;
            }
            if(r != 1){
                break;
            }

        }
    }

    fclose(pFile);
    free(pNode);
    free(pEmployee);


    return pArrayListEmployee->size;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
    Node* pNode;
    pNode = malloc(sizeof(Node));
    Employee* pEmployee;
    char nombreAux[51],confirm;
    int horasTrabajadasAux, sueldoAux, newID;
    int i,validate;
    int returnValue = -1, cElementos;
    if(pArrayListEmployee != NULL){
        pNode = pArrayListEmployee->pFirstNode;
        cElementos = ll_len(pArrayListEmployee);
        i = cElementos;
        newID = cElementos+1;

        do{
            pNode = pNode->pNextNode;
            i--;
        }while(i > 0);
        pEmployee = malloc(sizeof(Employee));
        if(pEmployee!=NULL){
            do{
                system("cls");
                do{

                    validate = getCharLen(nombreAux,"Ingrese nombre","Error, longitud MAX 51",1,51);
                }while (validate == 1);

                do{
                    validate = getNum(&horasTrabajadasAux,"Ingrese Horas Trabajadas","Error, MAX: 90 HORAS",1,90);

                }while(validate == 1);

                do{
                    validate = getNum(&sueldoAux,"Ingrese sueldo","Error, MAX: 100.000",1,100000);
                }while(validate == 1);

                printf("%s Horas: %d Sueldo:%d\n",nombreAux,horasTrabajadasAux,sueldoAux);
                validate = getAB(&confirm,"Estos datos son correctos? [S/N]", "Opcion inexistente [S/N]",'S','N');

                if(confirm == 'S'){
                    pNode->pElement = pEmployee;
                    strcpy(pEmployee->nombre,nombreAux);
                    pEmployee->horasTrabajadas = horasTrabajadasAux;
                    pEmployee->sueldo = sueldoAux;
                    pEmployee->id = newID;
                    pNode->pNextNode = malloc(sizeof(Node));
                    pArrayListEmployee->size++;
                    returnValue = 0;
                }
            }while(validate == 1 || confirm == 'N');
        }
        system("cls");
        printf("Empleado dado de alta!");
        getch();
    }
    free(pNode);
    free(pEmployee);
    printf("%d",ll_len(pArrayListEmployee));
    return returnValue;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
    int validate, idABuscar,max,indiceRetornado,seleccionCampo,returnValue = -1;
    char confirm;
    char nombreAux[51];
    int horasAux,sueldoAux;
    max = ll_len(pArrayListEmployee);
    Employee *pEmployee;
    if(pArrayListEmployee != NULL){
        do{
            system("cls");
            validate = getNum(&idABuscar,"Ingrese el ID del usuario","ID max superado",1,max);
            if(validate == 0){
                indiceRetornado = controller_searchID(pArrayListEmployee,idABuscar);
                if(indiceRetornado == -1){
                    printf("\nEmpleado no encontrado");
                    validate = 1;
                    getch();
                }
                if(indiceRetornado != -1){
                    pEmployee = ll_get(pArrayListEmployee,indiceRetornado);
                    printf("%d %s HS: %d Sueldo:%d\n",pEmployee->id,pEmployee->nombre,
                           pEmployee->horasTrabajadas,pEmployee->sueldo);
                    validate = getAB(&confirm,"Es este el usuario que desea modificar [S/N]","Seleccion invalida [S/N]",'S','N');
                }
            }
        }while(validate == 1 || confirm == 'N');

        if(confirm == 'S'){
            do{
                system("cls");
                printf("1.Nombre 2.Horas 3.Sueldo\n");
                validate = getNum(&seleccionCampo,"Que campo desea modificar? [1-3]","Opcion inexistente [1-3]",1,3);
                if(seleccionCampo == 1){
                    do{
                        ///MODIFICAR NOMBRE
                        validate = getCharLen(nombreAux,"Ingrese nuevo nombre", "Error: MAX 51 caracteres",1,51);
                        printf("\nEs este el nuevo nombre?   %s",nombreAux);
                        validate = getAB(&confirm,"[S/N]","Input invalido [S/N]",'S','N');
                    }while(validate == 1 || confirm == 'N');
                    if(confirm == 'S'){
                        strcpy(pEmployee->nombre,nombreAux);
                        returnValue = 0;
                        system("cls");
                        printf("Usuario modificado con éxito!");
                    }
                }else if(seleccionCampo == 2){
                    do{
                        ///MODIFICAR HORAS
                        validate = getNum(&horasAux,"Ingrese nueva cantidad de horas", "Error: MAX 90",1,90);
                        printf("Confirmar horas?: %d",horasAux);
                        validate = getAB(&confirm,"[S/N", "Input invalido: [S/N]",'S','N');
                    }while(validate == 1 || confirm == 'N');
                    if(confirm == 'S'){
                        pEmployee->horasTrabajadas = horasAux;
                        returnValue = 0;
                        system("cls");
                        printf("Usuario modificado con exito!");
                    }
                }else if(seleccionCampo == 3){
                    ///MODIFICAR SUELDO
                     do{
                        ///MODIFICAR HORAS
                        validate = getNum(&sueldoAux,"Ingrese nuevo sueldo", "Error: MAX 100.000",1,100000);
                        printf("Confirmar sueldo nuevo?: %d",sueldoAux);
                        validate = getAB(&confirm,"[S/N", "Input invalido: [S/N]",'S','N');
                    }while(validate == 1 || confirm == 'N');
                    if(confirm == 'S'){
                        pEmployee->sueldo = sueldoAux;
                        returnValue = 0;
                        system("cls");
                        printf("Usuario modificado con exito!");
                    }
                }
            }while(validate == 1);
        getch();
        }
    }

    free(pEmployee);
    return returnValue;
}
/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
    int idABuscar,validate,max,indiceRetornado,returnValue=-1;
    Employee* pEmployee;
    char confirm;
    max = ll_len(pArrayListEmployee);
    if(pArrayListEmployee!=NULL){
        do{
            system("cls");
            validate = getNum(&idABuscar,"Ingrese id a buscar","Error, id demasiado grande o menor a 1",1,max);
            indiceRetornado = controller_searchID(pArrayListEmployee,idABuscar);
            if(indiceRetornado == -1){
                validate = 1;
                printf("\nEmpleado no encontrado");
                getch();
            }
            if(indiceRetornado != -1){
                pEmployee = ll_get(pArrayListEmployee,indiceRetornado);
                printf("%d %s HS: %d Sueldo:%d\n",pEmployee->id,pEmployee->nombre,
                pEmployee->horasTrabajadas,pEmployee->sueldo);
                validate = getAB(&confirm,"Es este el usuario que desea eliminar [S/N]","Seleccion invalida [S/N]",'S','N');
            }

            if(confirm == 'S'){
                ll_remove(pArrayListEmployee,indiceRetornado);
                system("cls");
                printf("Uusario eliminado correctamente");
                getch();
            }
        }while(validate == 1 || confirm == 'N');

        returnValue = indiceRetornado;
        printf("%d",ll_len(pArrayListEmployee));
        getch();

    }
    free(pEmployee);
    return returnValue;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{

    Node* pNode;
    Employee* pEmployee;
    pNode = malloc(sizeof(Node));
    pNode = pArrayListEmployee->pFirstNode;
    int length, i,returnValue = -1;
    length = ll_len(pArrayListEmployee);

    if(pArrayListEmployee!=NULL){
        system("cls");
        if(pNode!=NULL){
            for(i=0;i<length;i++){
                if(pNode!=NULL){

                    pEmployee = pNode->pElement;
                    printf("%d",pEmployee->id);
                    printf("Nombre:%s\t\t",pEmployee->nombre);
                    printf("Horas: %d\t",pEmployee->horasTrabajadas);
                    printf("Sueldo: %d\n",pEmployee->sueldo);
                }
                returnValue = 0;
                pNode = pNode->pNextNode;
            }
        }
    }
    free(pEmployee);
    free(pNode);
    getch();
    return returnValue;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    Employee* pEmployeeI = malloc(sizeof(Employee));
    Employee* pEmployeeJ = malloc(sizeof(Employee));

    Node* pNodeJ= malloc(sizeof(Node));
    Node* pNodeI= malloc(sizeof(Node));
    Node* pNodeAux = malloc(sizeof(Node));

    int length,i,j;
    length = ll_len(pArrayListEmployee);
    pNodeI = pArrayListEmployee->pFirstNode;
    Node* pNextNodeJ;
    Node* pNextNodeI;

    system("cls");

    if(pArrayListEmployee!=NULL){
            for(i=0;i<length-1;i++){
                pNextNodeI = pNodeI->pNextNode;
                pEmployeeI = pNodeI->pElement;
                pNodeJ = pNextNodeI;
                if(pNextNodeI != NULL){
                for(j=i+1;j<length;j++){
                    pNextNodeJ = pNodeJ->pNextNode;
                    pEmployeeJ = pNodeJ->pElement;
                    if(pNextNodeJ != NULL){
                        if(strcmp(pEmployeeI->nombre, pEmployeeJ->nombre)>0){
                          pNodeAux->pElement = pNodeI->pElement;
                          pNodeI->pElement = pNodeJ->pElement;
                          pNodeJ->pElement = pNodeAux->pElement;
                          pEmployeeI = pNodeI->pElement;
                          pEmployeeJ = pNodeJ->pElement;
                        }
                    }
                    pNodeJ = pNextNodeJ;
                    }
                }
                pNodeI = pNextNodeI;
            }
            printf("Usuarios ordenados alfabeticamente");
            getch();
        }
        if(pArrayListEmployee == NULL){
            printf("Puntero de lista apunta a NULL, imposible ordenar");
            getch();
        }
        free(pEmployeeI);
        free(pEmployeeJ);
        free(pNodeI);
        free(pNodeAux);
        free(pNodeJ);
        free(pNextNodeI);
        free(pNextNodeJ);
        return 1;
}


/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
    FILE* pFile;
    Employee* pEmployee = malloc(sizeof(Employee));
    int i;
    char v1[128],v2[128],v3[128],v4[128];
    Node* pNode = malloc(sizeof(Node));
    Node* pNextNode = malloc(sizeof(Node));;
    pNode = pArrayListEmployee->pFirstNode;
    pFile = fopen(path,"r");
    if(pFile == NULL){
        printf("Error! Puntero archivo a  NULL, imposible guardar");
        getch();
    }
    if(pFile != NULL){
        pFile = fopen(path,"w");
    }
    int cant;

    cant = ll_len(pArrayListEmployee);
    rewind(pFile);
    if(pFile != NULL){
        for(i=0;i<cant;i++){
            pNextNode = pNode->pNextNode;
            pEmployee = pNode->pElement;
            itoa(pEmployee->id,v1,10);
            itoa(pEmployee->horasTrabajadas,v3,10);
            itoa(pEmployee->sueldo,v4,10);
            strcpy(v2,pEmployee->nombre);

            fprintf(pFile,"%s,%s,%s,%s\n",v1,v2,v3,v4);
            if(pNextNode!=NULL){
                pNode = pNextNode;
            }
            else{
                break;
            }
    }
    }
    free(pEmployee);
    fclose(pFile);
    return 1;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
    FILE* pFile;
    //int v1,v3,v4;
    //char v2[51];
    Node* pNode = malloc(sizeof(Node));
    Node* pNextNode = malloc(sizeof(Node));
    Employee* pEmployee = malloc(sizeof(Employee));
    int i,cant;
    cant = ll_len(pArrayListEmployee);

    pNode = pArrayListEmployee->pFirstNode;


    pFile = fopen(path,"rb");
    if(pFile != NULL){
        pFile = fopen(path,"wb");
    }
    if(pFile == NULL){
        printf("Error! Puntero archivo a  NULL, imposible guardar");
        getch();
    }

    rewind(pFile);
    if(pFile != NULL){
        for(i=0;i<cant;i++){
            pEmployee = pNode->pElement;
            pNextNode = pNode->pNextNode;

            fwrite(pEmployee,sizeof(Employee),1,pFile);

            pNode = pNextNode;
        }
    }

    free(pNode);
    free(pNextNode);
    free(pEmployee);
    fclose(pFile);


    return 1;
}

int controller_searchID(LinkedList* pArrayListEmployee, int id2Search){
    int i,max,returnValue = -1;
    Employee * pEmployee;
    Node* pNode;
    pNode = pArrayListEmployee->pFirstNode;
    max = ll_len(pArrayListEmployee);
    for(i=0;i<max;i++){
        pEmployee = pNode->pElement;
        if(pEmployee->id == id2Search){
            returnValue = i;
            break;
        }
        else{
            pNode=pNode->pNextNode;
        }
    }
    free(pEmployee);
    free(pNode);
    return returnValue;
}

