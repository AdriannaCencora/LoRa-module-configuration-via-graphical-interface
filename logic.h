
#ifndef LOGIC_H
#define LOGIC_H

#include "controller.h"

//class to passing controller object to gui

class Logic
{
    public:
        static Logic* instance(){
            static Logic ins;
            return &ins;
        }
    void setController(Controller *con){controller = con;}

    Controller* getController(){return this->controller;}

    private:
        Logic(){}
        Controller* controller;
};

#endif // LOGIC

