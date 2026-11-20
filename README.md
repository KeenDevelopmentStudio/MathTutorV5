# Math Tutor V5

<b>Table of Content</b>
- [Summary](#summary)
- [Maintainers](#maintainers)
- [New Features](#New-Features)
- [New Concepts Used](#new-concepts-used)
- [Functions Used](#Functions-Used)
- [Console Output Example](#console-output-example)

## Summary
This is the fifth iteration of the MathTutor program that asks the user basic math questions and 
displays a summary report detailing the user's performance.

## Maintainers
[@KeenDevelopmentStudio](https://github.com/KeenDevelopmentStudio) Treven Keen  
[@RCJColvard-dot](https://github.com/RCJColvard-dot) Connor Colvard

## New Features
 - Divided Main into smaller functions.
 - Stored prototypes in a header file.
 - Stored all functions (except main) in a matching source file.

## New Concepts Used
  - Functions (return type, parameters, arguments, pass by value)
  - Header file and prototypes
  - Source file

## Functions Used
  - void DisplayGameIntro();
  - string GetUserName();
  - vector GenerateRandomNumber(int mathLevel);
  - int GetNumericValue
  - bool GiveThreeAttempts(vector &currentQuestion);
  - void CheckForLevelChange(int &TotalCorrect, int &TotalIncorrect, int & MathLevel)
  - string AskToPlayAgain(); 
  - void DisplaySummaryReport(const vector<vector<int> > &QuestionsVector);

## Console Output Testing Example

Leveling Up:

<img width="550" src="https://github.com/user-attachments/assets/b95f782a-be82-4c43-b72b-ed2ae1489ff6" />


Leveling Down:

<img width="550" src="https://github.com/user-attachments/assets/66e069ae-50c2-4e1a-9994-7d1d6c0fdde7" />


Invalid Number:

<img width="550" src="https://github.com/user-attachments/assets/bd0f6ecf-1bf7-4ed8-a8f5-3c9ab1994b08" />


Invalid Yes/No Input:

<img width="550" src="https://github.com/user-attachments/assets/34102b25-c39b-49d1-8a00-a0f2aaa5dcf3" />


Summary Report:

<img width="550" src="https://github.com/user-attachments/assets/0eb610da-6695-4452-a58e-df28b8d6c880" />

[Back to Top](#math-tutor-v5)
