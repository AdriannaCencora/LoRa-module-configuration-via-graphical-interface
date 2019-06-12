#ifndef LOGIC_CONSOLE_H
#define LOGIC_CONSOLE_H

#include "console.h"
#include "controller.h"
#include<unistd.h>
#include "logic.h"
#include <iterator>
class LogicConsole

{
    public:
        static LogicConsole* instance(){
            static LogicConsole ins;
            return &ins;
        }

    Console *getInputCon(){return this->input;}
    void sendToOutput(){output->insertPlainText("\n"+input->toPlainText());
                        bool ok;
                        QString msg = input->toPlainText();
                        uint8_t C1 = msg.mid(2,2).toUInt(&ok,16);
                        uint8_t C2 = msg.mid(4,2).toUInt(&ok,16);;
                        uint8_t C3 = msg.mid(6,2).toUInt(&ok,16);;
                        sendToSerial(C1,C2,C3);}
    void sendToSerial(uint8_t C1, uint8_t C2, uint8_t C3){
                       int _fileDescriptor = Logic::instance()->getController()->getFileDescriptor();
                       write(_fileDescriptor,&C1,1);
                       write(_fileDescriptor,&C2,1);
                       write(_fileDescriptor,&C3,1);}
    void setInput(Console *in){input = in;}
    void setOutput(Console *out){output = out;}
    void writeToOutput(QString msg){
                            output->insertPlainText("\n"+msg);}
    QString toString(uint8_t *t, int sizeT){
        QString str;
        for(int i = 0; i <sizeT;i++)
            str += QString::number(t[i],16);
        return str;}

    private:
        LogicConsole(){}
        Console *input;
        Console *output;
       };
#endif // LOGIC_CONSOLE_H
