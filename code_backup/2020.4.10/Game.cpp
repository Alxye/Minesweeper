#include "Game.h"
/**
 *  资源管理器
 */
AssetManager* AssetManager::sInstance = nullptr;
AssetManager::AssetManager() {
	assert(sInstance == nullptr);
	sInstance = this;
}
sf::Texture& AssetManager::GetTexture(std::string const& filename) {
	auto& texMap = sInstance->m_Textures;
	auto pairFound = texMap.find(filename);
	if (pairFound != texMap.end()) {
		return pairFound->second;
	}
	auto& texture = texMap[filename];
	texture.loadFromFile(filename);
	return texture;
}
/**
 * change string to lpcwstr
 */
LPCWSTR string_To_LPCWSTR(string _string) {
	size_t origsize = _string.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t* _LPCWSTR = (wchar_t*)malloc(sizeof(wchar_t) * (_string.length() - 1));
	mbstowcs_s(&convertedChars, _LPCWSTR, origsize, _string.c_str(), _TRUNCATE);
	return _LPCWSTR;
}
/**
 * 类Game 构造函数的实现
 */
Game::Game() {
	window_width = 860;
	window_height =700; 
	game_level = 2;                    // set the game level ,the default one is normal --2
	image_background_No = 1;
	image_skin_No = 1;
	window.create(sf::VideoMode(window_width, window_height), L"MineSweeper_BY_赵茜茜");
}
Game::~Game() {}

void Game::Initial(){
	window.setFramerateLimit(60);     // set frame per second
	grid_size = gridsize;             // size of click area(grid)
	switch (game_level)
	{
	case 1:
		stage_width = level_1_width;
		stage_height = level_1_height;
		mines_amount = level_1_mine_amount;
		break;
	case 2:
		stage_width = level_2_width;
		stage_height = level_2_height;
		mines_amount = level_2_mine_amount;
		break;
	case 3:
		stage_width = level_3_width;
		stage_height = level_3_height;
		mines_amount = level_3_mine_amount;
		break;
	default:
		break;
	}
	for (int i = 0; i < 30; i++) //第 i 行
	{
		for (int j=0;j<30;j++)  //第 j 个
		{
			counter[i][j] = i+j;
		}
	}
	change_time_number = 1;     // start interface variable to constraint grid animator
	start_animator = true;      // start interface variable to constraint animator
	gameover = false;
	gamequit = false;
	is_gameover_state = nc_gameover_false; // initialize the original amount of gameover
	grid_flag_calulate = 0;                // initialize the original amount of flag 
	gamebegin = false;                     // initialize the original state of game( to judge whether the game begin)
	game_time = 0;                         // initialize the time to 0 (recount)
	// set the stage of game to the center of console
	stage_cornpoint.x = (window_width - stage_width * gridsize) / 2;
	stage_cornpoint.y = (window_height - stage_height * gridsize) / 2;
	//stage_cornpoint.x =0;
	//stage_cornpoint.y =0;
	
	Initial_Data();                        // initial data
	Initial_Media_Data();                  // initial load data
}
void Game::Initial_Data(){
	int i, j;
	// set all grid to null&unclicked
	for (j = 0; j < stage_height; j++) {
		for (i = 0; i < stage_width; i++) {
			game_data[j][i].grid_state = nc_bg_sqr;
			game_data[j][i].is_press_grid = false;
		}
	}
}
void Game::Initial_Load_Sound(Sound& sound, SoundBuffer& soundbuffer, string filename){
	if (!soundbuffer.loadFromFile(filename)) {
		int result=MessageBox(NULL, string_To_LPCWSTR("Invalid Path , audio is missing : " + filename), TEXT("Error ! Failed to load !"), MB_RETRYCANCEL);
		switch (result){
		case IDRETRY :
			return Initial_Load_Sound(sound, soundbuffer, filename);
		case IDCANCEL:
			exit(0);
		}
	}
	else {
		cout << "音频加载成功" << endl;
		sound.setVolume(50);
		cout << "音频载入缓存成功" << endl;
		sound.setBuffer(soundbuffer);
	}
}
void Game::Initial_Load_Music(Music& music, string filename) {
	if (!music.openFromFile(filename)) {
		int result = MessageBox(NULL, string_To_LPCWSTR("Invalid Path , audio is missing : " + filename), TEXT("Error ! Failed to load !"), MB_RETRYCANCEL);
		switch (result) {
		case IDRETRY:
			return Initial_Load_Music(music,filename);
		case IDCANCEL:
			exit(0);
		}
	}
	else {
		cout << "音频加载成功" << endl;
		music.setVolume(20);
		music.play();
		music.setLoop(true);
	}
}
void Game::Initial_Load_Image(Texture& texture, Sprite& sprite, string filename, float originX, float originY, float factorX, float factorY) {
	if (!texture.loadFromFile(filename)){
		int result = MessageBox(NULL, string_To_LPCWSTR("Invalid Path , image is missing : " + filename), TEXT("Error ! Failed to load !"), MB_RETRYCANCEL);
		switch (result) {
		case IDRETRY:
			return Initial_Load_Image(texture,sprite,filename,originX,originY,factorX,factorY);
		case IDCANCEL:
			exit(0);
		}
	}
	else {
		cout << "贴图加载成功" << endl;
		sprite.setTexture(texture);
 		sprite.setOrigin(originX, originY);
 		sprite.setScale(factorX, factorY);
	}
}

