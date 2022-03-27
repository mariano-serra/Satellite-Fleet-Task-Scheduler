/* ---------------------------------------------------------------------------*/
/* Includes                                                                   */
/* ---------------------------------------------------------------------------*/
#include "Satelite.h"

/* ---------------------------------------------------------------------------*/
/* Debug                                                                      */
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Defines, Estructuras y Typedef                                             */
/* ---------------------------------------------------------------------------*/

/* Porcenta Fake de falla en ejecucion de tarea */
static const uint16_t FailPercent = 10;

/* Tiempos maximos y minimos Fake en ejecucion de tarea */
static const uint16_t MinTaskTime = 5;
static const uint16_t MaxTaskTime = 100;

/* ---------------------------------------------------------------------------*/
/* Declaracion de funciones                                                   */
/* ---------------------------------------------------------------------------*/


/* ---------------------------------------------------------------------------*/
/* Variables externas y privadas                                              */
/* ---------------------------------------------------------------------------*/


/* ---------------------------------------------------------------------------*/
/* Implementacion de clases y funciones                                       */
/* ---------------------------------------------------------------------------*/

/*!
 * \\brief Constructor
 **/

Satelite::Satelite(UniqueDeviceId_t id, Resources::ResourcesList_t resourcesList, AppConexionLayer* appConexionLayer)
{
    m_sateliteId = id;
    m_hardwareResources = new Resources(resourcesList);
    m_availableResources = new Resources(resourcesList);

    m_appConexionLayer = appConexionLayer;
}

Satelite::~Satelite()
{

}

Resources::ResourcesList_t Satelite::getAvailableResources(void)
{
    return m_availableResources->getResourcesList();
}

bool Satelite::addTaskToDo(Task* task)
{
    /* Verifica si la terea puede ser ejecutada con los recursos actuales */
    bool ret = m_availableResources->contains(task->getResourcesList());

    if (ret)
    {
        /* Asigna la tarea a la lista de pendientes */
        TaskData_t taskData;
        taskData.task = task;
        taskData.time = FakeTaskTime();
        m_ongoingTasks[task->getId()] = taskData;

        task->setState(Task::IN_EXECUTION);

        /* Reserva los recursos necesarios */
        m_availableResources->substrac(task->getResourcesList());
    }

    return ret;
}

void Satelite::getNewTaskToDo(void)
{
    /* Get new Task ToDo */
    if (m_appConexionLayer)
    {
        Task* newTask;
        if (m_appConexionLayer->receiveTask(&newTask))
        {
            addTaskToDo(newTask);
        }
    }
}

void Satelite::runOngoingTask(void)
{
    Task::TaskIdList_t deleteTaskList;

    for (TaskMap_t::iterator ongoingTaskIt = m_ongoingTasks.begin(); ongoingTaskIt != m_ongoingTasks.end(); ++ongoingTaskIt)
    {
        Task::TaskId_t taskId = ongoingTaskIt->first;
        TaskData_t* taskData = &(ongoingTaskIt->second);
        Task* task = taskData->task;

        (taskData->time)--;
        if (taskData->time < 0)
        {
            if (FakeTaskSuccess())
            {
                task->setState(Task::EXECUTED);
            }
            else
            {
                task->setState(Task::FAILURE_DURING_EXECUTION);
            }

            /* Enviar tarea a estacion terrena con estado actualizado */
            if (m_appConexionLayer)
            {
                m_appConexionLayer->sendTask(task);
            }

            /* Libera los recursos */
            m_availableResources->add(task->getResourcesList());

            /* Agrego tarea a borra en el mapa */
            deleteTaskList.push_back(taskId);

            delete(task);
        }
    }

    for (Task::TaskIdList_t::iterator taskIdIt = deleteTaskList.begin(); taskIdIt < deleteTaskList.end(); ++taskIdIt)
    {
        Task::TaskId_t taskId = (*taskIdIt);
        m_ongoingTasks.erase(taskId);
    }
}

void Satelite::runnerTask(void)
{ 
    /* Get new Task ToDo */
    getNewTaskToDo();

    /* Run Satelite Task List */
    runOngoingTask();
}

bool Satelite::FakeTaskSuccess(void)
{
    bool success = (rand() % (100 / FailPercent)) != 0;

    return success;
}

Satelite::TaskTime_t Satelite::FakeTaskTime(void)
{
    TaskTime_t time = (rand() % (MaxTaskTime - MinTaskTime)) + MinTaskTime;

    return time;
}

/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/