#include "parser.h"

Parser::Parser()
{
    size = (int)MSG_LEN;
    lastSendID = NULL;
}

/* Protocol
 * |sop|set/get and ID|SubID|data|data|data|data|crc|
 */
int Parser::parse(QByteArray data, int msglength){

  //qDebug() << "parser recieved : " << data  << "With length: " <<  length << endl;

    if(msglength < size)
    {
        qDebug() << "Length of recieved message is not correct: Length: " << msglength << endl;
        return -1;
    }
    //Copy data from QByteArray to msg
    memcpy(&msg, data.data(), msglength);

    if(msg.sot != SOP){

        qDebug() << "Wrong SOP: Byte was: " << msg.sot << endl;
        return -1;
    }


    // Calculate Checksum from recvData
    unsigned char recvChk = CalcCRC((unsigned char*) &msg);

    if(recvChk == msg.crc){

        if((msg.cmd&ASYNC_MSG_BIT)){ // Async message recieved
            if(asyncMsgRecv()){
                return 1;
            }

        } else if((msg.cmd&SYNC_MSG_BIT)){ // Sync Message Recieved

            if(syncMsgRecv()){
                return 1;
            }

        } else
        {
            qDebug() << "Message CMD was not Async or Sync: " << msg.cmd << endl;
        }

    } else
    {
            qDebug() << "Wrong Checksum. Recieved Chk: " << msg.crc << "Calculated Chk from recieved message:" << recvChk << endl;
    }
    return -1;
}

unsigned char Parser::CalcCRC(unsigned char* data)
{
    unsigned char crc = 0;
    for(int i = 0; i < this->size-1; i++){
        crc ^= *data++;
    }
    return crc;
}

int Parser::asyncMsgRecv(){

   switch(msg.id){

       case ID_STATUS:
            if(msg.d.c[3] == STS_STARTUP){
                emit sReboot();
                return 1;
            }
            return -1;
       break;

      default:
       float value;
       value = *((float*)&msg.d);
       emit sAsyncMsg((unsigned int)msg.id,value);
       //qDebug() << msg[3] << " " << msg[4] << " " << msg[5] << " " << msg[6] << endl;
       //qDebug() << "Recieved an asyncMsg " << "with value: " << value << endl;
       return 1;

   }

}


int Parser::syncMsgRecv(){

    if(lastSendID == msg.id){
        float value;
        value = *((float*)&msg.d);
        qDebug() << "SyncMSG with correct ID was recieved" << endl;
        emit sSyncMsg((unsigned int)msg.id,value);
        return 1;
    } else
    {
       qDebug() << "SyncMSG with Incorrect ID was recieved ID:" << endl;
       return -1;
    }
}

void Parser::setLastSendID(unsigned char ID){
    lastSendID = ID;
}

