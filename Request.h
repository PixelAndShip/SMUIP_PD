#pragma once
class Request {
public:
    int waitTime;
    Request* nextInLine = nullptr;
    Request() {
        waitTime = 0;
    }
    Request(int waitT) :waitTime(waitT) {
    }
    virtual ~Request() {
        
    };

};