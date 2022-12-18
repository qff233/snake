#include "GameScreen.h"

#include <iostream>

USING_NS_AX;

bool GameScreen::init()
{
	if (!Scene::init())
		return false;

	auto visible_size = _director->getVisibleSize();
	auto origin = _director->getVisibleOrigin();

	////////////////////////背景图片////////////////////////////
	auto back_ground = Sprite::create("back_ground.jpg");
	back_ground->setScale(visible_size.x / back_ground->getContentSize().x, visible_size.y / back_ground->getContentSize().y);
	back_ground->setPosition(Vec2(origin.x + visible_size.x / 2, origin.y + visible_size.y / 2));
	this->addChild(back_ground, -1);

	//////////////////小角的返回按钮/////////////////////////////
	auto back_label = Label::createWithTTF("Back", "fonts/Marker Felt.ttf", 24);
	auto menu_back_item = MenuItemLabel::create(back_label, [this](Ref* sender) {
			auto screen = utils::createInstance<GameScreen>();
			this->_director->popScene();
		});
	menu_back_item->setPosition(Vec2(origin.x + visible_size.width/2  - back_label->getContentSize().width/2,
								     origin.y - visible_size.height/2 + back_label->getContentSize().height/2));
	auto menu = Menu::create(menu_back_item, NULL);
	this->addChild(menu, 1);

	/////////////////注册鼠标移动事件///////////////////////////
	m_mouse_listener = EventListenerMouse::create();
	m_mouse_listener->onMouseMove = AX_CALLBACK_1(GameScreen::on_mouse_move, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_mouse_listener, this);


	/////////////////绘制pikaqiu////////////////////////////////
	this->addChild(m_snake.get_data());
	m_speed = 700.0f / 1280 * visible_size.x;

	////////////////随机生成精灵球//////////////////////////////
	m_pea = Sprite::create("pea.png");
	m_pea->setPosition(Vec2(random() % (int)visible_size.width, 
						    random() % (int)visible_size.height));
	auto scale = 1.0 / (5.0 / 720 * visible_size.height);
	m_pea->setScale(scale);
	this->addChild(m_pea, -1);

	///////////////右上角的分数标签/////////////////////////////
	m_scores_lable = Label::createWithTTF(std::string("Scores: ")+std::to_string(m_scores), "fonts/Marker Felt.ttf", 52);
	m_scores_lable->setPosition(Vec2(origin.x + visible_size.width- m_scores_lable->getContentSize().width/2, origin.y+visible_size.height- m_scores_lable->getContentSize().height / 2));
	this->addChild(m_scores_lable, 1);

	scheduleUpdate();

    return true;
}

static float get_distance(float x, float y) {
	return std::pow(x * x + y * y, 0.5);
}

static float rad2deg(float x) {
	return x / (2 * M_PI) * 360.0f;
}

void GameScreen::update(float delta)
{
	auto visible_size = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	/////////// 判断球是否被吃到 //////////////////
	const auto& pea_position = m_pea->getPosition();
	const auto head_position = m_snake.get_position();

	if (head_position.x > pea_position.x - 25 && 
		head_position.x < pea_position.x + 25 &&
		head_position.y < pea_position.y + 25 &&
		head_position.y > pea_position.y -25)
	{
		m_pea->setPosition(Vec2(random() % (int)visible_size.width,
			random() % (int)visible_size.height));
		m_scores += 50;
		m_snake.add_body();
		
		this->removeChild(m_scores_lable);
		m_scores_lable->release();
		m_scores_lable = Label::createWithTTF(std::string("Scores: ") + std::to_string(m_scores), "fonts/Marker Felt.ttf", 52);
		m_scores_lable->setPosition(Vec2(origin.x + visible_size.width - m_scores_lable->getContentSize().width / 2, origin.y + visible_size.height - m_scores_lable->getContentSize().height / 2));
		this->addChild(m_scores_lable, 1);
	}

	/////////// pikaqiu移动////////////////////////
	auto snake_head_anix = m_snake.get_position();
	auto mouse_del_x = m_mouse_axis.x - snake_head_anix.x;
	auto mouse_del_y = m_mouse_axis.y - snake_head_anix.y;

	if (std::fabs(mouse_del_x) < 10.0f / 1280 * visible_size.x && std::fabs(mouse_del_y) < 10.0f / 1280 * visible_size.x)
		return;

	auto distance = std::min(m_speed* delta, get_distance(mouse_del_x, mouse_del_y));
	auto a = std::atan(mouse_del_y / mouse_del_x);

	float rot;
	if (mouse_del_x < 0)
	{
		auto tmp = -M_PI / 2.0f - a;
		rot = rad2deg(tmp);
	} 
	else if (mouse_del_x > 0)
	{
		auto tmp = M_PI / 2.0f - a;
		rot = rad2deg(tmp);
	}
	else 
	{
		if (mouse_del_y > 0)
		{
			rot = 0.0f;
		}
		else
		{
			rot = 180.0;
		}
	}

	a = fabs(a);
	float del_x = std::cos(a) * distance;
	float del_y = std::sin(a) * distance;
	if (mouse_del_x < 0)
	{
		del_x *= -1.0f;
	}

	if (mouse_del_y < 0)
	{
		del_y *= -1.0f;
	}

	static auto time_cout = 0.0f;
	if (time_cout > 0.01f) {
		m_snake.move_by(0.01f, del_x, del_y, rot);
		time_cout = 0;
	}
	else {
		time_cout += delta;
	}
}

