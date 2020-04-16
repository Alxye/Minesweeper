#include "game.h"
//#include "AssetManager.h"
int main()
{
      Game Mine;

	  while (Mine.window.isOpen())
	  {
		  Mine.Run();
	  }
	  	  //Mine.Draw_Grid_Animator();
	return 0;
}