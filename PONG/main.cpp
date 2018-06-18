#include "hwlib.hpp"
#include "object.hpp"
#include "vector2i.hpp"
#include "MPU6050.hpp"

int main( void ){
    
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
   hwlib::wait_ms(1);
   
   namespace target = hwlib::target;
   
   auto scl = target::pin_oc( target::pins::d8 );
   auto sda = target::pin_oc( target::pins::d9 );
   auto scl_mpu = target::pin_oc( target::pins::scl );
   auto sda_mpu = target::pin_oc( target::pins::sda );
   
   auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
   auto i2c_bus_mpu = hwlib::i2c_bus_bit_banged_scl_sda(scl_mpu, sda_mpu);
   
   auto button1 = hwlib::target::pin_in(hwlib::target::pins::d3);
   auto button2 = hwlib::target::pin_in(hwlib::target::pins::d4);
   
   auto display = hwlib::glcd_oled_buffered( i2c_bus, 0x3c );
   MPU6050 MPU_sensor(i2c_bus_mpu);
   MPU_sensor.init();
   
   auto player = object(display, vector2i(0,28), vector2i(2, 10));
   auto npc = object(display, vector2i(125, 28), vector2i(2, 10));
   auto pong_ball = object(display, vector2i(62, 30), vector2i(2,2));
   
   int score = 0;

   srand(1337.420);
   
   vector2i move_ball(-2,-2);
   
   
	  
  for(;;) //game loop
  {
	  
	  
	  int az = MPU_sensor.readAccelZ()*1000;
	  
	  //clear the buffer
	  display.clear();
	  
	  //button input (gyro WIP)
	  if(az > 200)
	  {
		  player.move(vector2i(0,-2));
	  }
	  else if(az < -200)
	  {
		  player.move(vector2i(0,2));
	  }

	  //abstract collision detection
	  if(pong_ball.bGame_over(pong_ball))
	  {
		  int ball_reset_y = rand() % 50 + 10;
		  pong_ball.setPos(vector2i(pong_ball.origin.x, ball_reset_y));
		  npc.setPos(vector2i(npc.origin.x, ball_reset_y-5));
		  
		  score-=5;
		  hwlib::cout << "score: " << score << "\n";
	  }
	  
	  switch(pong_ball.bCollides(player, npc))
	  {
		  case 'p' : move_ball.x *= -1;
					 score+=5;
					 hwlib::cout << "score: " << score << "\n";
					 break;
		  case 'l' : move_ball.y *= -1;
					 break;
		  case 'n' : move_ball.x *= -1;
					 break;
	  }
	  
	  //draw objects to the buffer
	  pong_ball.draw();
	  npc.draw();
	  player.draw();
	  
	  //move game objects
	  pong_ball.move(move_ball);
	  npc.move(vector2i(0, move_ball.y));	 
	  
	  //send the buffer to the screen
	  display.flush();
  }
   
}
