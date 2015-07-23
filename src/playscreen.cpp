/*
Project: Xoria
File: playscreen.cpp
Author: Joel McFadden
Created: July 13, 2015
Last Modified: July 22, 2015

Description:
    A simple sci-fi roguelike.

Copyright (C) 2015 Joel McFadden

Usage Agreement:
    This file is part of Xoria.

    Xoria is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Xoria is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Xoria.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "playscreen.h"

PlayScreen::PlayScreen(World& world, int width, int height)
    : Tui{world, width, height}
{
}

std::unique_ptr<Tui> PlayScreen::processNextEvent()
{
    // player's turn
    std::unique_ptr<Tui> nextScreen = processPlayerEvent();

    // monsters' turns
    processMonsterEvents();

    return nextScreen;
}

void PlayScreen::render()
{
    // clear screen
    console_.clear();

    // draw map
    world_.currentMap().render(&console_);

    // blit to root console
    TCODConsole::blit(&console_, 0, 0, 0, 0, TCODConsole::root, 0, 0);
}

std::unique_ptr<Tui> PlayScreen::processPlayerEvent()
{
    Entity& player = world_.currentMap().getPlayer();

    // move player
    switch (lastKeyPressed_.vk) {
    case TCODK_UP:
        player.move( 0, -1);
        break;
    case TCODK_DOWN:
        player.move( 0,  1);
        break;
    case TCODK_LEFT:
        player.move(-1,  0);
        break;
    case TCODK_RIGHT:
        player.move( 1,  0);
        break;
    default:
        break;
    }

    // quit game
    if (lastKeyPressed_.c) {
        switch (lastKeyPressed_.c) {
        case 'Q':
            close();
            break;
        default:
            break;
        }
    }

    return nullptr;
}

void PlayScreen::processMonsterEvents()
{

}
