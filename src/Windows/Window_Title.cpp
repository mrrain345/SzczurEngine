#include <Windows/Window_Title.h>
#include <SFML/Graphics.hpp>

namespace Szczur {
	static Vector2 bezier(Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3, float t) {
		float mt0 = t*t*t;
		float mt1 = (1-t) * t * t;
		float mt2 = (1-t) * (1-t) * t;
		float mt3 = (1-t) * (1-t) * (1-t);
		
		Vector2 point;
		point.x = mt3 * p0.x + 3 * mt2 * p1.x + 3 * mt1 * p2.x + mt0 * p3.x;
		point.y = mt3 * p0.y + 3 * mt2 * p1.y + 3 * mt1 * p2.y + mt0 * p3.y;
		return point;
	};


	static int x, y, _width, _height;
	static float start_x;
	static float start_y;
	static float end_x;
	static float end_y;
	
	static Vector2 p[7];
	static bool isPressed = false;
	static int pointId = 0;

	Window_Title::Window_Title() {
		setActive();
		
		option = 0;
		options_count = 4;
		
		options[0] = sf::String(L"Nowa Gra");
		options[1] = sf::String(L"Wczytaj Grę");
		options[2] = sf::String(L"Ustawienia");
		options[3] = sf::String(L"Wyjdź");
		
		_width = 280;
		_height = options_count * 32 + 32;
		x = (Game::width() - _width) / 2;
		y = Game::height() - _height - 64;
		
		start_x = float(x);
		start_y = float(y);
		end_x = 32;
		end_y = Game::height() - _height - 32.0f;
		
		p[0].set(100, 100); //point 0
		p[1].set(100, 150); //hand 0
		
		p[2].set(300, 150); //hand 1
		p[3].set(300, 100); //point 1
		p[4].set(300,  50); //hand 1
		
		p[5].set(500,  50); //hand 2
		p[6].set(500, 100); //point 2
	}
	
	static int animMode = 0;
	static float time = 0;
	
	void Window_Title::refresh() {
		content.fill(Color(128, 128, 128));
		
		// BEZIER BEGIN
		content.textColor = Color::Black;
		content.drawText(Vector2(550, 90), L"<- Nie zwracaj uwagi na tą\n     krzywą Beziera :P", 32);
		content.textColor = Color::White;
		
		//Line 1
		sf::VertexArray line1(sf::LinesStrip, 2);
		for (int i = 0; i < 2; i++) {
			line1[i].position = p[i];
			if (isPressed && pointId == i) line1[i].color = Color::Green;
			else line1[i].color = Color::Red;
		}
		Game::draw(line1);
		
		//Line 2
		sf::VertexArray line2(sf::LinesStrip, 3);
		for (int i = 0; i < 3; i++) {
			line2[i].position = p[i+2];
			if (isPressed && pointId == i+2) line2[i].color = Color::Green;
			else line2[i].color = Color::Red;
		}
		Game::draw(line2);
		
		//Line 3
		sf::VertexArray line3(sf::LinesStrip, 2);
		for (int i = 0; i < 2; i++) {
			line3[i].position = p[i+5];
			if (isPressed && pointId == i+5) line3[i].color = Color::Green;
			else line3[i].color = Color::Red;
		}
		Game::draw(line3);
		
		//Bezier Curve
		sf::VertexArray curve(sf::LinesStrip, 41);
		for (int i = 0; i <= 40; i++) curve[i].position = bezier(p[0], p[1], p[2], p[3], i/40.0f);
		Game::draw(curve);
		
		sf::VertexArray curve2(sf::LinesStrip, 41);
		for (int i = 0; i <= 40; i++) curve2[i].position = bezier(p[3], p[4], p[5], p[6], i/40.0f);
		Game::draw(curve2);
		
		//Handlers
		for (int i = 0; i < 7; i++) {
			sf::CircleShape cs(3);
			cs.setPosition(p[i]);
			cs.setOrigin(3, 3);
			if (isPressed && pointId == i) cs.setFillColor(Color::Green);
			else cs.setFillColor(Color::Red);
			Game::draw(cs);
		}
		
		// BEZIER END
		
		content.fillRect(Rect(x, y, _width, _height), Color(44, 200));
		content.fillRect(Rect(x + 16,  y + 16 + option*32, _width - 32, 32), Color::White);
		
		for (int i = 0; i < options_count; i++) {
			if (i == option) content.textColor = Color::Black;
			if (i == 1) content.textColor = Color(128, 128, 128);
			content.drawText(Vector2(x + 16.0f, y + 16.0f + i * 32.0f), options[i].toWideString().c_str(), 24);
			content.textColor = Color::White;
		}
		
		if (animMode > 0) {
			content.fillRect(Rect(Game::width()/2 - 250, Game::height()/2-50, 500, 100), Color(44, 200*time));
			content.textColor = Color(255, 255*time);
			content.drawText(Vector2(Game::width()/2 - 250+32, Game::height()/2-50+32), L"Ustawień nie ma ale też jest zajebiście ;)", 24);
			content.textColor = Color::White;
		}
	}
	
