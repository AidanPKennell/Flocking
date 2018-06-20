//Aidan Kennell, 5/28/2018
#include "VehicleSystem.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Flocking");
	sf::Clock clock;
	sf::Font font;

	if (!font.loadFromFile("Assets/arialbd.ttf"))
		cout << "Font failed to load." << endl;

	sf::Text sep_text, ali_text, coh_text;
	sep_text.setFont(font);
	sep_text.setString("Separation: OFF");
	sep_text.setCharacterSize(20);
	sep_text.setPosition(5, 5);

	ali_text.setFont(font);
	ali_text.setString("Alignment: OFF");
	ali_text.setCharacterSize(20);
	ali_text.setPosition(5, 25);

	coh_text.setFont(font);
	coh_text.setString("Cohesion: OFF");
	coh_text.setCharacterSize(20);
	coh_text.setPosition(5, 45);

	sf::Vector2f mouse_position;

	VehicleSystem* VS = new VehicleSystem();

	byte sep_ali_coh = 0;

	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {

			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Q) 
					sep_ali_coh = sep_ali_coh ^ SEP_MASK;
				if (event.key.code == sf::Keyboard::W) 
					sep_ali_coh = sep_ali_coh ^ ALI_MASK;				
				if (event.key.code == sf::Keyboard::E) 
					sep_ali_coh = sep_ali_coh ^ COH_MASK;
				break;
			default:
				break;
			}
		}

		if (sep_ali_coh & SEP_MASK)
			sep_text.setString("Separation: ON");
		else
			sep_text.setString("Separation: OFF");

		if(sep_ali_coh & ALI_MASK)
			ali_text.setString("Alignment: ON");
		else
			ali_text.setString("Alignment: OFF");

		if(sep_ali_coh & COH_MASK)
			coh_text.setString("Cohesion: ON");
		else
			coh_text.setString("Cohesion: OFF");


		mouse_position.x = (float)sf::Mouse::getPosition(window).x;
		mouse_position.y = (float)sf::Mouse::getPosition(window).y;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			VS->Add_Vehicle(mouse_position);
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			VS->Remove_Vehicle();
		}
		
		
		VS->Update(clock.restart().asSeconds(), sep_ali_coh);
		
		window.clear();
		window.draw(*VS);
		window.draw(sep_text);
		window.draw(ali_text);
		window.draw(coh_text);
		window.display();
	}
	delete VS;

	return 0;
}
