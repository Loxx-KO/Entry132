#include "pch.h"
#include "Game.h"

void Game::initializeVariables()
{
    this->window = nullptr;
    this->dtime = 0.f;
    this->gridSize = 50.f;
}

void Game::initializeGraphicSettings()
{
    this->graphicSettings.loadFromFile("Config/graphics.ini");
}

void Game::initializeStateData()
{
    this->stateData.window = this->window;
    this->stateData.gfxSettings = &this->graphicSettings;
    this->stateData.supportedKeys = &this->supportedKeys;
    this->stateData.states = &this->states;
    this->stateData.gridSize = this->gridSize;
}

void Game::initializeWindow()
{
    //creates sfml window

    if (this->graphicSettings.fullscreen)
    {
        this->window = new sf::RenderWindow(this->graphicSettings.resolution, 
            this->graphicSettings.title, this->graphicSettings.fullscreen, this->graphicSettings.contextSettings);
    }
    else
    {
        this->window = new sf::RenderWindow(this->graphicSettings.resolution, this->graphicSettings.title,
            sf::Style::Titlebar | sf::Style::Close, this->graphicSettings.contextSettings);
    }

    this->window->setFramerateLimit(this->graphicSettings.frameRateLimit);
    this->window->setVerticalSyncEnabled(this->graphicSettings.verticalSync);
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
    this->states.push(new MainMenuState(&this->stateData));
}

Game::Game()
{
    this->initializeVariables();
    this->initializeGraphicSettings();
    this->initializeWindow();
    this->initalizeKeys();
    this->initializeStateData();
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
