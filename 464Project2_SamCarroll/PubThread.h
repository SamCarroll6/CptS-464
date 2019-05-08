#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include "Position.h"
#include "PositionSupport.h"
#include "Accident.h"
#include "AccidentSupport.h"
#include "ndds/ndds_cpp.h"
#include <time.h>
#include <ctime>
#include <fstream>
#include <sstream>
#include <vector>

class ThreadPub
{
    public:
        std::string   timestamp ;
        std::string   route ;
        std::string   vehicle ;
        int           stopNumber ;
        int           numStops ;
        int           timeBetweenStops ;
        std::string   trafficConditions ;
        int           fillInRatio ;
        int           tbs;

        std::thread   test;

        ThreadPub();

        ThreadPub(std::string r, std::string v, int numberstops, int tbs);

        int start();

        int join();

        int checkAccident();

        std::string checkTraffic();

        int numRiders();

    private:
    
};


extern "C" int Accident_publisher_main(ThreadPub *val);

static int Accident_publisher_shutdown(DDSDomainParticipant *participant);

extern "C" int Position_publisher_main(ThreadPub *val);

/* Delete all entities */
static int Position_publisher_shutdown(DDSDomainParticipant *participant);