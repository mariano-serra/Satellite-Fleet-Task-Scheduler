/*!
 *  \author Mariano Serra
 *
 *
 *  \brief [Breve descripcion del Modulo]
 */

#ifndef TASK_H
#define TASK_H

/* ---------------------------------------------------------------------------*/
/* Includes 																  */
/* ---------------------------------------------------------------------------*/
#include <Types.h>
#include <string>
#include "Resources.h"

/* ---------------------------------------------------------------------------*/
/* Defines, Estructuras y Typedef Compartidos 								  */
/* ---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Variables Compartidas                                                      */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Clases y Prototipos de funciones Compartidas 				              */
/*----------------------------------------------------------------------------*/

/* FIXME: refactorizar, dividiendo entre ID y tarea */
class Task
{
public:
	/*! Identificador unico de tarea */
	typedef uint32_t TaskId_t;
	typedef float Payoff_t;

	typedef enum 
    {
		WAITING_TO_BE_EXECUTED,
		IN_EXECUTION,
		EXECUTED,
		FAILURE_DURING_EXECUTION,    	
    }State_t;

    Task(Task::TaskId_t taskId, std::string name, Resources::ResourcesList_t resourcesList, Payoff_t payoff);
	Task(std::string name, Resources::ResourcesList_t resourcesList, Payoff_t payoff);
	~Task();

	std::string getName(void);
	Resources::ResourcesList_t getResourcesList(void);
	Payoff_t getPayoff(void);
	TaskId_t getId(void);

	State_t getState(void);
	void setState(State_t state);

private:
	static TaskId_t idCount;
	static TaskId_t getNewId(void);

	std::string m_name;
	Resources::ResourcesList_t m_resourcesList;
	Payoff_t m_payoff;
	TaskId_t m_id;
	State_t m_state;
};

/*----------------------------------------------------------------------------*/
/* Fin 																		  */
/*----------------------------------------------------------------------------*/

#endif // TASK_H

