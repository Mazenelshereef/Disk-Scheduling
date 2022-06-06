#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//////////////////// Helper Functions //////////////////////////

// to print output of all algorithms
void printOutput(vector<int> sequence, int totalMovement)
{
    cout << "Head movement sequence: ";
    for (int i = 0; i < sequence.size() - 1; i++)
    {
        cout << sequence[i] << " -> ";
    }
    cout << sequence.back() << '\n';
    cout << "Total movement = " << totalMovement << endl << endl;
}

// used in the SSTF algorithm
void calculateDifference(vector<int> queue, int cHeadPos, vector<int>& difference)
{
    for (int i = 0; i < queue.size(); i++)
    {
        difference[i] = abs(cHeadPos - queue[i]);
    }
}

// used in the SSTF algorithm
int findIndexOfMinimumDistance(vector<int> difference, vector<bool> differenceTaken)
{
    int index = -1;
    int min = 199;

    for (int i = 0; i < difference.size(); i++)
    {
        if (difference[i] < min && !differenceTaken[i])
        {
            min = difference[i];
            index = i;
        }
    }
    return index;
}
////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////// Algorithms ///////////////////////////////////////////

pair<vector<int>, int> FCFS_algorithm(vector<int> queue, int initialCylinder)
{
    int totalMovement = 0, cHeadPos = initialCylinder;
    vector<int> seq;
    seq.push_back(initialCylinder);
    for (int i = 0; i < queue.size(); i++)
    {
        totalMovement += abs(queue[i] - cHeadPos);
        cHeadPos = queue[i];
        seq.push_back(cHeadPos);
    }
    return pair<vector<int>, int>(seq, totalMovement);
}

pair<vector<int>, int> SSTF_algorithm(vector<int> queue, int initialCylinder)
{
    int totalMovement = 0;
    int indexOfNext;
    int cHeadPos = initialCylinder;
    int queueSize = queue.size();
    vector<int> seq;
    vector<int> difference(queue.size());
    vector<bool> differenceTaken(queue.size());
    for (int i = 0; i < queue.size(); i++) //checks if it is taken before or not
    {
        differenceTaken[i] = false;
    }
    seq.push_back(initialCylinder);
    calculateDifference(queue, cHeadPos, difference);
    indexOfNext = findIndexOfMinimumDistance(difference, differenceTaken);
    differenceTaken[indexOfNext] = true;
    totalMovement += abs(queue[indexOfNext] - cHeadPos);

    for (int i = 0; i < queue.size(); i++)
    {
        cHeadPos = queue[indexOfNext];
        seq.push_back(cHeadPos);
        calculateDifference(queue, cHeadPos, difference);
        indexOfNext = findIndexOfMinimumDistance(difference, differenceTaken);
        if (indexOfNext >= 0)
        {
            differenceTaken[indexOfNext] = true;
            totalMovement += abs(queue[indexOfNext] - cHeadPos);
        }

    }
    return pair<vector<int>, int>(seq, totalMovement);
}


int main()
{
    int n, initialCylinder, chosenAlgo;
    cout << "How many I/O requests?\n";
    cin >> n;
    vector<int> queue(n);
    cout << "Enter the requests queue (space seperated):\n";
    for (int i = 0; i < n; i++)
    {
        cin >> queue[i];
    }
    cout << "Enter the initial cylinder position:\n";
    cin >> initialCylinder;
    while (true)
    {
        cout << "choose the algorithm:\n"
            << "0 - Exit\n"
            << "1 - FCFS\n"
            << "2 - SSTF\n"
            << "3 - Scan\n"
            << "4 - C-Scan\n"
            << "5 - Look\n"
            << "6 - C-Look\n"
            << "7 - Optimized algorithm\n";
        cin >> chosenAlgo;

        pair<vector<int>, int> result;
        switch (chosenAlgo)
        {
        case 1:
            result = FCFS_algorithm(queue, initialCylinder);
            break;
        case 2:
            result = SSTF_algorithm(queue, initialCylinder);
            break;
      
        default:
            return 0;
        }
        printOutput(result.first, result.second);
    }
}

