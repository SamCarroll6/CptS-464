
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <iomanip>
#include "Position.h"
#include "PositionSupport.h"
#include "ndds/ndds_cpp.h"
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

Accident *ahold;

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
            ahold = &data_seq[i];
            // printf("Received data\n");
            // AccidentTypeSupport::print_data(&data_seq[i]);
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

class PositionListener : public DDSDataReaderListener {
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

Position *hold;

void PositionListener::on_data_available(DDSDataReader* reader)
{
    PositionDataReader *Position_reader = NULL;
    PositionSeq data_seq;
    DDS_SampleInfoSeq info_seq;
    DDS_ReturnCode_t retcode;
    int i;

    Position_reader = PositionDataReader::narrow(reader);
    if (Position_reader == NULL) {
        fprintf(stderr, "DataReader narrow error\n");
        return;
    }

    retcode = Position_reader->take(
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
            hold = &data_seq[i];
            // printf("Received data\n");
            // PositionTypeSupport::print_data(&data_seq[i]);
        }
    }

    retcode = Position_reader->return_loan(data_seq, info_seq);
    if (retcode != DDS_RETCODE_OK) {
        fprintf(stderr, "return loan error %d\n", retcode);
    }
}

/* Delete all entities */
static int subscriber_shutdown(
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

extern "C" int subscriber_main(char *route, int start, int end)
{
    DDSDomainParticipant *participant = NULL;
    DDSSubscriber *subscriber = NULL;
    DDSTopic *topic = NULL;
    PositionListener *reader_listener = NULL; 
    DDSDataReader *reader = NULL;
    DDS_ReturnCode_t retcode;
    const char *type_name = NULL;
    int count = 0;
    DDS_Duration_t receive_period = {0,1500000000};
    int status = 0;

    /******************************************/

    DDSDomainParticipant *Aparticipant = NULL;
    DDSSubscriber *Asubscriber = NULL;
    DDSTopic *Atopic = NULL;
    AccidentListener *Areader_listener = NULL; 
    DDSDataReader *Areader = NULL;
    DDS_ReturnCode_t Aretcode;
    const char *Atype_name = NULL;
    int Acount = 0;
    DDS_Duration_t Areceive_period = {4,0};
    int Astatus = 0;

    /* To customize the participant QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    Aparticipant = DDSTheParticipantFactory->create_participant(
        0, DDS_PARTICIPANT_QOS_DEFAULT, 
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

    /******************************************/

    /* To customize the participant QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    // SAM, 0 should be domainid
    participant = DDSTheParticipantFactory->create_participant(
        0, DDS_PARTICIPANT_QOS_DEFAULT, 
        NULL /* listener */, DDS_STATUS_MASK_NONE);
    if (participant == NULL) {
        fprintf(stderr, "create_participant error\n");
        subscriber_shutdown(participant);
        return -1;
    }

    /* To customize the subscriber QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    subscriber = participant->create_subscriber(
        DDS_SUBSCRIBER_QOS_DEFAULT, NULL /* listener */, DDS_STATUS_MASK_NONE);
    if (subscriber == NULL) {
        fprintf(stderr, "create_subscriber error\n");
        subscriber_shutdown(participant);
        return -1;
    }

    /* Register the type before creating the topic */
    type_name = PositionTypeSupport::get_type_name();
    retcode = PositionTypeSupport::register_type(
        participant, type_name);
    if (retcode != DDS_RETCODE_OK) {
        fprintf(stderr, "register_type error %d\n", retcode);
        subscriber_shutdown(participant);
        return -1;
    }

    /* To customize the topic QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    topic = participant->create_topic(
        "Example Position",
        type_name, DDS_TOPIC_QOS_DEFAULT, NULL /* listener */,
        DDS_STATUS_MASK_NONE);
    if (topic == NULL) {
        fprintf(stderr, "create_topic error\n");
        subscriber_shutdown(participant);
        return -1;
    }

    /* Create a data reader listener */
    reader_listener = new PositionListener();

    /* To customize the data reader QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    reader = subscriber->create_datareader(
        topic, DDS_DATAREADER_QOS_DEFAULT, reader_listener,
        DDS_STATUS_MASK_ALL);
    if (reader == NULL) {
        fprintf(stderr, "create_datareader error\n");
        subscriber_shutdown(participant);
        delete reader_listener;
        return -1;
    }
    int remaining;
    char vehicle[15];
    int on = 0;
    int prev = 0;
    int total = 0;
    std::cout << "MessageType" << std::setw(10) << "Route" << std::setw(10) << "Vehicle" << std::setw(10) << "Traffic" << std::setw(10) << "Stop#" << std::setw(10) << "#Stops" << std::setw(20) << "TimeBetweenStops" << std::setw(10) << "Fill\%" << std::setw(15) << "Timestamp" << std::setw(10) << "\n"; 
    /* Main loop */
    for (count=0; (0 == 0) || (count < 0); ++count) {
        // PositionTypeSupport::print_data(hold);
        // if(hold)
        // {
        //     printf("%d  %d\n", end, hold->numStops);
        // }
        if(ahold)
        {
            std::cout << "Accident" << std::setw(10) << ahold->route << std::setw(10) << ahold->vehicle << std::setw(10) << "" << std::setw(10) << ahold->stopNumber << std::setw(10) << "" << std::setw(20) << "" << std::setw(10) << "" << std::setw(15) << ahold->timestamp << std::setw(10) << "\n"; 
            ahold = NULL;
        }
        //NDDSUtility::sleep(receive_period);
        if(hold)
        {
            std::cout << "Position" << std::setw(10) << hold->route << std::setw(10) << hold->vehicle << std::setw(10) << hold->trafficConditions << std::setw(10) << hold->stopNumber << std::setw(10) << hold->numStops << std::setw(20) << hold->timeBetweenStops << std::setw(10) << hold->fillInRatio << std::setw(15) << hold->timestamp << std::setw(10) << "\n"; 
            hold = NULL;
        }
    }

    /* Delete all entities */
    status = subscriber_shutdown(participant);
    delete reader_listener;

    return status;
}

int main(int argc, char *argv[])
{
    int domainId = 0;
    int sample_count = 0; /* infinite loop */
    char *route = "Express1";
    int start = 2;
    int end = 1;

    if (argc >= 4) {
        route = argv[1];
        start = atoi(argv[2]);
        end = atoi(argv[3]);
    }
    printf("Waiting for the bus...\n");
    /* Uncomment this to turn on additional logging
    NDDSConfigLogger::get_instance()->
    set_verbosity_by_category(NDDS_CONFIG_LOG_CATEGORY_API, 
    NDDS_CONFIG_LOG_VERBOSITY_STATUS_ALL);
    */

    return subscriber_main(route, start, end);
}

