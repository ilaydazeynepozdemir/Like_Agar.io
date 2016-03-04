#include "agar.h"

/*iki tane daire olusturur*/
/*bolunme esnasinda cagirilmali*/
void devide(BITMAP *buffer,Gamer gamer_1,Gamer *gamer_2,Gamer *gamer_3,
			int *sign,Food food_array[],int *food_count,Gamer bots[BOTS_NUM],
			Gamer green_things_arr[GREEN_THINGS_NUM]){
	
	int i;

 	circlefill(buffer,gamer_2->x,gamer_2->y,gamer_2->r,makecol(200,0,250));
    circlefill(buffer,gamer_3->x,gamer_3->y,gamer_3->r,makecol(200,0,250));      
   
    move_circle(gamer_2);
	for(i=0;i<ARRAY_NUM;++i){
		eat_and_create(&food_array[i],gamer_2,food_count);
	}
	eat_small_gamer(buffer,bots,gamer_2);
	escape_of_bots(buffer,gamer_2,bots,BOTS_NUM+1);
	for(i=0;i<GREEN_THINGS_NUM;++i){
		play_green_things(buffer,&green_things_arr[i],gamer_2,*sign);
	}

	move_circle(gamer_3);
	for(i=0;i<ARRAY_NUM;++i){
		eat_and_create(&food_array[i],gamer_3,food_count);
	}
	eat_small_gamer(buffer,bots,gamer_3);
	escape_of_bots(buffer,gamer_3,bots,BOTS_NUM+1);
	for(i=0;i<GREEN_THINGS_NUM;++i){
		play_green_things(buffer,&green_things_arr[i],gamer_3,*sign);
	}

	/*ayrilan parca her dongude yarim birim geri geliyor.*/
	if(gamer_3->x > gamer_2->x){
		
		gamer_3->x = gamer_2->x - (1.0/2) ;
	}
	
}

/*yardimci fonksiyon. bosluk tusuna basilmdiginda kontrol amacli*/
/*bu fonksiyon olmadiginda bosluk tusuna basilinca saniyelere */
/*gore algiladigi icin yanlis calisiyor*/
void push_space(int *sign,int *great_circle,int *food_count){
    if (key[KEY_SPACE]){
    	/*printf("%d\n",*sign );*/
	  	(*sign)++;
	  	/*if(*sign >= 5 && key[KEY_SPACE]){
	  		
	  		++(*sign);

	  	}*/
    }
	  
}


