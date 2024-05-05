#include <iostream>
#define MAX_SIZE 10

using namespace std;

class priority_queue {
   private:
    string queue[MAX_SIZE];
    int priority_val[MAX_SIZE];
    int front;
    int rear;

   public:
    priority_queue() {
        front = -1;
        rear = -1;
    }

    bool is_empty() { return front == -1; }

    bool is_full() { return rear == MAX_SIZE - 1; }

    void enqueue(string data, int priority) {
        if (is_full()) {
            cout << "Queue is full." << endl;
            return;
        }
        if (is_empty()) {
            front = 0;
            rear = 0;
            queue[rear] = data;
            priority_val[rear] = priority;
        } else {
            int i;
            rear++;
            for (i = rear-1; i >= front; i--) {
                if (priority_val[i] < priority) {
                    queue[i + 1] = queue[i];
                    priority_val[i + 1] = priority_val[i];
                } else {
                    break;
                }
            }
            queue[i + 1] = data;
            priority_val[i + 1] = priority;
        }
    }

    string dequeue() {
        if (is_empty()) {
            cout << "Queue is empty." << endl;
            return "";
        }
        string data = queue[front];
        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            front++;
        }
        return data;
    }

    int get_priority() {
        if (is_empty()) {
            return -1;
        }
        return priority_val[front];
    }

    void display() {
        if (is_empty()) {
            cout << "Queue is empty." << endl;
            return;
        }
        cout << "Queue is:" << endl;
        for (int i = front; i <= rear; i++) {
            cout << priority_val[i] << ":\t" << queue[i] << endl;
        }
        cout << endl;
    }
};

int main() {
    priority_queue queue;
    int ch = 0;
    int priority;
    string name;
    do {
        cout << "--- MAIN MENU ---" << endl;
        cout << "1 -> Add patient" << endl;
        cout << "2 -> Remove patient" << endl;
        cout << "3 -> Display queue" << endl;
        cout << "4 -> Exit" << endl;
        cout << "Choose an option (1-4):\t";
        cin >> ch;
        switch (ch) {
            case 1:
                cout << "Patient name:\t";
                cin >> name;
                cout << "Priority (0: General Checkup; 1: Non-serious; 2: Serious):\t";
                cin >> priority;
                queue.enqueue(name, priority);
                cout << "Patient added successfully." << endl;
                break;
            case 2:
                priority = queue.get_priority();
                name = queue.dequeue();
                cout << "Patient '" << name << "' with priority '" << priority
                     << "' removed." << endl;
                break;
            case 3:
                queue.display();
                break;
            case 4:
                cout << "\n\n// END OF CODE\n\n" << endl;
                break;
            default:
                cout << "Please choose a valid option (1-4)." << endl;
                break;
        }
    } while (ch != 4);

    return 0;
}
