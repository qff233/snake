#ifndef _GAME_SCREEN_H_
#define _GAME_SCREEN_H_

#include "axmol.h"

#include <vector>

struct Attitude {
	ax::Vec2 position;
	float rot;
};

class Snake{
public:
	Snake();

	void move_by(float duration, float x, float y, float rot);
	void add_body();
	bool is_head_hit_body();

	ax::Vec2 get_position();
	ax::Sprite* get_data() { return m_main; }
private:
	ax::Sprite* m_main;
	std::vector<std::shared_ptr<ax::Sprite>> m_bodys;
	std::vector<Attitude> m_later_position;
};

class GameScreen : public ax::Scene {
public:

	bool init() override;
	void update(float delta) override;
private:
	void on_mouse_move(ax::Event* event);

private:
	Snake m_snake;
	ax::Sprite* m_pea;
	ax::Vec2 m_mouse_axis;
	ax::EventListenerMouse* m_mouse_listener;

	float m_speed;

	ax::Label* m_scores_lable;
	size_t m_scores = 0;
};


#endif