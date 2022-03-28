/*!
 *  \author Mariano Serra
 *
 *
 *  \brief [Breve descripcion del Modulo]
 */

#ifndef PERMUTATION_TASK_SOLVER_H
#define PERMUTATION_TASK_SOLVER_H

/* ---------------------------------------------------------------------------*/
/* Includes                                                                   */
/* ---------------------------------------------------------------------------*/
#include "Resources.h"
#include "Task.h"
#include "SharedDeclarations.h"

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
 * @brief Metodos para la resolusion de matrix de permutaciones
 * @details Esta API resuelve el total de combinaciones posibles para la
 *          asignacion de tareas en los satelites y recursos disponibles.
 *
 */
class PermutationTaskSolver
{
public:
    /* Vector de Permutaciones posibles. De 0 a 3^(N) - 1 */
    typedef std::vector<uint32_t> PermutationVector_t;
    static PermutationVector_t m_permutationVector;

    /* Matriz de Dispositivos asociadas a cada tarea, por permurtacion posible */
    typedef std::vector<UniqueDeviceId_t> DeviceVector_t;
    typedef std::vector<DeviceVector_t> DevicePermutationMatrix_t;
    static DevicePermutationMatrix_t m_devicePermutationMatrix;

    /* Matriz de Listas de tareas asociadas a cada dispositivo, por permurtacion posible */
    typedef std::vector<Task::TaskList_t> TaskListVector_t;
    typedef std::vector<Task::TaskIdList_t> TaskIdListVector_t;
    typedef std::vector<TaskListVector_t> TaskListPermutationMatrix_t;
    static TaskListPermutationMatrix_t m_taskListPermutationMatrix;

    /* Vector de payoff total por permutacion posible */
    typedef std::vector<Task::Payoff_t> PayoffVector_t;
    static PayoffVector_t m_assignTaskPayoffVector;

    /* Vector de recursos necesario, por permutacion posible */
    typedef std::vector<Resources::ResourcesList_t> ResourcesListVector_t;
    static ResourcesListVector_t m_resourcesListVector;

    /**
     * @brief Inicializacion de datos interna
     * @details Obligatoria de llamar en cada computo.
     */
    static void initPermutatioMatrix(void);

    /**
     * @brief Calculo de matriz de permutacion posibles en funcion de lista de tareas a asignar, dispositivos y recursos disponibles.
     * @details
     *
     * @param taskList Vector de tareas a asignar
     */
    static void makeTaskPermutatioMatrix(Task::TaskList_t& taskList);

    /**
     * @brief Funcion para orden la matriz de permutacion, maximizando la funcion de consto (payoff)
     * @details
     */
    static void sortTaskPermutatioMatrixByPayoff(void);

    /**
     * @brief Funcion para la validacion de las permutaciones.
     * @details Validad si para una determinada conbinacion de tareas a cada dispositvo, se tiene la totalidad de los recursos necesarios.
     *          Esta ejeccuion de ejecuta en orden de payoff descendiente.
     *          La primera permutacion posible es la elegida.
     *
     * @param satelite1Resources Vector de recursos disponibles actualmente por el satelite 1
     * @param satelite2Resources Vector de recursos disponibles actualmente por el satelite 2
     * @param unassignedTaskList Vector de tareas que no pueden ser asignadas en este momento
     * @param satelite1TaskList Lista de tareas a asignar a satelite 1
     * @param satelite2TaskList Lista de tareas a asignar a satelite 1
     * @return devuelve true, si existe permutacion posible para la asignacion de tareas hacia los satelites
     */
    static bool validateTaskPermutatioMatrix(Resources& satelite1Resources, Resources& satelite2Resources,
            Task::TaskList_t& unassignedTaskList, Task::TaskList_t& satelite1TaskList, Task::TaskList_t& satelite2TaskList);

private:
    /**
     * @brief Funcion auxiliar para la generacion del vector de la matriz de permutaciones
     * @details
     *
     * @param vec Vector de permutacion
     * @param deviceNumber cantidad de dispositivos disponibles (3)
     */
    static void incrementDeviceVector(DeviceVector_t &vec, uint32_t deviceNumber);
};

/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/

#endif // PERMUTATION_TASK_SOLVER_H