void Game::Initial_Media_Data() {
	stringstream ss;
	ss << "data/images/BK0" << image_background_No << ".jpg";
	Initial_Load_Image(texture_background, sprite_background, ss.str(), 0, 0, 1, 1.5);
	ss.str("");           // clear ss
	//ss << "data/test/blue_whole0" << image_skin_No << ".png";
	ss << "data/images/Game" << image_skin_No << ".jpg";
	Initial_Load_Image(texture_tile, sprite_tile, ss.str(), 0, 0, 1, 1);
	//Initial_Load_Image(texture_tile, sprite_tile,"data/test/blue_whole.png", 0, 0, 1, 1);
	Initial_Load_Image(texture_number, sprite_number,"data/images/num.jpg", 0, 0, 1, 1);
	Initial_Load_Image(texture_timer, sprite_timer, "data/images/jishiqi.jpg", 0, 0, 1, 1);
	Initial_Load_Image(texture_counter, sprite_counter, "data/images/jishuqi.jpg", 0, 0, 1, 1);
	Initial_Load_Image(texture_buttoms, sprite_buttoms, "data/images/button.jpg", 0, 0, 1, 1);
	Initial_Load_Image(texture_gameover, sprite_gameover,"data/images/gameover.jpg", 0, 0, 1,1);

}
void Game::Mine_Set(int Py, int Px) {    // set mine

	int mine_count, i, j, k, l;
	mine_count = 0;

	srand(time(NULL));               //用当前系统时间作为随机数生成器的种子

	//随机布雷
	do {//万一生成在同一个位置？？？？？？？？？？？
		k = rand() % stage_height;//生成随机数
		l = rand() % stage_width;
		if (((k - Py) * (k - Py) + (l - Px) * (l - Px)) <= 2)
			continue;//如果随机左边为当前第一次点击的位置，则重新再来
		if (game_data[k][l].grid_state == nc_bg_sqr)
		{
			game_data[k][l].grid_state = nc_mine;
			game_data[k][l].grid_state_backup = nc_mine;//备份状态
			mine_count++;
		}
	} while (mine_count != mines_amount);
	// set the stage of grid
	for (i = 0; i < stage_height; i++)
		for (j = 0; j < stage_width; j++)
		{
			if (game_data[i][j].grid_state != nc_mine)
			{
				mine_count = 0;
				for (k = i - 1; k < i + 2; k++)
					for (l = j - 1; l < j + 2; l++)
						if (k >= 0 && k < stage_height && l >= 0 && l < stage_width)
						{
							if (game_data[k][l].grid_state == nc_mine)
								mine_count++;
						}//计算(i,j)周围雷的数目

				switch (mine_count)//保存状态
				{
				case 0:
					game_data[i][j].grid_state = nc_null;
					break;
				case 1:
					game_data[i][j].grid_state = nc_one;
					break;
				case 2:
					game_data[i][j].grid_state = nc_two;
					break;
				case 3:
					game_data[i][j].grid_state = nc_three;
					break;
				case 4:
					game_data[i][j].grid_state = nc_four;
					break;
				case 5:
					game_data[i][j].grid_state = nc_five;
					break;
				case 6:
					game_data[i][j].grid_state = nc_six;
					break;
				case 7:
					game_data[i][j].grid_state = nc_seven;
					break;
				case 8:
					game_data[i][j].grid_state = nc_eight;
					break;
				}
			}
		}
}

