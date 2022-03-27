/*!
 *  \author Mariano Serra
 *
 *
 *  \brief [Breve descripcion del Modulo]
 */

#ifndef APP_CONEXION_LAYER_H
#define APP_CONEXION_LAYER_H

/* ---------------------------------------------------------------------------*/
/* Includes 																  */
/* ---------------------------------------------------------------------------*/
#include "FrameLayer.h"

/* ---------------------------------------------------------------------------*/
/* Defines, Estructuras y Typedef Compartidos 								  */
/* ---------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Variables Compartidas                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Clases y Prototipos de funciones Compartidas 				              */
/*----------------------------------------------------------------------------*/
class AppConexionLayer
{
public:
    AppConexionLayer(Socket::SocketType sockeType, UniqueDeviceId_t serverId);
    ~AppConexionLayer();
    
    void sendTask(Task* task);
    bool receiveTask(Task** task);

    void runnerTask(void);
    
private:
    FrameLayer* m_frameLayer;
};

/*----------------------------------------------------------------------------*/
/* Fin 																		  */
/*----------------------------------------------------------------------------*/

#endif // APP_CONEXION_LAYER_H
