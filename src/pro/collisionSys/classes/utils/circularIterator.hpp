#pragma once
#include <vector>
#include "math.hpp"

namespace FVAI {
    struct circularIterator {
        using PointType = FVmath::Point2D;

    public:
        void setPath(std::vector<PointType> path);

        void addPoint(PointType point);

        PointType getNext();

        PointType getCurrent() const;
    private:
        std::vector<PointType> path_;
        size_t current_;
        size_t size_;
    };
};