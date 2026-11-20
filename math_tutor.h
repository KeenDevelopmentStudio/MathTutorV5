/******************************************************************************************************************
* Program......: MathTutorV5
 * Programmer(s): Treven Keen, Connor Colvard
 * Section(s)...: Section 3
 * Date.........: 2026-11-18
 * GitHub Repo..: https://github.com/KeenDevelopmentStudio/MathTutorV5
 * Description..:
   This file includes all the prototypes for the math tutor functions.
 *****************************************************************************************************************/
#ifndef MATHTUTORV5_MATH_TUTOR_H
#define MATHTUTORV5_MATH_TUTOR_H
#include <string>
#include <vector>

using namespace std;

// Define Functions
void DisplayGameIntro();
string GetUserName();
vector<int> GenerateRandomQuestion(int MathLevel, string UserName);
int GetNumericValue();
bool GiveThreeAttempts(string UserName, vector<int> &CurrentQuestion);
void CheckForLevelChange(int &TotalCorrect, int &TotalIncorrect, int &MathLevel);
string AskToPlayAgain();
void DisplaySummaryReport(const vector<vector<int> > &QuestionsVector);

#endif //MATHTUTORV5_MATH_TUTOR_H
