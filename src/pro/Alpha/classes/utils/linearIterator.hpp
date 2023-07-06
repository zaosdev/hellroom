#pragma once

#include <vector>
#include "math.hpp"

namespace FVAI {
    struct linearIterator {
        using PointType = FVmath::Point2Di;

    public:
        void setPath(std::vector<PointType> path);

        void addPoint(PointType point);

        PointType getNext();

        PointType getCurrent() const;

        std::vector<PointType> getPath();
    private:
        std::vector<PointType> path_;
        size_t current_;
        size_t size_;
    };
};