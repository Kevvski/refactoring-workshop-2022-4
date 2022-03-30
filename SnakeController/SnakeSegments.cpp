#include "SnakeSegments.hpp"
#include <algorithm>
#include <memory>
#include "EventT.hpp"
#include "SnakeInterface.hpp"


void SnakeSegments::addSegment(const Segment& segment)
{
    m_segments.push_back(segment);
}


void SnakeSegments::addHeadSegment(const Segment& segment, IPort& displayPort)
{
    m_segments.push_front(segment);

    Snake::DisplayInd placeNewHead;
    placeNewHead.x = segment.x;
    placeNewHead.y = segment.y;
    placeNewHead.value = Snake::Cell_SNAKE;

    displayPort.send(std::make_unique<EventT<Snake::DisplayInd>>(placeNewHead));
}


Segment SnakeSegments::calculateNewHead(int x, int y) const
{
    Segment const& currentHead = m_segments.front();

    Segment newHead;
    newHead.x = currentHead.x + x;
    newHead.y = currentHead.y + y;

    return newHead;
}


void SnakeSegments::removeTailSegment(IPort& displayPort)
{
    auto tail = m_segments.back();

    Snake::DisplayInd l_evt;
    l_evt.x = tail.x;
    l_evt.y = tail.y;
    l_evt.value = Snake::Cell_FREE;
    displayPort.send(std::make_unique<EventT<Snake::DisplayInd>>(l_evt));

    m_segments.pop_back();
}


bool SnakeSegments::isOnPosition(int x, int y) const
{
    return m_segments.end() !=  std::find_if(m_segments.cbegin(), m_segments.cend(),
        [x, y](auto const& segment){ return segment.x == x and segment.y == y; });
}