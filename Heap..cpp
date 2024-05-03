#include <iostream>
#include <algorithm>

using namespace std;

class Heap
{
    int marks1[100];
    int marks2[100];
    int n;

    void MinHeapify()
    {
        for (int i = n / 2 - 1; i >= 0; i--)
        {
            int p = i;
            int l = 2 * p + 1;
            int r = 2 * p + 2;
            int smallest = p;
            if (l < n && marks1[l] < marks1[smallest])
                smallest = l;
            if (r < n && marks1[r] < marks1[smallest])
                smallest = r;
            if (smallest != p)
            {
                swap(marks1[p], marks1[smallest]);
                MinHeapify();
            }
        }
    }

    void MaxHeapify()
    {
        for (int i = n / 2 - 1; i >= 0; i--)
        {
            int p = i;
            int l = 2 * p + 1;
            int r = 2 * p + 2;
            int largest = p;
            if (l < n && marks2[l] > marks2[largest])
                largest = l;
            if (r < n && marks2[r] > marks2[largest])
                largest = r;
            if (largest != p)
            {
                swap(marks2[p], marks2[largest]);
                MaxHeapify();
            }
        }
    }

public:
    void accept()
    {
        cout << "Enter the number of students: ";
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cout << "Enter the marks obtained by student " << i + 1 << ": ";
            cin >> marks1[i];
            marks2[i] = marks1[i];
        }
        MinHeapify();
        MaxHeapify();
        cout << "<-------------------------------------------------------------------->" << endl;
        cout << "MINIMUM marks scored by the students is : " << marks1[0] << endl;
        cout << "MAXIMUM marks scored by the students is : " << marks2[0] << endl;
        cout << "<-------------------------------------------------------------------->" << endl;
    }

    void display()
    {
        for (int i = 0; i < n; i++)
        {
            cout << "Marks of student " << i + 1 << " : " << marks1[i] << endl;
        }
    }
};

int main()
{
    Heap h;
    h.accept();
    h.display();
    return 0;
}
