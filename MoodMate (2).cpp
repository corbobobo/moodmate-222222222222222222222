// ============================================================
// MoodMate, Part 2 - Data Abstraction
// Name: Corbyn Leblanc
//
// A console mood log. A MoodEntry object holds one day's mood
// (date, rating, note). A MoodTracker object manages up to 20
// MoodEntry objects, so main() never touches the storage array
// or any private data directly.
//
// This is a programming exercise, not a mental health assessment.
// Use invented example entries only.
// ============================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

// ============================================================
// MoodEntry class declaration
// ============================================================
class MoodEntry
{
private:
    string date;   // e.g. 10/07/2026 (a nonempty string is sufficient)
    int rating;         // 1 (very bad) through 5 (great)
    string note;   // short single-line description

public:
    // Constructors
    MoodEntry();                                              // "Unspecified", 3, "No note"
    MoodEntry(string date, int rating, string note); // validated through the setters

    // The class owns the rating rule, so other code can ask it
    // instead of repeating the 1-5 check.
    static bool isValidRating(int rating);

    // Mutators (validate their input)
    void setDate(string date);
    void setRating(int rating);
    void setNote(string note);

    // Accessors
    string getDate() const;
    int getRating() const;
    string getNote() const;

    // Returns "Very Bad", "Bad", "Okay", "Good", or "Great"
    string getMoodLabel() const;

    // Prints the entry, including its mood label
    void printEntry() const;
};

// ============================================================
// MoodTracker class declaration
// ============================================================
class MoodTracker
{
private:
    static const int MAX_ENTRIES = 20;

    MoodEntry entries[MAX_ENTRIES];
    int entryCount;

public:
    MoodTracker();

    // Adds an entry. If the tracker is already full, the entry is
    // not stored and nothing is overwritten.
    void addEntry(const MoodEntry& entry);

    // Prints every stored entry using MoodEntry::printEntry().
    void displayEntries() const;

    // Mean of all stored ratings (0.0 if there are no entries).
    double calculateAverage() const;

    // First entry with the highest / lowest rating (a default
    // MoodEntry if there are no entries).
    MoodEntry getHighestMood() const;
    MoodEntry getLowestMood() const;

    int getEntryCount() const;
    int getCapacity() const;
    bool isFull() const;
};

// ============================================================
// MoodEntry member function definitions
// ============================================================

// Default constructor: a usable, empty entry.
MoodEntry::MoodEntry()
    : date("Unspecified"), rating(3), note("No note")
{
}

// Parameterized constructor: reuses the setters so the same
// validation rules apply no matter how an entry is created.
MoodEntry::MoodEntry(string date, int rating, string note)
{
    setDate(date);
    setRating(rating);
    setNote(note);
}

bool MoodEntry::isValidRating(int rating)
{
    return rating >= 1 && rating <= 5;
}

void MoodEntry::setDate(string date)
{
    if (!date.empty())
    {
        this->date = date;
    }
    else
    {
        this->date = "Unspecified";
    }
}

// An invalid rating is never stored. The object falls back to the
// neutral rating of 3 (same rule as MoodMate Part 1).
void MoodEntry::setRating(int rating)
{
    if (isValidRating(rating))
    {
        this->rating = rating;
    }
    else
    {
        this->rating = 3;
    }
}

void MoodEntry::setNote(string note)
{
    if (!note.empty())
    {
        this->note = note;
    }
    else
    {
        this->note = "No note";
    }
}

string MoodEntry::getDate() const
{
    return date;
}

int MoodEntry::getRating() const
{
    return rating;
}

string MoodEntry::getNote() const
{
    return note;
}

string MoodEntry::getMoodLabel() const
{
    switch (rating)
    {
        case 1:  return "Very Bad";
        case 2:  return "Bad";
        case 3:  return "Okay";
        case 4:  return "Good";
        case 5:  return "Great";
        default: return "Okay"; // cannot happen: the setter keeps rating in 1-5
    }
}

void MoodEntry::printEntry() const
{
    cout << "Date: " << date << endl;
    cout << "Mood Rating: " << rating << endl;
    cout << "Mood: " << getMoodLabel() << endl;
    cout << "Note: " << note << endl;
}

// ============================================================
// MoodTracker member function definitions
// ============================================================

MoodTracker::MoodTracker()
{
    entryCount = 0;
}

void MoodTracker::addEntry(const MoodEntry& entry)
{
    if (entryCount < MAX_ENTRIES)
    {
        entries[entryCount] = entry;
        entryCount++;
    }
}

void MoodTracker::displayEntries() const
{
    for (int i = 0; i < entryCount; i++)
    {
        cout << "\nEntry #" << (i + 1) << endl;
        entries[i].printEntry();
    }
}

double MoodTracker::calculateAverage() const
{
    if (entryCount == 0)
    {
        return 0.0;
    }

    int total = 0;
    for (int i = 0; i < entryCount; i++)
    {
        total += entries[i].getRating();
    }

    return static_cast<double>(total) / entryCount;
}

MoodEntry MoodTracker::getHighestMood() const
{
    if (entryCount == 0)
    {
        return MoodEntry();
    }

    int highestIndex = 0;
    for (int i = 1; i < entryCount; i++)
    {
        if (entries[i].getRating() > entries[highestIndex].getRating())
        {
            highestIndex = i;
        }
    }

    return entries[highestIndex];
}

