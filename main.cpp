#include <iostream>
#include <vector>


class Shape
{
protected:
	unsigned perim{ 0 };
public:
	Shape() = default;
	Shape(unsigned setPer): perim(setPer)
	{}

	virtual void draw(std::string fillStr = " ") {
		std::cout << "Shape::draw" << std::endl;
	}

	virtual unsigned perimeter() { return perim; }
};


class Triangle: public Shape
{
protected:
	unsigned size{ 5 };
public:
	Triangle(unsigned setSize) : Shape(3 * setSize), size(setSize)
	{}

	void draw(std::string fillStr = " ") override
	{
		std::cout << std::endl;
		unsigned delta{ 1 };
		for (unsigned i{ 0 }; i < size; ++i)
		{
			for (unsigned j{ 0 }; j < size - i; ++j)
				std::cout << " ";
			std::cout << "*";

			if (i == 0)
			{ 
				std::cout << std::endl;
				continue;
			}

			for (unsigned j{ 0 }; j < delta; ++j)
				std::cout << ((i == size - 1)?"*":fillStr);
			delta += 2;
			std::cout << "*";
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
};

class FilledTriangle : public Triangle
{
public:
	FilledTriangle(unsigned setSize): Triangle(setSize)
	{}

	void draw(std::string fillStr = " ") override
	{ Triangle::draw("*"); }

};


class Rectangle: public Shape
{
protected:
	unsigned a{ 3 }, b{ 5 };
public:
	Rectangle(unsigned height, unsigned width) : Shape(2 * (height + width)), a(height), b(width)
	{}

	void draw(std::string fillStr = " ") override
	{
		std::cout << std::endl;
		for (unsigned i{ 0 }; i < a; ++i)
		{
			for (unsigned j{ 0 }; j < b; ++j)
				if (i == 0 || i == a - 1)
					std::cout << "*";
				else
					std::cout << ((j == 0 || j == b - 1)?"*":fillStr);
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
};

class FilledRectangle : public Rectangle
{
public:
	FilledRectangle(unsigned height, unsigned width): Rectangle(height, width)
	{}

	void draw(std::string fillStr = " ") override
	{ Rectangle::draw("*"); }
};


class Romb: public Shape
{
protected:
	unsigned size{ 5 };
public:
	Romb(unsigned setSize): Shape(4 * setSize), size(setSize)
	{}

	void draw(std::string fillStr = " ") override
	{
		std::cout << std::endl;
		unsigned innerWidth{ 1 };
		unsigned before{ size - 1 };
		for (unsigned i{ 0 }; i < size * 2 - 1; ++i)
		{

			for (unsigned j{ 0 }; j < before; ++j)
				std::cout << ' ';
			std::cout << "*";

			if (i < size - 1)
				--before;
			else
				++before;

			if (i == 0)
			{
				std::cout << std::endl;
				continue;
			}

			for (unsigned j{ 0 }; j < innerWidth; ++j)
				std::cout << fillStr;
			if (i < size - 1)
				innerWidth += 2;
			else
				innerWidth -= ((i < size * 2 - 3)?2:1);
			
			if (i != size * 2 - 2)
				std::cout << "*";
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
};

class FilledRomb : public Romb
{
public:
	FilledRomb(unsigned setSize) : Romb(setSize)
	{}

	void draw(std::string fillStr = " ") override
	{ Romb::draw("*"); }

};

Shape createShape(std::string type, int size, unsigned secSize = 0, bool isFilled = true)
{
	Shape sh;
	if (type == "Triangle")
		sh = (isFilled) ? FilledTriangle(size) : Triangle(size);
	
	if (type == "Romb")
		sh = (isFilled) ? FilledRomb(size) : Romb(size);
	
	if (type == "Rectangle") {
		if (!secSize)
			secSize = 2 * size;
		sh = (isFilled) ? FilledRectangle(size, secSize) : Rectangle(size, secSize);
	}

	return sh;
}

class Canvas
{
	std::vector<Shape*>shapes;

public:
	void renderAll() 
	{
		for (Shape* each : shapes)
			each->draw();
	}

	void addFigure(Shape* shp)
	{
		shapes.push_back(shp);
	}
};

int main()
{
	FilledRectangle r1{ 10, 30 };
	Rectangle* r2 = &r1;
	r2->draw();
	Rectangle rct1{ 10, 50 };
	rct1.draw();

	FilledTriangle t1{ 10 };
	Triangle& t2 = t1;
	t2.draw();
	Triangle tri1{ 6 };
	tri1.draw();

	FilledRomb rmb1{ 10 };
	Romb& rmb2 = rmb1;
	rmb2.draw();
	Shape* rmb3 = &rmb1;
	Romb rmb4{ 6 };
	rmb4.draw();
	//rmb3->draw();

	Canvas cnv;
	cnv.addFigure(&r1);
	cnv.addFigure(r2);
	cnv.addFigure(&t1);
	cnv.addFigure(&t2);
	cnv.addFigure(&rmb1);
	cnv.addFigure(&rmb2);
	cnv.addFigure(rmb3);
	cnv.renderAll();

	Shape s = createShape("Rectangle", 5);
	s.draw();
	int p = s.perimeter();
	std::cout << "Perimeter: " << p << std::endl;
}