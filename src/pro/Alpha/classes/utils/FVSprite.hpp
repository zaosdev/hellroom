#pragma once

#include <SFML/Graphics.hpp>
#include "math.hpp"


namespace sfml_util{

   struct FVSprite : sf::Drawable, sf::Transformable
   {

        void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            states.transform *= getTransform();

            states.texture = texPtr_;

            target.draw(vertices_, states);
        }

        void assignTexture(sf::Texture* newTex)
        {
            if(newTex) texPtr_ = newTex;
            else std::terminate();
        }

        void initVertexArray( FVmath::Point2Di Size, std::vector<int>& tileMapLayer, FVmath::Point2Di tileSize )
        {
            vertices_.setPrimitiveType(sf::Quads);
            vertices_.resize(Size.x * Size.y *4);

            int gid{-1}, tu, tv;
            sf::Vertex* quad;

            for(int i{0}; i<Size.x ; i++)
            {
                for(int j{0}; j<Size.y; j++)
                {
                    gid = tileMapLayer[i+j*Size.x];

                    tu = gid % (texPtr_->getSize().x / tileSize.x);
                    tv = gid / (texPtr_->getSize().x / tileSize.x);

                    quad = &vertices_[(i+j*Size.x )*4];

                    quad[0].position = sf::Vector2f(i*tileSize.x, j*tileSize.y);
                    quad[1].position = sf::Vector2f((i+1)*tileSize.x, j*tileSize.y);
                    quad[2].position = sf::Vector2f((i+1)*tileSize.x, (j+1)*tileSize.y);
                    quad[3].position = sf::Vector2f(i*tileSize.x, (j+1)*tileSize.y);

                    quad[0].texCoords = sf::Vector2f(tu *tileSize.x , tv * tileSize.y);
                    quad[1].texCoords = sf::Vector2f((tu+1) *tileSize.x , tv * tileSize.y);
                    quad[2].texCoords = sf::Vector2f((tu+1) *tileSize.x , (tv+1) * tileSize.y);
                    quad[3].texCoords = sf::Vector2f(tu *tileSize.x , (tv+1) * tileSize.y);

                }
            }
        }

        private:

        sf::VertexArray vertices_;

        sf::Texture* texPtr_;
   };

}