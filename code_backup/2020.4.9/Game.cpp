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
	window_height =600; 
	game_level = 2;                    // set the game level ,the default one is normal --2
	image_background_No = 1;
	image_skin_No = 1;
	window.create(sf::VideoMode(window_width, window_height), L"MineSweeper_BY_赵茜茜");
}
Game::~Game() {}

void Game::Initial(){
	window.setFramerateLimit(60);     //set frame per second
	grid_size = gridsize;             // size of click area(grid)'
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
	change_time_number = 1;
	start_animator = true;
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
	Initial_Load_Image(texture_background, sprite_background, ss.str(), 0, 0, 1, 1);
	ss.str("");           // clear ss
	ss << "data/images/Game" << image_skin_No << ".jpg";
	Initial_Load_Image(texture_tile, sprite_tile, ss.str(), 0, 0, 1, 1);
	Initial_Load_Image(texture_tile, sprite_tile,"data/test/blue_whole.png", 0, 0, 1, 1);
	Initial_Load_Image(texture_number, sprite_number,"data/images/num.jpg", 0, 0, 1, 1);
	Initial_Load_Image(texture_timer, sprite_timer, "data/images/jishiqi.jpg", 0, 0, 1, 1);
	Initial_Load_Image(texture_counter, sprite_counter, "data/images/jishuqi.jpg", 0, 0, 1, 1);
	Initial_Load_Image(texture_buttoms, sprite_buttoms, "data/images/button.jpg", 0, 0, 1, 1);
	Initial_Load_Image(texture_gameover, sprite_gameover,"data/images/gameover.jpg", 0, 0, 1,1);

}
void Game::Mine_Set(int Py, int Px) {    // set mine
	int mine_count = 0; //记雷
	int k, l;
	srand(time(NULL));
	do 
	{
		k = rand() % stage_height;
		l = rand() % stage_width;
		if((k-Py)*(k-Py)+(1-Px)*(1-Px)<=2) continue;
		if (game_data[k][l].grid_state==nc_bg_sqr){
			game_data[k][l].grid_state = nc_mine;
			game_data[k][l].grid_state_backup = nc_mine;
			mine_count++;
		}
	} while (mine_count!=mines_amount);

}

