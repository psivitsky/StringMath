#ifndef FUNCINTERPRETER_H
#define FUNCINTERPRETER_H

class FuncInterpreter
{
public:
    FuncInterpreter();

    void    interpret() const;
private:
    FuncInterpreter(const FuncInterpreter &obj);
    FuncInterpreter &operator=(const FuncInterpreter &obj);
};
#endif // FUNCINTERPRETER_H
