#include "pch.h"
#include "Game.h"

void Game::initializeVariables()
{
    this->window = nullptr;
    this->fullscreen = false;
    this->dtime = 0.f;
}

void Game::initializeWindow()
{
    //creates sfml window

    std::ifstream file("Config/window.ini");

    this->VideoModes = sf::VideoMode::getFullscreenModes();

    std::string title = "None";
    sf::VideoMode window_size = sf::VideoMode::getDesktopMode();
    bool fullscreen = false;
    unsigned framerate_limit = 60;
    bool Vsync = false;
    unsigned antialiasing_level = 0;

    if (file.is_open())
    {
        std::getline(file, title);
        file >> window_size.width >> window_size.height;
        file >> fullscreen;
        file >> framerate_limit;
        file >> Vsync;
        file >> antialiasing_level;
    }

    file.close();

    this->fullscreen = fullscreen;
    this->window_settings.antialiasingLevel = antialiasing_level;

    if (this->fullscreen)
    {
        this->window = new sf::RenderWindow(window_size, title, sf::Style::Fullscreen, window_settings);
    }
    else
    {
        this->window = new sf::RenderWindow(window_size, title, sf::Style::Titlebar | sf::Style::Close, window_settings);
    }

    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(Vsync);
}

void Game::initalizeKeys()
{
    std::ifstream file("Config/supportedkeys.ini");

    if (file.is_open())
    {
        std::string key = "";
        int key_value = 0;

        while (file >> key >> key_value)
        {
            this->supportedKeys[key] = key_value;
        }
    }

    file.close();
}

void Game::initalizeStates()
{
    this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}

Game::Game()
{
    this->initializeWindow();
    this->initalizeKeys();
    this->initalizeStates();
}

Game::~Game()
{
    delete this->window;

    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
        //removing 1) the data and 2) pointer
    }
}

void Game::endGameApp()
{
    std::cout << "Ending the game process\n";
}

void Game::updateDt()
{
    //updates dtime with the time is takes to render one frame

    this->dtime = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLevents()
{
    while (this->window->pollEvent(this->Events))
    {
        if (this->Events.type == sf::Event::Closed)
            this->window->close();
    }
}

//updating current state
void Game::update()
{
    this->updateSFMLevents();

    if (!this->states.empty())
    {
        this->states.top()->update(this->dtime);
        
        if (this->states.top()->getEnd())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
//Closing the game
    else
    {
        this->endGameApp();
        this->window->close();
    }
} 

void Game::render()
{
    this->window->clear(); //clear old frame

    //rendering stuff
    if (!this->states.empty())
    {
        this->states.top()->render(this->window); //render to the window
    }

    this->window->display(); //window is done drawing
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}
