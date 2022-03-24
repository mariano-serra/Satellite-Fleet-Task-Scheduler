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
#include "Resources.h"
#include "Task.h"
#include "Satelite.h"

/* ---------------------------------------------------------------------------*/
/* Defines, Estructuras y Typedef Compartidos 								  */
/* ---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Variables Compartidas                                                      */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Clases y Prototipos de funciones Compartidas 				              */
/*----------------------------------------------------------------------------*/

class GroundControl
{
public:
    /*! Lista de Tareas */
    typedef std::vector<Task*> TaskList_t;
    typedef std::vector<Task::TaskId_t> TaskIdList_t;

    GroundControl(UniqueDeviceId_t id);
    ~GroundControl();

    bool addListTaskToDo(TaskList_t taskList);

    void runnerTask(void);

private:
    
    // No se todavia como va a ser la interfaz hacia el proxy. 
    // Cada entidad se va a tener que registrar como observer y generador de eventos

    // void sendSateliteTaskToDo(SateliteId_t id, Task* task);
    // Resources::ResourcesList_t updateSateliteAvailableResources(SateliteId_t id);
    // void updateSatelteTaskState(SateliteId_t id, Task* task);

    UniqueDeviceId_t m_groundControlId;
    Resources* m_satelite1Resources;
    Resources* m_satelite2Resources;

    void processTaskListToDo(void);

    TaskList_t newTaskList;
    TaskList_t satelite1TaskList;
    TaskList_t satelite2TaskList;
    TaskList_t todoTaskList;

    /* Permutation Problem */
    typedef std::vector<uint32_t> PermitationVector_t;
    PermitationVector_t m_permutationVector;

    typedef std::vector<UniqueDeviceId_t> DeviceVector_t;
    typedef std::vector<DeviceVector_t> DevicePermutationMatrix_t;                  /* UniqueDeviceId = f(permutationNumber, TaskId) */
    DevicePermutationMatrix_t m_devicePermutationMatrix;
    
    typedef std::vector<TaskList_t> TaskListVector_t;                              /* TaskList = f(UniqueDeviceId) */
    typedef std::vector<TaskIdList_t> TaskIdListVector_t;
    typedef std::vector<TaskListVector_t> TaskListPermutationMatrix_t;             /* TaskList = f(permutationNumber, UniqueDeviceId) */
    TaskListPermutationMatrix_t m_taskListPermutationMatrix;

    typedef std::vector<Task::Payoff_t> PayoffVector_t;
    PayoffVector_t assignTaskPayoffVector;

    typedef std::vector<Resources::ResourcesList_t> ResourcesListVector_t;
    ResourcesListVector_t m_resourcesListVector;

    void incrementDeviceVector(DeviceVector_t &vec, uint32_t deviceNumber);
    void makeTaskPermutatioMatrix(TaskList_t& taskList);
    void sortTaskPermutatioMatrixByPayoff(void);
    void validateTaskPermutatioMatrix(void);

};

/*----------------------------------------------------------------------------*/
/* Fin 																		  */
/*----------------------------------------------------------------------------*/

#endif // GROUND_CONTROL_H
