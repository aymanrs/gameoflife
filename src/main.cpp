#include <SFML/Graphics.hpp>
#define COLUMNS 140
#define ROWS 90
#define CASE_SIDE 8
#define BORDER_WIDTH 3
#define OVER_POPULATION 4
#define ISOLATION 1
#define BIRTH 3

unsigned short countNeighbours(unsigned int x, unsigned int y, bool backup[][ROWS+2]){
	unsigned short count = 0;
	for(unsigned int i = x-1;i <= x+1;i++){
		for(unsigned int j = y-1;j <= y+1;j++){
			count += backup[i][j];
		}
	}
	return count - backup[x][y];
}

int main(){
	sf::RenderWindow app;
	app.create(sf::VideoMode(COLUMNS * (CASE_SIDE + BORDER_WIDTH), ROWS * (CASE_SIDE + BORDER_WIDTH)), "Game Of Life");
	sf::Event event;
	bool start = false;
	bool matrix[COLUMNS+2][ROWS+2] = {0}, backup[COLUMNS+2][ROWS+2] = {0};
	sf::RectangleShape cases[COLUMNS][ROWS];
	for(unsigned int i = 0;i < COLUMNS;i++){
		for(unsigned int j = 0;j < ROWS;j++){
			cases[i][j].setFillColor(sf::Color::White);
			cases[i][j].setSize(sf::Vector2f(CASE_SIDE, CASE_SIDE));
			cases[i][j].setPosition(CASE_SIDE*i + BORDER_WIDTH*i, CASE_SIDE*j + BORDER_WIDTH*j);
			cases[i][j].setOutlineThickness(BORDER_WIDTH);
			cases[i][j].setOutlineColor(sf::Color::Blue);
		}
	}
	sf::Clock clock;
	while(app.isOpen()){
		while(app.pollEvent(event)){
			switch(event.type){
			case sf::Event::Closed:
				app.close();
				break;
			case sf::Event::MouseButtonPressed:
				matrix[event.mouseButton.x / (CASE_SIDE + BORDER_WIDTH) + 1][event.mouseButton.y / (CASE_SIDE + BORDER_WIDTH) + 1] = !matrix[event.mouseButton.x / (CASE_SIDE + BORDER_WIDTH) + 1][event.mouseButton.y / (CASE_SIDE + BORDER_WIDTH) + 1];
				break;
			case sf::Event::KeyPressed:
				if(event.key.code == sf::Keyboard::Space) start = !start;
				else if(event.key.code == sf::Keyboard::R) 
				for(unsigned int i = 1;i <= COLUMNS;i++){
					for(unsigned int j = 1;j <= ROWS;j++){
						matrix[i][j] = false;
					}
				}
				break;
			default:
				break;
			}
		}
		for(unsigned int i = 1;i <= COLUMNS;i++){
			for(unsigned int j = 1;j <= ROWS;j++){
				backup[i][j] = matrix[i][j];
			}
		}
		app.clear(sf::Color::Black);
		if(start && clock.getElapsedTime().asMilliseconds() >= 100) {
			clock.restart();
			for(unsigned int i = 1;i <= COLUMNS;i++){
			for(unsigned int j = 1;j <= ROWS;j++){
				unsigned short count = countNeighbours(i, j, backup);
				if(matrix[i][j]){
					if(count <= ISOLATION || count >= OVER_POPULATION) matrix[i][j] = false;
				} else if(count == BIRTH) matrix[i][j] = true;
			}
		}
	}
		for(unsigned int i = 0;i < COLUMNS;i++){
			for(unsigned int j = 0;j < ROWS;j++){
				if(matrix[i+1][j+1]){
					cases[i][j].setFillColor(sf::Color::Black);
				} else {
					cases[i][j].setFillColor(sf::Color::White);
				}
				app.draw(cases[i][j]);
			}
		}
		app.display();
	}
	return 0;
}
