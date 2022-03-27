/*!
 *  \author Mariano Serra
 *
 *
 *  \brief [Breve descripcion del Modulo]
 */

#ifndef SATELITE_H
#define SATELITE_H

/* ---------------------------------------------------------------------------*/
/* Includes 																  */
/* ---------------------------------------------------------------------------*/
#include "SharedDeclarations.h"
#include "Resources.h"
#include "Task.h"
#include "AppConexionLayer.h"

/* ---------------------------------------------------------------------------*/
/* Defines, Estructuras y Typedef Compartidos 								  */
/* ---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Variables Compartidas                                                      */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Clases y Prototipos de funciones Compartidas 				              */
/*----------------------------------------------------------------------------*/

class Satelite
{
public:
    /* Mapa de Tareas */
    typedef int64_t TaskTime_t;

    Satelite(UniqueDeviceId_t id, Resources::ResourcesList_t resourcesList, AppConexionLayer* appConexionLayer);
    ~Satelite();

    Resources::ResourcesList_t getAvailableResources(void);
    bool addTaskToDo(Task* task);

    void getNewTaskToDo(void);
    void runOngoingTask(void);

    void runnerTask(void);
    
    virtual bool FakeTaskSuccess(void);
    virtual TaskTime_t FakeTaskTime(void);

private:
    UniqueDeviceId_t m_sateliteId;
    Resources *m_hardwareResources; // Bakup
    Resources *m_availableResources;

    typedef struct TaskData
    {
        Task* task;
        TaskTime_t time;
    }TaskData_t;
    typedef std::map<Task::TaskId_t, TaskData_t> TaskMap_t;
    TaskMap_t m_ongoingTasks;

    AppConexionLayer* m_appConexionLayer;
};

/*----------------------------------------------------------------------------*/
/* Fin 																		  */
/*----------------------------------------------------------------------------*/

#endif // SATELITE_H
