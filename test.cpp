#include <bits/stdc++.h>
#include "lfu.hpp"
using namespace std;

int main()
{
    int n, choice, k, v;
    cout << "Enter size/capacity of LFU cache: ";
    cin >> n;
    LFUCache cache(n);
    do {
        cout << "Enter Your choice: \n \t 1)Add key - value pair to cache \n \t 2)Get key value \n \t 3)Exit\n";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Enter key and its value: ";
                cin >> k >> v;
                cache.add(k, v);
                break;

            case 2:
                cout << "Enter a key: ";
                cin >> k;
                cout << cache.get(k) << "\n";
                break;

            case 3:
                cout << "Thank you!\n";
                break;
                
            default:
                cout << "Enter a valid number\n";
                break;
        }        

    } while (choice != 3);
    return 0;
}