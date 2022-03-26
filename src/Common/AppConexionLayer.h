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
typedef void (*ReceiveTask_t)(Task& task);

/*----------------------------------------------------------------------------*/
/* Variables Compartidas                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Clases y Prototipos de funciones Compartidas 				              */
/*----------------------------------------------------------------------------*/
class AppConexionLayer
{
public:
    AppConexionLayer(ReceiveTask_t receiveTaskHandler, Socket::SocketType sockeType, UniqueDeviceId_t serverId);
    ~AppConexionLayer();
    
    void sendTask(Task& task);
    void runnerTask(void);
    
private:
    ReceiveTask_t m_receiveTaskHandler;

    FrameLayer* m_frameLayer;
    static void receiveFrameTask(FrameTask_t& task);

};

/*----------------------------------------------------------------------------*/
/* Fin 																		  */
/*----------------------------------------------------------------------------*/

#endif // APP_CONEXION_LAYER_H
