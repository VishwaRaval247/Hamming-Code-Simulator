#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <cmath>
    
using namespace std;

class red
{

public:
    red()
    {
        cout << "\033[38;5;160;48;5;235m";
    }
};

class green
{

public:
    green()
    {
        cout << "\033[38;5;28;48;5;235m";
    }
};

class white
{

public:
    white()
    {
        cout << "\033[38;5;7;48;5;235m";
    }
};

void HammmingCodeGen(vector<int> msg, int r, int m)
{
    reverse(msg.begin(), msg.end());
    vector<int> hammingcode(r + m + 1);
    for (int i = 0; i < r; i++)
    {
        hammingcode[pow(2, i)] = 2; // set redundant bit position to 2
    }

    int j = 0;
    for (int i = 1; i <= (r + m); i++)
    {
        if (hammingcode[i] != 2)
        {
            hammingcode[i] = msg[j]; // set msg into data position
            j++;
        }
    }

    int p = 1;
    int k = 1;
    for (int i = 1; i <= (r + m); i++)
    {
        if (hammingcode[i] != 2)
        {
            continue;
        }

        int count = 0;
        for (int j = i + 1; j <= (r + m); ++j)
        {
            if (p & j)
            {
                if (hammingcode[j] == 1)
                {
                    // cout<<"position: "<<p<<" "<<"covered index "<<j<<endl;
                    count++; // number of 1's corresponding to position p
                }
            }
        }
        p = pow(2, k);
        k++;

        if (count % 2 == 0)
            hammingcode[i] = 0; // even parity check
        else
            hammingcode[i] = 1;
    }
    int c = r - 1;
    cout << "Generated Hamming code is: ";
    for (int i = r + m; i >= 1; i--)
    {
        if (i == pow(2, c))
        {
            red();
            cout << hammingcode[i] << " ";
            c--;
        }
        else
        {
            green();
            cout << hammingcode[i] << " ";
        }
        white();
    }

    cout << endl
         << endl;
}

void HammingCode(vector<int> msg)
{
    int r = 1, m = msg.size();
    while (pow(2, r) < m + r + 1)
    {
        r++;
    }

    HammmingCodeGen(msg, r, m);
}

void ErrorDetection(vector<int> msg)
{
    int r = 1, m = msg.size();
    while (pow(2, r) < m + 1)
    {
        r++;
    }
    // cout<<"r "<<r<<endl;
    vector<int> redundant(r);

    reverse(msg.begin() + 1, msg.end());

    int p = 1;
    int k = 1;
    for (int i = 1; i <= m; i++)
    {

        int count = 0;
        for (int j = i; j <= m; ++j)
        {
            if (p & j)
            {
                if (msg[j] == 1)
                {
                    // cout<<"position: "<<p<<" "<<"covered index "<<j<<endl;
                    count++; // number of 1's corresponding to position p
                }
            }
        }
        p = pow(2, k);
        k++;

        if (count % 2 == 0)
            redundant[i - 1] = 0; // even parity check
        else
            redundant[i - 1] = 1;
    }

    // for(int i=0;i<redundant.size();i++)
    //     cout<<redundant[i]<<" ";

    cout << endl;
    int x = 0;
    int j = 0;
    for (int i = 0; i < redundant.size(); i++)
    {
        // cout<<"r "<<redundant[i];
        // cout<<"j"<<j<<"x"<<x<<endl;
        x += pow(2, j) * redundant[i];
        j++;
    }
    if (x == 0)
    {
        cout << "There is no error..." << endl;
    }

    else
    {
        cout << "There is error at position " << x << endl;
        if (msg[x] == 1)
            msg[x] = 0;
        else
            msg[x] = 1;

        reverse(msg.begin() + 1, msg.end());
        cout << "The correct code is ";
        for (int i = 1; i < m; i++)
        {
            if (i == m - x)
            {
                red();
                cout << msg[i] << " ";
            }
            else
            {
                white();
                cout << msg[i] << " ";
            }
        }
        white();
        cout << endl;
    }
}

void note()
{
    red();
    cout << "Here indexing starts from right to left." << endl
         << endl
         << endl;
    white();
}

void print()
{
    cout << endl;
    cout << "1.Hamming code generation" << endl;
    cout << "2.Error Correction and Detection" << endl;
    cout << "3.Exit" << endl;
}

int main()
{
    int choice;
    cout << "\t\t\t\t-----------------------WELCOME-------------------------" << endl;
    note();
    do
    {
        print();
    lable:
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            vector<int> msg;
            int n;

            cout << "Enter size of msg: ";
            cin >> n;

            cout << "Enter msg bits: " << endl;
            for (int i = 0; i < n; i++)
            {
                int k;
            bin:
                k = 0;
                cin >> k;
                if (k != 0 && k != 1)
                {
                    cout << "Please enter binary number..!!" << endl;
                    goto bin;
                }
                msg.push_back(k);
            }
            HammingCode(msg);
        }

        else if (choice == 2)
        {
            int n;
        csize:
            cout << "Enter size of data: ";
            cin >> n;

            if (n <= 2)
            {
                cout << "Please enter size more than 2..!!!" << endl;
                goto csize;
            }

            vector<int> data(n + 1, 0);
            data[0] = 8;
            cout << "Enter data bits: " << endl;
            for (int i = 1; i <= n; i++)
            {
                int k;
            c_bin:
                k = 0;
                cin >> k;
                if (k != 1 && k != 0)
                {
                    cout << "Please enter binary value..!!" << endl;
                    goto c_bin;
                }

                data[i] = k;
            }

            ErrorDetection(data);
            cout << endl;
        }

        else if (choice != 3)
        {
            cout << "Please Enter valid value..!" << endl;
            goto lable;
        }

        cout << "\t\t\t\t-----------------------------------------------------" << endl
             << endl;

    } while (choice != 3);

    return 0;
}