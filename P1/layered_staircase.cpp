#include <iostream>
#include <vector>
#include "staircase.cpp"

using namespace std;

class LayeredStaircases
{
private:
    vector<Staircase> staircases;
    unsigned long &counter;

    void add_staircase(Staircase s)
    {
        staircases.push_back(s);
    }

public:
    LayeredStaircases(unsigned long &counter) : counter(counter)
    {
        staircases = vector<Staircase>();
    }

    void add_point(pair<int, int> point)
    {
        // INV: staircases[j] = M_j for 0 <= j < k, for the first i points

        // Since each staircase has a pointer to it's latest element, we just need to do a sort on the Y values of each staircase
        // This can also be done very efficiently using binary search!

        int y = point.second;
        Staircase *staircase = nullptr;

        counter += 2;
        // Base case: empty staircase, or no staircase's y is smaller that the point's y
        if (size() == 0 || staircases[size() - 1].latest_step().second >= y)
        {
            Staircase s = Staircase(point, counter);
            add_staircase(s);
            // cout << "Created first staircase: " << point.first << " " << point.second << endl;
            return;
        }

        counter += 1;

        // Base case: the first staircase's y is smaller than the point's y
        if (staircases[0].latest_step().second < y)
        {

            // cout << "Adding to first staircase: " << point.first << " " << point.second << endl;
            staircases[0].add_step(point);
            return;
        }

        int l = 0;
        int r = size() - 1;

        // Only for debugging
        bool print = false;

        if (print)
        {

            cout << "Finding for element " << point.first << " " << point.second << endl;
            cout << "Current staircases:" << endl;

            for (int i = 0; i <= r; i++)
            {
                cout << "--(" << i << ")-- " << staircases[i].latest_step().first << " " << staircases[i].latest_step().second << endl;
            }
        }

        while (l <= r)
        {

            int m = (r + l) / 2;

            if (print)
            {
                cout << "l: " << l << " r: " << r << " m: " << m << endl;
            }

            Staircase s = get_staircase(m);

            if (print)
            {
                cout << "Staircase: " << m << " " << s.latest_step().first << " " << s.latest_step().second << endl;
            }

            if (y > s.latest_step().second)
            {
                r = m - 1;
            }
            else
            {
                l = m + 1;
            }

            counter += 2;
        }

        if (print)
        {
            cout << "Found index: " << l << endl;
            cout << "Staircase " << l << ": " << staircases[l].latest_step().first << " " << staircases[l].latest_step().second << endl;
        }

        if (l > 0)
        {
            // l is the staircase that can accomodate the point
            staircases[l].add_step(point);
        }
        else
        {
            Staircase s = Staircase(point, counter);
            add_staircase(s);
        }

        if (print)
        {

            cout << endl;
        }

        counter += 1;
    }

    Staircase get_staircase(int index)
    {
        return staircases[index];
    }

    int size()
    {
        return staircases.size();
    }

    void print()
    {
        for (int i = 0; i < size(); i++)
        {
            Staircase s = get_staircase(i);
            for (int j = 0; j < s.size(); j++)
            {
                cout << s.get_step(j).first << " " << s.get_step(j).second << endl;
            }
            cout << endl;
        }
    }
};
