#pragma once

#include <vector>
#include "math.hpp"
#include <SFML/System/Clock.hpp>

namespace FVAI {
    struct linearIterator {
        using PointType = FVmath::Point2Di;
        static const int nullValue = -9999999;

    public:
        void setPath(std::vector<PointType> path);

        void addPoint(PointType point);

        PointType getNext();

        PointType getCurrent() const;

        std::vector<PointType> getPath();

        void clear(); 

        bool isStuck();

    private:
        std::vector<PointType> path_ {};
        float passedTime_ {0};
        size_t size_      {0};
        size_t current_   {0};
        sf::Clock clock_   {};
        static constexpr float maxTileTime = {1.f};
    };
};