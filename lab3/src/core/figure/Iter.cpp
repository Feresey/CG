// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Figure.hpp"
#include "Polygon.hpp"

Figure::Iter::Iter(Figure::Figures::iterator f_start, const Figure::Figures::iterator f_end, Figure::Iter::bit_iterator v)
    : fig_start(f_start)
    , fig_end(f_end)
    , vis(v)
{
    if (fig_start != fig_end && !*vis)
        ++(*this);
}

Figure::Iter::Iter(Figure::Figures::iterator f_start, Figure::Iter::bit_iterator v)
    : Iter(f_start, f_start, v)
{
}

Figure::Iter::reference Figure::Iter::operator*() { return *fig_start; }
Figure::Iter::value_type Figure::Iter::operator*() const { return *fig_start; }
Figure::Iter::reference Figure::Iter::operator->() { return *fig_start; }
Figure::Iter::value_type Figure::Iter::operator->() const { return *fig_start; }

Figure::Iter& Figure::Iter::operator++()
{
    do {
        ++fig_start;
        ++vis;
    } while (fig_start != fig_end && *vis == false);
    return *this;
}

bool Figure::Iter::operator==(const Iter& other) { return fig_start == other.fig_start; }
bool Figure::Iter::operator!=(const Iter& other) { return !(*this == other); }

Figure::Iter Figure::begin()
{
    auto cb = visible.cbegin(),
         ce = visible.cend();
    if (cb == ce)
        throw std::range_error("Cannot create iterator: Figures is not set!!!");
    return Iter(changed.begin(), changed.end(), visible.cbegin());
}
Figure::Iter Figure::end() { return Iter(changed.end(), visible.cend()); }