/*bosluk tusuna basildiginda ikiye ayriliyor.sonra birlesiyor. */
/*oyunun diger hareketleri de bu fonsiyon icinde kullanildi*/	 
void play_circle(BITMAP *buffer,Gamer *gamer_1,Gamer *gamer_2,Gamer *gamer_3,
                int *sign,Food food_array[],int *food_count,int *great_circle,
                Gamer_team *G_team,Gamer bots[BOTS_NUM],
                Gamer green_things_arr[GREEN_THINGS_NUM]){
    int i;
	    /*ikinci basmada*/
/*	if((*sign) == 6 ){
		G_team->G_1.x = gamer_2->x + 50;
		G_team->G_1.y = gamer_2->y ;
		G_team->G_1.r = gamer_1->r / 4;
		
		gamer_2->r = gamer_1->r/4;

		G_team->G_2.x = gamer_2->x + 50;
		G_team->G_2.y = gamer_2->y +50 ;
		G_team->G_2.r = gamer_1->r / 4;
		
		gamer_3->r = gamer_1->r/4;
		++(*first);
	}*/

    /*bosluga basilmadigi ve tekrar birlesme zamaninda*/
    if(*sign == 0 || *sign == 1000){
    	circlefill(buffer,gamer_1->x,gamer_1->y,gamer_1->r,makecol(200,0,250));
		move_circle(gamer_1);
		for(i=0;i<ARRAY_NUM;++i){
			eat_and_create(&food_array[i],gamer_1,food_count);
		}
		eat_small_gamer(buffer,bots,gamer_1);

		gamer_2->x = gamer_1->x + 50;
		gamer_2->y = gamer_1->y + 50;

		gamer_3->x = gamer_1->x ;
		gamer_3->y = gamer_1->y ;

		gamer_2->r = gamer_1->r / 2;
		gamer_3->r = gamer_1->r / 2;

    }

    /*bosluk tusuna basildigi zamanlarda*/
    else if( (*sign > 0 ) && (gamer_1->r >= 20) ){	
		/*ilk bolunme*/
    	devide(buffer,*gamer_1,gamer_2,gamer_3,sign,food_array,food_count,bots,
    	green_things_arr);
    	gamer_1->r = gamer_2->r + gamer_3->r;
		gamer_1->x = (gamer_2->x + gamer_3->x)/2;
		gamer_1->y = (gamer_2->y + gamer_3->y)/2;
			
		/*ikinci,ucuncu bolunmeleri tamamlayamadim*/
    	/*if(*sign >= 6){

    		
    		devide(buffer,*gamer_2,&G_team->G_1,&G_team->G_2,sign,food_array,
    				food_count,bots,green_things_arr);
    		

    		gamer_1->r = gamer_2->r + gamer_3->r + G_team->G_1.r+G_team->G_2.r;
			gamer_1->x = (gamer_2->x + gamer_3->x)/2;
			gamer_1->y = (gamer_2->y + gamer_3->y)/2;
    	}*/
 
   	}

/*bosluga basildiginda ama yaricapi bolunmeye musait olmadiginda*/
/*(*sign != 1000) kosulu yaricap 20 altina dustugunde ve oyuncu iki */
/*parca oldugunda bir parca yesil sey tarafindan yenirse*/
/* diger parca yok olmasin diye*/
   	
   	else if( (*sign > 0 ) && (gamer_1->r < 20) && (*sign != 1000) ){
   	    circlefill(buffer,gamer_1->x,gamer_1->y,gamer_1->r,makecol(200,0,250));
		move_circle(gamer_1);
		for(i=0;i<ARRAY_NUM;++i){
			eat_and_create(&food_array[i],gamer_1,food_count);
		}
		gamer_2->x = gamer_1->x ;
		gamer_2->y = gamer_1->y ;
                                                                               
		gamer_3->x = gamer_1->x + (gamer_1->r+50);
		gamer_3->y = gamer_1->y + (gamer_1->r);

		gamer_2->r=gamer_1->r/2;      
       	gamer_3->r=gamer_1->r/2;

        *sign = 0;

   	}

	if(*food_count - *great_circle >= 10){
		*sign = 1000;
	} /*birlesme komutu gibi*/
	/*EKSIKLERI VAR!SADECE ILK BOLUNMEDE GECERLI.*/

}
/*yer sonra diger yemin koordinatlarini belirler*/
void eat_and_create(Food *food_1,Gamer *gamer_,int *food_count){
    if( sqrt( pow(( (double)(gamer_->y) - (food_1->f_y)) , 2) + 
              pow(( (double)(gamer_->x) - (food_1->f_x)) , 2) ) <= 
              (gamer_->r)-(food_1->f_r) ){
		/*kucuk daire buyuk daire icine geldiginde aralarindaki mesafeyi*/
		/*bu sekilde bulup sinirlandirdim*/
        (gamer_->r) = (gamer_->r) + (1.0/2);
        
		++(*food_count);

/*15 ekleme sebebim 0 dan kucuk koordinatlara kaymasin arkasinda iz*/
/* birakmasin diye*/
		srand(time(NULL));
		if((*food_count)%2 == 0)
			(food_1->f_x) = 15+rand()%(W-50); 
		else if((*food_count)%3 == 0)
			(food_1->f_x) = 15+rand()%(W-43);
		else if((*food_count)%4 == 0)
			(food_1->f_x) = 15+rand()%(W-27);
		else if((*food_count)%5 == 0)
			(food_1->f_x) = 15+rand()%(W-21);
		else if((*food_count)%7 == 0)
			(food_1->f_x) = 15+rand()%(W-29);
		else 
			(food_1->f_x) = 15+rand()%(W-30);

		srand(time(NULL));
		if((*food_count)%2 == 0)
			(food_1->f_y) = 15+rand()%(H-47);
		else if((*food_count)%3 == 0)
			(food_1->f_y) = 15+rand()%(H-46);
		else if((*food_count)%4 == 0)
			(food_1->f_y) = 15+rand()%(H-36);
		else if((*food_count)%5 == 0)
			(food_1->f_y) =	15+rand()%(H-32);
		else if((*food_count)%7 == 0)
			(food_1->f_y) = 15+rand()%(H-42);
		else 
			(food_1->f_y) = 15+rand()%(H-50);
			
	}
	
}

