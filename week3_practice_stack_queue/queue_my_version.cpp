//================================================================
//  Class Header
//================================================================
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

template <class KeyType> // template to setup the dataType
class Queue
{
    // objects: A finite ordered list with zero or more elements
public:
    Queue(int MaxQueueSize);
    // Create an empty Queue whose maximun size is MaxQueueSize
    bool IsFull();
    // if number of elements in the queue is equal to the maximun size of
    // the queue, return TRUE(1); otherwise, return FALSE(0)
    void Add(const KeyType &item);
    // if IsFull(), then QueueFull(); else insert item at rear of the queue
    bool IsEmpty();
    // if number of elements in the queue is equal to 0, return TRUE(1)
    // else return FALSE(0)
    KeyType *Delete(KeyType &);
    // if IsEmpty(), then QueueEmpty() and return 0;
    // elser remove the front of the queue and return a point to it
    // Returning a pointer of KeyType.

    void displayQueue();

private:
    int front, rear; // Front ptr and rear ptr for queue
    KeyType *queue;  // The pointer points to the address location of instantiate queue
    int MaxSize;     // The MaxSize for my queue.
};

// Constructor
template <class KeyType>
Queue<KeyType>::Queue(int MaxQueueSize) : MaxSize(MaxQueueSize)
{
    queue = new KeyType[MaxQueueSize+1];
    front = 0;
    rear = 0;
}

template <class KeyType>
inline bool Queue<KeyType>::IsFull()
{
    if (((rear + 1) % (MaxSize + 1)) == front)
        return true;
    else
        return false;
}

template <class KeyType>
inline bool Queue<KeyType>::IsEmpty()
{
    if (front == rear)
        return true;
    else
        return false;
}

template <class KeyType>
void Queue<KeyType>::Add(const KeyType &item)
{

    if (IsFull())
    {
        std::cout << "Full creating more space"
                  << "\n";
        KeyType *newQueue = new KeyType[2 * (MaxSize+1) - 1];
        // Making a new Queue, the pointer to the start of newQueue

        // Since after doubling queue, the last elements would be displaced,
        // Thus we have to combat it. start stores the location of the first

        int start = (front + 1) % (MaxSize + 1);
        if (start < 2)
        {
            // no wraps around
            // Copy function uses index to copy from one location
            // to another
            copy(queue + start, queue + MaxSize + 1, newQueue + 1);
        }
        else
        {
            // wraps around
            copy(queue + start, queue + MaxSize, newQueue + 2 * MaxSize);
            copy(queue, queue + rear, newQueue);
            front = 2 * MaxSize - 1;
        }


        // rear  = MaxSize - 2;
        MaxSize *= 2;
        delete[] queue;
        queue = newQueue;
    }
    else
    {
        rear = (rear + 1) % (MaxSize+1);
        queue[rear] = item;
    }
}

template <class KeyType>
KeyType *Queue<KeyType>::Delete(KeyType &item)
{
    // Given an address as an input, this address would be used to store the
    // Popped value of Queue.
    if (IsFull())
    {
        std::cout << "Empty!\n";
        return 0;
    }
    else
    {
        front = (front + 1) % (MaxSize + 1);
        item = queue[front];
    }

    return &item;
}

template <class KeyType>
void Queue<KeyType>::displayQueue()
{

    for (int i = (front + 1) % (MaxSize+1); i != rear % (MaxSize+1); i++)
    {
        std::cout << queue[i] << " <- ";
    }
    std::cout << queue[ rear % (MaxSize+1)] << std::endl;
}

std::string manual = "\n1:enqueue\n2:dequeue\n3:view\nYour choice";

int main()
{
    int MaxSize = 2;
    Queue<int> QueueObj(MaxSize);

    int choice;
    int enqueue_value, dequeue_value, *rear;

    while (true)
    {
        std::cout << manual;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cout << "value: ";
            cin >> enqueue_value;
            // Add the objects into queue.
            QueueObj.Add(enqueue_value);
            break;
        }
        case 2:
        {
            // Popping out objects from queue.
            rear = QueueObj.Delete(dequeue_value);
            if (rear != 0)
                cout << "value = " << dequeue_value << endl;
            break;
        }
        case 3:
        {
            QueueObj.displayQueue();
            break;
        }
        default:
        {
            cout << "Invalid Choice\n";
            break;
        }
        }
        std::cout << "Current queue is:\n";
        QueueObj.displayQueue();
    }
}