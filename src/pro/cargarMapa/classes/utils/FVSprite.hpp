#pragma once

#include <SFML/Graphics.hpp>

namespace sfml_util{

   struct FVSprite : sf::Drawable, sf::Transformable
   {

        void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            states.transform *= getTransform();

            states.texture = texPtr_;

            target.draw(vertices_, states);
        }

        void initVertexArray( int width, int height, std::vector<int> tileMapLayer, int tileWidth, int tileHeight)
        {
            vertices_.setPrimitiveType(sf::Quads);
            vertices_.resize(width * height *4);

            int gid{-1}, tu, tv;
            sf::Vertex* quad;

            for(int i{0}; i<height; i++)
            {
                for(int j{0}; j<width; j++)
                {
                    gid = tileMapLayer[i+j*width];

                    tu = gid % (texPtr_->getSize().x / tileWidth );
                    tv = gid / (texPtr_->getSize().x / tileWidth );

                    quad = &vertices_[(i+j*width)*4];

                    quad[0].position = sf::Vector2f(i*tileWidth, j*tileHeight);
                    quad[1].position = sf::Vector2f((i+1)*tileWidth, j*tileHeight);
                    quad[2].position = sf::Vector2f((i+1)*tileWidth, (j+1)*tileHeight);
                    quad[3].position = sf::Vector2f(i*tileWidth, (j+1)*tileHeight);

                    quad[0].texCoords = sf::Vector2f(tu *tileWidth , tv * tileHeight);
                    quad[1].texCoords = sf::Vector2f((tu+1) *tileWidth , tv * tileHeight);
                    quad[2].texCoords = sf::Vector2f((tu+1) *tileWidth , (tv+1) * tileHeight);
                    quad[3].texCoords = sf::Vector2f(tu *tileWidth , (tv+1) * tileHeight);

                }
            }
        }

        private:

        sf::VertexArray vertices_;

        sf::Texture* texPtr_;
   };

}