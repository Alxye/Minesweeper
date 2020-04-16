#include "Game.h"
//#include "AssetManager.h"
int main()
{
      Game Mine;

	  while (Mine.window.isOpen())
	  {
		  //Mine.Run();
		  do {
			  Mine.Initial();
			  while (Mine.window.isOpen() && Mine.gameover == false) {
				  Mine.Input();
				  Mine.Logic();
				  Mine.Draw();
			  }
		  } while (!Mine.gamequit);
		  //cout << "666" << endl;
	  }
	  	  //Mine.Draw_Grid_Animator();
	return 0;
}