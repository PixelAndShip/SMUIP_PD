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
        delete nextInLine;
    };

    void generateA1WaitTime() {

    };
    void generateK1WaitTime() {

    };
    void generateK2WaitTime() {

    };

};