#pragma
#include <SFML/Graphics.hpp>

class Camera {
private: 
    sf::View view; 
public: 
    Camera() {};
    void InitializeView(Window* window, sf::Vector2f vec) {
        this->view = window->getRenderWindow().getDefaultView(); 
        this->view.setCenter(vec); 
        window->getRenderWindow().setView(this->view);
    }

    void CameraUpdate() {
        // Basic Camera movement/camera shake
    }

    sf::View& getView() {
        return view; 
    }
};