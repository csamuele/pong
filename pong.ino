
#define H1 11
#define H2 2 
#define H3 7
#define H4 8
#define H5 3
#define H6 0
#define H7 4
#define H8 5

#define L1 A3
#define L2 A2
#define L3 A1
#define L4 10
#define L5 A0
#define L6 9
#define L7 A4
#define L8 A5
//define which pins corespond to certain buttons
const int p1bL = 6;
const int p1bR = 1;
const int p2bL = 12;
const int p2bR = 13;
//variables to tell whether button is pressed or not
int p1bsL;
int p1bsR;
int p2bsL;
int p2bsR;
//the two platforms' x position
int plyr1x = 1;
int plyr2x = 1;
//the two platforms' y position
const int plyr1y = 7;
const int plyr2y = 0;
//ball's location
int pBallX = 7;
int pBallY = 2;
int nBallY;
int nBallX;
//ball's velocity
int velocityX = -1;
int velocityY = 1;
//score
int plyr1score = 0;
int plyr2score = 0;
unsigned char canvas[8][8] =  
{
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  
};
unsigned char scoreboard[8][8] = 
{
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
};

void setup()
{
  pinMode(p1bL, INPUT);
  pinMode(p1bR, INPUT);
  pinMode(p2bL, INPUT);
  pinMode(p2bL, INPUT);
  pinMode(H1,OUTPUT);
  pinMode(H2,OUTPUT);
  pinMode(H3,OUTPUT);
  pinMode(H4,OUTPUT);
  pinMode(H5,OUTPUT);
  pinMode(H6,OUTPUT);
  pinMode(H7,OUTPUT);
  pinMode(H8,OUTPUT);
  
  pinMode(L1,OUTPUT);
  pinMode(L2,OUTPUT);
  pinMode(L3,OUTPUT);
  pinMode(L4,OUTPUT);
  pinMode(L5,OUTPUT);
  pinMode(L6,OUTPUT);
  pinMode(L7,OUTPUT);
  pinMode(L8,OUTPUT);
}

void loop() 
{
    p1bsL = digitalRead(p1bL);
    p1bsR = digitalRead(p1bR);
    p2bsL = digitalRead(p2bL);
    p2bsR = digitalRead(p2bR);
    //draws ball
    canvas[pBallY][pBallX] = 1;
    //draws platforms
    DrawPlatform(plyr1x, plyr1y);
    DrawPlatform(plyr2x, plyr2y);
    //checks if the platform is underneath the ball
    PlatformCollision(plyr1y, plyr1x, -1);\
  PlatformCollision(plyr2y, plyr2x, 1);
  //contols the platform
    if (millis() % 10 == 0)
    {
        plyr1x = Controls(plyr1x, plyr1y, p1bsL, p1bsR);
        plyr2x = Controls(plyr2x, plyr2y, p2bsL, p2bsR);
    }
    //controls the speed of the ball
    if (millis() % 50 == 0)
  { 
      //adds velocity to ball location in order to move the ball
    nBallY = pBallY + velocityY;
    nBallX = pBallX + velocityX;
    //erases the ball's previous location
    //canvas[pBallY][pBallX] = 0;
    for (int i = 1; i < 7; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            canvas[i][j] = 0;
        }
    }
    //edge check on X axis
    if (nBallX < 1 || nBallX > 6)
    {
      velocityX = velocityX * -1;
    }
    //cornercheck
    if (nBallY < 2) 
    {
        velocityX = 1;
        if (nBallX < 1)
        {
            if (plyr2x == 0)
          {
              velocityY = 1;
          }else
          {
              velocityY = -1;
          }
        } else if (nBallX > 6)
        {
            velocityX = -1;
            if (plyr2x == 6)
            {
                velocityY = 1;
            } else
            {
                velocityY = -1;
            }
          
        }
    } else if (nBallY > 5)
    {
        if (nBallX < 1)
        {
            velocityX = 1;
            if (plyr1x == 0)
            {
              velocityY = -1;
            } else 
            {
                velocityY = 1;
            }
        } else if (nBallX > 6)
            {
          velocityX = -1;
          if (plyr1x == 6)
          {
              velocityY = -1;
          } else
          {
              velocityY = 1;
          }
        }
  }
  }
  
    if (nBallY > 6 || nBallY < 1)
    {
        if(nBallY > 6)
        {
            plyr1score++;
            scorekeeper(plyr1score, 0);

        }else
        {
            plyr2score++;
            scorekeeper(plyr2score, 7);

        }
        
        //the two platforms' x position
plyr1x = 1;
plyr2x = 1;
//ball's location
nBallY=3;
nBallX=3;
//ball's velocity
velocityX = -1;
velocityY = 1;
    } else
    {
        Display(canvas);
        pBallY = nBallY;
        pBallX = nBallX;
    }

}

void scorekeeper(int score, int row)
{
    if (score > 0)
    {
        for (int j = 0; j < 3; j++)
        {
            scoreboard[row][score - 1] = 0;
            for (int i = 0; i < 70; i++)
            {
                Display(scoreboard);
                delay(1);
            }
            scoreboard[row][score - 1] = 1;
            for (int i = 0; i < 70; i++)
            {
                Display(scoreboard);
                delay(1);
            }
        }
    }
}

void PlatformCollision(int yPlatform, int xPlatform, int nVelocityY)
{
    if (nBallY == yPlatform + nVelocityY) 
  {
    if (nBallX == xPlatform && nBallX > 0)
    {
      velocityY = nVelocityY;
    } else if (nBallX == xPlatform + 1 && nBallX < 7)
    {
      velocityY = nVelocityY;
    }else if (nBallX == xPlatform - 1 && velocityX == 1)
    {
      velocityX *= -1;
      velocityY = nVelocityY;
    } else if (nBallX == xPlatform + 2 && velocityX == -1)
    {
        velocityX = 1;
        velocityY = nVelocityY;
    }
        
  }
}

