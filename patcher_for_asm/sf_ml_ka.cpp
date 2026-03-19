#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <optional>
#include <iostream>

#include "A_Main.h"


#define mouse_on_noo(randy_) \
            (mousePose.x > POSE_noo_OX + (float)randy_) && (mousePose.x < POSE_noo_OX + (float)randy_ + SIZE_but_OX) && \
                            (mousePose.y > POSE_noo_minus_OY + (float)randy_) && (mousePose.y < POSE_noo_minus_OY + (float)randy_ + SIZE_but_OY) \

#define mouse_on_yes(dobavka_) \
            (mousePose.x > POSE_yes_OX + dobavka_) && (mousePose.x < POSE_yes_OX + dobavka_ + SIZE_but_OX) && \
                            (mousePose.y > POSE_yes_minus_OY + dobavka_) && (mousePose.y < POSE_yes_minus_OY + dobavka_ + SIZE_but_OY) \


sf::Text text_create(sf::Vector2f pose, const char* yes_noo, sf::Font *font);

sf::RectangleShape create_butt(sf::Color color, sf::Vector2f pose);

void video_pusk_opreddelennoe(unsigned int OX, unsigned int OY, const char* name_vi, const char* format, size_t start_num_kadr, size_t finish_num_kadr, int mili_se_fps);

void update_window(sf::Sprite *morbius, sf::RenderWindow *window, int *what_now, int randy, struct Main_ wnd);

void what_draw(sf::Sprite *morbius, sf::RenderWindow *window, const char* name_vi, const char* format, int num_of_picture, struct Main_ wnd);



struct Main_
{
    sf::RectangleShape button_yes;
    sf::RectangleShape button_noo;

    sf::Text text_yes;
    sf::Text text_noo;

    sf::Text text_of_question;
};


int okno_sfml(const char* question)
{
    sf::RenderWindow window(sf::VideoMode({OX_OX, OY_OY}), "HAHAHACKER"); //создаем окно размером


    auto button_yes = create_butt(sf::Color(7, 67, 245), {POSE_yes_OX, POSE_yes_minus_OY});
    auto button_noo = create_butt(sf::Color(245, 7, 67), {POSE_noo_OX, POSE_noo_minus_OY});     //sf::RectangleShape


    sf::Font font;
    (void)font.openFromFile("Garamond Classico SC Regular.ttf");

    auto text_yes = text_create({POSE_yes_OX + 77, POSE_yes_minus_OY + 10}, "yes", &font);
    auto text_noo = text_create({POSE_noo_OX + 87, POSE_noo_minus_OY + 10}, "no" , &font);       //sf::Text
    
    //question
    auto text_of_question = text_create({(float)OX_OX / 2 - 100, (float)OY_OY - 60}, question, &font);
    
    Main_ for_wnd = {button_yes, button_noo, text_yes, text_noo, text_of_question};

   //
    sf::Texture texture_main_f;
    (void)texture_main_f.loadFromFile("morbius_moment/true_morbi.JPG");
   //
    sf::Sprite morbius(texture_main_f);        // morbius.setTexture(texture_main_f);

    // morbius.setPosition({123, -24});    //coordinats
    // morbius.setScale({1.1f, 1.1f});

    morbius.setPosition({126, -70});
    morbius.setScale({0.6f, 0.6f});

    int randy = 0;
    int what_now = 0;
    while(window.isOpen()) 
    {
        while(auto event = window.pollEvent()) //достаем событие
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            auto mousePose = sf::Mouse::getPosition(window);  //Vector2i
 
            update_window(&morbius, &window, &what_now, randy, for_wnd);

            //No
            if (auto* click = event->getIf<sf::Event::MouseButtonPressed>())    //достаем из событий нажатие мыши 
                {
                    if (click->button == sf::Mouse::Button::Left)   //кнопку через структуру///////////////
                    {
                        if((mousePose.x > POSE_noo_OX + (float)randy) && (mousePose.x < POSE_noo_OX + (float)randy + SIZE_but_OX) && \
                            (mousePose.y > POSE_noo_minus_OY + (float)randy) && (mousePose.y < POSE_noo_minus_OY + (float)randy + SIZE_but_OY))
                            {
                                randy = rand(); // max = 32767
                                randy = randy %400;
                                if(randy > 200)
                                    randy = randy * (-1) - 200;

                                button_noo = create_butt(sf::Color(245, 7, 67), {POSE_noo_OX + (float)randy, POSE_noo_minus_OY + (float)randy});     //sf::RectangleShape
                                text_noo = text_create({POSE_noo_OX + 87 + (float)randy, POSE_noo_minus_OY + 10 + (float)randy}, "no" , &font);


                                for_wnd.button_noo = button_noo;
                                for_wnd.text_noo = text_noo;
                            }
                    }
                }

            //Yes
            if (auto* click = event->getIf<sf::Event::MouseButtonPressed>())
                {
                    if (click->button == sf::Mouse::Button::Left)
                    {
                        if((mousePose.x > POSE_yes_OX) && (mousePose.x < POSE_yes_OX + SIZE_but_OX) && \
                            (mousePose.y > POSE_yes_minus_OY) && (mousePose.y < POSE_yes_minus_OY + SIZE_but_OY))
                                return JUST_YES;
                    }
                }
        }
            
        window.clear();

        ART(morbius);

        ART(button_yes);
        ART(text_yes);

        ART(button_noo);
        ART(text_noo);

        ART(text_of_question);
        
        window.display();
    }
    
    return 0;
}


