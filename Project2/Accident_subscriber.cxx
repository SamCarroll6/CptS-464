
/* Accident_subscriber.cxx

A subscription example

This file is derived from code automatically generated by the rtiddsgen 
command:

rtiddsgen -language C++ -example <arch> Accident.idl

Example subscription of type Accident automatically generated by 
'rtiddsgen'. To test them follow these steps:

(1) Compile this file and the example publication.

(2) Start the subscription with the command
objs/<arch>/Accident_subscriber <domain_id> <sample_count>

(3) Start the publication with the command
objs/<arch>/Accident_publisher <domain_id> <sample_count>

(4) [Optional] Specify the list of discovery initial peers and 
multicast receive addresses via an environment variable or a file 
(in the current working directory) called NDDS_DISCOVERY_PEERS. 

You can run any number of publishers and subscribers programs, and can 
add and remove them dynamically from the domain.

Example:

To run the example application on domain <domain_id>:

On Unix: 

objs/<arch>/Accident_publisher <domain_id> 
objs/<arch>/Accident_subscriber <domain_id> 

On Windows:

objs\<arch>\Accident_publisher <domain_id>  
objs\<arch>\Accident_subscriber <domain_id>   

*/

#include <stdio.h>
#include <stdlib.h>

#include "Accident.h"
#include "AccidentSupport.h"
#include "ndds/ndds_cpp.h"

class AccidentListener : public DDSDataReaderListener {
  public:
    virtual void on_requested_deadline_missed(
        DDSDataReader* /*reader*/,
        const DDS_RequestedDeadlineMissedStatus& /*status*/) {}

    virtual void on_requested_incompatible_qos(
        DDSDataReader* /*reader*/,
        const DDS_RequestedIncompatibleQosStatus& /*status*/) {}

    virtual void on_sample_rejected(
        DDSDataReader* /*reader*/,
        const DDS_SampleRejectedStatus& /*status*/) {}

    virtual void on_liveliness_changed(
        DDSDataReader* /*reader*/,
        const DDS_LivelinessChangedStatus& /*status*/) {}

    virtual void on_sample_lost(
        DDSDataReader* /*reader*/,
        const DDS_SampleLostStatus& /*status*/) {}

    virtual void on_subscription_matched(
        DDSDataReader* /*reader*/,
        const DDS_SubscriptionMatchedStatus& /*status*/) {}

    virtual void on_data_available(DDSDataReader* reader);
};

void AccidentListener::on_data_available(DDSDataReader* reader)
{
    AccidentDataReader *Accident_reader = NULL;
    AccidentSeq data_seq;
    DDS_SampleInfoSeq info_seq;
    DDS_ReturnCode_t retcode;
    int i;

    Accident_reader = AccidentDataReader::narrow(reader);
    if (Accident_reader == NULL) {
        fprintf(stderr, "DataReader narrow error\n");
        return;
    }

    retcode = Accident_reader->take(
        data_seq, info_seq, DDS_LENGTH_UNLIMITED,
        DDS_ANY_SAMPLE_STATE, DDS_ANY_VIEW_STATE, DDS_ANY_INSTANCE_STATE);

    if (retcode == DDS_RETCODE_NO_DATA) {
        return;
    } else if (retcode != DDS_RETCODE_OK) {
        fprintf(stderr, "take error %d\n", retcode);
        return;
    }

    for (i = 0; i < data_seq.length(); ++i) {
        if (info_seq[i].valid_data) {
            printf("Received data\n");
            AccidentTypeSupport::print_data(&data_seq[i]);
        }
    }

    retcode = Accident_reader->return_loan(data_seq, info_seq);
    if (retcode != DDS_RETCODE_OK) {
        fprintf(stderr, "return loan error %d\n", retcode);
    }
}