void Game::Input(){
	/**
	 * event types 包括Window、Keyboard、Mouse、Joystick，4类消息
	 * 通过  bool Window :: pollEvent（sf :: Event＆event） 从窗口顺序询问 （ polled ）事件。
     * 如果有一个事件等待处理，该函数将返回true，并且事件变量将填充（filled）事件数据。
	 * 如果不是，则该函数返回false。 同样重要的是要注意，一次可能有多个事件; 因此我们必须确保捕获每个可能的事件。
	 *
	 */
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			window.close();
			gamequit = true;
		}
		if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Escape) {
			window.close();
			gamequit = true;
		}
		if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
			p2 = Mouse::getPosition(window);
			if (is_gameover_state ==nc_gameover_false) {
				if (mouse_click_timer.getElapsedTime().asMilliseconds() < 500 && p2.x - p1.x < gridsize / 4 && p2.y - p1.y < gridsize / 4) {
					Left_Buttom_DoubleClick(Mouse::getPosition(window));
					cout << "Mouse::Left double click" << endl;
				}
				else {
					Left_Buttom_Down(Mouse::getPosition(window));
					cout << "Mouse::Left click" << endl;
				}
			}
			
		}
		if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
			if (is_gameover_state == nc_gameover_false) {
				p1 = Mouse::getPosition(window);
				mouse_click_timer.restart();      // SFML: Clock only contain two function: getElapsedTime() & restart(); * so easy
				if (gamebegin == false) {
					if (button_easy.contains(event.mouseButton.x, event.mouseButton.y))  game_level = 1;
					if (button_normal.contains(event.mouseButton.x, event.mouseButton.y))  game_level = 2;
					if (button_hard.contains(event.mouseButton.x, event.mouseButton.y))  game_level = 3;
					Initial();   // initialize stage then reset 
				}
				if (button_background.contains(event.mouseButton.x, event.mouseButton.y)) {
					image_background_No++;
					if (image_background_No > 7) image_background_No = 1;  // going to a loop when change background
					Initial_Media_Data();
				}
				if (button_skin.contains(event.mouseButton.x, event.mouseButton.y)) {
					image_skin_No++;
					if (image_skin_No > 6) image_skin_No = 1;  // going to a loop when change skin
					Initial_Media_Data();
				}
				if (button_restart.contains(event.mouseButton.x, event.mouseButton.y)) {
					Initial();
				}
				if (button_quit.contains(event.mouseButton.x, event.mouseButton.y)) {
					window.close();
					gamequit = true;
				}
				cout << "Mouse::Left Release" << endl;
			}
		}
		if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right) {
			if (is_gameover_state == nc_gameover_false)
				Right_Buttom_Down(Mouse::getPosition(window));  // press right button
			cout << "Mouse::right" << endl;
		}

		if (event.type == Event::MouseWheelScrolled) {
			cout << "滚轮滚动" << endl;
		}

		if (event.type == Event::MouseEntered) {
			cout << "鼠标进入窗口" << endl;
		}

		if (event.type == Event::MouseLeft) {
			cout << "鼠标移出窗口" << endl;
		}

		if (event.type == sf::Event::MouseMoved)
		{
			if (event.mouseMove.x > 0 && event.mouseMove.x < 220 && event.mouseMove.y > 0 && event.mouseMove.y < 80)
			{
				std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
				std::cout << "new mouse y: " << event.mouseMove.y << std::endl;
				std::cout << "鼠标位于按钮上" << std::endl;
			}
			else
			{
				std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
				std::cout << "new mouse y: " << event.mouseMove.y << std::endl;
				std::cout << "鼠标不在按钮上" << std::endl;
			}
		}

	}
}
void Right_Button_Down_backup(Vector2i mPoint) {
	int i, j, k, l, lvl;
// 	i = (mPoint.x - stage_cornpoint.x) / gridsize;
// 	j = (mPoint.y - stage_cornpoint.y) / gridsize;
// 
// 	if (i >= 0 && i < stage_width && j >= 0 && j < stage_height) { // if mouse click in the area 
// 		if (game_data[j][i].is_press_grid == true) {               // if it has been clicked
// 			if (game_data[j][i].grid_state != nc_flag) {           // if it is not flag
// 				// ergodic surrounding grids
// 				for (k = j - 1; k < j + 2; k++) 
// 					for (l = i - 1; l < i + 2; l++) 
// 						if (k >= 0 && k < stage_height && l >= 0 && l < stage_width)
// 							if (game_data[k][l].grid_state == nc_flag)  // if the state is flag
// 							{
// 								if (game_data[k][l].grid_state_backup != nc_mine) {
// 									is_gameover_state = nc_game_lose;
// 									gamebegin = false;
// 									Logic_Uncover();
// 								}
// 								else {   // if state is not flag
// 									if (game_data[k][l].is_press_grid == false) {
// 										game_data[k][l].is_press_grid = true;
// 										if (game_data[k][l].grid_state == nc_mine) {
// 											is_gameover_state = nc_game_lose;
// 											gamebegin = false;
// 											game_data[k][l].grid_state = nc_bombing_mine;
// 											Logic_Uncover();
// 										}
// 										if (game_data[k][l].grid_state == nc_null) { // if is blank grid
// 											NullClick(k, l);
// 										}
// 
// 									}
// 								}
// 
// 							}
// 			}
// 		}
// 	
// 	
// 	}
}
void Game::Right_Buttom_Down(Vector2i mPoint){

	int i, j;
	i = (mPoint.x - stage_cornpoint.x) / gridsize;
	j = (mPoint.y - stage_cornpoint.y) / gridsize;
	if (i >= 0 && i < stage_width && j >= 0 && j < stage_height)//如果点击是在范围内
	{
		if (game_data[j][i].is_press_grid == false)
		{
			game_data[j][i].is_press_grid = true;
			game_data[j][i].grid_state_backup = game_data[j][i].grid_state;
			game_data[j][i].grid_state = nc_flag;
			grid_flag_calulate++;
		}
		else
		{
			if (game_data[j][i].grid_state == nc_flag)
			{
				game_data[j][i].is_press_grid = true;
				game_data[j][i].grid_state = nc_question_mark;
				grid_flag_calulate--;
			}
			else if (game_data[j][i].grid_state == nc_question_mark)
			{
				game_data[j][i].is_press_grid = false;
				game_data[j][i].grid_state = game_data[j][i].grid_state_backup;
			}
		}
	}
}
void Game::Left_Buttom_Down(Vector2i mPoint){
	int i, j;
	i = (mPoint.x - stage_cornpoint.x) / gridsize;
	j = (mPoint.y - stage_cornpoint.y) / gridsize;
	if (i >= 0 && i < stage_width && j >= 0 && j < stage_height) {
		if (gamebegin==false){
			gamebegin = true;               // game begin
			game_clock.restart();           
			Mine_Set(j, i);                 // set mines after click stage 
		}
		if (game_data[j][i].grid_state != nc_flag) {    // if the state of grid is not flag
			if (game_data[j][i].is_press_grid == false) {
				game_data[j][i].is_press_grid = true;
				if (game_data[j][i].grid_state == nc_mine) {
					gamebegin = false;
					is_gameover_state = nc_game_lose;
					game_data[j][i].grid_state = nc_bombing_mine;  // mine have been clicked , then change state to bombing
					Logic_Uncover();   // uncover not-found mine
				}
			}
		}
		if (game_data[j][i].grid_state == nc_null) { // if the state of grid is null
			NullClick(j, i);          // find unclicked grid to uncover it
		}
	}

}
void Game::Left_Buttom_DoubleClick(Vector2i mPoint){
	
	int i, j, k, l, lvl;

	i = (mPoint.x - stage_cornpoint.x) / gridsize;
	j = (mPoint.y - stage_cornpoint.y) / gridsize;
	if (i >= 0 && i < stage_width && j >= 0 && j < stage_height)//如果点击是在范围内
	{
		if (game_data[j][i].is_press_grid == true)//如果已被点击
		{
			if (game_data[j][i].grid_state != nc_flag)//如果当前块不是旗子
				for (k = j - 1; k < j + 2; k++)
					for (l = i - 1; l < i + 2; l++)//遍历周围8个格子
						if (k >= 0 && k < stage_height && l >= 0 && l < stage_width)
						{
							if (game_data[k][l].grid_state == nc_flag)//如果状态是旗子
							{
								if (game_data[k][l].grid_state_backup != nc_mine) //如果原先状态不是雷
								{
									//gameOver = true;
									//MessageBox(NULL, TEXT("Game Over!"), NULL, MB_ICONINFORMATION | MB_YESNO);
									is_gameover_state = nc_game_lose;
									gamebegin = false;
									//game_data[j][i].grid_state = ncBOMBING;
									Logic_Uncover();
								}

							}
							else {//如果状态不是旗子
								if (game_data[k][l].is_press_grid == false)
								{
									game_data[k][l].is_press_grid = true;
									if (game_data[k][l].grid_state == nc_mine)//如果为雷
									{
										gamebegin = false;
										is_gameover_state = nc_game_lose;
										game_data[k][l].grid_state = nc_bombing_mine;
										Logic_Uncover();
									}
									if (game_data[k][l].grid_state == nc_null)//如果为空继续查找空块						
										NullClick(k, l);
								}
							}
						}
		}
	}

}
void Game::NullClick(int j, int i) {
// 	int k, l;
// 	for (k = j - 1; k < j + 2; k++) {
// 		for (l = i - 1; l < i + 2; l++) {
// 			if (k >= 0 && k < stage_width && l >= 0 && l < stage_width) {
// 				if (game_data[k][l].is_press_grid == false) {
// 					game_data[k][l].is_press_grid = true;
// 					if (game_data[k][l].grid_state == nc_null)
// 						NullClick(k, l);
// 				}
// 
// 			}
// 		}
// 	}
	int k, l;
	for (k = j - 1; k < j + 2; k++)
		for (l = i - 1; l < i + 2; l++)
			if (k >= 0 && k < stage_height && l >= 0 && l < stage_width)
			{
				if (game_data[k][l].is_press_grid == false)
				{
					game_data[k][l].is_press_grid = true; //显示为已点击
					if (game_data[k][l].grid_state == nc_null) {//如果状态为空
						NullClick(k, l);//则继续查找空块
					}
				}
			}
}

