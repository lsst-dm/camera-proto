// -*- lsst-c++ -*-

namespace camera {

// This class is *NOT* a CoordSys subclass: it's the part of a Detector-dependent CoordSys that doesn't
// include the Detector identifier.
class DetectorSys {
public:
    explicit DetectorSys(std::string const & name) : _name(name) {}

    std::string const & getName() const { return _name; }

    // ... hash and comparison stuff, just like CoordSys
};

// We don't need separate classes for these - just separate instances.
namespace sys {

extern CoordSys PUPIL;
extern CoordSys FOCAL_PLANE;
extern DetectorSys PIXEL;

} // namespace sys

} // namespace camera
