#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "inputsBordone.h"
/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
    10. Salir
*****************************************************/


int main()
{
    int option = 0, empleadosLeidos,validate;
    LinkedList* listaEmpleados = ll_newLinkedList();
    do{
        system("cls");
        printf("1.Cargar data.csv modo texto\n2.Cargar data.csv modo binario\n3.Alta empleado\n4.Modificar empleado\n5.Baja de empleado\n6.Listar Empleados\n7.Ordenar Empleados");
        printf("\n8.Guardar en data.csv (texto)\n9.Guardar en data.csv(modo binario)\n10.Salir del programa\n");
        validate = getNum(&option,"Ingrese opcion [1-10]:", "Error, opcion inexistente [1-10]",1,10);
        switch(option)
        {
            case 1:
                empleadosLeidos = controller_loadFromText("data.csv",listaEmpleados);
                printf("Se leyeron %d empleados",empleadosLeidos);
                getch();
                break;
            case 2:
                empleadosLeidos = controller_loadFromBinary("data.csv",listaEmpleados);
                printf("Se leyeron %d empleados",empleadosLeidos);
                getch();
                break;
            case 3:
                controller_addEmployee(listaEmpleados);
                break;
            case 4:
                controller_editEmployee(listaEmpleados);
                break;
            case 5:
                controller_removeEmployee(listaEmpleados);
                break;
            case 6:
                controller_ListEmployee(listaEmpleados);
                break;
            case 7:
                controller_sortEmployee(listaEmpleados);
                break;
            case 8:
                controller_saveAsText("data.csv",listaEmpleados);
                break;
            case 9:
                controller_saveAsBinary("data.csv",listaEmpleados);
                break;
            case 10:
                validate = 1;
                break;
        }
    }while(validate == 0);

    ll_deleteLinkedList(listaEmpleados);
    system("cls");
    printf("Programa terminado");
    getch();
    return 0;
}
