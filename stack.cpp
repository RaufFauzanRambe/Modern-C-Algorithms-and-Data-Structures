#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class Stack {
private:
    T* arr;           
    T* maxArr;       
    T* minArr;        
    int topIndex;
    int capacity;

    void resize() {
        int newCap = capacity * 2;
        T* newArr = new T[newCap];
        T* newMax = new T[newCap];
        T* newMin = new T[newCap];
        for (int i = 0; i <= topIndex; i++) {
            newArr[i] = arr[i];
            newMax[i] = maxArr[i];
            newMin[i] = minArr[i];
        }
        delete[] arr;
        delete[] maxArr;
        delete[] minArr;
        arr = newArr;
        maxArr = newMax;
        minArr = newMin;
        capacity = newCap;
        cout << "[Stack resized] New capacity: " << capacity << endl;
    }

public:
    Stack(int size = 10) {
        capacity = size;
        arr = new T[capacity];
        maxArr = new T[capacity];
        minArr = new T[capacity];
        topIndex = -1;
    }

    ~Stack() {
        delete[] arr;
        delete[] maxArr;
        delete[] minArr;
    }

    void push(T val) {
        if (topIndex + 1 == capacity) resize();
        arr[++topIndex] = val;
        maxArr[topIndex] = (topIndex == 0) ? val : max(val, maxArr[topIndex - 1]);
        minArr[topIndex] = (topIndex == 0) ? val : min(val, minArr[topIndex - 1]);
    }

    T pop() {
        if (isEmpty()) throw underflow_error("Stack Underflow!");
        return arr[topIndex--];
    }

    T top() const {
        if (isEmpty()) throw underflow_error("Stack is empty!");
        return arr[topIndex];
    }

    T getMax() const {
        if (isEmpty()) throw underflow_error("Stack is empty!");
        return maxArr[topIndex];
    }

    T getMin() const {
        if (isEmpty()) throw underflow_error("Stack is empty!");
        return minArr[topIndex];
    }

    bool isEmpty() const { return topIndex == -1; }
    int size() const { return topIndex + 1; }

    void display() const {
        cout << "Stack: ";
        for (int i = 0; i <= topIndex; i++)
            cout << arr[i] << " ";
        cout << endl;
    }
};

int main() {
    Stack<int> s(3);
    s.push(50);
    s.push(20);
    s.push(80);
    s.display();

    s.push(100);
    s.display();

    cout << "Top item: " << s.top() << endl;
    cout << "Max item: " << s.getMax() << endl;
    cout << "Min item: " << s.getMin() << endl;

    cout << "Popped: " << s.pop() << endl;
    s.display();
    cout << "Max now: " << s.getMax() << endl;
    cout << "Min now: " << s.getMin() << endl;

    return 0;
}
