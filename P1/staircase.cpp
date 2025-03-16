#include <vector>

using namespace std;

class Staircase
{
private:
    vector<pair<int, int>> steps;
    unsigned long &counter;

public:
    Staircase(pair<int, int> step, unsigned long &counter) : counter(counter)
    {
        steps = vector<pair<int, int>>();
        steps.push_back(step);
    }

    // Assumption: steps are added in DESCENDING order on X.
    // So no point with a higher X value will be added after a point with a lower X value.
    void add_step(pair<int, int> step)
    {
        pair<int, int> latest;

        try
        {
            latest = latest_step();
        }
        catch (const char *msg)
        {
            // First step being added, no validation needed
            steps.push_back(step);
            return;
        }

        counter += 1;
        // Validate the new step's x-value
        if (step.first > latest.first)
        {
            throw "New step's X value is not less than the latest step's X value.";
        }

        steps.push_back(step);
    }

    pair<int, int> latest_step()
    {
        counter += 1;
        if (steps.size() == 0)
        {
            throw "No steps added yet.";
        }

        return steps.back();
    }

    int size()
    {
        return steps.size();
    }

    pair<int, int> get_step(int index)
    {
        return steps[index];
    }
};