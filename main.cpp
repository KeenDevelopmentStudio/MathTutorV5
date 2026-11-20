/******************************************************************************************************************
 * Program......: MathTutorV5
 * Programmer(s): Treven Keen, Connor Colvard
 * Section(s)...: Section 3
 * Date.........: 2026-11-18
 * GitHub Repo..: https://github.com/KeenDevelopmentStudio/MathTutorV5
 * Description..:
    This program asks the user what their name is and welcomes them!
    It will also tell them some math fun facts and present them with some cool ASCII art.
    They will be asked random math questions.
    These questions will get easier or harder based on performance.
    This program will now save answers and questions to display at the end.
 *****************************************************************************************************************/

// Include Libraries
#include <iostream> // Adds cin and cout Commands, PLUS Left and Right Alignments
#include <ctime> // Adds usage for time(0)
#include <string> // Allows for manipulating strings
#include <cstdlib> // Adds randomization
#include <vector> // Allows for use of Vectors

#include "math_tutor.h" // Adds the functions

// Set Default Namespace
using namespace std;

int main() {
    /// THE VECTORRRRRR
    vector<vector<int> > AllQuestions;

    /// User's Input Strings
    string UserName;
    string UserInput = "?";

    /// Math Leveling Variables
    int MathLevel = 1;
    int TotalCorrect = 0;
    int TotalIncorrect = 0;

    // Title Display
    DisplayGameIntro();

    // Get Username
    UserName = GetUserName();

    // Set Seed
    srand(time(0));

    // Math Loop
    do {
        cout << endl;

        vector<int> CurrentQuestion = GenerateRandomQuestion(MathLevel, UserName);

        bool IsCorrect = GiveThreeAttempts(UserName, CurrentQuestion);

        if (IsCorrect)
            TotalCorrect++;
        else
            TotalIncorrect++;

        // Updating Questions Vector
        AllQuestions.push_back(CurrentQuestion);

        CheckForLevelChange(TotalCorrect, TotalIncorrect, MathLevel);

        UserInput = AskToPlayAgain();

    } while (UserInput == "yes" || UserInput == "y");


    DisplaySummaryReport(AllQuestions);

    cout << "Thank you for using MathTutorV5 to study! V6 is coming soon!" << endl;
    return 0;
    // End of main
}