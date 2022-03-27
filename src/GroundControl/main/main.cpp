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
    Task* task1;
    Task* task2;
    Task* task3;
    Task* task4;

    std::string task1Name = "task1";
    Resources::ResourcesList_t task1ResourcesList = {3,5,7};
    float task1Payoff = 10.0f;
    task1 = new Task(task1Name, task1ResourcesList, task1Payoff);
    taskList.push_back(task1);

    std::string task2Name = "task2";
    Resources::ResourcesList_t task2ResourcesList = {1,2};
    float task2Payoff = 2.5f;
    task2 = new Task(task2Name, task2ResourcesList, task2Payoff);
    taskList.push_back(task2);

    std::string task3Name = "task3";
    Resources::ResourcesList_t task3ResourcesList = {4,7,10};
    float task3Payoff = 2.5f;
    task3 = new Task(task3Name, task3ResourcesList, task3Payoff);
    taskList.push_back(task3);

    std::string task4Name = "task4";
    Resources::ResourcesList_t task4ResourcesList = {2,6,8};
    float task4Payoff = 5.0f;
    task4 = new Task(task4Name, task4ResourcesList, task4Payoff);
    taskList.push_back(task4);
    
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
