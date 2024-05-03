#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Patient
{
public:
    string name;
    int priority; // 1: Serious, 2: Non-Serious, 3: General Checkup

    // Constructor
    Patient(const string &name, int priority) : name(name), priority(priority) {}
};

class PriorityQueue
{
private:
    vector<Patient> heap;
    int maxSize;

    int parent(int index) const // for getting index of parent
    {
        return (index - 1) / 2;
    }
    int left(int index) const // for getting index of left child
    {
        return (2 * index) + 1;
    }
    int right(int index) const // for getting index of right child
    {
        return (2 * index) + 2;
    }

public:
    PriorityQueue(int size)
    {
        maxSize = size;
    }

    bool isEmpty() const
    {
        return heap.empty();
    }

    void accept()
    {
        string name, priority;
        cout << "Enter patient name: ";
        cin >> name;
        cout << "Enter patient priority (S: Serious, NS: Non-Serious, GC: General Checkup): ";
        cin >> priority;

        int priorityValue;
        if (priority == "S")
        {
            priorityValue = 1;
        }
        else if (priority == "NS")
        {
            priorityValue = 2;
        }
        else if (priority == "GC")
        {
            priorityValue = 3;
        }
        else
        {
            cout << "Invalid priority. Defaulting to Non-Serious." << endl;
            priorityValue = 2;
        }

        Patient patient(name, priorityValue);
        enqueue(patient);
        cout << "Patient added to the queue." << endl;
    }

    void enqueue(const Patient &patient)
    {
        if (heap.size() == maxSize)
        {
            cout << "Priority queue is full. Cannot enqueue patient." << endl;
            return;
        }
        heap.push_back(patient);
        int index = heap.size() - 1;
        // Heapify-up
        while (index > 0 && heap[parent(index)].priority > heap[index].priority)
        {
            swap(heap[parent(index)], heap[index]);
            index = parent(index);
        }
    }

    Patient dequeue()
    {
        if (heap.empty())
        {
            cout << "Priority queue is empty. No patient to dequeue." << endl;
            return Patient("", -1); // Dummy patient
        }
        Patient patient = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        // Heapify-down
        int index = 0;
        while (true)
        {
            int l = left(index);
            int r = right(index);
            int smallest = index;
            if (l < heap.size() && heap[l].priority < heap[smallest].priority)
                smallest = l;
            if (r < heap.size() && heap[r].priority < heap[smallest].priority)
                smallest = r;
            if (smallest != index)
            {
                swap(heap[index], heap[smallest]);
                index = smallest;
            }
            else
            {
                break;
            }
        }
        return patient;
    }

    void display() const
    {
        if (heap.empty())
        {
            cout << "Priority queue is empty. No patients to display." << endl;
            return;
        }
        cout << "Patient List:" << endl;
        for (int i = 0; i < heap.size(); ++i)
        {
            cout << "Name: " << heap[i].name << " | Priority: " << heap[i].priority << endl;
        }
    }
};

int main()
{
    int maxSize;
    cout << "Enter the maximum size of the priority queue: ";
    cin >> maxSize;
    PriorityQueue pq(maxSize);

    while (true)
    {
        cout << "\t\tPatient Management System" << endl;
        cout << "\t\t1. Add Patient" << endl;
        cout << "\t\t2. Serve Patient" << endl;
        cout << "\t\t3. Display Patient list" << endl;
        cout << "\t\t4. Exit" << endl;
        int choice;
        cout << "Enter your choice (1-4): ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            pq.accept();
            break;
        case 2:
            if (!pq.isEmpty())
            {
                Patient currentPatient = pq.dequeue();
                cout << "Serving patient: " << currentPatient.name << endl;
            }
            else
            {
                cout << "No patients in the queue." << endl;
            }
            break;
        case 3:
            pq.display();
            break;
        case 4:
            cout << "Thank you for using the Patient Management System." << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }

    return 0;
}
