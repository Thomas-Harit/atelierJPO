/*
** EPITECH PROJECT, 2021
** atelierJPO
** File description:
** IA
*/

#include "IA.hpp"

IA::IA() : isJumping(false), isFalling(false), SpriteIt(-1), speed(0), gravity(5)
{
}

IA::IA(const IA &other) : run_text(other.run_text), jump_text(other.jump_text), still_text(other.still_text), SpriteIt(-1)
{
    isJumping = false;
    isFalling = false;
    speed = 0;
    gravity = 5;
}

void IA::GoFaster()
{
    if (isFalling == false && isJumping == false) {
        speed += 1;
    }
}

void IA::GoSlower()
{
    if (isFalling == false && isJumping == false && speed > 0) {
        speed -= 1;
        if (speed <= 0) {
            speed = 0;
            SpriteIt = -1;
        }
    }
}

void IA::Jump()
{
    if (isFalling == false) {
        isJumping = true;
    }
}

void IA::Gravity()
{
    sf::FloatRect rect_1;
    sf::FloatRect rect_2;

    if (isJumping == true)
        return;
    rect_1 = this->sprite.getGlobalBounds();
    rect_1.top += gravity;
    for (auto it : obstacles) {
        if (rect_1.intersects(rect_2)) {
            if (this->isFalling == true)
                this->SpriteIt = -1;
            this->isFalling = false;
            return;
        }
    }
    for (auto it : grounds) {
        rect_2 = it.sprite.getGlobalBounds();
        if (rect_1.intersects(rect_2)) {
            if (this->isFalling == true)
                this->SpriteIt = -1;
            this->isFalling = false;
            return;
        }
    }
    if (this->isFalling == false)
                this->SpriteIt = -1;
    this->isFalling = true;
    this->sprite.move(0, gravity);
}

void IA::Animation()
{
    if (isFalling == true || isJumping == true) {
        this->AnimationInTheAir();
    } else if (speed > 0) {
        this->AnimationRunning();
    } else if (SpriteIt == -1) {
        this->sprite.setTexture(still_text, true);
        SpriteIt += 1;
    }
}

void IA::AnimationRunning()
{
    sf::IntRect rect(0, 0, 48, 36);
    float timing = 0.1;

    if (SpriteIt == -1) {
        this->sprite.setTexture(run_text);
        rect.left = 0;
        this->sprite.setTextureRect(rect);
        SpriteIt += 1;
        clock.reset();
    }
    if (speed > 0)
        timing = 0.1 / speed;
    else
        timing = 0.1;
    if (clock.time() >= timing) {
        SpriteIt += 1;
        if (SpriteIt > 3)
            SpriteIt = 0;
        rect.left = SpriteIt * 48;
        this->sprite.setTextureRect(rect);
        clock.reset();
    }
}

void IA::AnimationInTheAir()
{
    sf::IntRect rect(0, 0, 34, 35);
    float timing = 0.1;

    if (SpriteIt == -1) {
        this->sprite.setTexture(jump_text);
        rect.left = 0;
        this->sprite.setTextureRect(rect);
        SpriteIt += 1;
        clock.reset();
    }
    if (speed > 0)
        timing = 0.1 / speed;
    else
        timing = 0.1;
    if (clock.time() >= timing) {
        SpriteIt += 1;
        if (SpriteIt > 3)
            SpriteIt = 0;
        rect.left = SpriteIt * 34;
        this->sprite.setTextureRect(rect);
        clock.reset();
    }
}

bool IA::IsThereAHole(float distance)
{
    sf::FloatRect rect_1 = this->sprite.getGlobalBounds();
    sf::FloatRect rect_2;

    rect_1.top += rect_1.height;
    rect_1.left += distance;
    for (auto it : grounds) {
        rect_2 = it.sprite.getGlobalBounds();
        if (rect_1.intersects(rect_2) == false)
            return true;
    }
    return false;
}

bool IA::IsThereAnObstacle(float distance)
{
    sf::FloatRect rect_1 = this->sprite.getGlobalBounds();
    sf::FloatRect rect_2;

    for (auto it : obstacles) {
        rect_2 = it.sprite.getGlobalBounds();
        if (rect_1.intersects(rect_2) == true)
            return true;
    }
    return false;
}

void IA::updateMap(std::vector<Obstacle> newObstacles, std::vector<Ground> newGrounds)
{
    obstacles = newObstacles;
    grounds = newGrounds;
}

void IA::updateTexture(sf::Texture newRunText, sf::Texture newJumpText, sf::Texture newStillText)
{
    still_text = newStillText;
    run_text = newRunText;
    jump_text = newJumpText;
    sprite.setTexture(still_text, true);
}