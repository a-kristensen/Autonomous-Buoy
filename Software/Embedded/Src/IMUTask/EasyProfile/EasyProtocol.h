/**
  * @brief   An easy-to-use protocol to deal with small amount of transfered data.
  *
  * @version v1.7 -  Feb 21, 2016 - Accept all package with length <= MAX_PAYLOAD_SIZE_.
  * @version v2.1 -  Feb 23, 2016 - Make EasyProtocol independent from any kind of structure.
  *
  * @version --------- Branch C Language -----------
  * @version v2.2 -  Sep 02, 2016 - Port to C language. Search keyword "[v2.2]" for bug fix relative to v2.1
  *
  * @attention
  *          *****        DO NOT CHANGE THIS FILE           *****
  *          ***** Automatically Generated by IMU Assistant *****
  * @attention
  * <h2><center>&copy; COPYRIGHT(c) 2017 SYD Dynamics ApS</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  */
#ifndef EASYPROTOCOL_C_LANGUAGE_H
#define EASYPROTOCOL_C_LANGUAGE_H

#include <stdlib.h>   // malloc()
#include "EasyQueue.h"
#include "BasicTypes.h"

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC extern
#endif

//------------------------------------------------------------------------------
// Configure Parameters 1/2
    //#define EP_TURN_ON_STATISTICS_
    //#define EP_TURN_ON_DEBUG_
// Configure Parameters 1/2
//------------------------------------------------------------------------------

#ifdef EP_TURN_ON_DEBUG_
    #include <QDebug>
    #include <QString>
    #include <QObject>
#endif

EXTERNC void  EasyProtocol_Construct(void);
EXTERNC void  EasyProtocol_Destruct(void);
EXTERNC int   EasyProtocol_Init(int iDataMaxSize, int oDataMaxSize);

EXTERNC int   EasyProtocol_CreateOutputPackage(
                  char* payloadData,  int payloadSize,
                  char** packageData, int* packageSize);

EXTERNC int   EasyProtocol_AssembleInputPackage(
                  char* rawData,      int rawDataLenth,
                  char **payloadData, int *payloadSize);

EXTERNC void  EasyProtocol_SetChecksumOption(char option);
EXTERNC int   EasyProtocol_GetInDataMaxSize(void);
EXTERNC int   EasyProtocol_GetOutDataMaxSize(void);
EXTERNC int   EasyProtocol_GetRoundUp(void);

#ifdef EP_TURN_ON_DEBUG_
EXTERNC void  EasyProtocol_DebugPrint(QString title, char* data, int length);
#endif

#ifdef EP_TURN_ON_STATISTICS_
EXTERNC int   EasyProtocol_TotalBytesOfMemoryUsed();
EXTERNC int   EasyProtocol_GetStatistic_Recv_Byte_Total();
EXTERNC float EasyProtocol_GetStatistic_Recv_Byte_BadHeadRate();
EXTERNC int   EasyProtocol_GetStatistic_Recv_Pkg_Total();
EXTERNC float EasyProtocol_GetStatistic_Recv_Pkg_OmitRate();
EXTERNC float EasyProtocol_GetStatistic_Recv_Pkg_BadRate();
EXTERNC float EasyProtocol_GetStatistic_Recv_Pkg_GoodRate();
EXTERNC int   EasyProtocol_GetStatistic_Send_Pkg_Total();
#endif


#endif // EASYPROTOCOL_C_LANGUAGE_H