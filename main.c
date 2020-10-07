#include <stdio.h>

/* libraries for the pseudo-random number generator */
#include <stdlib.h>
#include <time.h>
/* Within the time.h library,
 *    time returns a value based upon the time of day
 * Within the stdlib.h library
 *    rand returns a pseudo-random integer between 0 and RAND_MAX
 */

/*
this function that uses the rand function to determine number
outcome of a spinner to adjust the number of cherries in a player's bucket
     preconditions:
     @param   int cherries:  the number of cherries originally in the bucket as an integer.
     postconditions:
     @returns the number of cherries in the bucket, based on the value of a simulated spinner as an integer
*/
 int turn (int cherries)
 {
   int spinner = 1 + rand() % 7 ;//save the value of the spinner
   if( spinner ==  1 )//if spinner lands on 1
   {
     cherries = cherries -1;//take one cherry off the tree
   }
   else if( spinner == 2 )
   {
     cherries = cherries -2;//take 2 cherries off the tree
   }
   else if( spinner == 3 )
   {
     cherries = cherries -3;
   }
   else if( spinner == 4 )
   {
     cherries = cherries -4;
   }
   else if(spinner == 7)
   // Spilled Basket
   {
     cherries = 10;
   }
   else if((spinner == 5 || spinner == 6) && cherries > 0 )
   //you have spun a Dog or Bird and cherries are not 0
   {
     if( cherries == 9 || cherries == 10 || cherries == 8)
     {
       cherries = 10;
     }
   }
   else
   //You have spun 5 or 6 with 0 cherries - Skipped turn: number of cherries //does not change
   {
     cherries = cherries;
   }
   return cherries;
 }//turn






/*
this function that simulates an entire game of Hi Ho Cherrio
    preconditions:
     @param    players   the number of players in the game as postive integer greater than 0.
    postconditions: 
     @returns  the number of rounds taken until some player wins as integer.
*/
int playGame(int players)
{ //Simulate First Player Separately
  int count;
  int newCount;
  int cherries = 10;
  //the following loop simulates the game for player 1 and returns the number //of rounds played as count.
  while( cherries > 0 )
  {
   cherries = turn(cherries);
   newCount++;
  }
  count = newCount;
  cherries = 10;
  newCount = 0;//reset newCount for remaining simulations
  //simulate game for remaining players
  int remainingPlayers = players-1;
  while (remainingPlayers > 0)
  {
   while( cherries > 0 )
  {
   cherries = turn(cherries);
   newCount++;
  }
  if( count > newCount) 
  //keep track of minimum number of rounds/turns played to get 0 cherries (win game)
  {
    count = newCount;
  }
  //set variables back to default for next simulation
  newCount = 0;
  cherries = 10;
  //one less player to go
  remainingPlayers--;
  }
  return count;//return number of turns for one game
}//playGame


/*
this is a function that plays several games of Hi Ho Cherrio and computes basic game statistics.
     preconditions:
     @param  players: the number of players in a game as postive integer > 0
     @param  games: the number of games to be simulated as positive integer > 0
     @param  avg:   the address for the average number of turns in a game
     @param  max:   the address for the maximum number of turns in a game
     @param  min:   the address for the minimum number of turns in a game
     post-conditions:
          the function has controlled the playing of the Hi Ho Cherrio games and stored the
              average, maximum, and minimum number of turns in a game in the last 3 addresses
          no printing is done in this function or in functions called by it
*/

void playNGames (int players, int games, double* avg, int* max, int* min)
{
  int totalturns = 0;
  int turns;
  //simulate 1 game so we can initialize min and max
  turns = playGame(players);
  int maxsofar = turns;
  int minsofar = turns;
  totalturns += turns;


  //siumulate remaining games
  int remainingGames = games - 1;
  
  for (int i = remainingGames ; i > 0; i--)
  { turns = playGame(players);
    totalturns += turns;
    
    if (turns > maxsofar)
    {
      maxsofar = turns;
    }
    if (turns < minsofar)
    {
      minsofar = turns;
    }  
    
  }//for

  *avg = (double) totalturns/games;
  *max = maxsofar;
  *min = minsofar;
}//playNGames





int main ()
{
  /* initialize pseudo-random number generator */
  /* change the seed to the pseudo-random number generator, 
     based on the time of day */
  srand (time ((time_t *) 0) );

  /*start with 10 cherries */
  int cherries = 10;
  //the following are initialized to give playNGames the relevant addresses
  double avg;
  int max;
  int min;
  int players;
  int games;
  printf("Enter number of players-games(seperated by -):\n");
  scanf("%d-%d", &players, &games);
   playNGames(players, games, &avg, &max, &min);
  /* reporting simulation results */
  printf ("Simulation of %d games\n",games);
  printf ("total games played: %d\naverage number of turns till someone wins:  %lf\nminimum turns per game:  %d  maximum turns per game:  %d\n", games,avg, min, max);

  return 0;
}
