#include <stdio.h>
#include <stdlib.h>


//-------------------------------------------------------------------------------------
// CONSTANTS
//-------------------------------------------------------------------------------------

#define WINS  8

// potential square locations
enum LOCATIONS
{
  TOP_LEFT,
  TOP_CENTRE,
  TOP_RIGHT,
  MIDDLE_LEFT,
  MIDDLE_CENTRE,
  MIDDLE_RIGHT,
  BOTTOM_LEFT,
  BOTTOM_CENTRE,
  BOTTOM_RIGHT,
  NUM_LOCATIONS
};

// enumeration of the potential state for each board square
enum STATES
{
  EMPTY = 'b',
  X = 'X',
  O = 'O',
};

// potential game outcomes (from computer's prespective)
enum OUTCOMES
{
  LOSS,
  DRAW,
  WIN
};

//-------------------------------------------------------------------------------------
// VARIABLES
//-------------------------------------------------------------------------------------

// winning states are always read top to bottom and then left to right
// static so that it can't be accessed outside this file
// done this way since I want easy initialization and it never changes
static enum LOCATIONS const winningStates[WINS][3] = 
{ 
  { TOP_LEFT, TOP_CENTRE, TOP_RIGHT },
  { MIDDLE_LEFT, MIDDLE_CENTRE, MIDDLE_RIGHT },
  { BOTTOM_LEFT, BOTTOM_CENTRE, BOTTOM_RIGHT },
  { TOP_LEFT, MIDDLE_LEFT, BOTTOM_LEFT },
  { TOP_CENTRE, MIDDLE_CENTRE, BOTTOM_CENTRE },
  { TOP_RIGHT, MIDDLE_RIGHT, BOTTOM_RIGHT },
  { TOP_LEFT, MIDDLE_CENTRE, BOTTOM_RIGHT },
  { TOP_RIGHT, MIDDLE_CENTRE, BOTTOM_LEFT },
};

int comparisons = 0;
char board[NUM_LOCATIONS];

//-------------------------------------------------------------------------------------
// PROTOTYPES
//-------------------------------------------------------------------------------------

void reset();
enum STATES currentState( int position );
enum STATES winner();
int full();
int gameOver();
int playerMove( int position );
enum LOCATIONS findOpponentMove( enum OUTCOMES * const outcome, enum OUTCOMES alpha, enum OUTCOMES beta );
enum LOCATIONS findComputerMove( enum OUTCOMES * const outcome, enum OUTCOMES alpha, enum OUTCOMES beta );
void computerMove();
void print();
void performance();

//-------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------

int main( int argc, char *argv[] )
{
  int position = 0;
  
  // read in player moves until the game's over
  reset();
  print();
  
  while ( !gameOver() )
  {
    do
    {
      printf( "Enter your choice (0-8): " );
      scanf( "%d", &position );
    } while ( !playerMove(position) );
    
    if ( !gameOver() )
      computerMove();
    
    print();
  }
  
  performance();
  
  return EXIT_SUCCESS;
}

// converts all of the board locations to be empty
void reset()
{
  int i;
  
  for ( i=0 ; i<NUM_LOCATIONS ; i++ )
    board[i] = EMPTY;
}

// returns the current board state for the given board location
enum STATES currentState( int position )
{
  return board[position];
}

// returns the game winner or EMPTY if none yet
enum STATES winner()
{
  enum STATES victor = EMPTY;
  int i;
  
  // check each winning state one by one to see if we're done
  for ( i=0 ; (i < WINS) && (victor == EMPTY) ; i++ )
  {
    // the winning states let us look at specific board locations
    
    if ( (board[winningStates[i][0]] == X) &&
        (board[winningStates[i][1]] == X) &&
        (board[winningStates[i][2]] == X) )
      victor = X;
    
    else if ( (board[winningStates[i][0]] == O) &&
             (board[winningStates[i][1]] == O) &&
             (board[winningStates[i][2]] == O) )
      victor = O;
  }
  
  return victor;
}

// returns true if there are no spaces left to put a piece
int full()
{
  int result = 1;
  int i;
  
  for ( i=0 ; i<NUM_LOCATIONS && result ; i++ )
    if ( board[i] == EMPTY )
      result = 0;
  
  return result;
}