void Game::Logic() { Logic_Is_Win(); }
void Game::Logic_Is_Win(){

	int i, j, c = 0;
	if (grid_flag_calulate == mines_amount)//判断插的所有旗是不是都是雷
	{
		for (i = 0; i < stage_width; i++)
			for (j = 0; j < stage_height; j++)
			{
				if (game_data[j][i].grid_state == nc_flag)
					if (game_data[j][i].grid_state_backup == nc_mine)
						c++;
			}
	}
	else {//判断插的剩下的块是不是都是雷
		for (i = 0; i < stage_width; i++)
			for (j = 0; j < stage_height; j++)
			{
				if (game_data[j][i].is_press_grid == false || game_data[j][i].grid_state == nc_flag) {
					c++;
				}
			}

	}
	if (c == mines_amount)//如果所有旗子都是雷，游戏结束
	{
		gamebegin = false;
		//gameOver = true;
		//MessageBox(NULL, TEXT("You Win!"), NULL, MB_USERICON | MB_YESNO);
		//isGameOverState = ncWIN;
		is_gameover_state = nc_game_win;
	}
}
void Game::Logic_Uncover(){
	int i, j;
	for (j = 0; j < stage_height; j++) {
		for (i = 0; j < stage_width; i++) {
			if (game_data[j][i].is_press_grid == false) {
				if (game_data[j][i].grid_state == nc_mine) {
					game_data[j][i].is_press_grid = true;
					game_data[j][i].grid_state = nc_unfound_mine;
				}
			}
		}
	}
}

