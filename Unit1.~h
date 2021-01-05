//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TImage *paddleLeft;
        TTimer *paddleLeftTimerUp;
        TTimer *paddleLeftTimerDown;
        TImage *paddleRight;
        TTimer *paddleRightTimerDown;
        TTimer *paddleRightTimerUp;
        TImage *ball;
        TTimer *ballTimer;
        TButton *newGame;
        TLabel *userMessageLabel;
        TLabel *overallScoreLabel;
        TLabel *numberOfBouncesLabel;
        TButton *nextRound;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall paddleLeftTimerUpTimer(TObject *Sender);
        void __fastcall paddleLeftTimerDownTimer(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall paddleRightTimerDownTimer(TObject *Sender);
        void __fastcall paddleRightTimerUpTimer(TObject *Sender);
        void __fastcall ballTimerTimer(TObject *Sender);
        void __fastcall newGameClick(TObject *Sender);
        void __fastcall nextRoundClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
 