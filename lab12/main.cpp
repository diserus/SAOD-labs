#include "stack.hpp"
#include "queue.hpp"
#define FILL_SIZE 50
int main()
{
    Stack<int> stack;
    Queue<int> queue;

    std::cout << "Dec stack: ";
    stack.fill_dec(FILL_SIZE);
    stack.printStack();
    stack.clear();

    std::cout << "Inc stack: ";
    stack.fill_inc(FILL_SIZE);
    stack.printStack();
    stack.clear();

    std::cout << "Rand stack: ";
    stack.fill_rand(FILL_SIZE);
    stack.printStack();

    int stacksum = stack.check_sum();
    std::cout << "Sum rand stack: " << stacksum << "\n";
    int stackseries = stack.check_series();
    std::cout << "Series rand stack: " << stackseries << "\n";

    std::cout << "\n";

    std::cout << "Dec queue: ";
    queue.fill_dec(FILL_SIZE);
    queue.printQueue();
    queue.clear();

    std::cout << "Inc queue: ";
    queue.fill_inc(FILL_SIZE);
    queue.printQueue();
    queue.clear();

    std::cout << "Rand queue: ";
    queue.fill_rand(FILL_SIZE);
    queue.printQueue();

    int queuesum = queue.check_sum();
    std::cout << "Sum rand queue: " << queuesum << "\n";
    int queueseries = queue.check_series();
    std::cout << "Series rand queue: " << queueseries << "\n";
    return 0;
}