void Game::Draw(){
	//window.clear();               // clear screen
	// draw background
	sprite_background.setPosition(0,0);
	window.draw(sprite_background);
	// draw stage
	Draw_Grid();
	Draw_Button();
	Draw_Score();
	Draw_Timer();

	if (is_gameover_state)
	{
		Draw_Game_End();
	}
	window.display();             // show the contents of buffer to the screen,SFML adopts double-buffering mechanism
}

void Game::Draw_Grid_Located(int X_Y_to_color, int _x, int _y, int limit_number) {
// 	if (game_data[j][i].is_press_grid=true)
// 	{
// 	}
	sprite_tile.setTextureRect(IntRect(40 * ((X_Y_to_color) % 30), (((X_Y_to_color) < 30) ? 0 : 40), (40 - 2), (40 - 2)));
	sprite_tile.setPosition(stage_cornpoint.x + gridsize * _x, stage_cornpoint.y + gridsize * _y);
	window.draw(sprite_tile);
}
void Game::Draw_Grid(){
// 	int i, j;
// 	//Draw_Grid_Animator();
// 
// 	for (int i = 0; i < stage_height; i++)  //第i行
// 	{
// 		for (int j = 0; j <stage_width; j++)   //第j个
// 		{
// 			if ((i + j) < change_time_number)
// 			{
// 				Draw_Grid_Located(i + j, j, i, 1);
// 				cout <<"1______1___ here!!!"<< endl;
// 			}
// 			if (change_time_number == counter[i][j]) {
// 				Draw_Grid_Located(change_time_number, j, i, 1);
// 				cout << "2_______2____here!!!"<< endl;
// 			}
// 		}
// 	}
// 	if (change_time_number < (stage_height+stage_width-1)){	change_time_number++;}
	for (int j = 0; j < stage_height; j++)
		for (int i = 0; i < stage_width; i++)
		{
			if (game_data[j][i].is_press_grid == true)
			{
				sprite_tile.setTextureRect(IntRect(game_data[j][i].grid_state * gridsize, 0, gridsize, gridsize));
				sprite_tile.setPosition(stage_cornpoint.x + i * gridsize, stage_cornpoint.y + j * gridsize);
			}
			else
			{
				sprite_tile.setTextureRect(IntRect(nc_bg_sqr * gridsize, 0, gridsize, gridsize));
				//sprite_tile.setTextureRect(IntRect(game_data[j][i].grid_state * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
				sprite_tile.setPosition(stage_cornpoint.x + i * gridsize, stage_cornpoint.y + j * gridsize);
			}
			window.draw(sprite_tile);
		}
}
void Game::Draw_Button_Locate(IntRect& button, Vector2i left_corner,int locate_info,Sprite sprite_buttoms, int deta_X, int button_width, int button_height) {
	left_corner.x = deta_X * locate_info + button_width * (locate_info-1);
	sprite_buttoms.setTextureRect(IntRect((locate_info - 1) * button_width, 0, button_width, button_height));
	sprite_buttoms.setPosition((float)left_corner.x, (float)left_corner.y);
	button.left = left_corner.x;
	button.top = left_corner.y;
	button.width = button_width;
	button.height = button_height;
	window.draw(sprite_buttoms);
}
void Game::Draw_Button(){
	Vector2i left_corner;
	int button_width = 60;
	int button_height = 36;
	int deta_X;
	deta_X = (window_width - button_width * 7) / 8;    // each button is array  at same interval on screen
	left_corner.y =window_height-2*((window_height - stage_height*gridsize)/2)/3;
	// draw each button
	Draw_Button_Locate(button_easy, left_corner, 1, sprite_buttoms, deta_X, button_width, button_height);         //button of easy level
	Draw_Button_Locate(button_normal, left_corner, 2, sprite_buttoms, deta_X, button_width, button_height);       //button of normal level
	Draw_Button_Locate(button_hard, left_corner, 3, sprite_buttoms, deta_X, button_width, button_height);         //button of hard level
	Draw_Button_Locate(button_skin, left_corner, 4, sprite_buttoms, deta_X, button_width, button_height);   //button of change background
	Draw_Button_Locate(button_background, left_corner, 5, sprite_buttoms, deta_X, button_width, button_height);         //button of change skin
	Draw_Button_Locate(button_restart, left_corner, 6, sprite_buttoms, deta_X, button_width, button_height);      //button of restart game
	Draw_Button_Locate(button_quit, left_corner, 7, sprite_buttoms, deta_X, button_width, button_height);         //button of quit game
}
void Game::Draw_Score(){
	Vector2i left_corner;
	left_corner.x = window_width - sprite_counter.getLocalBounds().width * 1.25;
	left_corner.y = sprite_counter.getLocalBounds().height * 0.5;
	sprite_counter.setPosition(left_corner.x, left_corner.y);
	window.draw(sprite_counter);

	int num_size = sprite_number.getLocalBounds().height;
	left_corner.x = left_corner.x + sprite_counter.getLocalBounds().width - num_size;
	left_corner.y = left_corner.y + sprite_counter.getLocalBounds().height * 0.8 - num_size;

	int game_score = mines_amount - grid_flag_calulate;
	//cout << "game_score===" << game_score << endl;
	//cout << "mines_amount===" << mines_amount << endl;
	//cout << "grid_flag_calulate===" << grid_flag_calulate << endl;
	// draw 0-9
	int a = game_score % 10;
	sprite_number.setTextureRect(IntRect(a * num_size, 0, num_size, num_size));
	sprite_number.setPosition(left_corner.x, left_corner.y);
	window.draw(sprite_number);
	// draw 10-99
	game_score = game_score / 10;
	a = game_score % 10;
	left_corner.x = left_corner.x - num_size;
	sprite_number.setTextureRect(IntRect(a * num_size, 0, num_size, num_size));
	sprite_number.setPosition(left_corner.x, left_corner.y);
	window.draw(sprite_number);
	// draw 100-990
	game_score = game_score / 10;
	a = game_score % 10;
	left_corner.x = left_corner.x - num_size;
	sprite_number.setTextureRect(IntRect(a * num_size, 0, num_size, num_size));
	sprite_number.setPosition(left_corner.x, left_corner.y);
	window.draw(sprite_number);
}
void Game::Draw_Timer(){
	Vector2i left_corner;
	left_corner.x = sprite_timer.getLocalBounds().width *0.25;
	left_corner.y = sprite_timer.getLocalBounds().height * 0.5;
	sprite_timer.setPosition(left_corner.x, left_corner.y);
	window.draw(sprite_timer);

	if (gamebegin) {game_time = game_clock.getElapsedTime().asSeconds();}

	int num_size = sprite_number.getLocalBounds().height;
	left_corner.x = left_corner.x + sprite_timer.getLocalBounds().width - num_size*2;
	left_corner.y = left_corner.y + sprite_timer.getLocalBounds().height * 0.8 - num_size;

	int game_score = game_time;
	//cout << game_time << endl;
	if (game_score > 999) { game_score = 999; }
	// draw 0-9
	int a = game_score % 10;
	sprite_number.setTextureRect(IntRect(a * num_size, 0, num_size, num_size));
	sprite_number.setPosition(left_corner.x, left_corner.y);
	window.draw(sprite_number);
	// draw 10-99
	game_score = game_score / 10;
	a = game_score % 10;
	left_corner.x = left_corner.x - num_size;
	sprite_number.setTextureRect(IntRect(a * num_size, 0, num_size, num_size));
	sprite_number.setPosition(left_corner.x, left_corner.y);
	window.draw(sprite_number);
	// draw 100-990
	game_score = game_score / 10;
	a = game_score % 10;
	left_corner.x = left_corner.x - num_size;
	sprite_number.setTextureRect(IntRect(a * num_size, 0, num_size, num_size));
	sprite_number.setPosition(left_corner.x, left_corner.y);
	window.draw(sprite_number);
}
void Game::Draw_Game_End(){
	Vector2i left_corner;
	int button_width = 200;
	int button_height = sprite_gameover.getLocalBounds().height;
	left_corner.x = (window_width - button_width) / 2;
	left_corner.y = (window_height - button_height) / 2;

	sprite_gameover.setPosition(left_corner.x, left_corner.y);

	if (is_gameover_state == nc_game_win)
		sprite_gameover.setTextureRect(IntRect(0 * button_width, 0, button_width, button_height));
	if (is_gameover_state == nc_game_lose)
		sprite_gameover.setTextureRect(IntRect(1 * button_width, 0, button_width, button_height));
	window.draw(sprite_gameover);
}
void Game::Draw_Grid_Animator() {}

//void Game::Run() {
// 	do {
// 		Initial();
// 		while (window.isOpen() && gameover == false) {
// 				Input();
// 				Logic();
// 				Draw();
// 		}
// 	} while (!gamequit);
//}
