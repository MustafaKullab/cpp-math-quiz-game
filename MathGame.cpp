#include <iostream>
using namespace std;

enum enQuestionLevel {Easy = 1 , Med = 2 , Hard = 3 , Mix = 4};
enum enOperationType {Add = 1 , Sub = 2 , Mul = 3 , Div = 4 , MixOp = 5};

struct stQuestion {

    short Number1 = 0;
    short Number2 = 0;
    enQuestionLevel QuestionLevel;
    enOperationType OperationType;
    short CorrectAnswer;
    short PlayerAnswer;
    bool AnswerResult;

};

struct stQuizz {
    
    stQuestion QuestionsList[100];
    short NumberOfQuestions;
    enQuestionLevel QuestionsLevel;
    enOperationType OperationType;
    short NumberOfRightAnswers = 0;
    short NumberOfWrongAnswers = 0;
    bool IsPass;

};

void ResetScreen(){

    system("cls");
    system("Color 0F");

}


short ReadHowManyQuestions(){

    int Questions;

    do {

        cout << "How Many Questions do you want to answer ? (1 to 10) ";
        cin >> Questions;
    
    } while(Questions < 1 || Questions > 10);

    return Questions;

}

enQuestionLevel ReadQuestionsLevel(){

    short Level;

    do{

        cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
        cin >> Level;

    } while(Level < 1 || Level > 4);

    return (enQuestionLevel)Level;

}

enOperationType ReadOperationType(){

    short OperationType;

    do{

        cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
        cin >> OperationType;

    } while(OperationType < 1 || OperationType > 5);

    return (enOperationType)OperationType;

}

short RandomNumber(short From , short To){

    return rand() % (To - From + 1) + From;

}


enOperationType GenerateRandomOperationType(){

    return (enOperationType)RandomNumber(1,4);

}

short SimpleCalculator(short Number1 , short Number2 , enOperationType OpType){

    switch(OpType){
        case enOperationType::Add:
            return Number1 + Number2;
            break;
            
        case enOperationType::Sub:
            return Number1 - Number2;
            break;
            
        case enOperationType::Mul:
            return Number1 * Number2;
            break;
            
        case enOperationType::Div:
            return Number1 / Number2;
            break;
        
            default:
            return Number1 + Number2;

    }

}


stQuestion GenerateQuestion(enQuestionLevel QuestionLevel , enOperationType OperationType){

    stQuestion Question;
    enOperationType OpType;

    if(QuestionLevel == enQuestionLevel::Mix){

        QuestionLevel = (enQuestionLevel)RandomNumber(1,3);

    }

    if(OperationType == enOperationType::MixOp){

        OpType = GenerateRandomOperationType();

    }

    Question.OperationType = OpType;

    switch(QuestionLevel){
        case enQuestionLevel::Easy:
            Question.Number1 = RandomNumber(1,10);
            Question.Number2 = RandomNumber(1,10);

            Question.QuestionLevel = QuestionLevel;
            break;

        case enQuestionLevel::Med:
            Question.Number1 = RandomNumber(10,50);
            Question.Number2 = RandomNumber(10,50);

            Question.QuestionLevel = QuestionLevel;
            break;

        case enQuestionLevel::Hard:
            Question.Number1 = RandomNumber(50,100);
            Question.Number2 = RandomNumber(50,100);

            Question.QuestionLevel = QuestionLevel;
            break;
    }

    switch(Question.OperationType){
        case enOperationType::Add:
            Question.CorrectAnswer = SimpleCalculator(Question.Number1 , Question.Number2 , Question.OperationType);
            return Question;
            break;

        case enOperationType::Sub:
            Question.CorrectAnswer = SimpleCalculator(Question.Number1 , Question.Number2 , Question.OperationType);
            return Question;
            break;

        case enOperationType::Mul:
            Question.CorrectAnswer = SimpleCalculator(Question.Number1 , Question.Number2 , Question.OperationType);
            return Question;
            break;

        case enOperationType::Div:
            Question.CorrectAnswer = SimpleCalculator(Question.Number1 , Question.Number2 , Question.OperationType);
            return Question;
            break;
    }

    return Question;

}

