# CptS-464
Washington State University Distributed Systems Course

This Repository contains files from the Distributed Systems Course at Washington State University. These projects are all done using rti liscensed software. The command to run these is "make -f [Choose makefile]" but will only work if you have already set up rti software.

# Project 1
A simple introduction for the class. All it does is have a single publisher and subscriber, the publisher writes a count and a fruit name and the subscriber displays both again. It only has ten fruit names and cycles through them in the same order every publish loop.

# Project 2
Deals with threaded publishers (ThreadPub). Each publisher is capable of two different publisher calls, position or accident. Accident calls have a 1/10 chance of occuring and position calls occur each loop. We call multiple threads of ThreadPub, each thread will have a different vehicle name and one of two possible routes. It has two types of subscribers. The Operator subscriber will receive and print any information provided by all of the publisher threads and display it. The other subscriber is a passenger subscriber, this will instead have start and end points, as well as a route, it will get on to whichever bus gets to the passengers start spot first that is also on their route. From there it receives any information published by the vehicle it is riding until it arrives at it's destination, at which point it gets off the bus and ends.