// returns true if the game's over
int gameOver()
{
  int gameOver = 1;
  
  // only need to check for a winner if it isn't a draw
  if ( !full() )
  {
    // if the winner isn't empty then the game's over
    gameOver = (winner() != EMPTY);
  }
  
  return gameOver;
}

// puts a player's piece (X) at the specified location
int playerMove( int position )
{
  int result = 0;
  
  // only want to allow the place if the current location isn't occupied
  if ( board[position] == EMPTY )
  {
    board[position] = X;
    result = 1;
  }
  
  return result;
}


// recursively find the best move the opponent will make
// the parameters are required since they will oscillate through
// the recursion and we need to keep each levels values
enum LOCATIONS findOpponentMove( enum OUTCOMES * const outcome, enum OUTCOMES alpha, enum OUTCOMES beta )
{
  int i;
  enum OUTCOMES response;
  enum LOCATIONS result;
  enum STATES victor = winner();
  
  // must test all end cases since we recurse to a complete board
  // instead of one level prior
  // we also have to full board last since now it can be full and
  // a win so we want to know about the win first
  if ( victor == X )
    *outcome = LOSS;
  else if ( victor == O )
    *outcome = WIN;
  else if ( full() )
    *outcome = DRAW;
  else
  {
    // worst case for the opponent, want to find something better
    *outcome = WIN;
    
    // prune if the computer can't produce a value lower than our 
    // current outcome (lower would replace ours and it's maximizing)
    for ( i=0 ; (i < NUM_LOCATIONS) && (*outcome > alpha) ; i++ )
    {
      // try all positions not currently in use
      if ( board[i] == EMPTY )
      {
        board[i] = X;
        // beta is our best so far, so tell the computer maximizer
        // where it can prune
        findComputerMove( &response, alpha, *outcome );
        board[i] = EMPTY;
        
        comparisons++;
        
        // if this move puts the computer in a worse position, use it
        if ( response < *outcome )
        {
          *outcome = response;
          result = (enum LOCATIONS)i;
        }
      }		
    }
  }
  
  return result;
}


// recursively find the best move for the computer to make
// the parameters are required since they will oscillate through
// the recursion and we need to keep each levels values
enum LOCATIONS findComputerMove( enum OUTCOMES * const outcome, enum OUTCOMES alpha, enum OUTCOMES beta )
{
  int i;
  enum OUTCOMES response;
  enum LOCATIONS result;
  enum STATES victor = winner();
  
  // must test all end cases since we recurse to a complete board
  // instead of one level prior
  // we also have to full board last since now it can be full and
  // a win so we want to know about the win first
  if ( victor == O )
    *outcome = WIN;
  else if ( victor == X )
    *outcome = LOSS;
  else if ( full() )
    *outcome = DRAW;
  else
  {
    // worst case for the computer, want to find something better
    *outcome = LOSS;
    
    // prune if the opponent can't produce a value higher than our 
    // current outcome (higher would replace ours and it's minimizing)
    for ( i=0 ; (i < NUM_LOCATIONS) && (*outcome < beta) ; i++ )
    {
      // try all positions not currently in use
      if ( board[i] == EMPTY )
      {
        board[i] = O;
        // alpha is our best so far, so tell the opponent minimizer
        // where it can prune
        findOpponentMove( &response, *outcome, beta );
        board[i] = EMPTY;
        
        comparisons++;
        
        // if this move puts the computer in a better position, use it
        if ( response > *outcome )
        {
          *outcome = response;
          result = (enum LOCATIONS)i;
        }
      }		
    }
  }
  
  return result;
}


// puts a computer's piece (O) on the board
void computerMove()
{
  // none of these parameters used here but needed for the recursion
  enum OUTCOMES outcome;
  enum OUTCOMES alpha = LOSS;   // computer adjusts alpha
  enum OUTCOMES beta = WIN;     // opponent adjusts beta
  
  board[findComputerMove( &outcome, alpha, beta )] = O;
}

// prints out the current board state
void print()
{
  int i;
  
  printf( "\n" );
  
  for ( i=0 ; i<NUM_LOCATIONS ; i++ )
  {
    printf( "%c ", (char)board[i] );
    if ( (i+1)%3 == 0 )
      printf( "\n" );
  }
  
  printf( "\n" );
}

// prints the current performance statistic
void performance()
{
  printf( "We performed %d comparisons.\n", comparisons );
}
