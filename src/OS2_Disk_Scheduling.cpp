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

pair<vector<int>, int> scan_algorithm(vector<int> queue, int initialCylinder)
{
    vector<int> sequence;
    sequence.push_back(initialCylinder);
    int totalMovement = 0, currentHead = initialCylinder;
    while (currentHead != 0)
    {
        int max = 0, index = -1;
        for (int i = 0; i < queue.size(); i++)
        {
            if (queue[i] > max && queue[i] <= currentHead)
            {
                max = queue[i];
                index = i;
            }
        }
        sequence.push_back(max);
        totalMovement += abs(currentHead - max);
        currentHead = max;
        if (index >= 0)
            queue.erase(queue.begin() + index);
    }
    while (!queue.empty())
    {
        int min = 199, index = -1;
        for (int i = 0; i < queue.size(); i++)
        {
            if (queue[i] < min)
            {
                min = queue[i];
                index = i;
            }
        }
        sequence.push_back(min);
        totalMovement += abs(min - currentHead);
        currentHead = min;
        if (index >= 0)
            queue.erase(queue.begin() + index);
    }
    return pair<vector<int>, int>(sequence, totalMovement);
}

pair<vector<int>, int> cscan_algorithm(vector<int> queue, int initialCylinder)
{
    vector<int> sequence;
    int indx, start = 0, endd = 199, totalMovement = 0;
    queue.push_back(start); queue.push_back(endd);
    sort(queue.begin(), queue.end());
    for (int i = 0; i < queue.size(); i++) {
        if (queue[i] > initialCylinder) {
            indx = i - 1;
            break;
        }
    }
    sequence.push_back(initialCylinder);
    int last = initialCylinder;
    while (queue.size() != 0) {
        sequence.push_back(queue[indx]);
        totalMovement += abs(queue[indx] - last);
        last = queue[indx];
        queue.erase(queue.begin() + indx);
        if (indx == 0)indx = queue.size() - 1;
        else indx--;
    }
    return pair<vector<int>, int>(sequence, totalMovement);
}

pair<vector<int>, int> look_algorithm(vector<int> queue, int initialCylinder)
{
    vector<int> sequence;
    sequence.push_back(initialCylinder);
    int totalMovement = 0, currentHead = initialCylinder, minimum = 200;


    for (int i = 0; i < queue.size(); i++)
    {
        if (queue[i] < minimum)
        {
            minimum = queue[i];
        }
    }
    while (currentHead != minimum)
    {
        int max = -1, index = -1;
        for (int i = 0; i < queue.size(); i++)
        {
            if (queue[i] > max && queue[i] <= currentHead)
            {
                max = queue[i];
                index = i;
            }
        }
        if (max >= 0)
        {
            sequence.push_back(max);
            totalMovement += abs(currentHead - max);
            currentHead = max;
            if (index >= 0)
                queue.erase(queue.begin() + index);
        }
    }
    while (!queue.empty())
    {
        int min = 199, index = -1;
        for (int i = 0; i < queue.size(); i++)
        {
            if (queue[i] < min)
            {
                min = queue[i];
                index = i;
            }
        }
        sequence.push_back(min);
        totalMovement += abs(min - currentHead);
        currentHead = min;
        if (index >= 0)
            queue.erase(queue.begin() + index);
    }
    return pair<vector<int>, int>(sequence, totalMovement);
}

pair<vector<int>, int> clook_algorithm(vector<int> queue, int initialCylinder)
{
    vector<int> sequence;
    int indx, endd = 199, totalMovement = 0;
    sort(queue.begin(), queue.end());
    for (int i = 0; i < queue.size(); i++) {
        if (queue[i] > initialCylinder) {
            indx = i;
            break;
        }
    }
    sequence.push_back(initialCylinder);
    int last = initialCylinder;
    while (queue.size() != 0) {
        sequence.push_back(queue[indx]);
        totalMovement += abs(queue[indx] - last);
        last = queue[indx];
        queue.erase(queue.begin() + indx);
        if (indx == queue.size())indx = 0;
    }
    return pair<vector<int>, int>(sequence, totalMovement);
}

pair<vector<int>, int> optimized_algorithem(vector<int> queue)
{
    int initHeadPos = 0, totalMovement = 0, cHeadPos = 0; vector<int> seq;
    seq.push_back(initHeadPos);
    sort(queue.begin(), queue.end());
    for (int i = 0; i < queue.size(); i++)
    {
        totalMovement += abs(queue[i] - cHeadPos);
        cHeadPos = queue[i];
        seq.push_back(cHeadPos);
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
        case 3:
            result = scan_algorithm(queue, initialCylinder);
            break;
        case 4:
            result = cscan_algorithm(queue, initialCylinder);
            break;
        case 5:
            result = look_algorithm(queue, initialCylinder);
            break;
        case 6:
            result = clook_algorithm(queue, initialCylinder);
            break;
        case 7:
            result = optimized_algorithem(queue);
            break;
        default:
            return 0;
        }
        printOutput(result.first, result.second);
    }
}

