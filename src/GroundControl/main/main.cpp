/* ---------------------------------------------------------------------------*/
/* Includes                                                                   */
/* ---------------------------------------------------------------------------*/
#include <string>
#include <sstream>
#include "GroundControl.h"

/* ---------------------------------------------------------------------------*/
/* Debug                                                                      */
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Defines, Estructuras y Typedef                                             */
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Declaracion de funciones                                                   */
/* ---------------------------------------------------------------------------*/


/* ---------------------------------------------------------------------------*/
/* Variables externas y privadas                                              */
/* ---------------------------------------------------------------------------*/


/* ---------------------------------------------------------------------------*/
/* Implementacion de clases y funciones                                       */
/* ---------------------------------------------------------------------------*/

int main(int argc, char **argv)
{
    std::cout << "Start Ground Control" << std::endl;

    /* Create Meassege Broker (Observer Pattern!) */
    AppConexionLayer* satelite1AppConexionLayer = new AppConexionLayer(Socket::SocketType::CLIENT, SATELITE_1_ID);
    AppConexionLayer* satelite2AppConexionLayer = new AppConexionLayer(Socket::SocketType::CLIENT, SATELITE_2_ID);

    GroundControl *groundControl = new GroundControl(GROUND_CONTROL_ID, satelite1AppConexionLayer, satelite2AppConexionLayer);


    /* Tareas Harcodeadas */
    Task::TaskList_t taskList;
    Task task1("task1", {3,4,5}, 1.0f);
    taskList.push_back(&task1);

    Task task2("task2", {1,5,5,7}, 3.33f);
    taskList.push_back(&task2);
    
    groundControl->addListTaskToDo(taskList);

    /* SCHEDULER */
    while(true)
    {
        /* Socket Runner */
        satelite1AppConexionLayer->runnerTask();
        //satelite2AppConexionLayer->runnerTask();

        /* Task  Runner */
        groundControl->runnerTask();
    }

    return 0;
}

/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/