void foods(BITMAP *buffer,Food food_array[20]){

	int i;
	for(i=0;i<ARRAY_NUM;++i){
		circlefill(buffer,(food_array[i].f_x),(food_array[i].f_y),
		(food_array[i].f_r),makecol(rand()%225,rand()%225,rand()%225));
		/*yiyecekler her dongude farkli renk aliyor*/
		/*belirgin olmasi icin oyle yaptim*/
		
	}
}

	/*hareket etmesini saglar*/
void move_circle(Gamer *gamer_1){
	
/*	if((gamer_1->x >= mouse_x) && (gamer_1->x != mouse_x))
		gamer_1->x -= 1.5 ;
	if((gamer_1->y >= mouse_y) && (gamer_1->y != mouse_y))
		gamer_1->y -= 1.5 ;
	if((mouse_x >= gamer_1->x) && (gamer_1->x != mouse_x))
		gamer_1->x += 1.5 ;
	if((mouse_y >= gamer_1->y) && (gamer_1->y != mouse_y))
		gamer_1->y += 1.5;
*/
	
	
	if(key[KEY_UP] && gamer_1->y >= 0)
		(gamer_1->y) -= SPEED_GAMER;
	else if(key[KEY_DOWN] && gamer_1->y <= H)
		(gamer_1->y) += SPEED_GAMER;
	if(key[KEY_LEFT] && gamer_1->x >= 0)
		(gamer_1->x) -= SPEED_GAMER;
	else if(key[KEY_RIGHT] && gamer_1->x <= W)
		(gamer_1->x) += SPEED_GAMER;

	if(gamer_1->x < 0 && key[KEY_LEFT])
		(gamer_1->x) += SPEED_GAMER+3;
	if(gamer_1->x > W && key[KEY_RIGHT])
		(gamer_1->x) -= SPEED_GAMER+3;
	if(gamer_1->y < 0 && key[KEY_UP])
		(gamer_1->y) += SPEED_GAMER+3;
	if(gamer_1->y > H && key[KEY_DOWN])
		(gamer_1->y) -= SPEED_GAMER+3;

}

/*yesil top oyuncu yanina geldiginde onun capini azaltir*/
/*kendine ceker*/
void play_green_things(BITMAP *buffer,Gamer *green_things,Gamer *gamer_,
                      int sign){
	
	 circlefill(buffer,green_things->x,green_things->y,green_things->r,
	            makecol(0,150,0));
	 if( sqrt( pow(( (double)(green_things->y) - (gamer_->y)) , 2) + 
              pow(( (double)(green_things->x) - (gamer_->x)) , 2) ) <= 
              (green_things->r)){

	 	if(sign == 0 || sign == 7000)
	 		gamer_->r -= 1.5;
	/*yesil sey oyuncuyu kendine ceker*/
	 	if((green_things->x > gamer_->x )&& (gamer_->x < ((green_things->x + gamer_->x)/2)))
	 		gamer_->x += 10;
	 	if((green_things->y > gamer_->y )&& (gamer_->y < ((green_things->y + gamer_->y)/2)))
	 		gamer_->y += 10;
	 	
	 	if((green_things->x > gamer_->x )&& (gamer_->x > ((green_things->x + gamer_->x)/2)))
	 		gamer_->x -= 10;
	 	if((green_things->y > gamer_->y )&& (gamer_->y > ((green_things->y + gamer_->y)/2)))
	 		gamer_->y -= 10;
	 	if( sqrt( pow(( (double)(green_things->y) - (gamer_->y)) , 2) + 
              pow(( (double)(green_things->x) - (gamer_->x)) , 2) ) <= 
              (green_things->r) - gamer_->r){
	 		gamer_->r = 0;
		}
	}
}

