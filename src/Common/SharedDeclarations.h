/*!
 *  \author Mariano Serra
 *
 *
 *  \brief [Breve descripcion del Modulo]
 */

#ifndef SHARED_DECLARATIONS_H
#define SHARED_DECLARATIONS_H

/* ---------------------------------------------------------------------------*/
/* Includes                                                                   */
/* ---------------------------------------------------------------------------*/
#include "Resources.h"

/* ---------------------------------------------------------------------------*/
/* Defines, Estructuras y Typedef Compartidos                                 */
/* ---------------------------------------------------------------------------*/

/* Identificador unico de Satelites */
/* WorkAround, para poder operar con los operadores ++, sin necesidad de sobrecargalos en un enum */
typedef uint32_t UniqueDeviceId_t;
static const UniqueDeviceId_t GROUND_CONTROL_ID = 0;
static const UniqueDeviceId_t SATELITE_1_ID = 1;
static const UniqueDeviceId_t SATELITE_2_ID = 2;
static const UniqueDeviceId_t NUM_DEVICES_ID = 3;

/* Recursos asociados a cada Satelite */
static const Resources::ResourcesList_t SATELITE_1_RES = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
static const Resources::ResourcesList_t SATELITE_2_RES = {1, 2, 3, 5, 5, 6, 7, 8, 10};


typedef enum
{
    UPDATE_AVAILABLE_RESOURCES,
    ADD_TASK_TODO,
    UPDATE_TASK_STATE,
    /* */
    NUM_COMM_CMDS,
} CommunicationsCmds_t;


/*----------------------------------------------------------------------------*/
/* Variables Compartidas                                                      */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Clases y Prototipos de funciones Compartidas                               */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/

#endif // SHARED_DECLARATIONS_H
