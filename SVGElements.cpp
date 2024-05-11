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
    void svg::Ellipse::translate(Point &t)
    {
        center = center.translate(t);
    }
    void svg::Ellipse::rotate(const Point &origin, int degrees)
    {
        center = center.rotate(origin, degrees);
    }
    void svg::Ellipse::scale(const Point &origin, int v)
    {
        // Calculate the distance from the center to the scaling origin
        Point dist;
        dist.x = center.x - origin.x;
        dist.y = center.y - origin.y;

        // Scale the distance
        dist.x = dist.x * v;
        dist.y = dist.y * v;

        // Move the center to the new location
        center.x = origin.x + dist.x;
        center.y = origin.y + dist.y;

        // Scale the radius
        radius.x = radius.x * v;
        radius.y = radius.y * v;
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
    void svg::Circle::translate(Point &t)
    {
        center = center.translate(t);
    }
    void svg::Circle::rotate(const Point &origin, int degrees)
    {
        center = center.rotate(origin, degrees);
    }
    void svg::Circle::scale(const Point &origin, int v)
    {
        Point dist;
        dist.x = center.x - origin.x;
        dist.y = center.y - origin.y;

        // Scale the distance
        dist.x = dist.x * v;
        dist.y = dist.y * v;

        // Move the center to the new location
        center.x = origin.x + dist.x;
        center.y = origin.y + dist.y;

        // Scale the radius
        radius = radius * v;
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
    void svg::Polygon::translate(Point &t)
    {
        for (auto &point : points)
        {
            point = point.translate(t);
        }
    }
    void svg::Polygon::rotate(const Point &origin, int degrees)
    {
        for (auto &point : points)
        {
            point = point.rotate(origin, degrees);
        }
    }
    void svg::Polygon::scale(const Point &origin, int v)
    {
        for (Point &point : points)
        {
            Point dist;
            dist.x = point.x - origin.x;
            dist.y = point.y - origin.y;

            // Scale the distance
            dist.x *= v;
            dist.y *= v;

            // Move the point to the new location
            point.x = origin.x + dist.x;
            point.y = origin.y + dist.y;
        }
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
    void svg::Rect::translate(Point &t)
    {
        for (auto &point : points)
        {
            point = point.translate(t);
        }
    }
    void svg::Rect::rotate(const Point &origin, int degrees)
    {
        for (auto &point : points)
        {
            point = point.rotate(origin, degrees);
        }
    }
    void svg::Rect::scale(const Point &origin, int v)
    {
        for (Point &point : points)
        {
            Point dist;
            dist.x = point.x - origin.x;
            dist.y = point.y - origin.y;

            // Scale the distance
            dist.x *= v;
            dist.y *= v;

            // Move the point to the new location
            point.x = origin.x + dist.x;
            point.y = origin.y + dist.y;
        }
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
    void svg::Polyline::translate(Point &t)
    {
        for (auto &point : points)
        {
            point = point.translate(t);
        }
    }
    void svg::Polyline::rotate(const Point &origin, int degrees)
    {
        for (auto &point : points)
        {
            point = point.rotate(origin, degrees);
        }
    }
    void svg::Polyline::scale(const Point &origin, int v)
    {
        for (Point &point : points)
        {
            Point dist;
            dist.x = point.x - origin.x;
            dist.y = point.y - origin.y;

            // Scale the distance
            dist.x *= v;
            dist.y *= v;

            // Move the point to the new location
            point.x = origin.x + dist.x;
            point.y = origin.y + dist.y;
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
    void svg::Line::translate(Point &t)
    {
        start = start.translate(t);
        end = end.translate(t);
    }
    void svg::Line::rotate(const Point &origin, int degrees)
    {
        start = start.rotate(origin, degrees);
        end = end.rotate(origin, degrees);
    }
    void svg::Line::scale(const Point &origin, int v)
    {
        Point dist;
        dist.x = start.x - origin.x;
        dist.y = start.y - origin.y;

        // Scale the distance
        dist.x *= v;
        dist.y *= v;

        // Move the start point to the new location
        start.x = origin.x + dist.x;
        start.y = origin.y + dist.y;

        // Do the same for the end point
        dist.x = end.x - origin.x;
        dist.y = end.y - origin.y;
        dist.x *= v;
        dist.y *= v;
        end.x = origin.x + dist.x;
        end.y = origin.y + dist.y;
    }

    // Group (initial code provided)
    Group::Group(const std::vector<SVGElement *> &elements)
        : elements(elements)
    {
    }
    void Group::draw(PNGImage &img) const
    {
        for (const auto &element : elements)
        {
            element->draw(img);
        }
    }
    void svg::Group::translate(Point &t)
    {
        for (auto &element : elements)
        {
            element->translate(t);
        }
    }
    void svg::Group::rotate(const Point &origin, int degrees)
    {
        for (auto &element : elements)
        {
            element->rotate(origin, degrees);
        }
    }
    void svg::Group::scale(const Point &origin, int v)
    {
        for (auto &element : elements)
        {
            element->scale(origin, v);
        }
    }
}