void Game::Input(){
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
		//if mouse_click_timer(event.type==sf::Event::MouseButtonPressed&&event.mouseButton.button==sf::Mouse::Left){
		//	if (mouse_click_timer.getElapsedTime().asMilliseconds() > 500)	cout << "Mouse::Left Press" << endl;
		//	else cout << "Mouse::Left Double Clicked" << endl;
		//}
		//if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
		//	mouse_click_timer.restart();
		//	cout << "Mouse::Left Released" << endl;
		//}
		//if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
		//	cout << "Mouse::Right Press" << endl;
		//}

		if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
			p2 = Mouse::getPosition(window);
			if (mouse_click_timer.getElapsedTime().asMilliseconds() < 500 && p2.x - p1.x < gridsize / 4 && p2.y - p1.y < gridsize / 4)
				cout << "Mouse::Left double click" << endl;
			else {
				cout << "Mouse::Left click" << endl;
			}
		}
		if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
			p1 = Mouse::getPosition(window);
			mouse_click_timer.restart();
			cout << "Mouse::Left Release" << endl;
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

		if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right) {
			cout << "Mouse::right" << endl;
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
void Game::Right_Buttom_Down(Vector2i mPoint){}
void Game::Left_Buttom_Down(Vector2i mPoint){}
void Game::Left_Buttom_DoubleClick(Vector2i mPoint){}

void Game::Logic() {}
void Game::Logic_Is_Win(){}
void Game::Logic_Uncover(){}

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
void Game::Draw_Grid(){
	int i, j;
	//Draw_Grid_Animator();

	for (int i = 0; i < stage_height; i++)  //第i行
	{
		for (int j = 0; j <stage_width; j++)   //第j个
		{
			if ((i + j) < change_time_number)
			{
				Temp_Animator_one(i + j, j, i, 1);
			}
			if (change_time_number == counter[i][j]) {
				Temp_Animator_one(change_time_number, j, i, 1);
			}
		}
	}
	if (change_time_number < (stage_height+stage_width-1)){	change_time_number++;}

// 	for (j = 0;j < stage_height; j++) {
// 		for (i=0;i<stage_width;i++)	{
// 			if (game_data[j][i].is_press_grid == true) {
// 				//sprite_tile.setTextureRect(IntRect(game_data[j][i].grid_state * gridsize, 0, gridsize, gridsize));
// 				Draw_Grid_Animator();
// 				//sprite_tile.setPosition(stage_cornpoint.x+i*gridsize,stage_cornpoint.y+j*gridsize);
// 			}
// 			else{
// 				//sprite_tile.setTextureRect(IntRect(nc_bg_sqr * gridsize, 0, gridsize, gridsize));
// 				//sprite_tile.setPosition(stage_cornpoint.x+i* gridsize,stage_cornpoint.y+j * gridsize);
// 			}
// 			window.draw(sprite_tile);
// 		}
// 	}

	//Draw_Grid_Animator();
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
	left_corner.y = window_height - gridsize * 3;
	// draw each button
	Draw_Button_Locate(button_easy, left_corner, 1, sprite_buttoms, deta_X, button_width, button_height);         //button of easy level
	Draw_Button_Locate(button_normal, left_corner, 2, sprite_buttoms, deta_X, button_width, button_height);       //button of normal level
	Draw_Button_Locate(button_hard, left_corner, 3, sprite_buttoms, deta_X, button_width, button_height);         //button of hard level
	Draw_Button_Locate(button_background, left_corner, 4, sprite_buttoms, deta_X, button_width, button_height);   //button of change background
	Draw_Button_Locate(button_skin, left_corner, 5, sprite_buttoms, deta_X, button_width, button_height);         //button of change skin
	Draw_Button_Locate(button_restart, left_corner, 6, sprite_buttoms, deta_X, button_width, button_height);      //button of restart game
	Draw_Button_Locate(button_quit, left_corner, 7, sprite_buttoms, deta_X, button_width, button_height);         //button of quit game
}
void Game::Draw_Score(){}
void Game::Draw_Timer(){}
void Game::Draw_Game_End(){}
void Game::Temp_Animator_one(int X_Y_to_color,int _x, int _y,int limit_number) {
	sprite_tile.setTextureRect(IntRect(40 * ((X_Y_to_color) % 30), (((X_Y_to_color) < 30) ? 0 : 40), (40 - 2), (40 - 2)));
	sprite_tile.setPosition(stage_cornpoint.x + 34 * _x, stage_cornpoint.y + 34 * _y);
	window.draw(sprite_tile);
}
void Game::Draw_Grid_Animator() {}

void Game::Run() {
	do {
		Initial();
		while (window.isOpen() && gameover == false) {
				Input();
				Logic();
				Draw();
		}
	} while (!gamequit);
}


/**
 *  类Animator 构造函数的实现
 */
//构造函数 Animator()
Animator::Animator(sf::Sprite& sprite): m_Sprite(sprite), m_CurrentTime(), m_CurrentAnimation(nullptr) {}

//Animator::CreateAnimation()，创建动画效果并存入 m_Animations 中。
Animator::Animation& Animator::CreateAnimation(std::string const& name,std::string const& textureName, sf::Time const& duration, bool loop) {
	m_Animations.push_back(	Animator::Animation(name, textureName, duration, loop));
	// 如果当前没有动画效果，则使用刚添加动画效果
	if (m_CurrentAnimation == nullptr)
		SwitchAnimation(&m_Animations.back());
	return m_Animations.back();
}
void Animator::SwitchAnimation(Animator::Animation* animation) {
	// 改变精灵的纹理
	if (animation != nullptr) {
		m_Sprite.setTexture(AssetManager::GetTexture(animation->m_TextureName));
	}
	m_CurrentAnimation = animation;
	m_CurrentTime = sf::Time::Zero; // 重置时间
}
// 是否切换成功
bool Animator::SwitchAnimation(std::string const& name) {
	auto animation = FindAnimation(name);
	if (animation != nullptr) {
		SwitchAnimation(animation);
		return true;
	}
	return false;
}
// 通过名字查找已经添加过的动画效果 Animation
Animator::Animation* Animator::FindAnimation(std::string const& name) {
	for (auto it = m_Animations.begin(); it != m_Animations.end(); it++) {
		if (it->m_Name == name) { return &*it;}
	}
	return nullptr;
}
std::string Animator::GetCurrentAnimationName() const {
	if (m_CurrentAnimation != nullptr) { return m_CurrentAnimation->m_Name; }
	return "";
}
void Animator::Update(sf::Time const& dt) {
	if (m_CurrentAnimation == nullptr)  return;

	m_CurrentTime += dt;

	// 获取当前帧
	float scaledTime = m_CurrentTime.asSeconds() / m_CurrentAnimation->m_Duration.asSeconds();
	int numFrames = m_CurrentAnimation->m_Frames.size();
	int currentFrame = static_cast<int>(scaledTime * numFrames);


	// 如果动画在进行，则计算当前帧
	if (m_CurrentAnimation->m_looping) {
		currentFrame %= numFrames;
	}
	else if (currentFrame >= numFrames) { // 如果当前帧不小于总的帧数，设为最后一帧
		currentFrame = numFrames - 1;
	}

	// 设置为当前帧
	m_Sprite.setTextureRect(m_CurrentAnimation->m_Frames[currentFrame]);
}

