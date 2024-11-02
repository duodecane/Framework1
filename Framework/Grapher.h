#pragma once
#include "App.h"
#include <deque>
class Grapher {
public:
	bool UpdatePoints(float x, float y) {

		if (x > Max.x)
			Max.x = x;

		if (y > Max.y)
			Max.y = y;

		

		for (auto& i : DataPoints) {
			if (i.first == x) {
				i.second = y;
				return true;
			}
		}
		DataPoints.push_back(std::make_pair(x, y));
		return false;
	}
	__inline Vec2 TransformPoint(float px, float py, float x, float y) {
		px = x + px * ModifierMax.x;
		py = y - 0.5f * py * ModifierMax.y;
		return Vec2(px, py);
	}
	void Render(float x, float y, float w, float h, Col col = Col(255,255,255), bool back = false, Col bckgrnd = Col(0,0,0)) {

		ModifierMax.x = 1.f / (Max.x * 1.05f) * w;
		ModifierMax.y = 1.f / (Max.y * 1.1f) * h;
		
		Vec2 last;
		Vec2 cur;

		if (back) {
			Render::FilledRoundedRect(x, y, w, h, bckgrnd, 3.f);
		}
		y += w * 0.5f;

		for (auto& Point : DataPoints) {
			if (cur.x == 0) {
				cur = TransformPoint(Point.first, Point.second,x,y);
				last = cur;
				continue;
			}

			cur = TransformPoint(Point.first, Point.second, x, y);
			Render::Line(last.x, last.y, cur.x, cur.y, col, 1.5f);
			last = cur;
		}
	}
	Vec2 Max;
	Vec2 ModifierMax;
	std::deque<std::pair<float, float>> DataPoints;
};