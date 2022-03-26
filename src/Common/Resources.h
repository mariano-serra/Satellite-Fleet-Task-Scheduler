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

/* FIXME: tambien podria ser un namespace */
class Resources
{
public:

	/*! Identificador de recurso. De 0 - 65535, creo que son suficientes */
	typedef uint8_t ResourceAmount_t;
	typedef uint16_t ResourceElement_t;

	/*! Lista de recursos */
	typedef	std::vector<ResourceElement_t> ResourcesList_t;

	/*! Mapa de recursos (ResourceElement_t, cantidad) */
	typedef std::map<ResourceElement_t, ResourceAmount_t> ResourcesMap_t;

	Resources(ResourcesList_t resourcesList);
	~Resources();

	/*! Calculos auxiliares */
	bool contains(ResourcesList_t resourcesList);
	void substrac(ResourcesList_t resourcesList);
	void add(ResourcesList_t resourcesList);

	ResourcesList_t getResourcesList(void);

private:
	ResourcesMap_t m_resourcesMap;
};

/*----------------------------------------------------------------------------*/
/* Fin 																		  */
/*----------------------------------------------------------------------------*/

#endif // RESOURCES_H
