#include "linearIterator.hpp" 
#include <iostream>

namespace FVAI {
    using PointType = linearIterator::PointType;

    PointType linearIterator::getNext() {
        if (current_ < path_.size() - 1) {
            ++current_;
            return path_[current_];
        } else {
            // Se alcanzó el final del vector, devolver un valor indicativo de fin
            std::cout << "Se alcanzo el final del vector..."
            << "size: "  << size_ 
            << "current: " << current_ 
            << "path size: " << path_.size()
            << std::endl;
            return {nullValue, nullValue}; 
        }
    }

    PointType linearIterator::getCurrent() const {
        return path_[current_];
    }

    void linearIterator::setPath(std::vector<PointType> path) {
        path_ = path;
        current_ = 0;
        size_ = path.size();
    }

    void linearIterator::addPoint(PointType point) {
        path_.push_back(point);
        ++size_;
    }

    std::vector<PointType> linearIterator::getPath() {
        return path_;
    }

    void linearIterator::clear()
    {
        path_.clear();
        current_ = 0;
        size_    = 0;
    }
}
