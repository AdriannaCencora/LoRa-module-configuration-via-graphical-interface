#ifndef LOGIC_CONSOLE_H
#define LOGIC_CONSOLE_H

#include "console.h"
#include <iterator>
class LogicConsole

{
    public:
        static LogicConsole* instance(){
            static LogicConsole ins;
            return &ins;
        }

    Console *getInputCon(){return this->input;}
    void sendToOutput(){output->insertPlainText("\n"+input->toPlainText());}
    void setInput(Console *in){input = in;}
    void setOutput(Console *out){output = out;}
    void write(QString msg){output->insertPlainText("\n"+msg);}
    QString toString(uint8_t *t, int sizeT){
        QString str;
        for(int i = 0; i<sizeT;i++)
            str += QString::number(t[i],16);
        return str;}

    private:
        LogicConsole(){}
        Console *input;
        Console *output;
       };
#endif // LOGIC_CONSOLE_H
