/*!
 *  \author Mariano Serra
 *
 *
 *  \brief [Breve descripcion del Modulo]
 */

#ifndef RESOURCES_H
#define RESOURCES_H

/* ---------------------------------------------------------------------------*/
/* Includes 																  */
/* ---------------------------------------------------------------------------*/
#include "Types.h"
#include <vector>
#include <map>

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
 * @brief 		Abstraccion para facilitar el manejo de recursos, tanto en tareas como en target (devices).
 * @details 	Genera un mapa de recursos, donde la key es el recurso y el valor la cantidad disponibles de dichos elementos.
 * 				Esto permite facilmente asignar, desasignar o validar recursos de una tarea respecto a un target o viceversa.
 */
class Resources
{
public:
	/** Cantidad de elementos del mismo recurso (0 a 255) */
	typedef uint8_t ResourceAmount_t;

	/** Identificador de recurso (0 a 65535) */
	typedef uint16_t ResourceElement_t;

	/** Lista de recursos */
	typedef	std::vector<ResourceElement_t> ResourcesList_t;

	/**
	 * @brief Contructor
	 * @details
	 *
	 * @param resourcesList Vector de recursos. Los recursos pueden no estar en orden, o repetirse cuantas veces se quiera.
	 */
	Resources(ResourcesList_t resourcesList);

	/**
	 * @brief Destructor
	 * @details
	 */
	~Resources();

	/**
	 * @brief Valida si una lista de recursos no ordenada, esta contenida en un objeto recurso determinado.
	 * @details
	 * 
	 * @param resourcesList Vector de recursos
	 * @return retorna true, si el recurso contiene la lista de recursos.
	 */
	bool contains(ResourcesList_t resourcesList);

	/**
	 * @brief Quita una lista de recursos a un objeto recurso determinado.
	 * @details
	 * 
	 * @param resourcesList Vector de recursos
	 */
	void substrac(ResourcesList_t resourcesList);

	/**
	 * @brief Agrega una lista de recursos a un objeto recurso determinado.
	 * @details
	 * 
	 * @param resourcesList Vector de recursos
	 */
	void add(ResourcesList_t resourcesList);

	/**
	 * @brief Obtiene la lista de recursos ordenada actual de un objeto recurso determinado.
	 * @details
	 * 
	 * @param resourcesList Vector de recursos
	 */
	ResourcesList_t getResourcesList(void);

private:
	/*! Mapa de recursos (ResourceElement_t, cantidad) */
	typedef std::map<ResourceElement_t, ResourceAmount_t> ResourcesMap_t;
	ResourcesMap_t m_resourcesMap;
};

/*----------------------------------------------------------------------------*/
/* Fin 																		  */
/*----------------------------------------------------------------------------*/

#endif // RESOURCES_H