/* Delete all entities */
static int Accident_subscriber_shutdown(
    DDSDomainParticipant *participant)
{
    DDS_ReturnCode_t retcode;
    int status = 0;

    if (participant != NULL) {
        retcode = participant->delete_contained_entities();
        if (retcode != DDS_RETCODE_OK) {
            fprintf(stderr, "delete_contained_entities error %d\n", retcode);
            status = -1;
        }

        retcode = DDSTheParticipantFactory->delete_participant(participant);
        if (retcode != DDS_RETCODE_OK) {
            fprintf(stderr, "delete_participant error %d\n", retcode);
            status = -1;
        }
    }

    /* RTI Connext provides the finalize_instance() method on
    domain participant factory for people who want to release memory used
    by the participant factory. Uncomment the following block of code for
    clean destruction of the singleton. */
    /*

    retcode = DDSDomainParticipantFactory::finalize_instance();
    if (retcode != DDS_RETCODE_OK) {
        fprintf(stderr, "finalize_instance error %d\n", retcode);
        status = -1;
    }
    */
    return status;
}

extern "C" int subscriber_main(int domainId, int sample_count)
{
    DDSDomainParticipant *Aparticipant = NULL;
    DDSSubscriber *Asubscriber = NULL;
    DDSTopic *Atopic = NULL;
    AccidentListener *Areader_listener = NULL; 
    DDSDataReader *Areader = NULL;
    DDS_ReturnCode_t Aretcode;
    const char *Atype_name = NULL;
    int Acount = 0;
    DDS_Duration_t Areceive_period = {1,0};
    int Astatus = 0;

    /* To customize the participant QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    Aparticipant = DDSTheParticipantFactory->create_participant(
        domainId, DDS_PARTICIPANT_QOS_DEFAULT, 
        NULL /* listener */, DDS_STATUS_MASK_NONE);
    if (Aparticipant == NULL) {
        fprintf(stderr, "create_participant error\n");
        Accident_subscriber_shutdown(Aparticipant);
        return -1;
    }

    /* To customize the subscriber QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    Asubscriber = Aparticipant->create_subscriber(
        DDS_SUBSCRIBER_QOS_DEFAULT, NULL /* listener */, DDS_STATUS_MASK_NONE);
    if (Asubscriber == NULL) {
        fprintf(stderr, "create_subscriber error\n");
        Accident_subscriber_shutdown(Aparticipant);
        return -1;
    }

    /* Register the type before creating the topic */
    Atype_name = AccidentTypeSupport::get_type_name();
    Aretcode = AccidentTypeSupport::register_type(
        Aparticipant, Atype_name);
    if (Aretcode != DDS_RETCODE_OK) {
        fprintf(stderr, "register_type error %d\n", Aretcode);
        Accident_subscriber_shutdown(Aparticipant);
        return -1;
    }

    /* To customize the topic QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    Atopic = Aparticipant->create_topic(
        "Example Accident",
        Atype_name, DDS_TOPIC_QOS_DEFAULT, NULL /* listener */,
        DDS_STATUS_MASK_NONE);
    if (Atopic == NULL) {
        fprintf(stderr, "create_topic error\n");
        Accident_subscriber_shutdown(Aparticipant);
        return -1;
    }

    /* Create a data reader listener */
    Areader_listener = new AccidentListener();

    /* To customize the data reader QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    Areader = Asubscriber->create_datareader(
        Atopic, DDS_DATAREADER_QOS_DEFAULT, Areader_listener,
        DDS_STATUS_MASK_ALL);
    if (Areader == NULL) {
        fprintf(stderr, "create_datareader error\n");
        Accident_subscriber_shutdown(Aparticipant);
        delete Areader_listener;
        return -1;
    }

    /* Main loop */
    for (Acount=0; (sample_count == 0) || (Acount < sample_count); ++Acount) {

        printf("Accident subscriber sleeping for %d sec...\n",
        Areceive_period.sec);

        NDDSUtility::sleep(Areceive_period);
    }

    /* Delete all entities */
    Astatus = Accident_subscriber_shutdown(Aparticipant);
    delete Areader_listener;

    return Astatus;
}

int main(int argc, char *argv[])
{
    int domainId = 0;
    int sample_count = 0; /* infinite loop */

    if (argc >= 2) {
        domainId = atoi(argv[1]);
    }
    if (argc >= 3) {
        sample_count = atoi(argv[2]);
    }

    /* Uncomment this to turn on additional logging
    NDDSConfigLogger::get_instance()->
    set_verbosity_by_category(NDDS_CONFIG_LOG_CATEGORY_API, 
    NDDS_CONFIG_LOG_VERBOSITY_STATUS_ALL);
    */

    return subscriber_main(domainId, sample_count);
}

