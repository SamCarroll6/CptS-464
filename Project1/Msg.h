

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Msg.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef Msg_1287711173_h
#define Msg_1287711173_h

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_cpp_h
#include "ndds/ndds_cpp.h"
#endif
#else
#include "ndds_standalone_type.h"
#endif

static const DDS_Long MSG_LEN= 256;
extern "C" {

    extern const char *MsgTYPENAME;

}

struct MsgSeq;
#ifndef NDDS_STANDALONE_TYPE
class MsgTypeSupport;
class MsgDataWriter;
class MsgDataReader;
#endif

class Msg 
{
  public:
    typedef struct MsgSeq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef MsgTypeSupport TypeSupport;
    typedef MsgDataWriter DataWriter;
    typedef MsgDataReader DataReader;
    #endif

    DDS_Long   count ;
    DDS_Char *   sender ;
    DDS_Char *   message ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

NDDSUSERDllExport DDS_TypeCode* Msg_get_typecode(void); /* Type code */

DDS_SEQUENCE(MsgSeq, Msg);

NDDSUSERDllExport
RTIBool Msg_initialize(
    Msg* self);

NDDSUSERDllExport
RTIBool Msg_initialize_ex(
    Msg* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool Msg_initialize_w_params(
    Msg* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
void Msg_finalize(
    Msg* self);

NDDSUSERDllExport
void Msg_finalize_ex(
    Msg* self,RTIBool deletePointers);

NDDSUSERDllExport
void Msg_finalize_w_params(
    Msg* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void Msg_finalize_optional_members(
    Msg* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool Msg_copy(
    Msg* dst,
    const Msg* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* Msg */

