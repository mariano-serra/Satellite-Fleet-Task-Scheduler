/*!
 *  \author Mariano Serra
 *
 *
 *  \brief [Breve descripcion del Modulo]
 */

#ifndef GROUND_CONTROL_H
#define GROUND_CONTROL_H

/* ---------------------------------------------------------------------------*/
/* Includes 																  */
/* ---------------------------------------------------------------------------*/
#include "PermutationTaskSolver.h"
#include "AppConexionLayer.h"
#include <map>

/* ---------------------------------------------------------------------------*/
/* Defines, Estructuras y Typedef Compartidos 								  */
/* ---------------------------------------------------------------------------*/
static const uint32_t MAX_TASK_NUMBER_PERMUTATION_SOLVER = 3;

/*----------------------------------------------------------------------------*/
/* Variables Compartidas                                                      */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Clases y Prototipos de funciones Compartidas 				              */
/*----------------------------------------------------------------------------*/

class GroundControl
{
public:
    GroundControl(UniqueDeviceId_t id, AppConexionLayer* satelite1AppConexionLayer, AppConexionLayer* satelite2AppConexionLayer);
    ~GroundControl();

    bool addListTaskToDo(Task::TaskList_t& taskList);

    virtual void sendSatelite1TaskList(Task::TaskList_t taskList);
    virtual void sendSatelite2TaskList(Task::TaskList_t taskList);

    void updateSatelite1TaskState(Task* task);
    void updateSatelite2TaskState(Task* task);
    void updateTaskState(void);

    void runnerTask(void);


private:
    
    // No se todavia como va a ser la interfaz hacia el proxy. 
    // Cada entidad se va a tener que registrar como observer y generador de eventos

    // void sendSateliteTaskToDo(SateliteId_t id, Task* task);
    // Resources::ResourcesList_t updateSateliteAvailableResources(SateliteId_t id);
    // void updateSatelteTaskState(SateliteId_t id, Task* task);

    UniqueDeviceId_t m_groundControlId;
    Resources* m_satelite1HardwareResources;
    Resources* m_satelite1AvailableResources;
    Resources* m_satelite2HardwareResources;
    Resources* m_satelite2AvailableResources;

    Task::TaskList_t m_TodoTaskList;
    Task::TaskList_t m_BestTodoTaskList;
    Task::TaskList_t m_UnassignedTaskList;
    Task::TaskList_t m_Satelite1TaskList;
    Task::TaskList_t m_Satelite2TaskList;

    typedef std::map<Task::TaskId_t, Task*> TaskMap_t;
    TaskMap_t m_taskMap;

    bool validateTaskOverHardwareResources(Task& task);
    void sortTodoTaskListByPayoff(void);
    void calcBestTodoTaskList(void);

    void processTaskListToDo(void);

    AppConexionLayer* m_satelite1AppConexionLayer;
    AppConexionLayer* m_satelite2AppConexionLayer;
};

/*----------------------------------------------------------------------------*/
/* Fin 																		  */
/*----------------------------------------------------------------------------*/

#endif // GROUND_CONTROL_H
