// -*- lsst-c++ -*-

namespace geom {

class TransformRegistry {
public:

    // ...

private:
    // Pass and hold CoordSys by value - it's nonpolymorphic and cheap to copy (and if it isn't we'll wrap
    // the std::string in a flyweight or shared_ptr).
    typedef std::map<CoordSys,PTR(XYTransform)> Map;
    Map _map;
    CoordSys _reference;
};

} // namespace geom
