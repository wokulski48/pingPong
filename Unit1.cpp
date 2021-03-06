//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int ballHorizontalMove = -7;
int ballVerticalMove = -7;
int round = 0;
int leftUserScore = 0;
int rightUserScore = 0;
int numberOfBounces = 0;
bool isLeftUserRoundWinner = false;

void setInitialObjectsPositions()
{
  Form1->paddleLeft->Left = 100;
  Form1->paddleLeft->Top = (Form1->ClientHeight / 2) - Form1->paddleLeft->Height / 2;

  Form1->paddleRight->Left = Form1->ClientWidth - 100 - Form1->paddleRight->Width;
  Form1->paddleRight->Top = (Form1->ClientHeight / 2) - Form1->paddleRight->Height / 2;

  Form1->ball->Left = (Form1->ClientWidth / 2) - Form1->ball->Width / 2;
  Form1->ball->Top = (Form1->ClientHeight / 2) - Form1->ball->Height / 2;

  Form1->numberOfBouncesLabel->Left = (Form1->ClientWidth / 2) - Form1->numberOfBouncesLabel->Width / 2;
  Form1->numberOfBouncesLabel->Top = (Form1->ClientHeight / 2) - Form1->numberOfBouncesLabel->Height / 2;

  Form1->overallScoreLabel->Left = (Form1->ClientWidth / 2) - Form1->overallScoreLabel->Width / 2;
  Form1->overallScoreLabel->Top = Form1->numberOfBouncesLabel->Top - 100;

  Form1->nextRound->Left = (Form1->ClientWidth / 2) - Form1->nextRound->Width / 2;
  Form1->nextRound->Top = Form1->numberOfBouncesLabel->Top + 100;

  Form1->userMessageLabel->Left = (Form1->ClientWidth / 2) - Form1->userMessageLabel->Width / 2;
  Form1->userMessageLabel->Top = Form1->overallScoreLabel->Top - 100;

  Form1->newGame->Left = (Form1->ClientWidth / 2) - Form1->newGame->Width / 2;
  Form1->newGame->Top = Form1->nextRound->Top + 100;
}

void setObjectsVisibilityOnGameStart()
{
  Form1->numberOfBouncesLabel->Visible = false; 
  Form1->overallScoreLabel->Visible = false;
  Form1->nextRound->Visible = false;
}

AnsiString setUserMessageLabelValue()
{
  AnsiString userMessageLabelValue = "";

  if (isLeftUserRoundWinner == true)
  {
    userMessageLabelValue = "< Lewy gracz zdoby� punkt";
    return userMessageLabelValue;
  }
  else
  {
    userMessageLabelValue = "Prawy gracz zdoby� punkt >";
    return userMessageLabelValue;
  }
}

