#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>


int main()
{
    std::vector<int> data = {5, 16, 4, 7};   
    std::vector<int> index(data.size(), 0);
    
    for (int i = 0 ; i != index.size() ; i++)
    {
        index[i] = i;
    }

    sort
    (
        index.begin(), index.end(),
        [&](const int& a, const int& b) {
            return (data[a] < data[b]);
        }
    );

    for (int i = 0 ; i != index.size() ; i++)
    {
        std::cout << index[i] << std::endl;
    }

    return 0;
}

