#include<iostream>
using namespace std;

class Heap {
    int n;
    int *marks;
public:
    Heap(int size) {
        n = size;
        marks = new int[n];
    }

    void get() {
        cout << "Enter marks of students." << endl;
        for (int i = 0; i < n; i++) {
            cin >> marks[i];
            upAdjust(i);
        }
    }

    void upAdjust(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (marks[index] > marks[parent])
                swap(marks[index], marks[parent]);
            else
                break;
            index = parent;
        }
    }

    int getMax() {
        return marks[0];
    }

    int getMin() {
        return marks[n - 1];
    }

    ~Heap() {
        delete[] marks;
    }
};

int main() {
    int n;
    cout << "Enter number of students." << endl;
    cin >> n;
    Heap maxHeap(n);
    maxHeap.get();
    cout << "Maximum marks are: " << maxHeap.getMax() << endl;
    cout << "Minimum marks are: " << maxHeap.getMin() << endl;
    return 0;
}
