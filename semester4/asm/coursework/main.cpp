#include <iostream>

using namespace std;

extern "C" void
swap(void* mem1, void* mem2, long len);

template <typename T>
void
print(const T* ptr, int size, const char* separator = "")
{
    for (int n = 0; n < size; ++n)
        cout << ptr[n] << separator;
    cout << "\n";
}

template <typename T>
void
read(T*& ptr, int size)
{
    ptr = new T[size];
    for (int n = 0; n < size; ++n)
        cin >> ptr[n];
}


int
main()
{
    int size;
    char* s1;
    char* s2;
    float* arr1;
    float* arr2;

    cout
        << "\n[FIRST EXAMPLE]\n"
        << "enter size: ";
    cin >> size;

    cout << "enter arr1: ";
    read(arr1, size);

    cout << "enter arr2: ";
    read(arr2, size);

    cout << "\n*swap magic*\n";
    swap(arr1, arr2, size * sizeof(arr1));
    print(arr1, size, ", ");
    print(arr2, size, ", ");

    cout
        << "\n[SECOND EXAMPLE]\n"
        << "enter size: ";
    cin >> size;

    cout << "enter s1: ";
    read(s1, size);

    cout << "enter s2: ";
    read(s2, size);

    cout << "\n*swap magic*\n";
    swap(s1, s2, size * sizeof(s1));
    print(s1, size);
    print(s2, size);

    free(arr1);
    free(arr2);
    free(s1);
    free(s2);

    return 0;
}

