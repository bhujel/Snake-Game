#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
typedef struct food{
 int x , y ;
 char v ;
}fo;
typedef struct snake{
int x , y ;
char v ;
struct snake *next ;
}sn;
void create_food( char b[100][100] , int r , int c , fo *ptr , sn* h){
(*ptr).v = 'x';
(*ptr).x = rand() % r ;
(*ptr).y = rand() % c ;
sn* p = h ;
while(1){
  sn *p = h ;
  int f = 0 ;
  while( p != NULL ){
if( (*ptr).x == p->x && (*ptr).y == p->y){
  f = 1 ;
  break ;
    }
    p = p->next ;
  }
if ( f == 1 ){
(*ptr).x = rand() % r ;
(*ptr).y = rand() % c ;
      }else
      break ; 
   }
b[(*ptr).x][(*ptr).y] = (*ptr).v ;
}
sn* create_snake( sn* h , char b[100][100] , sn* t){
  int n = 5 , r = 4 , c = 10 ;
  while( n-- ){
  sn* ptr = (sn*)malloc(sizeof(sn));
ptr->x = r ;
ptr->y = c ;
ptr->v = '#';
ptr->next = NULL ;
if ( h == NULL ){
  h = ptr ;
  t = ptr ;
}else{
  sn* temp = h ;
  while( temp->next != NULL )
  temp = temp->next ;
  temp->next = ptr ;
  t = ptr ;
      }
      c-- ;
   }
   h->v = '@';
   t->v = '*';
   sn* p = h ;
  return h ;
}
void create_board( sn *h , char b[100][100] , int r , int c , fo *f){
    for ( int i = 0 ; i <= r ; i++ ){
        for ( int j = 0 ; j <= c ; j++ ){
            b[i][j] = ' ' ;
        }
    }
    b[(*f).x][(*f).y] = (*f).v;
  sn* p = h ;
  while( p != NULL ){
    b[p->x][p->y] = p->v ;
    p = p->next ;
  }
}
void screen( char b[100][100] , int r , int c ){
    for ( int i = 0 ; i <= c+2 ; i++ )
    printf("-");
    printf("\n");
    for ( int i = 0 ; i <= r ; i++ ){
        printf("|");
        for ( int j = 0 ; j <= c ; j++ ){
            printf("%c",b[i][j]);
        }
        printf("|\n");
    }
    for ( int i = 0 ; i <= c+2 ; i++ )
    printf("-");
    printf("\n");
}
void swap( int *a , int *b ){
  int t = *a ;
  *a = *b ;
  *b = t ;
}
void move_snake( char b[100][100] , sn** h , int r , int c , fo *p1 , int *score){
  char op , pre_op = '~' ;
  printf("PRESS OPTION\n");
  scanf(" %c",&op);
  while( op != 'q'){
    int x1 , y1 ;
    if ( pre_op != '~' ){
      if ( op == 'a' && pre_op == 'd')
      op = pre_op ;
      if ( op == 'd' && pre_op == 'a')
      op = pre_op ;
      if ( op == 'w' && pre_op == 'z')
      op = pre_op ;
      if ( op == 'z' && pre_op == 'w')
      op = pre_op ;
    }
    pre_op =  op ;
    switch(op){
      case 'd' : x1 = 0 , y1 = 1 ;
      break ;
      case 'a' : x1 = 0 , y1 = -1 ;
      break ;
      case 'w' : x1 = -1 , y1 = 0 ;
      break ;
      case 'z' : x1 = 1 , y1 = 0 ;
      break ;
      default : x1 = 0 , y1 = 0 ;
      break ;	
    }
  int tempx = ((*h)->x)+x1 , tempy = ((*h)->y)+y1 ;
  if ( tempx < 0 )
  tempx = r ;
  if ( tempx > r )
  tempx = 0 ;
  if ( tempy < 0 )
  tempy = c ;
  if ( tempy > c )
  tempy = 0 ;
  //this will avoid snake from hiting itself
  //if it hit than over the game ;
  sn *s1 = *h ;
  int flag = 0 ;
  while( s1 != NULL ){
    if ( tempx == s1->x && tempy == s1->y ){
    flag = 1 ;
    break ;
    }
    s1 = s1->next ;
  }
  if ( flag == 0 ){
    //eat food if food is found else just move 
    int found = 0 ;
    if ( tempx == (*p1).x && (*p1).y == tempy ){
      found = 1 ;
      (*h)->v = '#';
  sn *new = (sn*)malloc(sizeof(sn*));
  new->v ='@';
  new->x = tempx ;
  new->y = tempy ;
  new->next = *h ;
  *h = new ;
  *score += 5 ;
    }else{
  sn *ptr = *h ;
  while( ptr != NULL ){
    swap( &(ptr->x) , &tempx );
    swap( &(ptr->y) , &tempy );
    ptr = ptr->next ;
       }
  }
    create_board( *h , b , r , c , p1 );
    if ( found == 1 )
    create_food( b , r , c , p1 , *h );
    system("clear") ;
    screen( b , r , c );
    //usleep(100);
    }else if(x1 == 0 && y1 == 0 ){
      printf("press valid key\n");
    }else{
      break ;
    }
    scanf(" %c",&op);
  }
}
int main(void) {
  char b[100][100] , name[20];
  fo f ;
  int r = 15 , c = 20 , score = 0 ;
  sn *h = NULL , *t = NULL ;
  usleep(100);
  srand(time(0));
  printf("WEL-COME TO SNAKE GAME\n");
  printf("ENTER NAME : ");
  scanf(" %[^\n]s",name);
  h = create_snake( h , b , t );
  create_food( b , r , c , &f , h );
  create_board( h , b , r , c , &f );
  //system("clear") ;
  printf("ENTER 'A' = LEFT , 'W' = UP , 'D' = RIGHT , 'Z' = DOWN\n");
  screen( b , r , c );
  move_snake ( b , &h , r , c , &f , &score);
  system("clear");
  printf("GAME OVER\n");
  printf("Thank You For Playing\nYour Score : ");
  printf("%d\n",score);
  return 0;
}
