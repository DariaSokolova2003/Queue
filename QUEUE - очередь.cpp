#include <iostream>
#include <cstdlib>
#define N 5
using namespace std;


class Queue {
    int start = -1;
    int end = -1;
    int size = N;
    int* buffer = new int[size];
 bool Is_full() const {
        return ((end + 1) % size == start);
    }
public:
    Queue() = default;
    Queue(const Queue& q): start(q.start), size(q.size),// конструктор копирования
        end(q.end), buffer(new int[size]) {
        
        for (int i = 0; i < size; i++) {
            buffer[i] = q.buffer[i];
        }
    }
    ~Queue() {
        delete buffer;
    }

    bool Is_empty() const {
        return ((start == end) && (end == -1));
    }

    Queue& operator=(const Queue& q)
    {
        if (this != &q) {
            if (counter() >= q.counter()) {
                for (int i = 0; i <= q.size; i++)
                    buffer[i] = q.buffer[i];
                end = q.end;
                start = q.start;
            }
            else {
                delete[] buffer;
                buffer = new int[q.size];
                for (int i = 0; i < q.size; i++)
                    buffer[i] = q.buffer[i];
                start = q.start;
                end = q.end;
                size = q.size;
            }
        }
       return *this;
    }

            
    int counter() const {
        if (Is_empty()) { return 0; }
        else
            return (end - start >= 0) ? (end - start + 1) : (size - (start - end - 1));

    }
    int front() const {
        if (Is_empty()) exit(1);
        return buffer[start];

    }
    int back() const {
        if (Is_empty()) exit(1);
        return buffer[end];
    }
    void reset() {
        start = end = -1;
    }
   

    bool pop() {
        if (Is_empty()) return false;
        if (start == end) start = end = -1;
        else start = (start + 1) % N;
        return true;
    }

    bool push(int element) {
        if (Is_empty()) start = end = 0;
        else {
            if (Is_full()) {
            int * buffer1 = new int[size * 2];
            int i = start, j=0;
            while (i != end) {
                buffer1[j] = buffer[i];
                i = (i + 1) % size;
                j++;
            }
            buffer1[j] = buffer[i];
            start = 0;
            end = j;
            size *= 2;
            delete[]buffer;
            buffer = buffer1;
            
        }
            end = (end + 1) % size;
        }   
        buffer[end] = element;
       
        return true;
    }

    void print() {
        if (Is_empty()) cout << "QUEUE IS EMPTY\n";
        else if (start == end)
            cout << buffer[start];

        else {
            int i = start;
            while (i != end) {

                cout << buffer[i] << " -> ";
                i = (i + 1) % N;
            }
            cout << buffer[i] << endl;

        }
    }
    
 
};

int main()
{
    Queue a;
    a.pop();
    a.push(1);
    a.push(2);
    a.push(3);
    a.pop();
    a.pop();
    a.push(4);
 
    Queue b;
    b.push(5);
    b.push(6);
    b.push(7);
    b.push(8);
   
    a = b;
    a.print();

    return 0;

}