	static float anim_linear(float x) { return x; }
	static float anim_cos(float x) { return float(-cos(x * M_PI / 2) + 1); }
	static float anim_cos2(float x) { return float(-cos(x * M_PI) + 1) / 2; }
	static float anim_asin(float x) { return asin(x); }
	
	void Window_Title::update() {
		if (animMode == 0) return;
		if (animMode == 1) time += Time::realDeltaTime()*4;
		if (animMode == 3) time -= Time::realDeltaTime()*4;
		
		x = int(content.animation(start_x, end_x, anim_cos, time));
		y = int(content.animation(start_y, end_y, anim_cos, time));
		
		if (animMode == 1) {
			if (time > 1) {
				animMode = 2;
				time = 1;
				x = int(end_x);
				y = int(end_y);
			}
			Game::refresh();
		}
		
		if (animMode == 3) {
			if (time < 0) {
				animMode = 0;
				time = 0;
				x = int(start_x);
				y = int(start_y);
			}
			Game::refresh();
		}
	}
	
	void Window_Title::onMousePress(Input::Button button) {
		if (button != Input::BTN_LEFT) return;
		Vector2 pos = Input::mousePosition();
		
		static int offset = 7;
		
		for (int i = 0; i < 7; i++) {
			if (Rect(p[i].x-offset, p[i].y-offset, 6+offset, 6+offset).contains(pos)) {
				isPressed = true;
				pointId = i;
				Game::refresh();
			}
		}
	}
	
	void Window_Title::onMouseMove(int x, int y) {
		if (!isPressed) return;
		Vector2 pos = Input::mousePosition();
		p[pointId].set(x, y);
		if (Input::isKeyReleased(Input::KEY_SHIFT)) {
			if (pointId == 2)		p[4] = p[3] + (p[3] - p[2]);
			else if (pointId == 4)	p[2] = p[3] + (p[3] - p[4]);
		}
		Game::refresh();
	}
	
	void Window_Title::onMouseRelease(Input::Button button) {
		if (isPressed) Game::refresh();
		isPressed = false;
	}
	
	void Window_Title::onKeyPress(Input::Key key) {
		if (key == Input::KEY_UP) {
			option--;
			if (option < 0) option = options_count-1;
			if (option == 1) option--;
			Game::refresh();
		}
		
		if (key == Input::KEY_DOWN) {
			option++;
			if (option >= options_count) option = 0;
			if (option == 1) option++;
			Game::refresh();
		}
		
		if (key == Input::KEY_ENTER) {
			if (option == 0) { new Window_Map(); close(); }
			if (option == 2 && animMode == 0) { time = 0; animMode = 1; }
			if (option == 2 && animMode == 2) { time = 1; animMode = 3; }
			if (option == options_count-1) Game::close();
		}
	}
}
