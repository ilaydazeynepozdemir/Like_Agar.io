#include "agar.h"
int main() {
	
	start();
	
	BITMAP *buffer=create_bitmap(3*W,3*H);/*!!!! onemli*/
	BITMAP *background1=load_bitmap("thema1.bmp",NULL),
		   *background2=load_bitmap("thema2.bmp",NULL),
		   *background3=load_bitmap("thema3.bmp",NULL);

	
	int sign=0,timer=0;
	Gamer gamer_1,gamer_2,gamer_3;
	/*gamer_1 ana oyuncuyu temsil ediyor*/
	/*gamer_2 ve gamer_3 de o bolundugu zaman ekranda gorunen toplardir*/
	
	Gamer_team G_team;
	/*bolunmenin bi kac gerceklesmesi icin*/

	Gamer green_things_arr[GREEN_THINGS_NUM];
	/*yesil seylerin arrayi*/


	Gamer bots[BOTS_NUM];
	/*botlarin arrayi*/

	int food_count=0,great_circle=0;
	/*great_circle birlesme zamanini belirlemek icin gerekli*/
	/*food_count ana oyuncu kac tane yem yiyiyor onu belirler*/
	
	int food_count_bot=0;
	/*food_count_bot ise botlarin yedigi yem sayisini belirliyor*/

	int speed=0;/*botlarin hizlari*/
	
	int i,j;
	srand(time(NULL));
	int thema_choose=rand()%30;/*tema secimi icin*/
	int scroll_x=0,scroll_y=0; /* ekran kaymasi icin*/

	Food food_array[ARRAY_NUM];
	
	srand(time(NULL));
		/*ilk konumlar*/

	gamer_1.x=rand()%(W);   	
	gamer_1.y=rand()%(H);   	
	gamer_1.r=R; 

	srand(time(NULL));
	for(i=0;i<GREEN_THINGS_NUM;++i){
		green_things_arr[i].x = 150+rand()%(W-250);
		green_things_arr[i].y = 150+rand()%(H-250);
		green_things_arr[i].r=100;

	} 

	srand(time(NULL));
	/*food_array'i doldurur*/
	for(i=0;i<ARRAY_NUM;++i){

		food_array[i].f_r = 5;
		food_array[i].f_x = 15+rand()%(W-25);
		food_array[i].f_y = 15+rand()%(H-25);
		
	}

	srand(time(NULL));
	for(i=0;i<BOTS_NUM;++i){
		bots[i].x = 30+rand()%(W-50);
		bots[i].y = 30+rand()%(H-50);
		bots[i].r = rand()%10+20;
		bots[i].col1 = rand()%250;
		bots[i].col2 = rand()%200;
		bots[i].col2 = rand()%2;
	}



	/*bu dongu icindekiler ekranda gorunur*/
	while (!key[KEY_ESC]  ) {
		++timer;
		/*printf("%d\n",sign );*/

		show_mouse(buffer);

		/*if(mouse_b && 1 ){
	       printf("BASTI %d %d \n",mouse_x,mouse_y);
	      
  		}*/
		scroll_x = gamer_1.x - (W/4);
		scroll_y = gamer_1.y - (H/4);
		
		/*tema secimi*/	
		if(thema_choose <= 3 )
			blit(background1,buffer,0,0,0,0,W,H);
		else if(thema_choose > 3 && thema_choose <= 5 )
			blit(background2,buffer,0,0,0,0,W,H);
		else if(thema_choose > 5 && thema_choose <= 9 )
			blit(background3,buffer,0,0,0,0,W,H);

        push_space(&sign,&great_circle,&food_count);
       
	    foods(buffer,food_array);
		bot(buffer,bots,food_array,&food_count_bot,&speed,timer);
		escape_of_bots(buffer,&gamer_1,bots,BOTS_NUM+1);
		
		play_circle(buffer,&gamer_1,&gamer_2,&gamer_3,&sign,food_array,
		            &food_count,&great_circle,&G_team,bots,green_things_arr);

		for(i=0;i<GREEN_THINGS_NUM;++i){
			play_green_things(buffer,&green_things_arr[i],&gamer_1,sign);
			for(j=0;j<BOTS_NUM;++j){
				play_green_things(buffer,&green_things_arr[i],&bots[j],sign);
			}
		}		
		if(sign == 0 ){/*birlesme icin*/
			great_circle = food_count ;		
		}
		if(gamer_1.r == 0){	
			textout_justify_ex(buffer, font, "#GAME OVER!!",gamer_1.x-50,gamer_1.x+50, 
		                    gamer_1.y, gamer_1.y+50, makecol(100, 22, 150), makecol(-1,0,0));
		}
		/*ana oyuncunun yaricapi ile yedigi yemlerin toplami*/
		textprintf_ex(buffer,font,gamer_1.x,gamer_1.y+50,makecol(225,225,255),makecol(0,0,0),
		              "%.1f",gamer_1.r+food_count);
	    rest(50);
		blit(buffer,screen,scroll_x,scroll_y,0,0,W/2,H/2);
		clear_bitmap(buffer);

		

	}
	end();
return 0;
}
END_OF_MAIN()
