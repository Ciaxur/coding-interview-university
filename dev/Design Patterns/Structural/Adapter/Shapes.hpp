/*
  OOP for placing simple shapes in their holes.
  Peg and Hold Game played as a Child
*/


/** PEGS */
class RoundPeg {
private:
  float _radius;

public:
  RoundPeg(float radius): _radius(radius) {}
  float getRadius() { return _radius; }
};

class SquarePeg {
  private:
  float _width;

public:
  SquarePeg(float width): _width(width) {}
  float getWidth() { return _width; }
};


/** ADAPTER PEGS */
class AdapterSquarePeg: public RoundPeg {
private:
  SquarePeg *_sp;

public:
  AdapterSquarePeg(SquarePeg &sp): _sp(&sp), RoundPeg(sp.getWidth() * sqrt(2) / 2) {}
};



/** HOLES */
class RoundHole {
private:
  float _radius;
  
public:
  RoundHole(float radius): _radius(radius) {}

  // Checks if given Object fits
  bool fits(RoundPeg *peg) {
    return this->_radius >= peg->getRadius();
  }
};