void miss()
{
  setInitialObjectsPositions();
  
  Form1->ballTimer->Enabled = false;
  Form1->ball->Visible = false;

  Form1->userMessageLabel->Caption = setUserMessageLabelValue();
  Form1->userMessageLabel->Visible = true;

  Form1->overallScoreLabel->Caption = AnsiString(leftUserScore) + " : " + AnsiString(rightUserScore);
  Form1->overallScoreLabel->Visible = true;

  Form1->numberOfBouncesLabel->Caption = "Liczba odbi�: " + AnsiString(numberOfBounces);
  Form1->numberOfBouncesLabel->Visible = true;

  Form1->nextRound->Visible = true;

  Form1->newGame->Visible = true;
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
  Application->MessageBox("Witaj w grze Ping Pong.\n\n"
                          "Lewy gracz steruje wciskaj�c klawisze A oraz Z.\n"
                          "Prawy gracz steruje wciskaj�c strza�ki do g�ry i w d�.\n\n"
                          "Dla urozmaicenia zabawy:\n"
                          "Kiedy odbijesz pi�k� na �rodku paletki, w�wczas zmienisz jej k�t odbicia i pi�ka przyspieszy."
                          "Im d�u�ej odbijasz, tym pi�ka szybciej przemieszcza si�.\n"
                          "Mo�esz dowolnie zmienia pole gry.\n\n"
                          "Mi�ej zabawy!",
                          "Ping Pong", MB_OK);

  setInitialObjectsPositions();

  setObjectsVisibilityOnGameStart();

  userMessageLabel->Caption = "Zagrajmy w ping-ponga!";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::paddleLeftTimerUpTimer(TObject *Sender)
{
  if(paddleLeft->Top > 0) paddleLeft->Top -= 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::paddleLeftTimerDownTimer(TObject *Sender)
{
  if(paddleLeft->Top + paddleLeft->Height < Form1->ClientHeight - 1) paddleLeft->Top += 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if((Key == 'a') || (Key == 'A')) paddleLeftTimerUp->Enabled = true;
  if((Key == 'z') || (Key == 'Z')) paddleLeftTimerDown->Enabled = true;

  if(Key == VK_UP) paddleRightTimerUp->Enabled = true;
  if(Key == VK_DOWN) paddleRightTimerDown->Enabled = true;
  }
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if((Key == 'a') || (Key == 'A')) paddleLeftTimerUp->Enabled = false;
  if((Key == 'z') || (Key == 'Z')) paddleLeftTimerDown->Enabled = false;

  if(Key == VK_UP) paddleRightTimerUp->Enabled = false;
  if(Key == VK_DOWN) paddleRightTimerDown->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::paddleRightTimerDownTimer(TObject *Sender)
{
  if(paddleRight->Top + paddleRight->Height < Form1->ClientHeight - 1) paddleRight->Top += 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::paddleRightTimerUpTimer(TObject *Sender)
{
  if(paddleRight->Top > 0) paddleRight->Top -= 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ballTimerTimer(TObject *Sender)
{
  if (numberOfBounces > 0 && numberOfBounces % 5 == 0)
  {
    switch(numberOfBounces)
    {
        case 5:
            ballTimer->Interval = 18;
            break;
        case 10:
            ballTimer->Interval = 16;
            break;
        case 15:
            ballTimer->Interval = 14;
            break;
        case 20:
            ballTimer->Interval = 12;
            break;
        case 25:
            ballTimer->Interval = 10;
            break;
        case 30:
            ballTimer->Interval = 8;
            break;
    }
  }

  ball->Left += ballHorizontalMove;
  ball->Top += ballVerticalMove;

  if(ball->Top + Form1->ClientHeight - 10 < Form1->ClientHeight) ballVerticalMove = -ballVerticalMove;

  if(ball->Top + ball->Height + Form1->ClientHeight > (2 * Form1->ClientHeight) - 10) ballVerticalMove = -ballVerticalMove;

  if((ball->Left < paddleLeft->Left + paddleLeft->Width - 2) || (ball->Left + ball->Width > paddleRight->Left + 2))
  {
    if(ball->Left < paddleLeft->Left + paddleLeft->Width - 2)
    {
      rightUserScore++;
      isLeftUserRoundWinner = false;
      miss();
    }
    else
    {
      leftUserScore++;
      isLeftUserRoundWinner = true;
      miss();
    }
  }
  //bounce off left paddle
  else if(ball->Left - paddleLeft->Left - paddleLeft->Width < 5 &&
          ball->Top + ball->Height / 2 >= paddleLeft->Top &&
          ball->Top - ball->Height / 2 <= paddleLeft->Top + paddleLeft->Height)
  {
    if(ballHorizontalMove < 0) ballHorizontalMove = -ballHorizontalMove;

    //bounce off centre of left paddle
    if((ball->Top + ball->Height / 2) + 5 >= (paddleLeft->Top + paddleLeft->Height / 2) &&
       (ball->Top + ball->Height / 2) - 5 <= (paddleLeft->Top + paddleLeft->Height / 2))
    {
      ballVerticalMove = ballVerticalMove * 0.9;
    }

    numberOfBounces++;
  }
  //bounce off right paddle
  else if(ball->Left + ball->Width - paddleRight->Left > -5 &&
          ball->Top + ball->Height / 2 >= paddleRight->Top &&
          ball->Top - ball->Height / 2 <= paddleRight->Top + paddleRight->Height)
  {
    if(ballHorizontalMove > 0) ballHorizontalMove = -ballHorizontalMove;

    //bounce off centre of right paddle
    if((ball->Top + ball->Height / 2) + 5 >= (paddleLeft->Top + paddleLeft->Height / 2) &&
       (ball->Top + ball->Height / 2) - 5 <= (paddleLeft->Top + paddleLeft->Height / 2))
    {
      ballVerticalMove = ballVerticalMove * 0.9;
    }
    
    numberOfBounces++;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::newGameClick(TObject *Sender)
{
  setInitialObjectsPositions();

  ballTimer->Interval = 20;

  if(round == 0)
  {
    round = 0;
    leftUserScore = 0;
    rightUserScore = 0;
    numberOfBounces = 0;
    isLeftUserRoundWinner = false;

    round++;

    ballTimer->Enabled = true;
    newGame->Visible = false;
    userMessageLabel->Visible = false;
  }
  else
  {
    if(Application->MessageBox("Czy na pewno chcesz rozpocz�� now� gr�?", "Nowa Gra", MB_YESNO) == IDYES)
    {
      round = 0;
      leftUserScore = 0;
      rightUserScore = 0;
      numberOfBounces = 0;
      isLeftUserRoundWinner = false;

      round++;

      ball->Visible = true;
      ballTimer->Enabled = true;
      newGame->Visible = false;
      userMessageLabel->Visible = false;
      numberOfBouncesLabel->Visible = false;
      overallScoreLabel->Visible = false;
      nextRound->Visible = false;
    }
  }
}
//---------------------------------------------------------------------------



void __fastcall TForm1::nextRoundClick(TObject *Sender)
{
  setInitialObjectsPositions();

  round++;
  numberOfBounces = 0;

  ballTimer->Interval = 20;
  ballTimer->Enabled = true;
  ball->Visible = true;

  numberOfBouncesLabel->Visible = false;
  overallScoreLabel->Visible = false;
  nextRound->Visible = false;
  userMessageLabel->Visible = false;
  newGame->Visible = false;
}
//---------------------------------------------------------------------------

