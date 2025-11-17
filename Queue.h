#pragma once
#include "Request.h"
class Queue {

public:
    
    Request* firstInLine = nullptr;

    virtual ~Queue() {
        Request* currentRequest = firstInLine;
        while (currentRequest != nullptr) {
            Request* deleteAbleRequest = currentRequest;
            currentRequest = currentRequest->nextInLine;
            delete deleteAbleRequest;
        };
    };

    void generateRequest() {
        //TODO: make request waittime generator
        Request* newRequest = new Request(1);
        
        Request* currentRequest = firstInLine;
        if (currentRequest == nullptr) {
            firstInLine = newRequest;
        }
        else {
            while (currentRequest != nullptr) {
                
                Request* nextRequest = currentRequest->nextInLine;
                if (nextRequest == nullptr) {
                    currentRequest->nextInLine = newRequest;
                    break;
                }
                else {
                    currentRequest = nextRequest;
                }
            };
        }
        
    };
};