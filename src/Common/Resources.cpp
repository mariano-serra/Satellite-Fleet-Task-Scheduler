/* ---------------------------------------------------------------------------*/
/* Includes                                                                   */
/* ---------------------------------------------------------------------------*/
#include "Resources.h"

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

Resources::Resources(ResourcesList_t resourcesList)
{
    /* Creo mapa en funcion de lista de elementos */
    m_resourcesMap.clear();
    for (ResourcesList_t::iterator it = resourcesList.begin(); it != resourcesList.end(); ++it)
    {
        ResourceElement_t resourceElement = *it;

        /* Populo mapa */
        if (m_resourcesMap.find(resourceElement) != m_resourcesMap.end())
        {
            m_resourcesMap[resourceElement]++;
        }
        else
        {
            m_resourcesMap[resourceElement] = 1;
        }
    }
}

Resources::~Resources()
{
    
}

bool Resources::contains(ResourcesList_t resourcesList)
{
    bool ret = true;

    ResourcesMap_t auxResourcesMap = m_resourcesMap;
    
    for (ResourcesList_t::iterator it = resourcesList.begin(); (it != resourcesList.end()) && (ret == true); ++it)
    {
        ResourceElement_t resourceElement = *it;

        if (auxResourcesMap.find(resourceElement) != auxResourcesMap.end())
        {
            auxResourcesMap[resourceElement]--;
            if (auxResourcesMap[resourceElement] < 0)
            {
                ret = false;       
            }   
        }
        else
        {
            ret = false;
        }
    }

    return ret;
}

void Resources::substrac(ResourcesList_t resourcesList)
{
    for (ResourcesList_t::iterator it = resourcesList.begin(); it != resourcesList.end(); ++it)
    {
        ResourceElement_t resourceElement = *it;

        /* Supongo que la validacion ya se hiso mediante el metodo 'contains' */
        m_resourcesMap[resourceElement]--;
    }
}

void Resources::add(ResourcesList_t resourcesList)
{
    for (ResourcesList_t::iterator it = resourcesList.begin(); it != resourcesList.end(); ++it)
    {
        ResourceElement_t resourceElement = *it;

        /* Supongo que la validacion ya se hiso mediante el metodo 'contains' */
        m_resourcesMap[resourceElement]++;
    }
}

Resources::ResourcesList_t Resources::getResourcesList(void)
{
    ResourcesList_t resourcesList;

    for (ResourcesMap_t::iterator it = m_resourcesMap.begin(); it != m_resourcesMap.end(); ++it)
    {
        ResourceElement_t resourceElement = it->first;  /* Key */
        ResourceAmount_t resourceAmount = it->second;   /* Value */

        for (uint16_t i = 0; i < resourceAmount; ++i)
        {
            resourcesList.push_back(resourceElement);
        }
    }

    return resourcesList;
}

/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/





