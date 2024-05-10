#include "SVGElements.hpp"

namespace svg
{
    // These must be defined!
    SVGElement::SVGElement() {}
    SVGElement::~SVGElement() {}

    // Ellipse (initial code provided)
    Ellipse::Ellipse(const Color &fill,
                     const Point &center,
                     const Point &radius)
        : fill(fill), center(center), radius(radius)
    {
    }
    void Ellipse::draw(PNGImage &img) const
    {
        img.draw_ellipse(center, radius, fill);
    }
    // @todo provide the implementation of SVGElement derived classes
    // HERE -->

    // Circle (initial code provided)
    Circle::Circle(const Color &fill,
                   const Point &center,
                   const int &radius)
        : Ellipse(fill, center, Point{radius, radius}), radius(radius)
    {
    }
    void Circle::draw(PNGImage &img) const
    {
        img.draw_ellipse(center, Point{radius, radius}, fill);
    }

    // Polygon (initial code provided)
    Polygon::Polygon(const Color &fill,
                     const std::vector<Point> &points)
        : fill(fill), points(points)
    {
    }
    void Polygon::draw(PNGImage &img) const
    {
        img.draw_polygon(points, fill);
    }

    // Rect (initial code provided)
    Rect::Rect(const Color &fill,
               const Point &top_left,
               const Point &bottom_right)
        : Polygon(fill, {top_left, Point{bottom_right.x, top_left.y}, bottom_right, Point{top_left.x, bottom_right.y}})
    {
    }
    void Rect::draw(PNGImage &img) const
    {
        img.draw_polygon(points, fill);
    }

    // Polyline (initial code provided)
    Polyline::Polyline(const Color &stroke,
                       const std::vector<Point> &points)
        : stroke(stroke), points(points)
    {
    }
    void Polyline::draw(PNGImage &img) const
    {
        for (size_t i = 0; i < points.size() - 1; ++i)
        {
            img.draw_line(points[i], points[i + 1], stroke);
        }
    }

    // Line (initial code provided)
    Line::Line(const Color &stroke,
               const Point &start,
               const Point &end)
        : Polyline(stroke, {start, end}), start(start), end(end)
    {
    }
    void Line::draw(PNGImage &img) const
    {
        img.draw_line(start, end, stroke);
    }
}
