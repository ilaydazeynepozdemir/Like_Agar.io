/*##########################################################################################*/
/*Ilayda Zeynep Ozdemir																		*/
/*131044022																					*/
/*								YAZ ODEVI													*/
/*Ana oyuncu klavye ile kontrol edilir.														*/
/*buyuk bir alanin icinden parcalar gosteriyor.										        */
/*Yesil sey oyuncular icine girdiginde onlara zarar veriyor	.								*/
/*Botlar alan icinde rastgele hareket ediyor.											    */
/*Botlar birbirlerinden kaciyor.															*/
/*Botlar ve ana oyuncu yemleri yiyerek yaricaplarini buyutuyor.							    */
/*Yaricapi buyuk olan kucuk olani yer.														*/
/*ve yaricapi kucuk olan ondan kacmaya calisir.												*/
/*Bir bot bir botu yediginde ya da ana oyuncu bir botu yediginde yeni bir bot olusur. 		*/
/*Bir yem yendiginde yeni bir yem olusur .													*/
/*Oyuncu ve botlar ekran disina cikamaz.												    */
/*Sinirlarda takiliyorlar geri donemiyorlar. ve baska bot takip ediyorsa sinirdan cikiyor . */
/*Eger bir botun yaricapi 50den fazlaysa hizi 0.2 azalir .                                  */
/*##########################################################################################*/


#include <allegro.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#define W 1280
#define H 960
#define ARRAY_NUM 100/*yem sayisi*/
#define R 40 /*oyuncu yaricapi*/
#define DEBUG
#define BOTS_NUM 20	
#define NUM 15
#define GREEN_THINGS_NUM 1
#define SPEED_GAMER 5

typedef struct 
{
	double x;
	double y;
	double r;
	int col1,col2,col3;
	
} Gamer ;


/*eger colunmeyi basarili bir sekilde */
/*yapabilseydim gamer_team structini kullanacaktim*/

typedef struct 
{
	Gamer G_1;
	Gamer G_2;
	Gamer G_3;
	
}Gamer_team;

typedef struct 
{
	int f_x;
	int f_y;
	int f_r;
	
} Food;
/*allegroda baslangic ve bitis icin gerekli olan seylerin bulundugu fonksiyonlar*/
extern void start();
extern void end();
/************************************/
/*ana oyuncunun klavye kontrolu icin*/
extern void move_circle(Gamer *gamer_1);
/*yemler olusturulur*/
extern void foods(BITMAP *buffer,Food food_array[ARRAY_NUM]);
/*yem yenir ve yeni koordinatlar atilir*/
extern void eat_and_create(Food *food_1,Gamer *gamer_,int *food_count);

/*green_things_arr ise oyuncularla temas haline gectiginde onlarin yaricapini azaltir*/
extern void play_green_things(BITMAP *buffer,Gamer *green_things,Gamer *gamer_1,int sign);
/*ana fonksiyon gibidir*/
extern void play_circle(BITMAP *buffer,Gamer *gamer_1,Gamer *gamer_2,Gamer *gamer_3,
                int *sign,Food food_array[],int *food_count,int *great_circle,
                Gamer_team *G_team,Gamer bots[BOTS_NUM],Gamer green_things_arr[GREEN_THINGS_NUM]);
/*bolunme fonksiyonu*/
extern void devide(BITMAP *buffer,Gamer gamer_1,Gamer *gamer_2,Gamer *gamer_3,
			int *sign,Food food_array[],int *food_count,Gamer bots[BOTS_NUM],
			Gamer green_things_arr[GREEN_THINGS_NUM]);
/*botlarin genel fonksiyonu*/
extern void bot(BITMAP *buffer,Gamer bots[BOTS_NUM],Food food_array[ARRAY_NUM],int *food_count_bot,
				int *speed,int timer);
/*buyuk olan kucuk olani yer*/
extern void eat_small_gamer(BITMAP *buffer,Gamer bots[BOTS_NUM],Gamer *big_or_small);
/*kucuk olan buyuk olandan kacar*/
extern void escape_of_bots(BITMAP *buffer,Gamer *gamer_1,Gamer bots[BOTS_NUM],int i);
/*botlarin hareket fonksiyonu*/
extern void bots_move(Gamer *bot_,int *speed,int i,int timer);
/*bosluga basildiginda isaret yollamak icin*/
extern void push_space(int *sign,int *great_circle,int *food_count);