void bots_move(Gamer *bot_ ,int speed,int i,int timer){

	if(i%2 == 0 && timer%2 == 1){
		if(bot_->x-bot_->r-25 >= 0 && bot_->x+bot_->r+25 <= W){
			speed = 1;
			if(bot_->r >= 50)
				speed -= 0.2;
		}

		if(bot_->x+bot_->r > W)
			speed = -5;
		
		bot_->x += speed;
	}
		
	else if(i%2 == 1 && timer%2 == 0){
		if(bot_->x-bot_->r-25 >= 0 && bot_->x+bot_->r+25 <= W){
			speed = -1;
			if(bot_->r >= 50)
				speed += 0.2;
		}else if(bot_->x-bot_->r < 0)
			speed = 5;

		bot_->x += speed;
	}
	
	if(i%2 == 1 && timer%2 == 0){	
		if(bot_->y-bot_->r-25 >= 0 && bot_->y+bot_->r+25 <= H){
			speed = 1;
			if(bot_->r >= 50)
				speed -= 0.2;
		}else if(bot_->y+bot_->r+5 > H)
			speed = -5;
		
		bot_->y += speed;
	}
	
	else if(i%2 == 0 ){
		if(bot_->y-bot_->r-25 >= 0 && bot_->y+bot_->r+25 <= H){
			speed = -1;
			if(bot_->r >= 50)
				speed += 0.2;
		}else if(bot_->y-bot_->r-5 < 0)
			speed = 5;
		
		bot_->y += speed;
	}


	if(bot_->x > W)
		bot_->x = 100;
	if(bot_->y > H)
		bot_->y = 100;
	if(bot_->x < 0)
		bot_->x = 100;
	if(bot_->y < 0)
		bot_->y = 100;
}

void bot(BITMAP *buffer,Gamer bots[BOTS_NUM],Food food_array[ARRAY_NUM],
        int *food_count_bot,int speed,int timer){

		int i,j;

	for(i=0;i<BOTS_NUM;++i){
		circlefill(buffer,(bots[i].x),(bots[i].y),
		(bots[i].r),makecol(bots[i].col1,bots[i].col2,bots[i].col3));		
		for(j=0;j<ARRAY_NUM;++j){
			eat_and_create(&food_array[j],&bots[i],food_count_bot);
		}
		eat_small_gamer(buffer,bots,&bots[i]);
		escape_of_bots(buffer,&bots[i],bots,i);/*!!!!!!!!!!!!!!*/
		bots_move(&bots[i],speed,i,timer);
		
	}

}

/* int i degiskeninin olus sebebi bot fonksiyonundaki dongu icindeki */
/* i ile k ayni olmasin diye. yani bi bot kendini yiyiyor olmamasi icin*/
/*bot fonksiyonu disindaki fonksiyonlarda cagirilirken BOTS_NUM+1 olarak*/
/* yollanirsa problem cikmaz*/