sf::RectangleShape create_butt(sf::Color color, sf::Vector2f pose)
{
    sf::RectangleShape button(sf::Vector2f(SIZE_but_OX, SIZE_but_OY));   //size in float -- Vector2_f/i/ui
    button.setFillColor(color);
    button.setPosition(pose);

    return button;
}


sf::Text text_create(sf::Vector2f pose, const char* yes_noo, sf::Font *font)
{
    sf::Text text(*font, yes_noo, 22);
    text.setFillColor(sf::Color::White);
    text.setPosition(pose);

    return text;
}

   
void update_window(sf::Sprite *morbius, sf::RenderWindow *window, int *what_now, int randy, struct Main_ wnd)
{
    auto mousePose = sf::Mouse::getPosition(*window);

    if(mouse_on_yes(0))     // on button
    {
        usleep(100000);
        if(*what_now == 0)
        {
            what_draw(morbius, window, "morbius_moment/veseli_", ".JPG", 4, wnd);
            (*what_now)++;
        }
        else
        {
            what_draw(morbius, window, "morbius_moment/veseli_", ".JPG", 5, wnd);
            (*what_now)--;
        }

        return ;
    }

    if(mouse_on_yes(20))     
    {
        what_draw(morbius, window, "morbius_moment/veseli_", ".JPG", 3, wnd);

        return ;
    }
        
    if(mouse_on_yes(45))
    {
        what_draw(morbius, window, "morbius_moment/veseli_", ".JPG", 2, wnd);

        return ;
    }

    if(mouse_on_yes(70))   
    {
        what_draw(morbius, window, "morbius_moment/veseli_", ".JPG", 1, wnd);

        return ;
    }

    if(mouse_on_noo(randy))
    {
        usleep(100000);
        if(*what_now == 0)
        {
            what_draw(morbius, window, "morbius_moment/zloy_", ".JPG", 4, wnd);
            (*what_now)++;
        }
        else
        {
            what_draw(morbius, window, "morbius_moment/zloy_", ".JPG", 5, wnd);
            (*what_now)--;
        }

        return ;
    }
 
    if(mouse_on_noo(randy + 20))    
    {
        what_draw(morbius, window, "morbius_moment/zloy_", ".JPG", 3, wnd);

        return ;
    }

    if(mouse_on_noo(randy + 45))    
    {
        what_draw(morbius, window, "morbius_moment/zloy_", ".JPG", 2, wnd);

        return ;
    }

    if(mouse_on_noo(randy + 70))    
    {
        what_draw(morbius, window, "morbius_moment/zloy_", ".JPG", 1, wnd);

        return ;
    }


    static sf::Texture texture_main;
    (void)texture_main.loadFromFile("morbius_moment/true_morbi.JPG");

    morbius->setTexture(texture_main);

    return ;
}


void what_draw(sf::Sprite *morbius, sf::RenderWindow *window, const char* name_vi, const char* format, int num_of_picture, struct Main_ wnd)
{
    char str[513] = {};
    snprintf(str, sizeof(str), "%s%d%s", name_vi, num_of_picture, format);

    static sf::Texture New_textureveseli_4;
    (void)New_textureveseli_4.loadFromFile(str);

    morbius->setTexture(New_textureveseli_4);

    window->clear();
    window->draw(*morbius);

    window->draw(wnd.button_yes);
    window->draw(wnd.text_yes);

    window->draw(wnd.button_noo);
    window->draw(wnd.text_noo);

    window->draw(wnd.text_of_question);

    window->display();

    return ;
}


void video_pusk_opreddelennoe(unsigned int OX, unsigned int OY, const char* name_vi, const char* format, size_t start_num_kadr, size_t finish_num_kadr, int mili_se_fps)
{
    sf::RenderWindow window(sf::VideoMode({OX, OY}), "Hack_ed"); //создаем окно размером

    while(window.isOpen()) 
    {
        char str[513] = {};
        for(int i = start_num_kadr; i <= finish_num_kadr; ++i)
        {     
            snprintf(str, sizeof(str), "%s%d%s", name_vi, i, format);

            sf::Texture textura_ostrov;
            (void)textura_ostrov.loadFromFile(str);
        
            sf::Sprite ostrov(textura_ostrov);

            while(auto event = window.pollEvent())
                if (event->is<sf::Event::Closed>())
                    window.close();
            
            window.clear();

            ART(ostrov);
            usleep(mili_se_fps);
            
            window.display();
        }

        break;
    }
}
