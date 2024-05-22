//
//  Process.h
//  Eco.Lab1
//
//  Created by Nikita Kuritsyn on 21/05/2024.
//

#ifndef Process_h
#define Process_h

typedef struct Process {
    size_t pid;
    size_t burstTime;
    size_t arrivalTime;
    size_t turnAroundTime;
    size_t waitingTime;
    size_t completeTime;
} Process;

#endif /* Process_h */
