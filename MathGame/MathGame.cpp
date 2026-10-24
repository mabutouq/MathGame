
#include <iostream>
#include <cstdlib>    
#include <ctime>      
using namespace std;

enum enQuestionLevel { Easy = 1, Med = 2, Hard = 3, MixLevel = 4 };
enum enOperation { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOperation = 5 };

struct stQuestion
{
    int Number1 = 0, Number2 = 0;
    enOperation OperationType;
    enQuestionLevel QuestionLevel;
    int CorrectAnswer = 0, PlayerAnswer = 0;
    bool AnswerResult = false;

};
struct stQuiz
{
    stQuestion QuestionList[100];
    short NumberOfQuestions;

    enQuestionLevel QuestionLevel;
    enOperation OpType;
    short NumberOfRightAnswers = 0, NumberOfWrongAnswers = 0;
    bool isPass = false;

};

int RandomNumber(int From, int To)
{
    int RandNum = rand() % (To - From + 1) + From;
    return RandNum;
}
string GetOpTypeSymbol(enOperation OpType)
{
    switch (OpType)
    {
    case enOperation::Add:
        return "+";
    case enOperation::Sub:
        return "-";
    case enOperation::Mul:
        return "x";
    case enOperation::Div:
        return "/";
    default:
        return "Mix";
    }
}
void SetScreenColor(bool Right)
{
    if (Right)
        system("color 2F"); 
    else
    {
        system("color 4F"); 
        cout << "\a";
    }
}
short ReadHowManyQuestions()
{
    short NumberOfQuestions;

    do
    {
        cout << "How many questions do you want to answer? ";
        cin >> NumberOfQuestions;

    } while (NumberOfQuestions < 1 || NumberOfQuestions>10);

    return NumberOfQuestions;
}
string GetQuestionLevelText(enQuestionLevel QuestionLevel)
{
    string arrQuestionLevelText[4] = { "Easy","Med","Hard","Mix" };
    return arrQuestionLevelText[QuestionLevel - 1];
}
enQuestionLevel ReadQuestionLevel()
{
    short QuestionLevel = 0;

    do
    {
        cout << "Enter Questions Level: Easy = 1, Med = 2, Hard = 3, Mix = 4 ? ";
        cin >> QuestionLevel;
    } while (QuestionLevel < 1 || QuestionLevel > 4);

    return (enQuestionLevel)QuestionLevel;
}
enOperation ReadOperationType()
{
    short OpType;
    do
    {
        cout << "Enter Operation type: Add = 1, Sub = 2, Mul = 3, Div = 4, Mix = 5 ? ";
        cin >> OpType;

    } while (OpType < 1 || OpType > 5);

    return (enOperation)OpType;
}

int SimpleCalculator(int Number1, int Number2, enOperation OpType)
{
    switch (OpType)
    {
    case enOperation::Add:
        return Number1 + Number2;
    case enOperation::Div:
        return Number1 / Number2;
    case enOperation::Mul:
        return Number1 * Number2;
    case enOperation::Sub:
        return Number1 - Number2;
    default:
        return Number1 + Number2;
    }

}
enOperation GetRandomOperationType()
{
    int Op = RandomNumber(1, 4);
    return (enOperation)Op;
}
stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperation OpType)
{
    stQuestion Question;

    if (QuestionLevel == enQuestionLevel::MixLevel)
        QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);
    if (OpType == enOperation::MixOperation)
        OpType = GetRandomOperationType();

    Question.OperationType = OpType;

    switch (QuestionLevel)
    {
    case enQuestionLevel::Easy:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;
    case enQuestionLevel::Med:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;
    case enQuestionLevel::Hard:
        Question.Number1 = RandomNumber(50,100);
        Question.Number2 = RandomNumber(50,100);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;
    }

    return Question;

}
void GenerateQuizQuestions(stQuiz& Quiz)
{
    for (short Question = 0; Question < Quiz.NumberOfQuestions; Question++)
    {
        Quiz.QuestionList[Question] = GenerateQuestion(Quiz.QuestionLevel, Quiz.OpType);
    }
}
int ReadQuestionAnswer()
{
    int Answer = 0;
    cin >> Answer;
    return Answer;
}
void PrintTheQuestion(stQuiz& Quiz, short QuestionNumber)
{
    cout << "\n";
    cout << "Question [" << QuestionNumber + 1 << "/" << Quiz.NumberOfQuestions << "]\n\n";
    cout << Quiz.QuestionList[QuestionNumber].Number1 << endl;
    cout << Quiz.QuestionList[QuestionNumber].Number2 << " ";
    cout << GetOpTypeSymbol(Quiz.QuestionList[QuestionNumber].OperationType);
    cout << "\n---------";
}
void CorrectQuestionAnswer(stQuiz& Quiz, short QuestionNumber)
{
    if (Quiz.QuestionList[QuestionNumber].PlayerAnswer != Quiz.QuestionList[QuestionNumber].CorrectAnswer)
    {
        Quiz.QuestionList[QuestionNumber].AnswerResult = false;
        Quiz.NumberOfWrongAnswers++;

        cout << "Wrong Answer :-(\n";
        cout << "The right answer is " << Quiz.QuestionList[QuestionNumber].CorrectAnswer << endl;
    }
    else
    {
        Quiz.QuestionList[QuestionNumber].AnswerResult = true;
        Quiz.NumberOfRightAnswers++;
        cout << "Right Answer :-)\n";
    }
    cout << endl;
    SetScreenColor(Quiz.QuestionList[QuestionNumber].AnswerResult);

}
void AskAndCorrectQuestionListAnswers(stQuiz& Quiz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quiz.NumberOfQuestions; QuestionNumber++)
    {
        PrintTheQuestion(Quiz, QuestionNumber);
        Quiz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
        CorrectQuestionAnswer(Quiz, QuestionNumber);
    }

    Quiz.isPass = (Quiz.NumberOfRightAnswers >= Quiz.NumberOfWrongAnswers);
}


string GetFinalResultsText(bool Pass)
{
    if (Pass)
        return "Pass :-)";
    else
        return "Fail :-(";
}
void PrintQuizResults(stQuiz Quiz)
{
    cout << "\n";
    cout << "-------------------------------------\n\n";
    cout << "Final Result is " << GetFinalResultsText(Quiz.isPass);
    cout << "\n-----------------------------------\n\n";

    
    cout << "Number of questions : " << Quiz.NumberOfQuestions << endl;
    cout << "Question level      : " << GetQuestionLevelText(Quiz.QuestionLevel) << endl;
    cout << "Op Type             : " << GetOpTypeSymbol(Quiz.OpType) << endl;
    cout << "Number of right answers        : " << Quiz.NumberOfRightAnswers << endl;
    cout << "Number of wrong answers    : " << Quiz.NumberOfWrongAnswers << endl;
    cout << "------------------------------------------\n";


}
void PlayMathGame()
{
    stQuiz Quiz;
    Quiz.NumberOfQuestions = ReadHowManyQuestions();
    Quiz.QuestionLevel = ReadQuestionLevel();
    Quiz.OpType = ReadOperationType();

    GenerateQuizQuestions(Quiz);
    AskAndCorrectQuestionListAnswers(Quiz);
    PrintQuizResults(Quiz);

}
void ResetScreen()
{
    system("cls");
    system("color 0F");
}
void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        ResetScreen();
        PlayMathGame();

        cout << "\nDo you want to play again ? Y/N ? ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');

}


int main()
{
    srand((unsigned)time(NULL));

    StartGame();


    return 0;
}
