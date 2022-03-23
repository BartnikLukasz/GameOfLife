#ifndef CELLAGE_H
#define CELLAGE_H


class CellAge
{
public:
    CellAge();
    void addAge();
    short getAge();

    void setAge(short age);
private:
    short age;
};

#endif // CELLAGE_H
