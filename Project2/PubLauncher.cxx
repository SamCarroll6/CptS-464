#include "PubThread.h"



int main(int argc, char *argv[])
{
    srand(time(NULL));
    int domainId = 0;
    int sample_count = 0; // infinite loop
    std::ifstream myfile("pub.properties");
    std::string line;
    std::vector<std::string> values;
    int numRoutes;
    int numVehicles;
    int stops, between;
    std::vector<std::string> routes;
    std::vector<ThreadPub> threads; 
    ThreadPub holdval;
    int i = 0;
    /*
        2
        3
        Express1
        Express2
        4
        2
        Bus11
        Bus12
        Bus13
        6
        3
        Bus21
        Bus22
        Bus23

    */

    while(std::getline(myfile,line))
    { 
        std::string data = line;
        std::stringstream linestream(line);
        
        std::string hold;
        std::getline(linestream, data, '='); 

        linestream >> hold;
        values.push_back(hold);
    }
    numRoutes = atoi(values[0].c_str());
    numVehicles = atoi(values[1].c_str());
    for(i = 2; i < numRoutes + 2; i++)
    {
        routes.push_back(values[i]);
    }
    for(int j = 0; j < numRoutes; j++)
    {
        stops = atoi(values[i].c_str());
        i++;
        between = atoi(values[i].c_str());
        i++;
        for(int count = 0; count < numVehicles; count++)
        {
            threads.push_back(ThreadPub(routes[j], values[i], stops, between));
            i++;
        }
    }

    for(int s = 0; s < 2; s++)
    {
        threads[s].start();
    }
    for(int s = 3; s < 5; s++)
    {
        threads[s].start();
    }
    for(int s = 0; s < 2; s++)
    {
        threads[s].join();
    }
    for(int s = 3; s < 5; s++)
    {
        threads[s].join();
    }

    // ThreadPub eleven("Express1", "Bus11", 4, 2);
    // ThreadPub twelve("Express1", "Bus12", 4, 2);
    // ThreadPub thirteen("Express1", "Bus13", 4, 2);

    // ThreadPub one("Express2", "Bus21", 6, 3);
    // ThreadPub two("Express2", "Bus22", 6, 3);
    // ThreadPub three("Express2", "Bus23", 6, 3);

    // if (argc >= 2) {
    //     domainId = atoi(argv[1]);
    // }
    // if (argc >= 3) {
    //     sample_count = atoi(argv[2]);
    // }
    // std::cout << "Launching Publishers...\n";
    // eleven.start();
    // std::cout << "Thread " << eleven.vehicle << " started\n";
    // one.start();
    // std::cout << "Thread " << one.vehicle << " started\n";
    // twelve.start();
    // std::cout << "Thread " << twelve.vehicle << " started\n";
    // two.start();
    // std::cout << "Thread " << two.vehicle << " started\n";
    // thirteen.start();
    // std::cout << "Thread " << thirteen.vehicle << " started\n";
    // three.start();
    // std::cout << "Thread " << three.vehicle << " started\n";
    
    
    
    // eleven.join();
    // one.join();

    // twelve.join();
    // two.join();

    // thirteen.join();
    // three.join();
    // std::thread run;
    // run = std::thread(Position_publisher_main, std::ref(value));
    // run.join(); 
    //Position_publisher_main(value);
    //std::thread eleven(Position_publisher_main);
    //std::thread twelve(Accident_publisher_main);
    // std::thread thirteen();
    // std::thread twentyone();
    // std::thread twentytwo();
    // std::thread twentythree();
    //eleven.join();
    //twelve.join();
    // thirteen.join();
    // twentyone.join();
    // twentytwo.join();
    // twentythree.join();
}