//================================================================
//  Class Header
//================================================================
#include <iostream>
#include <string>
#include <algorithm>

template <class KeyType> // template to setup the dataType
class Stack
{
    // objects: A finite ordered list with zero or more elements
public:
    Stack(int MaxStackSize);
    // Create an empty Stack whose maximun size is MaxStackSize
    bool IsFull();
    // if number of elements in the stack is equal to the maximun size of
    // the stack, return TRUE(1); otherwise, return FALSE(0)
    void Push(const KeyType &item);
    // if IsFull(), then StackFull(); else insert item at front of the stack
    bool IsEmpty();
    // if number of elements in the stack is equal to 0, return TRUE(1)
    // else return FALSE(0)
    KeyType *Pop(KeyType &);
    // if IsEmpty(), then StackEmpty() and return 0;
    // elser remove the front of the stack and return a point to it
    // Returning a pointer of KeyType.

    void displayStack();

private:
    int front;      // Front ptr and front ptr for stack
    KeyType *stack; // The pointer points to the address location of instantiate stack
    int MaxSize;    // The MaxSize for my stack.
};

template <class KeyType>
Stack<KeyType>::Stack(int MaxStackSize) : MaxSize(MaxStackSize)
{
    stack = new KeyType[MaxStackSize];
    front = 0;
}

template <class KeyType>
inline bool Stack<KeyType>::IsEmpty()
{
    return front == 0;
}

template <class KeyType>
inline bool Stack<KeyType>::IsFull()
{
    return front == MaxSize;
}

template <class KeyType>
void Stack<KeyType>::Push(const KeyType &item)
{
    if (IsFull())
    {
        std::cout << "Stack is full!\n";
        std::cout << "Extending Stack Size\n";
        MaxSize = MaxSize * 2;
        KeyType *newStack = new KeyType[MaxSize * 2];

        std::copy(stack, stack + front, newStack);
        newStack[front++] = item;
        delete[] stack;
        stack = newStack;
    }
    else
    {
        std::cout << "Pushing value " << item << " into stack\n";
        stack[front++] = item;
    }
}

template <class KeyType>
KeyType *Stack<KeyType>::Pop(KeyType &item)
{
    if (IsEmpty())
    {
        std::cout << "Stack is empty\n";
        return 0;
    }

    item = stack[--front];
    std::cout << "Popping out value " << item << " into stack\n";

    return &item;
}

template <class KeyType>
void Stack<KeyType>::displayStack()
{
    for (int i = 0; i < front; i = i + 1)
    {
        std::cout << stack[i] << "\n";
    }
}

std::string manual = "\n1:Push\n2:Pop\n3:view\n4:Exit\nYour choice: ";

int main()
{
    int MaxSize = 2;
    Stack<int> stack_obj(MaxSize);

    int choice;
    int push_value, pop_value;

    while (true)
    {
        std::cout << manual;
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            std::cin >> push_value;
            stack_obj.Push(push_value);
            std::cout << "You pushed value" << push_value << "\n";
            break;
        }
        case 2:
        {
            stack_obj.Pop(pop_value);
            break;
        }
        case 3:
        {
            stack_obj.displayStack();
            break;
        }
        case 4:
        {
            std::cout << "EXITING"
                      << "\n";
            goto exit;
        }
        default:
        {
            std::cout << "INVALID CHOICE"
                      << "\n";
            break;
        }
        }
    }

exit:

    return 0;
}