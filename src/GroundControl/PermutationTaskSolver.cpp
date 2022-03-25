/* ---------------------------------------------------------------------------*/
/* Includes                                                                   */
/* ---------------------------------------------------------------------------*/
#include <iostream>
#include <algorithm>
#include "PermutationTaskSolver.h"
#include "Utilities.h"

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
PermutationTaskSolver::PermutationVector_t PermutationTaskSolver::m_permutationVector;
PermutationTaskSolver::DevicePermutationMatrix_t PermutationTaskSolver::m_devicePermutationMatrix;
PermutationTaskSolver::TaskListPermutationMatrix_t PermutationTaskSolver::m_taskListPermutationMatrix;
PermutationTaskSolver::PayoffVector_t PermutationTaskSolver::m_assignTaskPayoffVector;
PermutationTaskSolver::ResourcesListVector_t PermutationTaskSolver::m_resourcesListVector;

/* ---------------------------------------------------------------------------*/
/* Implementacion de clases y funciones                                       */
/* ---------------------------------------------------------------------------*/

void PermutationTaskSolver::incrementDeviceVector(DeviceVector_t& vec, uint32_t deviceNumber)
{
    vec[0] = static_cast<UniqueDeviceId_t>(static_cast<uint32_t>(vec[0]) + 1);

    for (DeviceVector_t::iterator deviceIdIterator = vec.begin(); deviceIdIterator < vec.end() - 1; ++deviceIdIterator)
    {
        DeviceVector_t::iterator nextDeviceIdIterator = deviceIdIterator + 1;

        if ((*deviceIdIterator) >= deviceNumber)
        {
            (*deviceIdIterator) = 0;
            (*nextDeviceIdIterator)++;
        }
    }
}

void PermutationTaskSolver::makeTaskPermutatioMatrix(TaskList_t& taskList)
{
    /* Orden de Solucion de permutacion */
    uint32_t taskNumber = taskList.size();                                  /* order        */
    uint32_t deviceNumber = NUM_DEVICES_ID;                                 /* base         */
    uint32_t permutationNumber = Utilities::ipow(deviceNumber, taskNumber); /* base^order   */

    /* Max Payoff Calc */
    Task::Payoff_t maxPayoff = 0;
    for (TaskList_t::iterator taskListIt = taskList.begin(); taskListIt < taskList.end(); ++taskListIt)
    {
        Task* task = (*taskListIt);
        maxPayoff += task->getPayoff(); 
    }

    /* Permutation Matrix */
    m_devicePermutationMatrix.clear();
    m_taskListPermutationMatrix.clear();

    DeviceVector_t deviceVector(taskNumber);
    for (uint32_t permutation = 0; permutation < permutationNumber; ++permutation)
    {
        /* Device Permutation Matrix */
        TaskListVector_t taskListVector(deviceNumber);
        TaskIdListVector_t taskIdListVector(deviceNumber);

        m_devicePermutationMatrix.push_back(deviceVector);
        
        DEBUG_MSG("Permutation:\t" << permutation  << "\t- Devices:\t" << deviceVector);

        /*  TaskList Permutation Matrix*/
        uint32_t taskIndex = 0;
        for (DeviceVector_t::iterator deviceceIdIt = deviceVector.begin(); deviceceIdIt < deviceVector.end(); ++deviceceIdIt)
        {
            Task* task = (taskList[taskIndex]);

            taskListVector[(*deviceceIdIt)].push_back(task);            /* Task*                */
            taskIdListVector[(*deviceceIdIt)].push_back(task->getId()); /* TaskId - para debug  */

            ++taskIndex;
        }
        m_taskListPermutationMatrix.push_back(taskListVector);

        /* Payoff Vector
         *  Se utiliza el GROUND_CONTROL_ID, como indice de las tareas que no pueden ser asignadas a los satelites,
         *  por falta de recursos. */
        DEBUG_MSG("\t- Non Assigned TaskIdList:\t" << taskIdListVector[GROUND_CONTROL_ID]);
        TaskList_t nonAssignTaskList = taskListVector[GROUND_CONTROL_ID];
        Task::Payoff_t nonAssignTaskPayoff = 0;

        for (TaskList_t::iterator taskListIt = nonAssignTaskList.begin(); taskListIt < nonAssignTaskList.end(); ++taskListIt)
        {
            Task* task = (*taskListIt);
            nonAssignTaskPayoff += task->getPayoff();
        }
        m_assignTaskPayoffVector.push_back(maxPayoff - nonAssignTaskPayoff);
        
        DEBUG_MSG("\t- Payoff:\t" << m_assignTaskPayoffVector[permutation] << std::endl);

        /* Permutation Vector */
        m_permutationVector.push_back(permutation);

        /* ++ */
        incrementDeviceVector(deviceVector, deviceNumber);
    }
}

