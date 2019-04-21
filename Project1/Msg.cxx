

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Msg.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_cpp_h
#include "ndds/ndds_cpp.h"
#endif
#ifndef dds_c_log_impl_h              
#include "dds_c/dds_c_log_impl.h"                                
#endif        

#ifndef cdr_type_h
#include "cdr/cdr_type.h"
#endif    

#ifndef osapi_heap_h
#include "osapi/osapi_heap.h" 
#endif
#else
#include "ndds_standalone_type.h"
#endif

#include "Msg.h"

#include <new>

/* ========================================================================= */
const char *MsgTYPENAME = "Msg";

DDS_TypeCode* Msg_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode Msg_g_tc_sender_string = DDS_INITIALIZE_STRING_TYPECODE(((MSG_LEN)));
    static DDS_TypeCode Msg_g_tc_message_string = DDS_INITIALIZE_STRING_TYPECODE(((MSG_LEN)));
    static DDS_TypeCode_Member Msg_g_tc_members[3]=
    {

        {
            (char *)"count",/* Member name */
            {
                0,/* Representation ID */          
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL/* Ignored */
        }, 
        {
            (char *)"sender",/* Member name */
            {
                1,/* Representation ID */          
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL/* Ignored */
        }, 
        {
            (char *)"message",/* Member name */
            {
                2,/* Representation ID */          
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL/* Ignored */
        }
    };

    static DDS_TypeCode Msg_g_tc =
    {{
            DDS_TK_STRUCT,/* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"Msg", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            3, /* Number of members */
            Msg_g_tc_members, /* Members */
            DDS_VM_NONE  /* Ignored */         
        }}; /* Type code for Msg*/

    if (is_initialized) {
        return &Msg_g_tc;
    }

    Msg_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;

    Msg_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&Msg_g_tc_sender_string;

    Msg_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)&Msg_g_tc_message_string;

    is_initialized = RTI_TRUE;

    return &Msg_g_tc;
}

RTIBool Msg_initialize(
    Msg* sample) {
    return Msg_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool Msg_initialize_ex(
    Msg* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return Msg_initialize_w_params(
        sample,&allocParams);

}

RTIBool Msg_initialize_w_params(
    Msg* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    if (!RTICdrType_initLong(&sample->count)) {
        return RTI_FALSE;
    }

    if (allocParams->allocate_memory){
        sample->sender= DDS_String_alloc (((MSG_LEN)));
        if (sample->sender == NULL) {
            return RTI_FALSE;
        }

    } else {
        if (sample->sender!= NULL) { 
            sample->sender[0] = '\0';
        }
    }

    if (allocParams->allocate_memory){
        sample->message= DDS_String_alloc (((MSG_LEN)));
        if (sample->message == NULL) {
            return RTI_FALSE;
        }

    } else {
        if (sample->message!= NULL) { 
            sample->message[0] = '\0';
        }
    }

    return RTI_TRUE;
}

void Msg_finalize(
    Msg* sample)
{

    Msg_finalize_ex(sample,RTI_TRUE);
}

void Msg_finalize_ex(
    Msg* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    Msg_finalize_w_params(
        sample,&deallocParams);
}

void Msg_finalize_w_params(
    Msg* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if (sample->sender != NULL) {
        DDS_String_free(sample->sender);
        sample->sender=NULL;

    }
    if (sample->message != NULL) {
        DDS_String_free(sample->message);
        sample->message=NULL;

    }
}

void Msg_finalize_optional_members(
    Msg* sample, RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParamsTmp =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
    struct DDS_TypeDeallocationParams_t * deallocParams =
    &deallocParamsTmp;

    if (sample==NULL) {
        return;
    } 
    if (deallocParams) {} /* To avoid warnings */

    deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
    deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

}

RTIBool Msg_copy(
    Msg* dst,
    const Msg* src)
{
    try {

        if (dst == NULL || src == NULL) {
            return RTI_FALSE;
        }

        if (!RTICdrType_copyLong (
            &dst->count, &src->count)) { 
            return RTI_FALSE;
        }
        if (!RTICdrType_copyStringEx (
            &dst->sender, src->sender, 
            ((MSG_LEN)) + 1, RTI_FALSE)){
            return RTI_FALSE;
        }
        if (!RTICdrType_copyStringEx (
            &dst->message, src->message, 
            ((MSG_LEN)) + 1, RTI_FALSE)){
            return RTI_FALSE;
        }

        return RTI_TRUE;

    } catch (std::bad_alloc&) {
        return RTI_FALSE;
    }
}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'Msg' sequence class.
*/
#define T Msg
#define TSeq MsgSeq

#define T_initialize_w_params Msg_initialize_w_params

#define T_finalize_w_params   Msg_finalize_w_params
#define T_copy       Msg_copy

#ifndef NDDS_STANDALONE_TYPE
#include "dds_c/generic/dds_c_sequence_TSeq.gen"
#include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
#else
#include "dds_c_sequence_TSeq.gen"
#include "dds_cpp_sequence_TSeq.gen"
#endif

#undef T_copy
#undef T_finalize_w_params

#undef T_initialize_w_params

#undef TSeq
#undef T

