#ifndef OPINTERPRETER_H
#define OPINTERPRETER_H

class OpInterpreter
{
public:
    OpInterpreter();

    void    interpret();
private:
    OpInterpreter(const OpInterpreter &obj);
    OpInterpreter &operator=(const OpInterpreter &obj);
};
#endif // OPINTERPRETER_H