void PermutationTaskSolver::sortTaskPermutatioMatrixByPayoff(void)
{
    /* Sorting */
    std::sort(m_permutationVector.begin(), m_permutationVector.end(), 
              [&](const int& a, const int& b) {return (m_assignTaskPayoffVector[a] > m_assignTaskPayoffVector[b]);}); /* FIXME: definir afuera, si es posible */

    DEBUG_MSG("Sorted Payoff Permutation Verctor:\t" << m_permutationVector << std::endl);
}

bool PermutationTaskSolver::validateTaskPermutatioMatrix(Resources& satelite1Resources, Resources& satelite2Resources, 
                                                         TaskList_t& satelite1TaskList, TaskList_t& satelite2TaskList)
{
    bool ret = false;
    uint32_t permutation = 0;
    TaskListVector_t taskListVector;

    /* Validate Permutations */
    bool continueFlag = true;
    for (PermutationVector_t::iterator permutationIt = m_permutationVector.begin(); permutationIt < m_permutationVector.end() && continueFlag; ++permutationIt)
    {
        m_resourcesListVector.clear();
        
        permutation = (*permutationIt);

        DEBUG_MSG("Permutation:\t" << permutation << std::endl);

        /* Resources - Agrupo recursos de todas las tareas asociadas a un mismo device_id  */
        UniqueDeviceId_t deviceIndex = GROUND_CONTROL_ID;
        taskListVector = m_taskListPermutationMatrix[permutation];

        for (TaskListVector_t::iterator taskListIt = taskListVector.begin(); taskListIt < taskListVector.end(); ++taskListIt)
        {
            TaskList_t taskList = (*taskListIt);
            DEBUG_MSG("\tDeviceId\t" << deviceIndex << "\t- TaskList:\t" << taskList);

            Resources::ResourcesList_t resourcesList;
            for (TaskList_t::iterator taskIt = taskList.begin(); taskIt < taskList.end(); ++taskIt)
            {
                Task* task = (*taskIt);
                Resources::ResourcesList_t resourcesListTask = task->getResourcesList();

                resourcesList.insert(resourcesList.end(), resourcesListTask.begin(), resourcesListTask.end());

            }
            DEBUG_MSG("\t- ResourcesList:\t" << resourcesList);
            m_resourcesListVector.push_back(resourcesList);      

            DEBUG_MSG(resourcesList << std::endl);

            /* ++ */
            ++deviceIndex;
        }

        continueFlag = !(satelite1Resources.contains(m_resourcesListVector[SATELITE_1_ID]) && (satelite2Resources.contains(m_resourcesListVector[SATELITE_2_ID])));
        DEBUG_MSG("\t- Valid?:\t" << !continueFlag << std::endl);
    }

    if (continueFlag == false)
    {

        satelite1TaskList = taskListVector[SATELITE_1_ID];
        satelite2TaskList = taskListVector[SATELITE_2_ID];

        ret = true;
    }

    return ret;
}

/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/