#include "circularIterator.hpp"

namespace FVAI
{
    using PointType = circularIterator::PointType;

    PointType circularIterator::getNext() 
    {
        PointType next = path_[current_];
        current_ = (current_ + 1) % size_;
        return next;
    }

    PointType circularIterator::getCurrent() const 
    {
        return path_[current_];
    }

    void circularIterator::setPath(std::vector<PointType> path)
    {
        this->path_     = path;
        this->current_  = 0;
        this->size_     = path.size();
    }

    void circularIterator::addPoint(PointType point)
    {
        path_.push_back(point);
        ++size_;
    }
};
        

