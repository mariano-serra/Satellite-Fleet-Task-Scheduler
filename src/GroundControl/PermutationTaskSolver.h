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

class PermutationTaskSolver
{
public:
    typedef std::vector<uint32_t> PermutationVector_t;
    static PermutationVector_t m_permutationVector;

    typedef std::vector<UniqueDeviceId_t> DeviceVector_t;
    typedef std::vector<DeviceVector_t> DevicePermutationMatrix_t;
    static DevicePermutationMatrix_t m_devicePermutationMatrix;
    
    typedef std::vector<Task::TaskList_t> TaskListVector_t;
    typedef std::vector<Task::TaskIdList_t> TaskIdListVector_t;
    typedef std::vector<TaskListVector_t> TaskListPermutationMatrix_t;
    static TaskListPermutationMatrix_t m_taskListPermutationMatrix;

    typedef std::vector<Task::Payoff_t> PayoffVector_t;
    static PayoffVector_t m_assignTaskPayoffVector;

    typedef std::vector<Resources::ResourcesList_t> ResourcesListVector_t;
    static ResourcesListVector_t m_resourcesListVector;

    static void initPermutatioMatrix(void);
    static void makeTaskPermutatioMatrix(Task::TaskList_t& taskList);
    static void sortTaskPermutatioMatrixByPayoff(void);
    static bool validateTaskPermutatioMatrix(Resources& satelite1Resources, Resources& satelite2Resources, 
                                             Task::TaskList_t& unassignedTaskList, Task::TaskList_t& satelite1TaskList, Task::TaskList_t& satelite2TaskList); 
    
private:
    static void incrementDeviceVector(DeviceVector_t &vec, uint32_t deviceNumber);
};

/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/

#endif // PERMUTATION_TASK_SOLVER_H