void DrawPlatform(int xPlatform, int yPlatform)
{
    canvas[yPlatform][xPlatform] = 1;
  canvas[yPlatform][xPlatform + 1] = 1;
}

int Controls(int xPlatform, int yPlatform, int buttonState1, int buttonState2)
{
    if (buttonState2 == HIGH && xPlatform < 6)      
  {       
    xPlatform++;      
    canvas[yPlatform][xPlatform - 1] = 0;     
  } else if (buttonState1 == HIGH && xPlatform > 0)     
  {       
    xPlatform--;      
    canvas[yPlatform][xPlatform + 2] = 0;     
  }
  return xPlatform;
}

void Display(unsigned char dat[8][8])                 
{
  digitalWrite(L1,LOW);    
  digitalWrite(H1,dat[0][0]);
  digitalWrite(H2,dat[1][0]);
  digitalWrite(H3,dat[2][0]);
  digitalWrite(H4,dat[3][0]);
  digitalWrite(H5,dat[4][0]);
  digitalWrite(H6,dat[5][0]);
  digitalWrite(H7,dat[6][0]);
  digitalWrite(H8,dat[7][0]); 
  delay(1);         
  Clear();          
 
  digitalWrite(L2,LOW);     
  digitalWrite(H1,dat[0][1]);
  digitalWrite(H2,dat[1][1]);
  digitalWrite(H3,dat[2][1]);
  digitalWrite(H4,dat[3][1]);
  digitalWrite(H5,dat[4][1]);
  digitalWrite(H6,dat[5][1]);
  digitalWrite(H7,dat[6][1]);
  digitalWrite(H8,dat[7][1]);
  delay(1);
  Clear();
  
  digitalWrite(L3,LOW);       
  digitalWrite(H1,dat[0][2]);
  digitalWrite(H2,dat[1][2]);
  digitalWrite(H3,dat[2][2]);
  digitalWrite(H4,dat[3][2]);
  digitalWrite(H5,dat[4][2]);
  digitalWrite(H6,dat[5][2]);
  digitalWrite(H7,dat[6][2]);
  digitalWrite(H8,dat[7][2]);
  delay(1);
  Clear();
  
  digitalWrite(L4,LOW);     
  digitalWrite(H1,dat[0][3]);
  digitalWrite(H2,dat[1][3]);
  digitalWrite(H3,dat[2][3]);
  digitalWrite(H4,dat[3][3]);
  digitalWrite(H5,dat[4][3]);
  digitalWrite(H6,dat[5][3]);
  digitalWrite(H7,dat[6][3]);
  digitalWrite(H8,dat[7][3]);
  delay(1);
  Clear();
  
  digitalWrite(L5,LOW);        
  digitalWrite(H1,dat[0][4]);
  digitalWrite(H2,dat[1][4]);
  digitalWrite(H3,dat[2][4]);
  digitalWrite(H4,dat[3][4]);
  digitalWrite(H5,dat[4][4]);
  digitalWrite(H6,dat[5][4]);
  digitalWrite(H7,dat[6][4]);
  digitalWrite(H8,dat[7][4]);
  delay(1);
  Clear();
  
  digitalWrite(L6,LOW);       
  digitalWrite(H1,dat[0][5]);
  digitalWrite(H2,dat[1][5]);
  digitalWrite(H3,dat[2][5]);
  digitalWrite(H4,dat[3][5]);
  digitalWrite(H5,dat[4][5]);
  digitalWrite(H6,dat[5][5]);
  digitalWrite(H7,dat[6][5]);
  digitalWrite(H8,dat[7][5]);
  delay(1);
  Clear();
  
  digitalWrite(L7,LOW);     
  digitalWrite(H1,dat[0][6]);
  digitalWrite(H2,dat[1][6]);
  digitalWrite(H3,dat[2][6]);
  digitalWrite(H4,dat[3][6]);
  digitalWrite(H5,dat[4][6]);
  digitalWrite(H6,dat[5][6]);
  digitalWrite(H7,dat[6][6]);
  digitalWrite(H8,dat[7][6]);
  delay(1);
  Clear();
  
  digitalWrite(L8,LOW);      
  digitalWrite(H1,dat[0][7]);
  digitalWrite(H2,dat[1][7]);
  digitalWrite(H3,dat[2][7]);
  digitalWrite(H4,dat[3][7]);
  digitalWrite(H5,dat[4][7]);
  digitalWrite(H6,dat[5][7]);
  digitalWrite(H7,dat[6][7]);
  digitalWrite(H8,dat[7][7]);
  delay(1);  
  Clear();
}

void Clear() 
{
  digitalWrite(H1,LOW);
  digitalWrite(H2,LOW);
  digitalWrite(H3,LOW);
  digitalWrite(H4,LOW);
  digitalWrite(H5,LOW);
  digitalWrite(H6,LOW);
  digitalWrite(H7,LOW);
  digitalWrite(H8,LOW);
  
  digitalWrite(L1,HIGH);
  digitalWrite(L2,HIGH);
  digitalWrite(L3,HIGH);
  digitalWrite(L4,HIGH);
  digitalWrite(L5,HIGH);
  digitalWrite(L6,HIGH);
  digitalWrite(L7,HIGH);
  digitalWrite(L8,HIGH);
}
