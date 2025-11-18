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

    void appendToQueue(Request* newR) {
        Request* currentRequest = firstInLine;
        while (currentRequest != nullptr) {
            if (currentRequest->nextInLine == nullptr) {
                currentRequest->nextInLine = newR;
                break;
            }
            currentRequest = currentRequest->nextInLine;
        }
    }

    
};