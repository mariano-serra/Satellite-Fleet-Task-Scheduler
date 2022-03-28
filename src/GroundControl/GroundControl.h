/*!
 *  \author Mariano Serra
 *
 *
 *  \brief [Breve descripcion del Modulo]
 */

#ifndef GROUND_CONTROL_H
#define GROUND_CONTROL_H

/* ---------------------------------------------------------------------------*/
/* Includes                                                                   */
/* ---------------------------------------------------------------------------*/
#include "PermutationTaskSolver.h"
#include "AppConexionLayer.h"
#include <map>

/* ---------------------------------------------------------------------------*/
/* Defines, Estructuras y Typedef Compartidos                                 */
/* ---------------------------------------------------------------------------*/

/*
 * Maximo de Tareas a ejecutar al mismo tiempo.
 * Esto es una litacion es debido a que la funcion de resolucion de la funcion de
 * costo tiene un orden elevado (3^N) y no esta optimizada.
 * A fines de debug y testing (unit), y para que sea facilmente entendible la ejecucion del
 * codigo se deja hardcodeado a 3.
 * Pero se probo con ordenes de 10 tareas y la solucion tarde aprox 1min.
 * Para tener una idea, con 10 tareas, el orden de la matriz de permutacion es de 59094 permutaciones!!!
 *
 */
static const uint32_t MAX_TASK_NUMBER_PERMUTATION_SOLVER = 3;

/*----------------------------------------------------------------------------*/
/* Variables Compartidas                                                      */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Clases y Prototipos de funciones Compartidas                               */
/*----------------------------------------------------------------------------*/

/**
 * @brief Abstraccion de GroundContol
 * @details
 */
class GroundControl
{
public:
    /**
     * @brief Contructor
     * @details GroundControl ya conoce de antemano los recursos de los satelites.
     *
     * @param id Identificador unico de dispositivo
     * @param satelite1AppConexionLayer Puntero a capa de comunicacion hacia satelite 1
     * @param satelite2AppConexionLayer Puntero a capa de comunicacion hacia satelite 2
     */
    GroundControl(UniqueDeviceId_t id, AppConexionLayer* satelite1AppConexionLayer, AppConexionLayer* satelite2AppConexionLayer);

    /**
     * @brief Destructor
     * @details
     */
    ~GroundControl();

    /**
     * @brief Funcion para el envio de tareas desde el GroundControl hacia los satelites
     * @details La tareas que se quieran ejecutar, seran almacendas y ejecutadas en la medida de que
     *          haya o liberen recursos en los satelites.
     *
     * @param taskList Lista de tareas a ejectutar
     * @return true
     */
    bool addListTaskToDo(Task::TaskList_t& taskList);

    /**
     * @brief Funcion de envio de tareas hacia Satelite 1
     * @details El GroundControl ocupa los recursos necesarions para la ejecucion de dichas tareas en de cada satelite
     *
     * @param taskList Lista de tareas a ejectutar por el satelite 1
     */
    virtual void sendSatelite1TaskList(Task::TaskList_t taskList);

    /**
     * @brief Funcion de envio de tareas hacia Satelite 2
     * @details El GroundControl ocupa los recursos necesarions para la ejecucion de dichas tareas en de cada satelite
     *
     * @param taskList Lista de tareas a ejectutar por el satelite 2
     */
    virtual void sendSatelite2TaskList(Task::TaskList_t taskList);

    /**
     * @brief Funcion encargada de validar el estado de las tareas que fueron ejecutas por el satelite 1.
     * @details El GroundControl libera los recursos necesarions de las tareas ya ejecutadas en de cada satelite
     *
     * @param task Puntero a tarea recibida.
     */
    virtual void updateSatelite1TaskState(Task* task);

    /**
     * @brief Funcion encargada de validar el estado de las tareas que fueron ejecutas por el satelite 2.
     * @details El GroundControl libera los recursos necesarions de las tareas ya ejecutadas en de cada satelite
     *
     * @param task Puntero a tarea recibida.
     */
    virtual void updateSatelite2TaskState(Task* task);

    void runnerTask(void);


private:

    /* Recursos disponibles en satelites */
    UniqueDeviceId_t m_groundControlId;
    Resources* m_satelite1HardwareResources;
    Resources* m_satelite1AvailableResources;
    Resources* m_satelite2HardwareResources;
    Resources* m_satelite2AvailableResources;

    /* Lista de tareas a ejecutar (pendientes) */
    Task::TaskList_t m_TodoTaskList;

    /* Lista de tareas ordenada de mayor a menor payoff */
    Task::TaskList_t m_BestTodoTaskList;

    /* Lista de tareas que no son posibles de asignar en ese momento */
    Task::TaskList_t m_UnassignedTaskList;

    /* Lista de tareas a asignar en ese momento para ambos satelites */
    Task::TaskList_t m_Satelite1TaskList;
    Task::TaskList_t m_Satelite2TaskList;

    /* Mapa de tareas */
    typedef std::map<Task::TaskId_t, Task*> TaskMap_t;
    TaskMap_t m_taskMap;

    /**
     * @brief Funcion para procesar la lista de tareas pendientes
     * @details
     */
    void ProcessToDoTaskList(void);

    /**
     * @brief Ordena la lista de tareas pendientes de mayor a menor payoff
     * @details
     */
    void sortToDoTaskListByPayoff(void);

    /**
     * @brief Recorta la lista de tareas a ejecutar a un maximo (MAX_TASK_NUMBER_PERMUTATION_SOLVER == 3).
     * @details Las tareas que no pueden ser ejecutadas en ese momento vuelven a la lista de tareas a realizar
     */
    void calcBestToDoTaskList(void);

    /**
     * @brief Funcion para la resolusion de matriz de permutaciones y optimizacion de funcion de costo
     * @details
     */
    void solveToDoTaskList(void);

    /**
     * @brief Verifica los estados de las tareas realizadas por los satelites
     * @details En caso de que se liberen recursos de los satelites, vuelve a validar y enviar tareas a ejecutar por los satelites
     */
    void updateTaskState(void);

    /**
     * @brief Funcion de valicicion de una tarea sobre los recursos disponibles de ambos satelites
     * @details
     *
     * @param task puntero a tarea
     * @return true, en caso de que la tarea pueda ser ejecutada por culquiera de los dos satelites
     */
    bool validateTaskOverHardwareResources(Task& task);

    /*
     * Punteros a capa de comunicaciones de cada satelite
     * El GroundControl se registra como cliente de los server de cada satelite
     */
    AppConexionLayer* m_satelite1AppConexionLayer;
    AppConexionLayer* m_satelite2AppConexionLayer;
};

/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/

#endif // GROUND_CONTROL_H
