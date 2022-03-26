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

    void runnerTask(void);
    
    virtual bool FakeTaskSuccess(void);
    virtual TaskTime_t FakeTaskTime(void);

private:
    // No se todavia como va a ser la interfaz hacia el proxy. 
    // Cada entidad se va a tener que registrar como observer y generador de eventos
    void setTaskState(Task* task, Task::State_t state);

    UniqueDeviceId_t m_sateliteId;
    Resources *m_hardwareResources; // Bakup
    Resources *m_availableResources;

    typedef std::map<Task*, TaskTime_t> TaskMap_t;
    TaskMap_t m_ongoingTasks;

    AppConexionLayer* m_appConexionLayer;
};

/*----------------------------------------------------------------------------*/
/* Fin 																		  */
/*----------------------------------------------------------------------------*/

#endif // SATELITE_H
