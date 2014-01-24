// -*- lsst-c++ -*-

namespace camera {

class Detector {
public:

    CoordSys const PIXELS; // maybe weird to make this a const data member, but it makes for a consistent
                           // user interface with the non-detector-specific CoordSys objects.

    // ... other methods; convert() delegates to lookup(), below

    // Here's the ugly part: this needs to be instantiated 4 times, for each combination of CoordSys and
    // DetectorSys, and so does everything that delegates to it (like convert()).
    template <typename SourceSys, typename DestinationSys>
    PTR(XYTransform) lookup(SourceSys const & source, DestinationSys const & destination) const {
        return _registry.lookup(getCoordSys(source), getCoordSys(destination));
    }

    CoordSys const & getCoordSys(DetectorSys const & sys) const { return _allSys[sys]; }

private:

    // We don't need this one to be public, since it's just a pass-through
    CoordSys const & getCoordSys(CoordSys const & sys) const { return sys; }

    std::map<DetectorSys,CoordSys> _allSys; // includes PIXELS, too (minor duplication)
    geom::TransformRegistry _registry;
};


} // namespace camera
