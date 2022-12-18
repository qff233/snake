#include "StartScreen.h"

#include "GameScreen.h"

USING_NS_AX;

bool StartScreen::init()
{
	if(!Scene::init())
		return false;

	auto visibleSize = _director->getVisibleSize();
	auto origin = _director->getVisibleOrigin();

	auto back_ground = Sprite::create("snake.jpg");
	back_ground->setScale(visibleSize.x/back_ground->getContentSize().x, visibleSize.y/back_ground->getContentSize().y);
	back_ground->setPosition(Vec2(origin.x+visibleSize.x/2, origin.y+visibleSize.y/2));
	this->addChild(back_ground, -1);

	auto label = Label::createWithTTF("Snake Game", "fonts/Marker Felt.ttf", 82);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2, 
							origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);


	TTFConfig label_config;
	label_config.fontFilePath = "fonts/Marker Felt.ttf";
	label_config.fontSize = 52;
	label_config.glyphs = GlyphCollection::DYNAMIC;
	label_config.outlineSize = 1;
	label_config.customGlyphs = "";
	label_config.distanceFieldEnabled = false;

	Vector<MenuItem*> menu_item_list;

	auto start_game_lable = Label::createWithTTF(label_config, "Start The Game");
	auto menu_start_game_item = MenuItemLabel::create(start_game_lable, [this](Ref* sender) {
			auto screen = utils::createInstance<GameScreen>();
			this->_director->pushScene(screen);
		});
	menu_start_game_item->setPosition(Vec2(0, 0));
	menu_item_list.pushBack(menu_start_game_item);

	auto quit_lable = Label::createWithTTF(label_config, "Quit");
	auto menu_quit_game_item = MenuItemLabel::create(quit_lable, [this](Ref* sender) {
			_director->end();
		});
	menu_quit_game_item->setPosition(Vec2(0, - menu_quit_game_item->getContentSize().height));
	menu_item_list.pushBack(menu_quit_game_item);

	auto menu = Menu::createWithArray(menu_item_list);
	menu->setPosition(origin.x + visibleSize.x / 2, origin.y + visibleSize.y / 4);
	this->addChild(menu);

	return true;
}