void GameScreen::on_mouse_move(Event* event)
{
	EventMouse* e = (EventMouse*)event;

	m_mouse_axis.x = e->getCursorX();
	m_mouse_axis.y = e->getCursorY();
}

Snake::Snake()
{
	auto visible_size = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	m_main = Sprite::create();
	m_main->setPosition(Vec2(origin.x + visible_size.x/2, origin.y + visible_size.y/2));

	m_bodys.resize(4);
	m_bodys[0] = std::shared_ptr<Sprite>(Sprite::create("head.png"));
	m_bodys[1] = std::shared_ptr<Sprite>(Sprite::create("body.png"));
	m_bodys[2] = std::shared_ptr<Sprite>(Sprite::create("body.png"));
	m_bodys[3] = std::shared_ptr<Sprite>(Sprite::create("body.png"));

	int offset = 0;
	float scale = visible_size.y / 8 / m_bodys[0]->getContentSize().y;
	for (auto& i : m_bodys) {
		m_main->addChild(i.get());
		i->setScale(scale);
		i->setPosition(Vec2(0.0f, offset));
		offset -= 50.0f / 1280 * visible_size.x;
	}
	m_bodys[0]->setPosition(Vec2(visible_size.x/180, visible_size.y/55));  // 矫正头部坐标
}

void Snake::move_by(float duration, float x, float y, float rot)
{
	auto visible_size = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	m_later_position.resize(m_bodys.size());
	for (size_t i = 0; i < m_bodys.size(); ++i)
	{
		Attitude attitude;
		attitude.position = m_bodys[i]->getPosition();
		attitude.rot = m_bodys[i]->getRotation();
		m_later_position[i] = attitude;
	}
	auto action_move = MoveBy::create(duration, Vec2(x, y));
	auto action_rot  = RotateTo::create(duration, rot);
	auto actions	 = Spawn::createWithTwoActions(action_move, action_rot);
	m_bodys[0]->runAction(actions);

	auto distance = get_distance(x, y);
	for (size_t i = 1; i < m_later_position.size(); ++i)
	{
		Attitude latter_attitude = m_later_position[i - 1];
		auto position = m_bodys[i]->getPosition();
		auto del_x = latter_attitude.position.x - position.x;
		auto del_y = latter_attitude.position.y - position.y;
		auto del_rot = latter_attitude.rot - m_bodys[i]->getRotation();

		static auto k1 = 12.0 / 144 * glfwGetVideoMode(glfwGetPrimaryMonitor())->refreshRate;
		static auto k2 = 10.0 / 144 * glfwGetVideoMode(glfwGetPrimaryMonitor())->refreshRate;
		auto body_action_move = MoveBy::create(duration, Vec2(del_x/k1, del_y/k1));
		auto body_action_rot  = RotateBy::create(duration, del_rot/k2);
		auto body_actions	  = Spawn::createWithTwoActions(body_action_move, body_action_rot);
		m_bodys[i]->runAction(body_actions);
	}
}

void Snake::add_body()
{
	auto visible_size = Director::getInstance()->getVisibleSize();
	float scale = visible_size.y / 8 / m_bodys[0]->getContentSize().y;

	m_bodys.push_back(std::shared_ptr<Sprite>(Sprite::create("body.png")));
	auto position = m_bodys[m_bodys.size()-2]->getPosition();
	m_bodys[m_bodys.size() - 1]->setScale(scale);
	m_bodys[m_bodys.size() - 1]->setPosition(position);
	m_main->addChild(m_bodys[m_bodys.size() - 1].get());
}

bool Snake::is_head_hit_body()
{
	return false;
}

ax::Vec2 Snake::get_position()
{
	Vec2 result;
	auto main_position = m_main->getPosition();
	auto head_position = m_bodys[0]->getPosition();
	result.x = main_position.x + head_position.x;
	result.y = main_position.y + head_position.y;
	return result;
}