MoodEntry MoodTracker::getLowestMood() const
{
    if (entryCount == 0)
    {
        return MoodEntry();
    }

    int lowestIndex = 0;
    for (int i = 1; i < entryCount; i++)
    {
        if (entries[i].getRating() < entries[lowestIndex].getRating())
        {
            lowestIndex = i;
        }
    }

    return entries[lowestIndex];
}

int MoodTracker::getEntryCount() const
{
    return entryCount;
}

int MoodTracker::getCapacity() const
{
    return MAX_ENTRIES;
}

bool MoodTracker::isFull() const
{
    return entryCount >= MAX_ENTRIES;
}

// ============================================================
// Client program (menu and user input)
// ============================================================

void displayMenu();
int getMenuChoice();
int getRatingInput();
void skipLeftoverNewline();

void addMoodEntry(MoodTracker& tracker);
void viewAllEntries(const MoodTracker& tracker);
void viewAverageMood(const MoodTracker& tracker);
void viewHighestMood(const MoodTracker& tracker);
void viewLowestMood(const MoodTracker& tracker);

int main()
{
    MoodTracker tracker;
    bool running = true;

    while (running)
    {
        displayMenu();
        int choice = getMenuChoice();

        switch (choice)
        {
            case 1: addMoodEntry(tracker);     break;
            case 2: viewAllEntries(tracker);   break;
            case 3: viewAverageMood(tracker);  break;
            case 4: viewHighestMood(tracker);  break;
            case 5: viewLowestMood(tracker);   break;
            case 6:
                cout << "\nThank you for using MoodMate!" << endl;
                running = false;
                break;
        }
    }

    return 0;
}

void displayMenu()
{
    cout << "\n=========================" << endl;
    cout << "       MOODMATE" << endl;
    cout << "=========================" << endl;
    cout << "1. Add Mood Entry" << endl;
    cout << "2. View All Entries" << endl;
    cout << "3. View Average Mood" << endl;
    cout << "4. View Highest Mood" << endl;
    cout << "5. View Lowest Mood" << endl;
    cout << "6. Exit" << endl;
    cout << "=========================" << endl;
}

// Reads a menu choice from 1 to 6. Non-numeric input is cleared and
// re-asked so the program never gets stuck. If input ends entirely
// (end-of-file), this returns 6 so the program can exit cleanly.
int getMenuChoice()
{
    int choice;

    while (true)
    {
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.eof())
        {
            cout << "\nNo more input detected. Exiting." << endl;
            return 6;
        }

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number from 1 to 6." << endl;
            continue;
        }

        if (choice < 1 || choice > 6)
        {
            cout << "Invalid choice. Please enter a number from 1 to 6." << endl;
            continue;
        }

        return choice;
    }
}

// Keeps asking until the user enters a rating the MoodEntry class
// accepts (1-5). The rule itself lives in MoodEntry::isValidRating.
int getRatingInput()
{
    int rating;

    while (true)
    {
        cout << "Enter mood rating (1-5): ";
        cin >> rating;

        if (cin.eof())
        {
            cout << "\nNo more input detected. Using a neutral rating of 3." << endl;
            return 3;
        }

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a whole number from 1 to 5." << endl;
            continue;
        }

        if (!MoodEntry::isValidRating(rating))
        {
            cout << "Invalid rating. The rating must be between 1 and 5." << endl;
            continue;
        }

        return rating;
    }
}

// Discards one leftover newline (from an earlier cin >>) before a
// getline() call. Safe to call whether or not a newline is waiting.
void skipLeftoverNewline()
{
    if (cin.peek() == '\n')
    {
        cin.ignore();
    }
}

void addMoodEntry(MoodTracker& tracker)
{
    cout << endl;

    if (tracker.isFull())
    {
        cout << "The mood log is full (" << tracker.getCapacity()
             << " entries). Cannot add another entry." << endl;
        return;
    }

    string date;
    cout << "Enter date: ";
    skipLeftoverNewline();
    getline(cin, date);

    int rating = getRatingInput();

    string note;
    cout << "Enter note: ";
    skipLeftoverNewline();
    getline(cin, note);

    // Build the entry, then give it to the tracker.
    MoodEntry today(date, rating, note);
    tracker.addEntry(today);

    cout << "\nMood entry added!" << endl;
}

void viewAllEntries(const MoodTracker& tracker)
{
    cout << "\n----- All Entries -----" << endl;

    if (tracker.getEntryCount() == 0)
    {
        cout << "No entries have been added yet." << endl;
        return;
    }

    tracker.displayEntries();
}

void viewAverageMood(const MoodTracker& tracker)
{
    cout << endl;

    if (tracker.getEntryCount() == 0)
    {
        cout << "No entries yet, so an average cannot be calculated." << endl;
        return;
    }

    cout << fixed << setprecision(1);
    cout << "Average Mood: " << tracker.calculateAverage() << endl;
}

void viewHighestMood(const MoodTracker& tracker)
{
    cout << "\n----- Highest Mood -----" << endl;

    if (tracker.getEntryCount() == 0)
    {
        cout << "No entries have been added yet." << endl;
        return;
    }

    MoodEntry highest = tracker.getHighestMood();
    highest.printEntry();
}

void viewLowestMood(const MoodTracker& tracker)
{
    cout << "\n----- Lowest Mood -----" << endl;

    if (tracker.getEntryCount() == 0)
    {
        cout << "No entries have been added yet." << endl;
        return;
    }

    MoodEntry lowest = tracker.getLowestMood();
    lowest.printEntry();
}
