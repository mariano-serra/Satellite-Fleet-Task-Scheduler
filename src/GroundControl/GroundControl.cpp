/* ---------------------------------------------------------------------------*/
/* Includes                                                                   */
/* ---------------------------------------------------------------------------*/
#include <iostream>
#include <algorithm>
#include "GroundControl.h"
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


/* ---------------------------------------------------------------------------*/
/* Implementacion de clases y funciones                                       */
/* ---------------------------------------------------------------------------*/
    
GroundControl::GroundControl(UniqueDeviceId_t id)
{
	m_groundControlId = id;
	m_satelite1Resources = new Resources(SATELITE_1_RES);
	m_satelite2Resources = new Resources(SATELITE_2_RES);
}

GroundControl::~GroundControl()
{
	delete(m_satelite1Resources);
	delete(m_satelite2Resources);
}

bool GroundControl::addListTaskToDo(TaskList_t taskList)
{
	// FIXME: validar antes de agregar, si con los recursos de hardware de cada satelite, la terea es posible de ejecutar
	// Ordenar las tareas pendientes por payoff, y pasarselas a la matriz de permutacion cada 10 tareas maximo
	newTaskList.insert(newTaskList.end(), taskList.begin(), taskList.end());

	makeTaskPermutatioMatrix(newTaskList);
	sortTaskPermutatioMatrixByPayoff();
	validateTaskPermutatioMatrix();
}

void GroundControl::runnerTask(void)
{

}

void GroundControl::processTaskListToDo(void)
{

}

void GroundControl::incrementDeviceVector(DeviceVector_t &vec, uint32_t deviceNumber)
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

void GroundControl::makeTaskPermutatioMatrix(TaskList_t& taskList)
{
	/* Orden de Solucion de permutacion */
	uint32_t taskNumber = taskList.size();									/* order 		*/
	uint32_t deviceNumber = NUM_DEVICES_ID;									/* base  		*/
	uint32_t permutationNumber = Utilities::ipow(deviceNumber, taskNumber);	/* base^order  	*/

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
		
		std::cout << permutation  << " > " << deviceVector << " > ";

		/* 	TaskList Permutation Matrix*/
		uint32_t taskIndex = 0;
		for (DeviceVector_t::iterator deviceceIdIt = deviceVector.begin(); deviceceIdIt < deviceVector.end(); ++deviceceIdIt)
		{
			Task* task = (taskList[taskIndex]);

			taskListVector[(*deviceceIdIt)].push_back(task);			/* Task*				*/
			taskIdListVector[(*deviceceIdIt)].push_back(task->getId());	/* TaskId - para debug	*/
			
			++taskIndex;
		}
		std::cout << taskIdListVector[0] << " " << taskIdListVector[1] << " " << taskIdListVector[2] << " > ";
		m_taskListPermutationMatrix.push_back(taskListVector);

		/* Payoff Vector
		 * 	Se utiliza el GROUND_CONTROL_ID, como indice de las tareas que no pueden ser asignadas a los satelites,
		 * 	por falta de recursos. */
		TaskList_t nonAssignTaskList = taskListVector[GROUND_CONTROL_ID];
		Task::Payoff_t nonAssignTaskPayoff = 0;

		for (TaskList_t::iterator taskListIt = nonAssignTaskList.begin(); taskListIt < nonAssignTaskList.end(); ++taskListIt)
		{
			Task* task = (*taskListIt);
			nonAssignTaskPayoff += task->getPayoff();
		}
		assignTaskPayoffVector.push_back(maxPayoff - nonAssignTaskPayoff);
		std::cout << assignTaskPayoffVector[permutation] << std::endl;

		/* Permutation Vector */
		m_permutationVector.push_back(permutation);

		/* ++ */
		incrementDeviceVector(deviceVector, deviceNumber);
	}
}

void GroundControl::sortTaskPermutatioMatrixByPayoff(void)
{
	/* Sorting */
    sort(m_permutationVector.begin(), m_permutationVector.end(), 
    	 [&](const int& a, const int& b) {return (assignTaskPayoffVector[a] > assignTaskPayoffVector[b]);}); /* FIXME: definir afuera, si es posible */

    std::cout << std::endl <<  m_permutationVector << std::endl << std::endl;
}

void GroundControl::validateTaskPermutatioMatrix(void)
{

    /* Validate Permutations */
	bool continueFlag = true;
	for (PermitationVector_t::iterator permutationIt = m_permutationVector.begin(); permutationIt < m_permutationVector.end() && continueFlag; ++permutationIt)
	{
		m_resourcesListVector.clear();
		uint32_t permutation = (*permutationIt);

		std::cout << permutation << std::endl;;

		/* Resources - Agrupo recursos de todas las tareas asociadas a un mismo device_id  */
		UniqueDeviceId_t deviceIndex = GROUND_CONTROL_ID;
		TaskListVector_t taskListVector = m_taskListPermutationMatrix[permutation];

		for (TaskListVector_t::iterator taskListIt = taskListVector.begin(); taskListIt < taskListVector.end(); ++taskListIt)
		{
			TaskList_t taskList = (*taskListIt);
			std::cout << " > " << deviceIndex << " > " << taskList  << " > ";

			Resources::ResourcesList_t resourcesList;
			for (TaskList_t::iterator taskIt = taskList.begin(); taskIt < taskList.end(); ++taskIt)
			{
				Task* task = (*taskIt);
				Resources::ResourcesList_t resourcesListTask = task->getResourcesList();

				resourcesList.insert(resourcesList.end(), resourcesListTask.begin(), resourcesListTask.end());

				std::cout << resourcesListTask  << " > ";
			}

			m_resourcesListVector.push_back(resourcesList);		 

			std::cout << resourcesList << std::endl;

			/* ++ */
			++deviceIndex;
		}

		continueFlag = !(m_satelite1Resources->contains(m_resourcesListVector[SATELITE_1_ID]) && (m_satelite2Resources->contains(m_resourcesListVector[SATELITE_2_ID])));
	
		std::cout << " >> " << continueFlag << std::endl;
	}
}



/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/