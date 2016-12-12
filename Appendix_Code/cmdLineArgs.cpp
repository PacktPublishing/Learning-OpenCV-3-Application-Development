#include <iostream>
#include <cstdlib>

using namespace std;

int add(int x, int y) {
    return (x + y);
}

int main(int argc, char** argv)
{
    if (argc != 3) {
        cout << "The program expects two integer parameters.\n";
        return -1;
    }

    int num1 = atoi(argv[1]), num2 = atoi(argv[2]);
    cout << "Sum = " << add(num1, num2) << "\n";
    return 0;
}
