#include <iostream>
#include <vector>
#include "layered_staircase.cpp"
using namespace std;

// ASSUMPTION: No duplicates. Points can have duplicate Xs or Ys, but not both.

int main()
{
    int n;
    vector<pair<int, int>> points = vector<pair<int, int>>();

    unsigned long counter = 0;

    int is_test = 0;

    cin >> is_test;

    if (is_test == -1)
    {
        cin >> n;
    }
    else
    {
        n = is_test;
    }

    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        points.push_back(make_pair(x, y));
    }

    // First sort each point on X, and if X is the same, sort on Y
    // X and Y are both sorted on descending order
    sort(points.begin(), points.end(), [&counter](pair<int, int> a, pair<int, int> b)
         {
            counter += 2;
        if (a.first == b.first)
        {
            return a.second > b.second;
        }
        return a.first > b.first; });

    LayeredStaircases ls = LayeredStaircases(counter);

    for (int i = 0; i < n; i++)
    {

        // cout << points[i].first << " " << points[i].second << endl;
        ls.add_point(points[i]);
    }

    if (is_test == -1)
    {
        cout << counter << endl;
    }
    else
    {
        ls.print();
    }
}
