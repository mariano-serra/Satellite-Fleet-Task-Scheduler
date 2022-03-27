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
#include "SocketServer.h"
#include "SocketClient.h"

/* ---------------------------------------------------------------------------*/
/* Defines, Estructuras y Typedef Compartidos 								  */
/* ---------------------------------------------------------------------------*/
typedef uint32_t FrameId_t;


typedef struct FrameTask
{
    FrameId_t frameId;           /* Like a SOF */
    Task::TaskId_t taskId;
    Task::Payoff_t payoff;
    Resources::ResourceAmount_t resourcesAmount;
    Resources::ResourceElement_t resourcesList[256];
    Task::State_t state;
}FrameTask_t;

/*----------------------------------------------------------------------------*/
/* Variables Compartidas                                                      */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Clases y Prototipos de funciones Compartidas 				              */
/*----------------------------------------------------------------------------*/
class FrameLayer
{
public:

    FrameLayer(Socket::SocketType sockeType, UniqueDeviceId_t serverId);
    ~FrameLayer();
    
    void sendFrameTask(FrameTask_t* taskFrame);
    bool receiveFrameTask(FrameTask_t* taskFrame);

    void runnerTask(void);

private:
    Socket::SocketType m_sockeType;
    SocketServer* m_socketServer;
    SocketClient* m_socketClient;
};

/*----------------------------------------------------------------------------*/
/* Fin 																		  */
/*----------------------------------------------------------------------------*/

#endif // FRAME_LAYER_H
