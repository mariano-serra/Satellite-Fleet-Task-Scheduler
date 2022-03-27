/*!
 *  \author Mariano Serra
 *
 *
 *  \brief [Breve descripcion del Modulo]
 */

#ifndef SATELITE_H
#define SATELITE_H

/* ---------------------------------------------------------------------------*/
/* Includes                                                                   */
/* ---------------------------------------------------------------------------*/
#include "SharedDeclarations.h"
#include "Resources.h"
#include "Task.h"
#include "AppConexionLayer.h"

/* ---------------------------------------------------------------------------*/
/* Defines, Estructuras y Typedef Compartidos                                 */
/* ---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Variables Compartidas                                                      */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Clases y Prototipos de funciones Compartidas                               */
/*----------------------------------------------------------------------------*/

/**
 * @brief Abstraccion de Satelite
 * @details
 */
class Satelite
{
public:

    /**
     * @brief Constructor
     * @details
     *
     * @param id Identificador unico de dispositivo
     * @param resourcesList Vector de recursos disponibles en satelite
     * @param appConexionLayer Puntero a capa de comunicacion.
     */
    Satelite(UniqueDeviceId_t id, Resources::ResourcesList_t resourcesList, AppConexionLayer* appConexionLayer);

    /**
     * @brief Destructor
     * @details
     */
    ~Satelite();

    /**
     * @brief Funcion para la optencion de los recursos disponibles actualmente
     *        (no ocupados por tareas en ejecucion) en el satelite.
     * @details
     * @return Vector de recursos disponibles
     */
    Resources::ResourcesList_t getAvailableResources(void);

    /**
     * @brief Funcion para la asignaciones de tareas hacia el satelite
     * @details Esta funcion valida si con los recursos de hardware del satelite (el total),
     *          es posible realizar dicha tarea en algun momento (o cuando los recursos este disponibles).
     *          Al mismo tiempo le asigna un tiempo de ejecucion (FAKE), en el que la tarea ocupara los recursos necesarion.
     *          El conjunto de tareas que se estan ejecutando es almacenado en un vector para dicho fin.
     *
     * @param task Puntero a nueva tarea
     * @return devuelve true, en caso de que la tarea haya sido asignada correctamente
     */
    bool addTaskToDo(Task* task);

    /**
     * @brief Funcion que verifica si llegan nuevas tareas por el protocolo a asignar.
     * @details En caso de que se reciba una nueva tareas desde el GroundControl, la asigna mediante la
     *          funcion addTaskToDo().
     */
    void getNewTaskToDo(void);

    /**
     * @brief Task Runner
     * @details Funcion principal para la ejeccion de las tareas.
     *          Esta funcion deberia ser la encargada de llamar a los runnerTask de cada una de las tareas.
     *          Al finalizar una tarea (por tiempo), se evalua el exito de la ejecucion (FAKE), modificando el
     *          estado de la misma tarea de IN_EXECUTION a EXECUTED o FAILURE_DURING_EXECUTION.
     */
    void runOngoingTask(void);

    /**
     * @brief RunnerTask Principal
     * @details
     */
    void runnerTask(void);

    /* Tiempo de ejecucion asociado a una tarea */
    typedef int64_t TaskTime_t;

    /**
     * @brief Funcion FAKE para la obtencion de tiempo de ejecion de una tarea
     * @details
     * @return Tiempo de ejecuccion
     */
    virtual TaskTime_t FakeTaskTime(void);

    /**
     * @brief Funcion FAKE para la obtencion de exito de ejecucion de tarea.
     * @details
     * @return true, si la tarea se ejecuto con exito
     */
    virtual bool FakeTaskSuccess(void);

private:
    /* Identificar unico de dispositivo */
    UniqueDeviceId_t m_sateliteId;

    /* Recursos de hardware de satelite. Estos no se modifican nunca */
    Resources *m_hardwareResources;

    /* Recursos disponibles actualmente. Varia de acuerdo a las tareas asignadas en ese momento */
    Resources *m_availableResources;

    /* Mapa de tarea */
    typedef struct TaskData
    {
        Task* task;
        TaskTime_t time;
    } TaskData_t;
    typedef std::map<Task::TaskId_t, TaskData_t> TaskMap_t;

    /* Vector de tareas en ejecuccion */
    TaskMap_t m_ongoingTasks;

    /* Puntero a capa de comunicacion */
    AppConexionLayer* m_appConexionLayer;
};

/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/

#endif // SATELITE_H
