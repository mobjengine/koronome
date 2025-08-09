/*
A retro-styled horror FPS with graphic violence and survival elements.
Copyright (C) 2025  mobjengine

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <SFML/Graphics.hpp>
#include <stdarg.h>
#include <math.h>
#include "k_main.hh"
#include "k_lump.hh"

int main(int argc, const char **argv) {
    K_LumpInit(argc, argv);

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "KORONOME");

    lump_t *l = &lumps["ground1.png"];
    uint8_t d[l->size];
    l->data(d);

    sf::Texture texture;
    texture.loadFromMemory(d, l->size);

    // Crear quad con coordenadas de pantalla (forma trapezoidal)
    sf::VertexArray quad(sf::Quads, 4);

    quad[0].position = sf::Vector2f(100, 300); // abajo izq
    quad[1].position = sf::Vector2f(300, 300); // abajo der
    quad[2].position = sf::Vector2f(250, 150); // arriba der (más cerca)
    quad[3].position = sf::Vector2f(150, 150); // arriba izq

    // Coordenadas de textura (mapear quad a toda la imagen)
    quad[0].texCoords = sf::Vector2f(0, texture.getSize().y);
    quad[1].texCoords = sf::Vector2f(texture.getSize().x, texture.getSize().y);
    quad[2].texCoords = sf::Vector2f(texture.getSize().x, 0);
    quad[3].texCoords = sf::Vector2f(0, 0);

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(quad, &texture);
        window.display();
    }

    return EXIT_SUCCESS;
}

void K_LogInfo(const char *fmt, ...)
{
    va_list	argptr;

    va_start (argptr,fmt);
    fprintf (stdout, "Info: ");
    vfprintf (stdout,fmt,argptr);
    fprintf (stdout, "\n");
    va_end (argptr);

    fflush( stdout );
}
