#ifndef SORTALGORITHMS_H
#define SORTALGORITHMS_H

class sortAlgorithms
{
public:
    sortAlgorithms();
    ~sortAlgorithms();
    void generateData(int);
    int getLength();
    short getItem(int);
    void printData();
    void bubbleSort();
    void selectionSort();
    void quickSort();
    void countSort();

private:
    int length;
    short* myArray;
    static const int LIMIT = 7000;

    void selectionSort(int, int);
    void quickSort(int, int);
    int partition(int, int);

};

#endif // SORTALGORITHMS_H
