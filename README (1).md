# MoodMate Part 2: Data Abstraction

A console mood log written in C++. This version adds a MoodTracker class that manages a collection of MoodEntry objects, plus mood labels, an average, and highest and lowest mood lookups.

This is a programming exercise, not a mental health assessment. Use invented example entries only.

## Files

- MoodMate.cpp: the whole program in one file. It contains the MoodEntry class (one day's date, rating, and note), the MoodTracker class (stores up to 20 entries), and main with the menu and user input.

## How to Compile and Run

```bash
g++ -std=c++11 -Wall -Wextra -o MoodMate MoodMate.cpp
./MoodMate
```

## Design Notes

- MoodEntry keeps date, rating, and note private. They are only changed through setDate, setRating, and setNote, and only read through the const getters.
- The 1 to 5 rule lives in one place, MoodEntry::isValidRating. The setter uses it, and main uses it to keep asking until the user types a valid rating. If a bad rating ever reaches the setter or constructor anyway, it is not stored and the neutral rating of 3 is used instead.
- getMoodLabel returns Very Bad, Bad, Okay, Good, or Great, and printEntry shows the label with each entry.
- MoodTracker keeps the entries array and entryCount private. main only creates a MoodEntry and passes it to tracker.addEntry, so main never touches the array.
- displayEntries calls printEntry on each stored entry instead of repeating display code.
- If two entries tie for highest or lowest, the earliest one entered is returned.
- addEntry never overwrites an existing entry. When the tracker is full, main tells the user and skips the prompts.
- Menu input is checked, so non-numeric or out of range choices show a message and ask again.

## Testing Done

- The example run from the assignment (ratings 4 and 5) gives an average of 4.5, highest of 5 (Great), and lowest of 4 (Good).
- Ratings 5, 3, 4, 4 give an average of 4.0.
- All five mood labels match their ratings.
- Ratings of 0, 6, -2, and abc are rejected and re-asked.
- Options 2 to 5 show a helpful message when there are no entries.
- The 21st entry is refused and nothing is overwritten.
- Calling the classes directly confirms that the constructor and setter reject bad ratings without any help from main.
