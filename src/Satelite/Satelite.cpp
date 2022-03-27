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
        m_ongoingTasks[task] = FakeTaskTime();
        task->setState(Task::IN_EXECUTION);

        /* Reserva los recursos necesarios */
        m_availableResources->substrac(task->getResourcesList());
    }

    return ret;
}

void Satelite::runnerTask(void)
{ 
    /* Get new Task ToDo */
    if (m_appConexionLayer)
    {
        Task* newTask;
        if (m_appConexionLayer->receiveTask(&newTask))
        {
            DEBUG_MSG(">> new Task() = " << newTask << std::endl);
            addTaskToDo(newTask); 
        }
    }

    /* Run Satelite Task List */
    for (TaskMap_t::iterator ongoingTaskIt = m_ongoingTasks.begin(); ongoingTaskIt != m_ongoingTasks.end(); ++ongoingTaskIt)
    {
        Task* task = ongoingTaskIt->first;
        TaskTime_t* time = &(ongoingTaskIt->second);
        (*time) = (*time) - 1;

        if (*time < 0)
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

            /* Borra tarea a la lista de pendientes */
            /* FIXME: ver si la puede borrar dentro del iterador */
            ongoingTaskIt = m_ongoingTasks.erase(ongoingTaskIt);  //sino generar lista de tasks a borrar

            delete(task);
        }
    }
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