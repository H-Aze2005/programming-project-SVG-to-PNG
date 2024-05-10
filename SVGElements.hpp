//! @file shape.hpp
#ifndef __svg_SVGElements_hpp__
#define __svg_SVGElements_hpp__

#include "Color.hpp"
#include "Point.hpp"
#include "PNGImage.hpp"

namespace svg
{
    class SVGElement
    {

    public:
        SVGElement();
        virtual ~SVGElement();
        virtual void draw(PNGImage &img) const = 0;
    };

    // Declaration of namespace functions
    // readSVG -> implement it in readSVG.cpp
    // convert -> already given (DO NOT CHANGE) in convert.cpp

    void readSVG(const std::string &svg_file,
                 Point &dimensions,
                 std::vector<SVGElement *> &svg_elements);
    void convert(const std::string &svg_file,
                 const std::string &png_file);

    class Ellipse : public SVGElement
    {
    public:
        Ellipse(const Color &fill, const Point &center, const Point &radius);
        void draw(PNGImage &img) const override;

    protected:
        Color fill;
        Point center;
        Point radius;
    };

    class Circle : public Ellipse
    {
    public:
        Circle(const Color &fill, const Point &center, const int &radius);
        void draw(PNGImage &img) const override;
    private:
        int radius;
    };

    class Polygon : public SVGElement
    {
    public:
        Polygon(const Color &fill, const std::vector<Point> &points);
        void draw(PNGImage &img) const override;
    protected:
        Color fill;
        std::vector<Point> points;
    };

    class Rect : public Polygon
    {
    public:
        Rect(const Color &fill, const Point &top_left, const Point &bottom_right);
        void draw(PNGImage &img) const override;
    private:
        Point top_left;
        Point bottom_right;
    };

    class Polyline : public SVGElement
    {
    public:
        Polyline(const Color &stroke, const std::vector<Point> &points);
        void draw(PNGImage &img) const override;
    protected:
        Color stroke;
        std::vector<Point> points;
    };

    class Line : public Polyline
    {
    public:
        Line(const Color &stroke, const Point &start, const Point &end);
        void draw(PNGImage &img) const override;
    private:
        Point start;
        Point end;
    };

}
#endif
