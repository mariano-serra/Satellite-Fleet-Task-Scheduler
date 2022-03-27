/* ---------------------------------------------------------------------------*/
/* Includes                                                                   */
/* ---------------------------------------------------------------------------*/
#include "FrameLayer.h"
#include "SharedDeclarations.h"
#include "SocketServer.h"
#include "SocketClient.h"

/* ---------------------------------------------------------------------------*/
/* Debug                                                                      */
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Defines, Estructuras y Typedef                                             */
/* ---------------------------------------------------------------------------*/

/*
 * Por simplificacion ("time constrain"), el protocolo esta pensado para soportar
 * un unico comando (enviar/recibir tarea).
 * TODO: Modoficar el frameBuilde / frameParser, para que soporte multiples comandos y
 * estructuras de datos a transmitir.
 */
static const FrameId_t UniqueTaskFrameId = 0x14F6FE0C; /* Hash */

/* ---------------------------------------------------------------------------*/
/* Declaracion de funciones                                                   */
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Variables externas y privadas                                              */
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Implementacion de clases y funciones                                       */
/* ---------------------------------------------------------------------------*/

FrameLayer::FrameLayer(Socket::SocketType sockeType, UniqueDeviceId_t serverId)
{
    /* Contruyo capa layer inferior (Socket) */
    m_sockeType = sockeType;

    if (m_sockeType == Socket::SERVER)
    {
        m_socketServer = new SocketServer(serverId);
    }
    else if (m_sockeType == Socket::CLIENT)
    {
        m_socketClient = new SocketClient(serverId);
    }
}

FrameLayer::~FrameLayer()
{

}

void FrameLayer::sendFrameTask(FrameTask_t* taskFrame)
{
    taskFrame->frameId = UniqueTaskFrameId;

    /* Reinterpreto estrutura de tarea como buffer para transmitir mediante socket */
    BufferData_t* bufferData = reinterpret_cast<BufferData_t*>(taskFrame);

    /* Envio buffer a socket, Server o Cliente, de acuerdo a lo que corresponda */
    if (m_sockeType == Socket::SERVER)
    {
        m_socketServer->sendData(bufferData, sizeof(FrameTask_t));
    }
    else if (m_sockeType == Socket::CLIENT)
    {
        m_socketClient->sendData(bufferData, sizeof(FrameTask_t));
    }
}

bool FrameLayer::receiveFrameTask(FrameTask_t* taskFrame)
{
    bool ret;

    /* Reintepreto puntero en donde almacenare lo recibido por el socket */
    BufferData_t* bufferData = reinterpret_cast<BufferData_t*>(taskFrame);

    /*
     * Leo del socket un buffer de datos de tamaño determinado sizeof(FrameTask_t).
     * Esto solamente es valido por que el protocolo, ahora, solamente soporta un unico comando.
     */

    if (m_sockeType == Socket::SERVER)
    {
        ret = m_socketServer->receiveData(bufferData, sizeof(FrameTask_t));
    }
    else if (m_sockeType == Socket::CLIENT)
    {
        ret = m_socketClient->receiveData(bufferData, sizeof(FrameTask_t));
    }

    if (ret)
    {
        FrameId_t frameId = taskFrame->frameId;
        ret = (frameId == UniqueTaskFrameId);
    }
    return ret;
}


void FrameLayer::runnerTask(void)
{

}


/*----------------------------------------------------------------------------*/
/* Fin                                                                        */
/*----------------------------------------------------------------------------*/