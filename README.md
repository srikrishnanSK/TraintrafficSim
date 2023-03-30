Train Traffic Signalling system
=======================================
Millions of people use Trains for daily commute all over the world. Trains are integral part of the society that helps us commute with ease. It is thus very 
important that they arrive in timely manner, reach the assigned destination, and act accordinly based on thr signals provided.The cuurently provided project 
is a starting point which can evolve into a real time simulation system. For sanity purposes 10 tracks with static names, arbitary lengths and 6 trains have
been considered for the project. Once the binary has been executed press any key on the screen to see the movements of various trains.

/** Initial Layout
 * A->B->C->Junction->D
 *        |      |
 *        I      F->G->H->Junction->L
 *        |                 |
 *        J                 E 
*/

How to build the project
=========================
1. Clone the project on to any linux based environment (preferrably Ubuntu 14.04.6 LTS Trusty as this has been developed and tested tested with the same) with the command git clone <URL provided by the repository>.
2. cd to build directory.
3. run make.
4. ./traintrafficsimulation to view the actual simulation.

The binary has been compiled with -g flag for it to be used with gdb debugger. This should help debug critical issues such as nullptr expection.

