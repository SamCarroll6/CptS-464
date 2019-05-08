#include "PubThread.h"

    ThreadPub::ThreadPub()
    {
        //srand(time(NULL));
    }

    ThreadPub::ThreadPub(std::string r, std::string v, int numberstops, int tbs)
    {
        route = r;
        vehicle = v;
        numStops = numberstops;
        timeBetweenStops = tbs;
        stopNumber = 1;
        trafficConditions = "normal";
        fillInRatio = 0;
        timestamp = "00:00:00";
        //srand(time(NULL));
    }

    int ThreadPub::start()
    {
        test = std::thread(Position_publisher_main, this);
    }

    int ThreadPub::join()
    {
        test.join();
    }

    std::string ThreadPub::checkTraffic()
    {
        int check = rand() % 100;
        if(check < 10)
        {
            trafficConditions = "heavy";
            return "heavy";
        }
        else if(check >=10 && check < 35)
        {
            trafficConditions = "light";
            return "light";
        }
        else
        {
            trafficConditions = "normal";
            return "normal";
        }
    }

    int ThreadPub::numRiders()
    {
        int check = rand() % 100;
        return check;
    }

    int ThreadPub::checkAccident()
    {
        int check;
        
        check = rand() % 10;
        return (check);
        // if(check == 1)
        //     return 1;
        // else
        // {
        //     return 0;
        // }
    }


