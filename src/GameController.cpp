#include "./headers/GameController.h"

GameController::GameController()
{
    m_score = 0;
    
    if(!m_font.loadFromFile("./assets/font.ttf"))
    {
        std::cerr << "Couldn't load font!";
    }

    //CREATING OUR SCORE TEXT
    m_score_text.setFont(m_font);
    m_score_text.setString("Score: 0");
    m_score_text.setCharacterSize(24); //pixels!
    m_score_text.setFillColor(sf::Color::White);
    m_score_text.setPosition(15,5);

    //CREATING OUR TITLE TEXTS
    m_title_head.setFont(m_font);
    m_title_body.setFont(m_font);
    m_title_head.setString("FLAPPY CLONE!");
    m_title_body.setString("Press SPACE to Start!");

    m_title_head.setFillColor(sf::Color::White);
    m_title_body.setFillColor(sf::Color::White);

    m_title_head.setCharacterSize(42);
    m_title_body.setCharacterSize(30);

    //CREATING OUR GAME OVER TEXTS
    m_gameover_head.setFont(m_font);
    m_gameover_body.setFont(m_font);
    m_gameover_return.setFont(m_font);

    m_gameover_head.setString("GAME OVER!");
    m_gameover_body.setString("Final Score: 0!");
    m_gameover_return.setString("Press P to Return to Start!");

    m_gameover_head.setFillColor(sf::Color::White);
    m_gameover_body.setFillColor(sf::Color::White);
    m_gameover_return.setFillColor(sf::Color::White);

    m_gameover_head.setCharacterSize(42);
    m_gameover_body.setCharacterSize(30);
    m_gameover_return.setCharacterSize(30); 

    
}

GameController& GameController::GetInstance()
{
    static GameController instance;
    return instance;
}

void GameController::AddObserver(const std::shared_ptr<GameObject>& observer)
{
    m_observers.push_back(observer);
}

void GameController::Reset()
{
    std::shared_ptr<GameObject> temp;
    for(const auto& observer : m_observers)
    {
        if(observer->IsPlayer)
        {
            observer->Reset();
            temp = observer;
            break;
        }
    }

    m_observers.clear();
    m_observers.push_back(temp);
    m_score = 0;
    UpdateScoreText();
}


void GameController::NotifyPlayer(const std::string& player_specific_event)
{
    for (const auto& observer : m_observers)
    {
        if(observer->IsPlayer)
        {
            observer->OnNotifyEvent(player_specific_event);
            break;
        }  
    }
}

void GameController::RemoveObserver(const std::shared_ptr<GameObject>& observer)
{ 
     m_pending_removal.push_back(observer);
}

void GameController::NotifyObservers(const std::string& ev)
{
    for (const auto& observer : m_observers)
    {
        observer->OnNotifyEvent(ev);
    }
}

void GameController::UpdateEvent()
{

    //Sends the "update" command to all of our observers
    NotifyObservers("update");

    //Checks to see if we have any game objects that need to be removed, removes if needed
    if(!m_pending_removal.empty())
    {
         for (const auto& observer : m_pending_removal) {
                m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), observer), m_observers.end());
            }
            m_pending_removal.clear(); // Clear the removal list
    }

    //Find our player object for use with collision detection
    std::shared_ptr<GameObject> player_object;
    for (auto o : m_observers)
    {
        if(o->IsPlayer)
        {
            player_object = o;
        }
    }

    //Collision detection phase
    for (auto o : m_observers)
    {   
        if(!o->IsPlayer)
        {   
            if(o->IsColliding(player_object->GetCollider()))
            {
                SoundController::GetInstance().PlaySound("gameover");
                SoundController::GetInstance().StopMusic("background");
                PlayerDeadEvent();
                break;  
            }
            //If the game object is not collinding with the player, check to see if it is behind the player for score keeping
            else if (o->GetPositionX() < player_object->GetPositionX())
            {
                if(!o->Scored)
                {   
                    SoundController::GetInstance().PlaySound("success");
                    m_score += 1;
                    o->Scored = true;
                    UpdateScoreText();
                }
            }
        }
    }    
}



void GameController::DrawEvent()
{ 
    //Sends the "draw" event command to our observers
    NotifyObservers("draw");
}

void GameController::SetGameState(GAMESTATE gamestate)
{
    m_current_state = gamestate;
}

GameController::GAMESTATE GameController::GetGameState()
{
    return m_current_state;
}

void GameController::PlayerDeadEvent()
{
    //TODO ADD FURTHER HANDLING (audio)

    m_current_state = GAME_OVER;
}

void GameController::SetRenderWindow(sf::RenderWindow* window)
{
    m_window = window;
}

void GameController::UpdateScoreText()
{
    //Updates the string of our Score text
    std::stringstream new_text;
    new_text << "Score: " << m_score;
    m_score_text.setString(new_text.str());
}

void GameController::DisplayScoreText()
{
    m_window->draw(m_score_text);
}


void GameController::DisplayTitleText()
{
    //Setting positions of our texts
    float mid_y = m_window->getSize().y / 2;
    m_title_head.setPosition((m_window->getSize().x / 2) - (m_title_head.getGlobalBounds().getSize().x / 2), mid_y - 50 - m_title_head.getGlobalBounds().getSize().y);
    m_title_body.setPosition((m_window->getSize().x / 2) - (m_title_body.getGlobalBounds().getSize().x / 2), mid_y - 25 + m_title_head.getGlobalBounds().getSize().y);

    //Drawing text to window
    m_window->draw(m_title_head);
    m_window->draw(m_title_body);

}

void GameController::DisplayGameOverText()
{
    //Setting our body text string
    std::stringstream str;
    str << "Final Score: " << m_score;
    m_gameover_body.setString(str.str());

    //Setting the positions of our texts
    float mid_y = m_window->getSize().y / 2;
    m_gameover_head.setPosition((m_window->getSize().x / 2) - (m_gameover_head.getGlobalBounds().getSize().x / 2), mid_y - 50 - m_gameover_head.getGlobalBounds().getSize().y);
    m_gameover_body.setPosition((m_window->getSize().x / 2) - (m_gameover_body.getGlobalBounds().getSize().x / 2), mid_y - 25 + m_gameover_head.getGlobalBounds().getSize().y);
    m_gameover_return.setPosition((m_window->getSize().x / 2) - (m_gameover_return.getGlobalBounds().getSize().x / 2), mid_y - 10 + m_gameover_head.getGlobalBounds().getSize().y + m_gameover_body.getGlobalBounds().getSize().y);

    //Drawing to window
    m_window->draw(m_gameover_head);
    m_window->draw(m_gameover_body);
    m_window->draw(m_gameover_return);
}
