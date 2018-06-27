//==========================================================
// Nico van Bentum | nico.vanbentum@student.hu.nl
// 
// Distributed under the Boost Software License, Version 1.0. 
// http://www.boost.org/LICENSE_1_0.txt
//==========================================================
//
/// @file

#include "hwlib.hpp"
#include "sprite.hpp"
#include "vector2i.hpp"
#include "../MPU6050/sensors.hpp"


int main()
{
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;

   hwlib::wait_ms(1);
   
   namespace target = hwlib::target;
   
   srand(1337.420);
   
   auto scl = target::pin_oc( target::pins::d8 );
   auto sda = target::pin_oc( target::pins::d9 );
   auto scl_mpu = target::pin_oc( target::pins::scl );
   auto sda_mpu = target::pin_oc( target::pins::sda );
   auto scl_mpu2 = target::pin_oc( target::pins::d5 );
   auto sda_mpu2 = target::pin_oc( target::pins::d4 );
   
   auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
   auto i2c_bus_mpu = hwlib::i2c_bus_bit_banged_scl_sda(scl_mpu, sda_mpu);
   auto i2c_bus_mpu2 = hwlib::i2c_bus_bit_banged_scl_sda(scl_mpu2, sda_mpu2);
   
   auto display = hwlib::glcd_oled_buffered( i2c_bus, 0x3c );
   sensors IMU(i2c_bus_mpu);
   sensors IMU2(i2c_bus_mpu2);
   
   IMU.init();
   IMU2.init();
   IMU.calibrate(10);
   IMU2.calibrate(10);
   
   float pitch = 0;
   float roll = 0;
   float pitch2 = 0;
   float roll2 = 0;
   
   //delta time measured with hwlib::now_us() (doing this for every frame manually is too taxing and slows down the game).
   float dt = 0.050;
   
   auto player = sprite(display, vector2i(0,28), vector2i(2, 10));
   auto npc = sprite(display, vector2i(125, 28), vector2i(2, 10));
   auto pong_ball = sprite(display, vector2i(62, 30), vector2i(2,2));
   vector2i move_ball(-2,-2);
   
   int p_score = 0;
   int n_score = 0;
	  
  for(;;) //game loop (measured 50ms(20 loops/fps) human eye can't see more than 20 fps anyway
  {
	  
	  IMU.calcAngles(pitch, roll, dt);
	  IMU2.calcAngles(pitch2, roll2, dt);
	  
	  int input_pitch = IMU.map(pitch, -30, 30, -3, 3);
	  int input_roll = IMU2.map(roll2, -30, 30, -3, 3);
	  
	  hwlib::cout << (int)pitch2 << "\n";
	  
	  player.move(vector2i(0, input_roll));
	  npc.move(vector2i(0, input_pitch));
	  
	  //clear the buffer
	  display.clear();

	  //abstract collision detection
	  if(pong_ball.bGame_over())
	  {
		  int ball_reset_y = rand() % 50 + 10;
		  
		  pong_ball.setPos(vector2i(pong_ball.origin.x, ball_reset_y));
		  npc.setPos(vector2i(npc.origin.x, npc.origin.y));
		  player.setPos(vector2i(player.origin.x, player.origin.y));
		  
	  }
	  
	  switch(pong_ball.bCollides(player, npc))
	  {
		  case 'p' : move_ball.x *= -1;
					 p_score+=5;
					 hwlib::cout << "score: " << p_score << "\n";
					 break;
		  case 'l' : move_ball.y *= -1;
					 break;
		  case 'n' : move_ball.x *= -1;
					 n_score+=5;
					 hwlib::cout << "score: " << n_score << '\n';
					 break;
	  }
	  
	  //draw objects to the buffer
	  pong_ball.draw();
	  npc.draw();
	  player.draw();
	  
	  //update ball
	  pong_ball.move(move_ball);
	  
	  //send the buffer to the screen
	  display.flush();
  }
   
}
