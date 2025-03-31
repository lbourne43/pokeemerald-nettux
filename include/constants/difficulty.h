#ifndef GUARD_DIFFICULTY_CONSTANTS_H
#define GUARD_DIFFICULTY_CONSTANTS_H

enum DifficultyLevel
{
    DIFFICULTY_EASY, // Switch Mode
    DIFFICULTY_NORMAL, // If you rename this, the word "Normal" in fprint_trainers must be replaced with the new difficulty name.
    DIFFICULTY_HARD, // hard parties
    DIFFICULTY_DOUBLES, // doubles parties
    DIFFICULTY_COUNT, 
};

#define DIFFICULTY_MIN 0
#define DIFFICULTY_MAX (DIFFICULTY_COUNT - 1)

#endif // GUARD_DIFFICULTY_CONSTANTS_H
