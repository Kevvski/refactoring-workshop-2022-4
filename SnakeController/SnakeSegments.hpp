#pragma once
#include <list>
#include "IPort.hpp"


struct Segment
{
    int x;
    int y;
};

class SnakeSegments
{
    public:
    void addSegment(const Segment& segment);
    void addHeadSegment(const Segment& segment, IPort& displayPort);
    Segment calculateNewHead(int x, int y) const;
    void removeTailSegment(IPort& displayPort);

    bool isOnPosition(int x, int y) const;

    private:
    std::list<Segment> m_segments;
};