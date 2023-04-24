//================================================================
//  Class Header
//================================================================
#include <iostream>

using namespace std;

template <class KeyType> // template to setup the dataType
class Queue
{
    //objects: A finite ordered list with zero or more elements
    public:
        Queue(int MaxQueueSize);
        // Create an empty Queue whose maximun size is MaxQueueSize
        bool IsFull();
        // if number of elements in the queue is equal to the maximun size of
        // the queue, return TRUE(1); otherwise, return FALSE(0)
        void Add(const KeyType& item);
        // if IsFull(), then QueueFull(); else insert item at rear of the queue
        bool IsEmpty();
        // if number of elements in the queue is equal to 0, return TRUE(1)
        // else return FALSE(0)
        KeyType* Delete(KeyType&);
        // if IsEmpty(), then QueueEmpty() and return 0;
        // elser remove the front of the queue and return a point to it
        // Returning a pointer of KeyType.
    private:
        int front, rear; // Front ptr and rear ptr for queue
        KeyType *queue; // The pointer points to the address location of instantiate queue
        int MaxSize; // The MaxSize for my queue.
};

//================================================================
//  MAIN DESIGN
//================================================================

template <class KeyType>
Queue<KeyType>::Queue(int MaxQueueSize): MaxSize(MaxQueueSize)
{
  //The constructor for Queue class.
  queue = new KeyType[MaxSize];  // Instatiating array of type KeyType.
  front = 0; // Setting the front pointer
  rear = 0;  //Setting the rear pointer
}


template <class KeyType>
inline bool Queue<KeyType>::IsFull()
{
  //Reduce the compile time, once called, compiler would call a copy of this
  //function, and then reuse it later without recompiling it again.
  //since in real world example, lots of functions and lots of things are
  //generated, thus this is used for optimization and speedup of code.
  //This actually trades memory for speed. Reduce the contraol transfer overHead.
  if( (rear+1)%MaxSize == front) return true; //Front and rear should be 1 pointer apart.
  else return false;
}


template <class KeyType>
inline bool Queue<KeyType>::IsEmpty()
{
  if( front == rear) return true;
  else return false;
}


template <class KeyType>
void Queue<KeyType>::Add(const KeyType& item)
{
  /* add an item into the global Queue */
  if(IsFull())
    cout << "Queue is full\n"; //Queue_Full()
  else{
    queue[rear] = item;
    rear = (rear+1)%MaxSize;
  }
}


template <class KeyType>
KeyType* Queue<KeyType>::Delete(KeyType& item)
{
  if(IsEmpty()){
    cout << "Queue is empty\n"; //Queue_Empty()
    return 0;
  }
  item = queue[front];
  front = (front+1)%MaxSize;
  // Due to being a circular buffer, must use modulo to indicate the right position in queue.
  return &item;
}

char manual[] = "\n1:enqueue\n2:dequeue\n3:view\nYour choice: ";

int main()
{
  //Instantiate a queue class out with user-defined dataType
  Queue<int> QueueObj(5);
  int choice;
  int enqueue_value, dequeue_value, *rear;

  //Loop waiting user inputs
  while(true){
    cout << manual;
    cin >> choice;

    switch(choice){
      case 1:
        cout << "value: ";
        cin >> enqueue_value;
        // Add the objects into queue.
        QueueObj.Add(enqueue_value);
        break;

      case 2:
        // Popping out objects from queue.
        rear = QueueObj.Delete(dequeue_value);
        if(rear != 0)
          cout << "value = " << dequeue_value << endl;
        break;

      case 3:
        cout << "Please write it by yourself...\n";
        break;

      default:
        cout << "Invalid Choice\n";
        break;
    }
  }

  return 0;
}