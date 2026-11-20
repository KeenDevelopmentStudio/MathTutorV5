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
#include <limits> // Allows for limiting of values with cin.ignore
#include <cstdlib> // Adds randomization
#include <cctype> // Adds character handling like tolower Commands
#include <vector> // Allows for use of Vectors
#include <iomanip> // Allows for setw Command

// Set Default Namespace
using namespace std;

// Define Functions
void DisplayGameIntro();
string GetUserName();
vector<int> GenerateRandomQuestion(int MathLevel);
int GetNumericValue();
bool GiveThreeAttempts(string UserName, vector<int> &CurrentQuestion);
void CheckForLevelChange(int &TotalCorrect, int &TotalIncorrect, int &MathLevel);
string AskToPlayAgain();
void DisplaySummaryReport(const vector<vector<int> > &QuestionsVector);

// Initial Variables
/// Constants
const int MaxAttempts = 3;
const int LEVEL_RANGE_CHANGE = 10;
int UserAnswer = 0;

int main() {
    /// THE VECTORRRRRR
    vector<vector<int> > AllQuestions;

    /// User's Input Strings
    string UserName;
    string UserInput = "?";

    /// Equation Type Variables
    enum MathType { MT_ADD, MT_SUBTRACT, MT_MULTIPLY, MT_DIVIDE };

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

        vector<int> CurrentQuestion = GenerateRandomQuestion(MathLevel);

        // Ensure Correct Answer Type (a number)
        UserAnswer = GetNumericValue();

        bool IsCorrect = GiveThreeAttempts(UserName, CurrentQuestion);

        if (IsCorrect)
            TotalCorrect++;
        else
            TotalIncorrect++;

        // Updating Questions Vector
        AllQuestions.push_back(CurrentQuestion);

        CheckForLevelChange(TotalCorrect, TotalIncorrect, MathLevel);
        // Request Additional Questions
        cout << "Would you like to continue? (y / yes || n / no): " << endl;

        // Clears Lines From Input Buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');


        UserInput = AskToPlayAgain();
    } while (UserInput == "yes" || UserInput == "y");


    DisplaySummaryReport(AllQuestions);

    cout << "Thank you for using MathTutorV5 to study! V6 is coming soon!" << endl;
    return 0;
    // End of main
}


void DisplayGameIntro() {
    /**************************************
     * Display ASCII Title and Math Facts
     **************************************/

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
}

/********************************
 *gets username
 *****************************/
string GetUserName() {
    string UserName = "?";

    cout << "Please enter your Username:" << endl;;
    getline(cin, UserName);
    cout << "Welcome to the Math Tutor " << UserName << "!" << endl;

    return UserName;
}

// Generates 3 random numbers for questions
vector<int> GenerateRandomQuestion(int MathLevel) {
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
            exit (-1); //ends program due to error
    }
    // Declare 1D vector
    vector<int> CurrentQuestion = {MathLevel, LeftNum, MathOperator, RightNum, CorrectAnswer};
    return CurrentQuestion;
}
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

// Use a forloop to give them three attempts

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


string AskToPlayAgain() {
    string UserInput = "?";
    while (true) {
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
