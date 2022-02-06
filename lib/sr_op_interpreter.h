#ifndef SROPINTERPRETER_H
#define SROPINTERPRETER_H

class SROpInterpreter
{
public:
    SROpInterpreter();

    void    interpret() const;
private:
    SROpInterpreter(const SROpInterpreter &obj);
    SROpInterpreter &operator=(const SROpInterpreter &obj);
};
#endif // SROPINTERPRETER_H