void escape_of_bots(BITMAP *buffer,Gamer *bot1,Gamer bots[BOTS_NUM],int i){
	int k;
	for(k=0;k<BOTS_NUM;++k){	
		if(i != k){
			if( sqrt( pow(( (double)(bot1->y) - (bots[k].y)) , 2) + 
           	 	pow(( (double)(bot1->x) - (bots[k].x)) , 2) ) <=
           	 	(bot1->r)+(bots[k].r) ){
					
				if(bot1->r > bots[k].r){
					if(bot1->x >= bots[k].x && bot1->y >= bots[k].y){
						bots[k].x -=1.5;
						bots[k].y -=1.5;

					}

					if(bot1->x >= bots[k].x && bot1->y <= bots[k].y){
						bots[k].x -=1.5;
						bots[k].y +=1.5;

					}

					if(bot1->x <= bots[k].x && bot1->y >= bots[k].y){
						bots[k].x +=1.5;
						bots[k].y -=1.5;
					}

					if(bot1->x <= bots[k].x && bot1->y <= bots[k].y){
						bots[k].x +=1.5;
						bots[k].y +=1.5;
					}
				}

				if(bots[k].r >= bot1->r){
					if(bot1->x >= bots[k].x && bot1->y >= bots[k].y){
						bots[k].x +=1.5;
						bots[k].y +=1.5;

					}

					if(bot1->x >= bots[k].x && bot1->y <= bots[k].y){
						bots[k].x +=1.5;
						bots[k].y -=1.5;
					}

					if(bot1->x <= bots[k].x && bot1->y >= bots[k].y){
						bots[k].x -=1.5;
						bots[k].y +=1.5;
					}

					if(bot1->x <= bots[k].x && bot1->y <= bots[k].y){
						bots[k].x -=1.5;
						bots[k].y -=1.5;
					}

				}
			}
		}

		if(bots[k].x > W)
			bots[k].x = 100;
		if(bots[k].y > H)
			bots[k].y = 100;
		if(bots[k].x < 0)
			bots[k].x = 100;
		if(bots[k].y < 0)
			bots[k].y = 100;
		/*disari kacmasin diye*/
	}	
}


void eat_small_gamer(BITMAP *buffer,Gamer bots[BOTS_NUM],Gamer *big_or_small){

	int i,k;
	for(k=0;k<BOTS_NUM;++k){


		if(big_or_small->r > bots[k].r){
			if( sqrt( pow(( (double)(big_or_small->y) - (bots[k].y)) , 2) + 
           	 pow(( (double)(big_or_small->x) - (bots[k].x)) , 2) ) <= 
           	 (big_or_small->r)-(bots[k].r) ){

           	 	big_or_small->r = big_or_small->r + bots[k].r;

           	 	srand(time(NULL));
           	 	bots[k].x = 20+rand()%(W-150);
           	 	bots[k].y = 20+rand()%(H-100);
           	 	bots[k].r = rand()%20+10;
           	 	bots[k].col1 = rand()%250;
           	 	bots[k].col2 = rand()%200;
           	 	bots[k].col3 = rand()%250;
			}

		}

		else if(bots[k].r > big_or_small->r){
			if( sqrt( pow(( (double)(bots[k].y) - (big_or_small->y)) , 2) + 
           	 pow(( (double)(bots[k].x) - (big_or_small->x)) , 2) ) <= 
           	 (bots[k].r)-(big_or_small->r) ){
           	 	
           	 	bots[k].r = bots[k].r + big_or_small->r;
          	 	srand(time(NULL));
           	 	big_or_small->x = 20+rand()%(W-150);
           	 	big_or_small->y = 20+rand()%(H-100);
           	 	big_or_small->r = rand()%20+10;
           	 	big_or_small->col1 = rand()%250;
           	 	big_or_small->col2 = rand()%200;
           	 	big_or_small->col3 = rand()%250;

           	 	/*Ana oyuncu yendiginde tekrar olusmasin diye*/
           	 	for(i=0;i<BOTS_NUM;++i){

					if(big_or_small->r != bots[i].r &&
						big_or_small->x != bots[i].x &&
						big_or_small->y != bots[i].y )
						big_or_small->r = 0;
				}

			}
		}
	}

	
}

void start() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) 
		depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED,W/2,H/2,0,0);
	  
	/*if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}*/
	install_timer();
	install_keyboard();
	install_mouse();
 
}
void end() {
	clear_keybuf();
 
}
