

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID 
static const Worker_T INVALID_ID = (unsigned int)-1;


// Prototypes for helper functions
bool scheduleHelper(
	 	const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
		size_t currentDay,
		size_t currentWorkers
);

bool isValid(
	 	const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
		size_t currentDay,
		size_t currentWorkers,
		Worker_T id
);

// Implementations of functions

/* 
 * Function checking if the current
 * worker is a valid choice given
 * requirements set by the prompt
 */

bool isValid(
	 	const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
		size_t currentDay,
		size_t currentWorkers,
		Worker_T id
)
{
	size_t count = 0;
	// Check how many times they have been scheduled thus far
	for (size_t i = 0; i < sched.size(); ++i)
	{
		for (size_t j = 0; j < dailyNeed; ++j)
		{
			if (sched[i][j] == id)
			{
				count++;
			}
		}
	}

	// If the count is the wrong size, then return false
	return (count <= maxShifts);
}

/* 
 * Primary helper function,
 * calling isValid() and 
 * implementing backtracing
 */
bool scheduleHelper(
	 	const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
		size_t currentDay,
		size_t currentWorkers
)

// currentDay = row for sched
// currentWorkers = col for sched
{
	// Base Case: we reached the end of the schedule
	if (currentDay == sched.size())
	{
		return true;
	}

		// Trying to schedule each worker
		for (size_t i = 0; i < avail[0].size(); ++i)
		{
			if (avail[currentDay][i]){
				// If this worker is already scheduled for today, move on
				if (find(sched[currentDay].begin(), sched[currentDay].end(), i) != sched[currentDay].end())
				{
					continue;
				}

				// Schedule worker and test if valid for this and following iteration
				sched[currentDay][currentWorkers] = i;			
				if (isValid(avail, dailyNeed, maxShifts, sched, currentDay, currentWorkers, i))
				{
					// If we are at the end of column, that means the next call must start on new row (day + 1)
					if (currentWorkers == dailyNeed - 1)
					{
						if (scheduleHelper(avail, dailyNeed, maxShifts, sched, currentDay + 1, 0))
						{
							return true;
						}
					}
					// If we still have space in this row, increment the column (worker + 1)
					else
					{
						if (scheduleHelper(avail, dailyNeed, maxShifts, sched, currentDay, currentWorkers + 1))
						{
							return true;
						}
					}
				}
			}
		}

		// If not valid after trying all workers, backtrace
		sched[currentDay][currentWorkers] = INVALID_ID;
		return false;
}

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();

		// Initializing the sched matrix of size n x d
		std::vector<Worker_T> init(dailyNeed, INVALID_ID);
    for (size_t row = 0; row < avail.size(); ++row)
    {
				sched.push_back(init);
    }

    // Call helper and return it's value
		return scheduleHelper(avail, dailyNeed, maxShifts, sched, 0, 0);

}

