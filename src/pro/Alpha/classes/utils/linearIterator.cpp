#include "linearIterator.hpp"

namespace FVAI
{
    using PointType = linearIterator::PointType;

    PointType linearIterator::getNext() 
    {
        PointType next = path_[current_];
        current_ = (current_ + 1) % size_;
        return next;
    }

    PointType linearIterator::getCurrent() const 
    {
        return path_[current_];
    }

    void linearIterator::setPath(std::vector<PointType> path)
    {
        this->path_     = path;
        this->current_  = 0;
        this->size_     = path.size();
    }

    void linearIterator::addPoint(PointType point)
    {
        path_.push_back(point);
        ++size_;
    }

    std::vector<PointType> linearIterator::getPath()
    {
        return path_;
    }
};
        