void GenerateQuestionsList(stQuizz& Quizz){

    for(short Question = 0 ; Question < Quizz.NumberOfQuestions ; Question++){

        Quizz.QuestionsList[Question] = GenerateQuestion(Quizz.QuestionsLevel , Quizz.OperationType);

    }

}

string GetOperationTypeSymbol(enOperationType OpType){

    string ArrayOfOperationTypes[5] = {"+" , "-" , "X" , "/" , "Mix"};
    return ArrayOfOperationTypes[OpType - 1];

}

void PrintTheQuestion(stQuizz Quizz , short Question){

    cout << "Question [" << Question + 1 << "/" << Quizz.NumberOfQuestions << "]\n";
    cout << Quizz.QuestionsList[Question].Number1 << endl;
    cout << Quizz.QuestionsList[Question].Number2 << " ";
    cout << GetOperationTypeSymbol(Quizz.QuestionsList[Question].OperationType) << endl;
    cout << "--------------\n";

}


void SetColorScreen(bool IsCorrect){

    if(IsCorrect){

        system("Color 2F");
        
    } else {

        system("Color 4F");
        
    }
}



void CorrectAnswer(stQuizz& Quizz , short Question){
    
    cout << Quizz.QuestionsList[Question].PlayerAnswer << endl;

    if(Quizz.QuestionsList[Question].CorrectAnswer != Quizz.QuestionsList[Question].PlayerAnswer){

        cout << "Wrong Answer :-(\n";
        cout << "The Right Answer is: " << Quizz.QuestionsList[Question].CorrectAnswer << endl << endl;
        Quizz.QuestionsList[Question].AnswerResult = false;
        Quizz.NumberOfWrongAnswers++;
        
    } else {
        
        cout << "Right Answer :-)\n\n";
        Quizz.QuestionsList[Question].AnswerResult = true;
        Quizz.NumberOfRightAnswers++;

    }

    SetColorScreen(Quizz.QuestionsList[Question].AnswerResult);
    Quizz.IsPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);

}


short ReadPlayerAnswer(){
    short Answer;
    cin >> Answer;
    return Answer;
}


void AskAndCorrectQUestionsAnswer(stQuizz& Quizz){

    for(short Question = 0; Question < Quizz.NumberOfQuestions ; Question++){

        PrintTheQuestion(Quizz , Question);

        Quizz.QuestionsList[Question].PlayerAnswer = ReadPlayerAnswer();

        CorrectAnswer(Quizz , Question);

    }

}

void PrintFinalResult(bool Pass){

    if(Pass){

        cout << "Final Result Is PASS :-)\n";

    } else {
        
        cout << "Final Result Is FAIL :-(\n";

    }

    SetColorScreen(Pass);

}

string GetQuestionLevel(enQuestionLevel QuestionLevel){

    string ArrayOfLevel[4] = {"Easy" , "Med" , "Hard" , "Mix"};
    return ArrayOfLevel[QuestionLevel - 1];

}


void PrintFinalResultOfQuizz(stQuizz Quizz){

    PrintFinalResult(Quizz.IsPass);

    cout << "------------------------------------\n";
    cout << "Number Of Questions     : " << Quizz.NumberOfQuestions << endl;
    cout << "Questions Level         : " << GetQuestionLevel(Quizz.QuestionsLevel) << endl;
    cout << "OpType                  : " << GetOperationTypeSymbol(Quizz.OperationType) << endl;
    cout << "Number Of Right Answers : " << Quizz.NumberOfRightAnswers << endl;
    cout << "Number Of Wrong Answers : " << Quizz.NumberOfWrongAnswers << endl;
    cout << "------------------------------------\n";   

}

void PlayMathGame(){

    stQuizz Quizz;

    Quizz.NumberOfQuestions = ReadHowManyQuestions();
    Quizz.QuestionsLevel = ReadQuestionsLevel();
    Quizz.OperationType = ReadOperationType();

    GenerateQuestionsList(Quizz);
    AskAndCorrectQUestionsAnswer(Quizz);
    PrintFinalResultOfQuizz(Quizz);

}


void StartGame(){

    string PlayAgain = "Y";

    do {

       ResetScreen(); 
       PlayMathGame();

       cout << "Do you want to play again ? ";
       cin >> PlayAgain;

    } while(PlayAgain == "Y" || PlayAgain == "y");

}


int main(){
 
    srand((unsigned)time(NULL));

    StartGame();

}