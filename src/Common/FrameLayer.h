/*!
 *  \author Mariano Serra
 *
 *
 *  \brief [Breve descripcion del Modulo]
 */

#ifndef FRAME_LAYER_H
#define FRAME_LAYER_H

/* ---------------------------------------------------------------------------*/
/* Includes 																  */
/* ---------------------------------------------------------------------------*/
#include "Task.h"
#include "Socket.h"

/* ---------------------------------------------------------------------------*/
/* Defines, Estructuras y Typedef Compartidos 								  */
/* ---------------------------------------------------------------------------*/
typedef struct FrameTask
{
    Task::TaskId_t id;
    /* Por simplificacion, no trasmito, el nombre */
    Resources::ResourceAmount_t resourcesAmount;
    Resources::ResourceElement_t resourcesList[256];
    Task::State_t state;
}FrameTask_t;

typedef void (*ReceiveFrameTask_t)(FrameTask_t& frameTask);

/*----------------------------------------------------------------------------*/
/* Variables Compartidas                                                      */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Clases y Prototipos de funciones Compartidas 				              */
/*----------------------------------------------------------------------------*/
class FrameLayer
{
public:

    FrameLayer(ReceiveFrameTask_t receiveFrameTaskHandler, Socket::SocketType sockeType, UniqueDeviceId_t serverId);
    ~FrameLayer();
    
    void sendFrameTask(FrameTask_t& taskFrame);

private:
    ReceiveFrameTask_t m_receiveFrameTaskHandler;

    Socket* m_socket;
    static void processReciveData(BufferData_t data);
};

/*----------------------------------------------------------------------------*/
/* Fin 																		  */
/*----------------------------------------------------------------------------*/

#endif // FRAME_LAYER_H
