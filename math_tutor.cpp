/******************************************************************************************************************
* Program......: MathTutorV5
 * Programmer(s): Treven Keen, Connor Colvard
 * Section(s)...: Section 3
 * Date.........: 2026-11-18
 * GitHub Repo..: https://github.com/KeenDevelopmentStudio/MathTutorV5
 * Description..:
   This file includes all the functions for the math tutor.
 *****************************************************************************************************************/
// Include Libraries
#include <iostream> // Adds cin and cout Commands, PLUS Left and Right Alignments
#include <string> // Allows for manipulating strings
#include <limits> // Allows for limiting of values with cin.ignore
#include <cstdlib> // Adds randomization
#include <cctype> // Adds character handling like tolower Commands
#include <vector> // Allows for use of Vectors
#include <iomanip> // Allows for setw Command

// Set Default Namespace
using namespace std;

// Initial Variables
/// Constants
const int MaxAttempts = 3;
const int LEVEL_RANGE_CHANGE = 10;
int UserAnswer = 0;

/// Equation Type Variables
enum MathType { MT_ADD, MT_SUBTRACT, MT_MULTIPLY, MT_DIVIDE };

/**************************************
 * Display ASCII Title and Math Facts
 **************************************/
void DisplayGameIntro() {

    cout << setfill('*') << setw(78) << "*" << endl; // Make a Line
    cout << R"(
         __  __       _   _   _____      _           __     ______
        |  \/  | __ _| |_| |_|_   _|   _| |_ ___  _ _\ \   / / ___|
        | |\/| |/ _` | __| '_ \| || | | | __/ _ \| '__\ \ / /|___ \
        | |  | | (_| | |_| | | | || |_| | || (_) | |   \ V /  ___) |
        |_|  |_|\__,_|\__|_| |_|_| \__,_|\__\___/|_|    \_/  |____/ )" << endl << endl;
    cout << setfill('*') << setw(78) << "*" << endl; // Make a Line
    cout << "*    Welcome to Version 5 of the Awesome Math Tutor!        *" << endl;
    cout << setfill('*') << setw(78) << "*" << endl; // Make a Line

    // Math Facts
    cout << "   Un-fun math rules:" << endl << endl;
    cout << "* No fun allowed, only mathematical equations." << endl;
    cout << "* Laughing results in weekend detention." << endl;
    cout << "* You must recite 1000 digits of Pi numbers at the start of each class period." << endl;
    cout << "* If it seems easy, you're wrong." << endl;
    cout << setfill('*') << setw(78) << "*" << endl; // Make a Line
    return;
}
// end of DisplayGameIntro

/**************
 *gets username
 **************/
string GetUserName() {
    string UserName = "?";

    cout << "Please enter your Username:" << endl;;
    getline(cin, UserName);
    cout << "Welcome to the Math Tutor " << UserName << "!" << endl;

    return UserName;
}
// End of GetUserName

/****************************************************************************
// Generates 3 random numbers for questions and stores the values in a vector
*****************************************************************************/
vector<int> GenerateRandomQuestion(int MathLevel, string UserName) {
    /// Math Equation Variables
    enum MathOperatorType { MT_ADD, MT_SUBTRACT, MT_MULTIPLY, MT_DIVIDE };
    int LeftNum;
    int RightNum;
    int MathType;
    int CorrectAnswer;
    char MathOperator;

    /// Math Leveling Variables
    int CurrentRange = MathLevel + LEVEL_RANGE_CHANGE;

    /// Answer and Temporary Storage
    int Temp;

    // Math Problem Variables
    LeftNum = rand() % (CurrentRange) + 1;
    RightNum = rand() % (CurrentRange) + 1;

    // Math Operator Choosing
    MathType = static_cast<MathOperatorType>(rand() % 4);

    // Switch
    switch (MathType) {
        case MT_ADD:
            // Addition
            MathOperator = '+';
            CorrectAnswer = LeftNum + RightNum;
            break;

        case MT_SUBTRACT:
            // Subtraction
            MathOperator = '-';

            // Left Number must be greater than Right Number
            if (LeftNum < RightNum) {
                Temp = LeftNum;
                LeftNum = RightNum;
                RightNum = Temp;
            }
            CorrectAnswer = LeftNum - RightNum;
            break;

        case MT_MULTIPLY:
            // Multiplication
            MathOperator = 'x';
            CorrectAnswer = LeftNum * RightNum;
            break;

        case MT_DIVIDE:
            // Division
            /// No Fractions Allowed
            MathOperator = '/';
            CorrectAnswer = LeftNum; // Set Correct Answer to Old Left Number
            LeftNum *= RightNum; // Set New Left Number to Dividend and Right Number to Divisor
            break;

        default:
            // Error Handling
            cout << "Invalid question type: " << MathType << endl;
            cout << "Program ended with an error -1" << endl;
            cout << "Please report this problem to the developers." << endl;
            exit(-1); //ends program due to error
    }

    // Declare 1D vector
    return {MathLevel, LeftNum, MathOperator, RightNum, CorrectAnswer};
}
// End of GenerateRandomNumber

/**********************************************
 *Gets user's answer and checks for valid inputs
 **********************************************/
int GetNumericValue() {
    int UserAnswer = 0;

    // Ensure Correct Answer Type (a number)
    while (!(cin >> UserAnswer)) {
        cin.clear(); // Clear cin error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore Max Input up to \n
        cout << "Invalid input. Please enter a number: " << endl << endl;
    }
    return UserAnswer;
}
// end of GetNumericValue

/*********************************************************************************************************
* Use a forloop to give them three attempts, checks for user's accuracy, and extracts data from the vector
**********************************************************************************************************/
bool GiveThreeAttempts(string UserName, vector<int> &CurrentQuestion) {
    int UserAnswer = 0;
    bool IsCorrect = false;

    // Extract Data from Vector
    int MathLevel = CurrentQuestion.at(0);
    int LeftNum = CurrentQuestion.at(1);
    char MathOperator = static_cast<char>(CurrentQuestion.at(2));
    int RightNum = CurrentQuestion.at(3);
    int CorrectAnswer = CurrentQuestion.at(4);

    // Request Math Answer
    for (int i = 0; i <= MaxAttempts; i++) {
        cout << "[Level #" << MathLevel << "] " << UserName << ", ";
        cout << "what is the answer to " << LeftNum << " " << MathOperator << " " << RightNum << "?" << endl;

        UserAnswer = GetNumericValue();

        /// Correct Answer
        if (UserAnswer == CorrectAnswer) {
            CurrentQuestion.push_back(i + 1);
            cout << "You got it right. Good!" << endl;
            IsCorrect = true;
            break;
        }

        // Incorrect Answer
        if (i == MaxAttempts) {
            // Out of Math Question Attempts
            CurrentQuestion.push_back(0);
            cout << "You got it wrong. Disappointing." << endl;
            cout << "The correct answer was: " << CorrectAnswer << endl;
            cout << "You are a failure..." << endl;
            IsCorrect = false;
        } else {
            // Still Has Math Question Attempts
            cout << "You got it wrong. Disappointing." << endl;
            cout << "You have " << (MaxAttempts - i) << " attempts left." << endl;
        }
    }
    return IsCorrect;
}
// end of GiveThreeAttempts

/***************************************************************************
 *Changes MathLevel and range of possible numbers based on user's accuracy
 **************************************************************************/
void CheckForLevelChange(int &TotalCorrect, int &TotalIncorrect, int &MathLevel) {
    // Leveling Up mathLevel
    int CurrentRange = 10;

    if (TotalCorrect >= 3) {
        MathLevel++; // Increase Level by 1
        TotalCorrect = 0; // Reset Correct Count
        TotalIncorrect = 0; // Reset Incorrect Count
        CurrentRange += LEVEL_RANGE_CHANGE; // Update Range to Match Level
        cout << "You have risen to Math Level " << (MathLevel + LEVEL_RANGE_CHANGE) << endl;
        cout << "Your new range is 0 - " << CurrentRange << endl;
    }

    // Leveling Down mathLevel
    else if (TotalIncorrect >= 3 && MathLevel > 1) {
        MathLevel--; // Decrease Level by 1
        TotalCorrect = 0; // Reset Correct Count
        TotalIncorrect = 0; // Reset Incorrect Count
        CurrentRange -= LEVEL_RANGE_CHANGE; // Update Range to Match LevelK
        cout << "You have fallen to Math Level " << MathLevel << endl;
        cout << "Your new range is 0 - " << CurrentRange << endl;
    }
}
// end of CheckForLevelChange

/*******************************************************************
 *Asks if the user wants to keep playing and checks for valid input
 *******************************************************************/
string AskToPlayAgain() {
    string UserInput = "?";
    while (true) {
                // Request Additional Questions
        cout << "Would you like to continue? (y / yes || n / no): " << endl;

        // Get Answer for Continue Question
        getline(cin, UserInput);

        // Lowercase transition
        for (int i = 0; i < UserInput.size(); i++) {
            UserInput.at(i) = tolower(UserInput.at(i));
        }

        // Decision based on answer
        if (UserInput == "yes" || UserInput == "y" || UserInput == "no" || UserInput == "n") {
            break;
        }

        cout << "Invalid input. Please enter a correct answer (y / yes || n / no): " << endl;
        cout << endl;
    }
    return UserInput;
}
// end of AskToPlayAgain

/******************************************************************************
 * Pulls data from vector to display a summary report of the user's answers
 * It displays the questions, answers, number of attempts, and average accuracy
 * *****************************************************************************/
void DisplaySummaryReport(const vector<vector<int> > &QuestionsVector) {
    // Generate Report
    char MathOperator = 0;
    int LeftNum = 0;
    int RightNum = 0;
    int CorrectAnswer = 0;
    int MathLevel = 1;
    int TotalCorrect = 0;
    int TotalIncorrect = 0;
    int TotalAttempts = 0;
    // Summary Report
    cout << setfill('*') << setw(34) << "*" << endl; // Make a Line
    cout << "         Summary Report" << endl;
    cout << setfill('*') << setw(34) << "*" << endl; // Make a Line
    cout << "Level       Question        Attempt" << endl;
    cout << "----- | ---------------- | ---------" << endl;
    cout << setfill(' '); // Reset setfill()

    // Reset Counters
    TotalCorrect = 0;
    TotalIncorrect = 0;

    // Generate Report
    for (int i = 0; i < QuestionsVector.size(); i++) {
        // Extract Data from Vector
        MathLevel = QuestionsVector.at(i).at(0);
        LeftNum = QuestionsVector.at(i).at(1);
        MathOperator = static_cast<char>(QuestionsVector.at(i).at(2));
        RightNum = QuestionsVector.at(i).at(3);
        CorrectAnswer = QuestionsVector.at(i).at(4);
        TotalAttempts = QuestionsVector.at(i).at(5);

        // cout Summary Report Printing
        cout << "   " << setw(2) << right << MathLevel << " | ";
        cout << setw(3) << right << LeftNum << " ";
        cout << setw(1) << MathOperator << " ";
        cout << setw(3) << left << RightNum << " = ";
        cout << setw(4) << right << CorrectAnswer << " | ";

        // Printing Attempts
        if (TotalAttempts != 0) {
            cout << "    " << TotalAttempts << endl;
            TotalCorrect++; // Increase Correct Count
        } else {
            cout << "Incorrect" << endl;
            TotalIncorrect++; // Increase Incorrect Count
        }
    }

    // Summary Totals
    cout << endl;
    cout << "Total Questions: " << setw(4) << right << QuestionsVector.size() << endl;
    cout << "Total Correct:   " << setw(4) << right << TotalCorrect << endl;
    cout << "Total Incorrect: " << setw(4) << right << TotalIncorrect << endl;
    cout << "Average Correct: " << setw(4) << right << ((TotalCorrect * 100) / QuestionsVector.size()) << "%" << endl <<
            endl;;
}
// end of DisplaySummaryReport