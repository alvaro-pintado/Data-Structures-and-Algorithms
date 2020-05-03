#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>
#include <mutex>

using namespace std;

void computeNum();
int divSum(int);
void increment();
void printPair(int, int);
int grabNum();

mutex incMutex;
mutex printMutex;
mutex grabMutex;
int numCount = 10;
int lim = 0;

int main(int argc, char* argv[])
{
    // get start timer...
    auto t1 = chrono::high_resolution_clock::now();

    if (argc == 1) {
        cout << "Usage: amicableNumes -t <threadCount> -l <limitValue>" << endl;
        exit(1);
    }

    if (argc != 5) {
        cout << "Error, invalid command line options." << endl;
        exit(1);
    }

    if (string(argv[1]) != "-t") {
        cout << "Error, invalid thread count specifier." << endl;
        exit(1);
    }

    if (string(argv[3]) != "-l") {
        cout << "Error, invalid upper limit specifier." << endl;
        exit(1);
    }

    int thCount = stoi(argv[2]);
    lim = stoi(argv[4]);

    /*
    if(thCount > thread::hardware_concurrency()){
        cout << "Error, number of requested threads is not supported on this maachine." << endl;
        cout << "This petty machine can only handle " << thread::hardware_concurrency << " threads at a time." << endl;
        exit(1);
    }

    cout << "Threads: " << thCount << endl;
    cout << "Upper limit: " << lim << endl;
    */

// /////////////////////////////////////////////////////////////////////////////////

    thread* threads = new thread[thCount];

    for(int i = 0; i < thCount; i++)
        threads[i] = thread(computeNum);

    for(int i = 0; i < thCount; i++)
        threads[i].join();

// //////////////////////////////////////////////////////////////////////////////
    // get end time...
    auto t2 = chrono::high_resolution_clock::now();

    // show results with times
   cout << "Program took: " << std::chrono::duration_cast<std::chrono::milliseconds>
           (t2-t1).count() << " milliseconds" << endl;

}

void computeNum()
{
    int num = grabNum();
    while(num != 0)
    {
        int dSum = divSum(num);
        if(num == divSum(dSum) && dSum > num)
        {
            printPair(num, dSum);
        }
        num = grabNum();
    }
}

int divSum(int num)
{
    int i = num-1;
    int sum = 0;
    while(i!=0)
    {
        if(num%i == 0)
            sum += i;
        i--;
    }

    return sum;
}

void printPair(int a, int b)
{
    lock_guard<mutex> guard(printMutex);
        cout << a << " & " << b << endl;
}

int grabNum()
{
    lock_guard<mutex> guard(grabMutex);
    if(numCount < lim)
    {
        numCount++;
        return numCount-1;
    }
    else
        return 0;
}
