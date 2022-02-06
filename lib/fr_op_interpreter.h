#ifndef FROPINTERPRETER_H
#define FROPINTERPRETER_H

class FROpInterpreter
{
public:
    FROpInterpreter();

    void    interpret() const;
private:
    FROpInterpreter(const FROpInterpreter &obj);
    FROpInterpreter &operator=(const FROpInterpreter &obj);
};
#endif // FROPINTERPRETER_H
