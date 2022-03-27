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
#include "Types.h"
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

/**
 * @brief 		Abstraccion para la asignacion de tareas a los dispositivos.
 * @details
 */
class Task
{
public:
	/** Identificador unico de tarea */
	typedef uint32_t TaskId_t;

	/** Payoff */
	typedef float Payoff_t;

	/** Listas de Tareas */
	typedef std::vector<Task*> TaskList_t;

	/** Listas Ids de Tareas */
	typedef std::vector<Task::TaskId_t> TaskIdList_t;

	/** Estados de tarea */
	typedef enum
	{
		WAITING_TO_BE_EXECUTED,
		IN_EXECUTION,
		EXECUTED,
		FAILURE_DURING_EXECUTION,
	} State_t;

	/**
	 * @brief Contructor
	 * @details Este constructor se utiliza cuando se desea crear una tarea nueva. El identificador unico de tarea se asigna
	 * 			automaticamente, como un numero ascendente.
	 * 			El estado queda asignado automaticamente a WAITING_TO_BE_EXECUTED.
	 *
	 * @param name Nombre de tarea
	 * @param resourcesList Vector de recursos
	 * @param payoff Payoff de tarea
	 */
	Task(std::string name, Resources::ResourcesList_t resourcesList, Payoff_t payoff);

	/**
	 * @brief Contructor
	 * @details Este constructor se utiliza cuando la tarea es recibida como una copia de la tarea original.
	 * 			TODO: Este construcor deberia ser definido como 'protected', y solamente las clases amigas tener la
	 * 			posibilidad de llamarlo.
	 *
	 * @param taskId Identificador unico de tarea
	 * @param name Nombre de tarea
	 * @param resourcesList Vector de recursos
	 * @param payoff Payoff de tarea
	 * @param state Estado
	 */
	Task(Task::TaskId_t taskId, std::string name, Resources::ResourcesList_t resourcesList, Payoff_t payoff, State_t state);

	/**
	 * @brief Destructor
	 * @details
	 */
	~Task();

	/**
	 * @brief Obtiene el nombre de una tarea.
	 * @details
	 * @return Nombre de tarea
	 */
	std::string getName(void);

	/**
	 * @brief Obtiene la lista de recursos no ordenada de la tarea.
	 * @details
	 * @return Vector de recursos
	 */
	Resources::ResourcesList_t getResourcesList(void);

	/**
	 * @brief Obtiene el payoff de una tarea
	 * @details
	 * @return Payoff de tarea
	 */
	Payoff_t getPayoff(void);

	/**
	 * @brief Obtiene el identificador unico de tarea.
	 * @details
	 * @return Id unico de tarea
	 */
	TaskId_t getId(void);

	/**
	 * @brief Obtiene el estado de una tarea.
	 * @details
	 * @return Estado de tarea
	 */
	State_t getState(void);

	/**
	 * @brief Configura el estado de una tarea.
	 * @details
	 *
	 * @param state Estado de tarea
	 */
	void setState(State_t state);

private:

	/**
	 * @brief Generador de id unico de tarea.
	 * @details Numero ascendendiante
	 * @return Nuevo id Unico
	 */
	static TaskId_t getNewId(void);
	static TaskId_t idCount;

	/** Propiedades de Tarea */
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

