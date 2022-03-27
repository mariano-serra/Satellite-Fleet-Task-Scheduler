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

/**
 * Identificador unico de dispositivos. 
 * FIXME. se utiliza el tipo de datos 'uint32_t' en vez de enum, 
 * para poder operar con los operadores ++, sin necesidad de definirlos.
 */
typedef uint32_t UniqueDeviceId_t;
static const UniqueDeviceId_t GROUND_CONTROL_ID = 0;
static const UniqueDeviceId_t SATELITE_1_ID = 1;
static const UniqueDeviceId_t SATELITE_2_ID = 2;
static const UniqueDeviceId_t NUM_DEVICES_ID = 3;

/** 
 * Recursos disponibles a cada Satelite (SATELITE_1_ID y SATELITE_2_ID)
 */
static const Resources::ResourcesList_t SATELITE_1_RES = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
static const Resources::ResourcesList_t SATELITE_2_RES = {1, 2, 3, 5, 5, 6, 7, 8, 10};

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
