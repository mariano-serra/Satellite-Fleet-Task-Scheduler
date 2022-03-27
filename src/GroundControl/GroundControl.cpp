/* ---------------------------------------------------------------------------*/
/* Includes                                                                   */
/* ---------------------------------------------------------------------------*/
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
    
GroundControl::GroundControl(UniqueDeviceId_t id, AppConexionLayer* satelite1AppConexionLayer, AppConexionLayer* satelite2AppConexionLayer)
{
	m_groundControlId = id;

    m_satelite1HardwareResources = new Resources(SATELITE_1_RES);
    m_satelite1AvailableResources = new Resources(SATELITE_1_RES);

    m_satelite2HardwareResources = new Resources(SATELITE_2_RES);
    m_satelite2AvailableResources = new Resources(SATELITE_2_RES);

	m_TodoTaskList.clear();
	m_BestTodoTaskList.clear();
	m_UnassignedTaskList.clear();
	m_Satelite1TaskList.clear();
	m_Satelite2TaskList.clear();

	m_satelite1AppConexionLayer = satelite1AppConexionLayer;
	m_satelite2AppConexionLayer = satelite2AppConexionLayer;
}

GroundControl::~GroundControl()
{
	delete(m_satelite1HardwareResources);
	delete(m_satelite1AvailableResources);

	delete(m_satelite2HardwareResources);
	delete(m_satelite2AvailableResources);
}

bool GroundControl::addListTaskToDo(Task::TaskList_t& taskList)
{

	DEBUG_MSG("TaskList:\t" << taskList << std::endl);

	for (Task::TaskList_t::iterator taskIt = taskList.begin(); taskIt < taskList.end(); ++taskIt)
	{
		Task* task = (*taskIt);

		if (validateTaskOverHardwareResources(*task))
		{
			/* Add Task to List */
			m_TodoTaskList.push_back(task);
			/* Add Task to Map */
			m_taskMap[task->getId()] = task;
		}
	}

	DEBUG_MSG("TodoTaskList:\t" << m_TodoTaskList << std::endl);

	/* Process Task List */
	sortTodoTaskListByPayoff();

	DEBUG_MSG("Sorted TodoTaskList:\t" << m_TodoTaskList << std::endl);
	
	calcBestTodoTaskList();

	DEBUG_MSG("Trim TodoTaskList:\t" << m_TodoTaskList << std::endl);

	/* Solver */
	processTaskListToDo();

	return true;
}

void GroundControl::sendSatelite1TaskList(Task::TaskList_t taskList)
{
	/* Hacia protocolo */
	for (Task::TaskList_t::iterator taskIt = taskList.begin(); taskIt < taskList.end(); ++taskIt)
	{
		Task* task = (*taskIt);

		/* Asigno la tarea al satelite mediante el protocolo */
		if (m_satelite1AppConexionLayer)
		{
			m_satelite1AppConexionLayer->sendTask(task);
		}

		/* Quito los recursos disponibles de ese satelite mientras este realizando la tarea */
		m_satelite1AvailableResources->substrac(task->getResourcesList());
	}
}

void GroundControl::sendSatelite2TaskList(Task::TaskList_t taskList)
{
	/* Hacia protocolo */
	for (Task::TaskList_t::iterator taskIt = taskList.begin(); taskIt < taskList.end(); ++taskIt)
	{
		Task* task = (*taskIt);

		/* Asigno la tarea al satelite mediante el protocolo */
		if (m_satelite2AppConexionLayer)
		{
			m_satelite2AppConexionLayer->sendTask(task);
		}

		/* Quito los recursos disponibles de ese satelite mientras este realizando la tarea */
		m_satelite2AvailableResources->substrac(task->getResourcesList());
	}
}

void GroundControl::updateSatelite1TaskState(Task* task)
{
	/* Borro tarea del mapa */
	m_taskMap.erase(task->getId());

	/* Reasigno nuevamente los recursos de ese satelite que la tarea libero */
	m_satelite1AvailableResources->add(task->getResourcesList());

	/* Borro tarea */
	delete(task);
}

void GroundControl::updateSatelite2TaskState(Task* task)
{
	/* Borro tarea del mapa */
	m_taskMap.erase(task->getId());

	/* Reasigno nuevamente los recursos de ese satelite que la tarea libero */
	m_satelite2AvailableResources->add(task->getResourcesList());

	/* Borro tarea */
	delete(task);
}

void GroundControl::updateTaskState(void)
{
    /* Get new Task ToDo */
    if (m_satelite1AppConexionLayer)
    {
        Task* newTask;
        if (m_satelite1AppConexionLayer->receiveTask(&newTask))
        {
            updateSatelite1TaskState(newTask);
        }
    }

    /* Get new Task ToDo */
    if (m_satelite2AppConexionLayer)
    {
        Task* newTask;
        if (m_satelite2AppConexionLayer->receiveTask(&newTask))
        {
            updateSatelite2TaskState(newTask);
        }
    }
}

void GroundControl::runnerTask(void)
{
    updateTaskState();
}

bool GroundControl::validateTaskOverHardwareResources(Task& task)
{
	Resources::ResourcesList_t resourcesList = task.getResourcesList();

	bool ret = (m_satelite1HardwareResources->contains(resourcesList)) || 
		       (m_satelite2HardwareResources->contains(resourcesList));

    return ret;
}

void GroundControl::sortTodoTaskListByPayoff(void)
{
	typedef Task* TaskPtr_t;

	std::sort(m_TodoTaskList.begin(), m_TodoTaskList.end(),
              [](const TaskPtr_t& task1, const TaskPtr_t& task2) { return task1->getPayoff() > task2->getPayoff();});

}

void GroundControl::calcBestTodoTaskList(void)
{
	Task::TaskList_t::iterator initTaskIt = m_TodoTaskList.begin();
	Task::TaskList_t::iterator endTaskIt = m_TodoTaskList.end();

	if (m_TodoTaskList.size() > MAX_TASK_NUMBER_PERMUTATION_SOLVER)
	{
		endTaskIt = initTaskIt + MAX_TASK_NUMBER_PERMUTATION_SOLVER;
	}

	m_BestTodoTaskList.clear();
	m_BestTodoTaskList.insert(m_BestTodoTaskList.begin(), initTaskIt, endTaskIt);
	m_TodoTaskList.erase(initTaskIt, endTaskIt);
}

void GroundControl::processTaskListToDo(void)
{
	m_UnassignedTaskList.clear();
	m_Satelite1TaskList.clear();
	m_Satelite2TaskList.clear();

	PermutationTaskSolver::initPermutatioMatrix();
	PermutationTaskSolver::makeTaskPermutatioMatrix(m_BestTodoTaskList);
	PermutationTaskSolver::sortTaskPermutatioMatrixByPayoff();
	PermutationTaskSolver::validateTaskPermutatioMatrix(*m_satelite1AvailableResources, *m_satelite2AvailableResources,
													    m_UnassignedTaskList, m_Satelite1TaskList, m_Satelite2TaskList);
	
	sendSatelite1TaskList(m_Satelite1TaskList);
	sendSatelite2TaskList(m_Satelite2TaskList);

	m_TodoTaskList.insert(m_TodoTaskList.end(), m_UnassignedTaskList.begin(), m_UnassignedTaskList.end());
	sortTodoTaskListByPayoff();
}


/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/