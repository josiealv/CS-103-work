//
//  main.cpp
//  recursive_binsearch_peak_value
//
//  Created by Josie Alvarez on 2/23/19.
//  Copyright © 2019 Josie Alvarez. All rights reserved.
//

#include <iostream>
using namespace std;
int binSearch (int n, int a []/*, int i */)
{
    if (n==1)
    {
        return 0;
    }
    else
    {
        int mid = (n-1)/2;
        
        if (a[mid]>a[mid+1] && a[mid]>a[mid-1])
        {
            return mid;
        }
        if (a[mid]<a[mid-1])
        {
            return binSearch (n-1, a);
        }
        return binSearch (n+1, a);
    }
    
}
int main() {

    int arr[5] = {2,9,8,7,2};
    int peak = binSearch(5, arr);
    
    cout << "Peak is at index: " << peak << endl;
    
    return 0;
}