/* Delete all entities */
static int Accident_publisher_shutdown(
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

    /* RTI Connext provides finalize_instance() method on
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


/* Delete all entities */
static int Position_publisher_shutdown(
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

    /* RTI Connext provides finalize_instance() method on
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

extern "C" int Position_publisher_main(ThreadPub *val)
{
        // The following is the dds code
    DDS_DomainParticipantFactoryQos factoryQoS;
    DDSTheParticipantFactory->get_qos(factoryQoS);
    /* increase max_objects_per_thread as needed.
    * The default is 1024 (512 for 4.4c and below). */
    factoryQoS.resource_limits.max_objects_per_thread = 4096;
    DDSTheParticipantFactory->set_qos(factoryQoS);
    // DDS_DomainParticipantFactoryQos factoryQos = new DDS_DomainParticipantFactoryQos();
    // DDS_DomainParticipantFactory->TheParticipantFactory.get_qos(factoryQos);
    // factoryQos.resource_limits.max_objects_per_thread = 2048;
    // DDS_DomainParticipantFactory->TheParticipantFactory.set_qos(factoryQos);

    DDSDomainParticipant *participant = NULL;
    DDSPublisher *publisher = NULL;
    DDSTopic *topic = NULL;
    DDSDataWriter *writer = NULL;
    PositionDataWriter * Position_writer = NULL;
    Position *instance = NULL;
    DDS_ReturnCode_t retcode;
    DDS_InstanceHandle_t instance_handle = DDS_HANDLE_NIL;
    const char *type_name = NULL;
    int count = 0;  

    /************************************************/

    DDSDomainParticipant *Aparticipant = NULL;
    DDSPublisher *Apublisher = NULL;
    DDSTopic *Atopic = NULL;
    DDSDataWriter *Awriter = NULL;
    AccidentDataWriter * Accident_writer = NULL;
    Accident *Ainstance = NULL;
    DDS_ReturnCode_t Aretcode;
    DDS_InstanceHandle_t Ainstance_handle = DDS_HANDLE_NIL;
    const char *Atype_name = NULL;
    int Acount = 0;  
    DDS_Duration_t Asend_period = {10,0};

    /* To customize participant QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    Aparticipant = DDSTheParticipantFactory->create_participant(
        // Here SAM
        0, DDS_PARTICIPANT_QOS_DEFAULT, 
        NULL /* listener */, DDS_STATUS_MASK_NONE);
    if (Aparticipant == NULL) {
        fprintf(stderr, "create_participant error\n");
        Accident_publisher_shutdown(Aparticipant);
        return -1;
    }

    /* To customize publisher QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    Apublisher = Aparticipant->create_publisher(
        DDS_PUBLISHER_QOS_DEFAULT, NULL /* listener */, DDS_STATUS_MASK_NONE);
    if (Apublisher == NULL) {
        fprintf(stderr, "create_publisher error\n");
        Accident_publisher_shutdown(Aparticipant);
        return -1;
    }

    /* Register type before creating topic */
    Atype_name = AccidentTypeSupport::get_type_name();
    Aretcode = AccidentTypeSupport::register_type(
        Aparticipant, Atype_name);
    if (Aretcode != DDS_RETCODE_OK) {
        fprintf(stderr, "register_type error %d\n", Aretcode);
        Accident_publisher_shutdown(Aparticipant);
        return -1;
    }

    /* To customize topic QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    Atopic = Aparticipant->create_topic(
        "Example Accident",
        Atype_name, DDS_TOPIC_QOS_DEFAULT, NULL /* listener */,
        DDS_STATUS_MASK_NONE);
    if (Atopic == NULL) {
        fprintf(stderr, "create_topic error\n");
        Accident_publisher_shutdown(Aparticipant);
        return -1;
    }

    /* To customize data writer QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    Awriter = Apublisher->create_datawriter(
        Atopic, DDS_DATAWRITER_QOS_DEFAULT, NULL /* listener */,
        DDS_STATUS_MASK_NONE);
    if (Awriter == NULL) {
        fprintf(stderr, "create_datawriter error\n");
        Accident_publisher_shutdown(Aparticipant);
        return -1;
    }
    Accident_writer = AccidentDataWriter::narrow(Awriter);
    if (Accident_writer == NULL) {
        fprintf(stderr, "DataWriter narrow error\n");
        Accident_publisher_shutdown(Aparticipant);
        return -1;
    }

    /* Create data sample for writing */
    Ainstance = AccidentTypeSupport::create_data();
    if (Ainstance == NULL) {
        fprintf(stderr, "AccidentTypeSupport::create_data error\n");
        Accident_publisher_shutdown(Aparticipant);
        return -1;
    }

    /************************************************/

    //DDS_Duration_t send_period = {4,0};
    DDS_Duration_t send_period = {val->timeBetweenStops,0};
    // DDS_UnsignedLong giventime = 4000000000;
    // if(val->timeBetweenStops)
    // {
    //     giventime = (DDS_UnsignedLong)(val->timeBetweenStops * 1000000000);
    //     send_period = {0, giventime};
    // }
    // else
    // {
    //     send_period = {4,0};
    // }
    /* To customize participant QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    participant = DDSTheParticipantFactory->create_participant(
        // Here SAM
        0, DDS_PARTICIPANT_QOS_DEFAULT, 
        NULL /* listener */, DDS_STATUS_MASK_NONE);
    if (participant == NULL) {
        fprintf(stderr, "create_participant error\n");
        Position_publisher_shutdown(participant);
        return -1;
    }

    /* To customize publisher QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    publisher = participant->create_publisher(
        DDS_PUBLISHER_QOS_DEFAULT, NULL /* listener */, DDS_STATUS_MASK_NONE);
    if (publisher == NULL) {
        fprintf(stderr, "create_publisher error\n");
        Position_publisher_shutdown(participant);
        return -1;
    }

    /* Register type before creating topic */
    type_name = PositionTypeSupport::get_type_name();
    retcode = PositionTypeSupport::register_type(
        participant, type_name);
    if (retcode != DDS_RETCODE_OK) {
        fprintf(stderr, "register_type error %d\n", retcode);
        Position_publisher_shutdown(participant);
        return -1;
    }

    /* To customize topic QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    topic = participant->create_topic(
        "Example Position",
        type_name, DDS_TOPIC_QOS_DEFAULT, NULL /* listener */,
        DDS_STATUS_MASK_NONE);
    if (topic == NULL) {
        fprintf(stderr, "create_topic error\n");
        Position_publisher_shutdown(participant);
        return -1;
    }

    /* To customize data writer QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    writer = publisher->create_datawriter(
        topic, DDS_DATAWRITER_QOS_DEFAULT, NULL /* listener */,
        DDS_STATUS_MASK_NONE);
    if (writer == NULL) {
        fprintf(stderr, "create_datawriter error\n");
        Position_publisher_shutdown(participant);
        return -1;
    }
    Position_writer = PositionDataWriter::narrow(writer);
    if (Position_writer == NULL) {
        fprintf(stderr, "DataWriter narrow error\n");
        Position_publisher_shutdown(participant);
        return -1;
    }

    /* Create data sample for writing */
    instance = PositionTypeSupport::create_data();
    if (instance == NULL) {
        fprintf(stderr, "PositionTypeSupport::create_data error\n");
        Position_publisher_shutdown(participant);
        return -1;
    }

    /* For a data type that has a key, if the same instance is going to be
    written multiple times, initialize the key here
    and register the keyed instance prior to writing */
    /*
    instance_handle = Position_writer->register_instance(*instance);
    */
    // Sample Count SAM
    /* Main loop */
    //for (count=0; (sample_count == 0) || (count < sample_count); ++count) {


    int accident;
    int breaker = 0;
    std::string traffic;
    int tbs = val->timeBetweenStops;
    for (count=0; (0 == 0) || (count < 0); ++count) {
        const std::time_t now = std::time(nullptr);
        const std::tm calendar_time = *std::localtime(std::addressof(now));
        int hour = calendar_time.tm_hour, minute = calendar_time.tm_min, sec = calendar_time.tm_sec;
        std::string time1 = "", h = std::to_string(hour), m = std::to_string(minute), s = std::to_string(sec);
        
        if(hour < 10)
        {
            h = "0" + std::to_string(hour);
        }
        if(minute < 10)
        {
            m = "0" + std::to_string(minute);
        }
        if(sec < 10)
        {
            s = "0" + std::to_string(sec);
        }
        time1 = h + ":" + m + ":" + s;
        
        accident = val->checkAccident();
        traffic = val->checkTraffic();
        val->fillInRatio = val->numRiders();
        if(breaker == 3)
        {
            printf("%s has finished it's loops and will now shut down.\n", val->vehicle.c_str());
            break;
        }
        if(traffic == "heavy")
        {
            if(send_period.sec > 1)
                send_period.sec = send_period.sec * 1.50;
            else
            {
                send_period.sec = 2;
            }
        }
        else if(traffic == "light")
        {
            send_period.sec = send_period.sec * .75;
            if(send_period.sec == 0)
                send_period.sec = 1;
        }
        else
        {
           // giventime = (DDS_UnsignedLong)(tbs * 1000000000);
            send_period = {tbs, 0};
        }
        val->timeBetweenStops =send_period.sec;
        if(!accident)
        {
            std::cout << "P3464_SCARROLL: ";
            std::cout << val->vehicle << " published a position message at stop #" << val->stopNumber << " on route " << val->route << " at " << time1 <<"\n"; 
            strcpy(instance->timestamp, (char*)time1.c_str());
            strcpy(instance->route, (char*)val->route.c_str());
            strcpy(instance->vehicle, (char*)val->vehicle.c_str());
            instance->stopNumber = val->stopNumber;
            instance->numStops = val->numStops;
            instance->timeBetweenStops = val->timeBetweenStops;
            strcpy(instance->trafficConditions, (char*)val->trafficConditions.c_str());
            instance->fillInRatio = val->fillInRatio;
            /* Modify the data to be sent here */
            retcode = Position_writer->write(*instance, instance_handle);
            if (retcode != DDS_RETCODE_OK) {
                fprintf(stderr, "write error %d\n", retcode);
            }


            std::cout << val->vehicle << " published an accident message at stop " << val->stopNumber << " on route " << val->route << " at " << time1 << "\n";
            /* Modify the data to be sent here */
            Ainstance->stopNumber = val->stopNumber;
            strcpy(Ainstance->timestamp, (char*)time1.c_str());
            strcpy(Ainstance->route, (char*)val->route.c_str());
            strcpy(Ainstance->vehicle, (char*)val->vehicle.c_str());
            // instance->timestamp = (char*)val->timestamp.c_str();
            // instance->route = (char*)val->route.c_str();
            // instance->vehicle = (char*)val->vehicle.c_str();        
            Aretcode = Accident_writer->write(*Ainstance, Ainstance_handle);
            if (Aretcode != DDS_RETCODE_OK) {
                fprintf(stderr, "write error %d\n", Aretcode);
            }
            NDDSUtility::sleep(send_period);
            NDDSUtility::sleep(Asend_period);
           //Accident_publisher_main(val);
        }
        else
        {
            std::cout << "P3464_SCARROLL: ";
            std::cout << val->vehicle << " published a position message at stop #" << val->stopNumber << " on route " << val->route << " at " << time1 <<"\n"; 
            strcpy(instance->timestamp, (char*)time1.c_str());
            strcpy(instance->route, (char*)val->route.c_str());
            strcpy(instance->vehicle, (char*)val->vehicle.c_str());
            instance->stopNumber = val->stopNumber;
            instance->numStops = val->numStops;
            instance->timeBetweenStops = val->timeBetweenStops;
            strcpy(instance->trafficConditions, (char*)val->trafficConditions.c_str());
            instance->fillInRatio = val->fillInRatio;
            /* Modify the data to be sent here */
            retcode = Position_writer->write(*instance, instance_handle);
            if (retcode != DDS_RETCODE_OK) {
                fprintf(stderr, "write error %d\n", retcode);
            }

            NDDSUtility::sleep(send_period);
            //send_period = {val->timeBetweenStops, 0};
        }

        if(val->stopNumber == val->numStops)
        {
            val->stopNumber = 1;
            breaker++;
        }
        else
        {
            val->stopNumber++;
        }

    }

    /*
    retcode = Position_writer->unregister_instance(
        *instance, instance_handle);
    if (retcode != DDS_RETCODE_OK) {
        fprintf(stderr, "unregister instance error %d\n", retcode);
    }
    */

    /* Delete data sample */
    Aretcode = AccidentTypeSupport::delete_data(Ainstance);
    if (Aretcode != DDS_RETCODE_OK) {
        fprintf(stderr, "AccidentTypeSupport::delete_data error %d\n", Aretcode);
    }

    /* Delete data sample */
    retcode = PositionTypeSupport::delete_data(instance);
    if (retcode != DDS_RETCODE_OK) {
        fprintf(stderr, "PositionTypeSupport::delete_data error %d\n", retcode);
    }


    /* Delete all entities */
    Accident_publisher_shutdown(Aparticipant);
    /* Delete all entities */
    return Position_publisher_shutdown(participant);
}