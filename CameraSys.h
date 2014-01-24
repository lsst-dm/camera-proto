// -*- lsst-c++ -*-

/**
 * Virtual base class for camera and detector coordinate systems
 */
class CameraSys : public geom::CoordSys {
public:
    /**
     * Get detector name, or "" if not detector-based
     */
    std::string getDetectorName() const = 0;

    /**
     * Is this coordinate system detector-based (hence can detector name be non-blank)?
     */
    bool isDetectorBased() const = 0;
};

/**
 * Virtual base class for non-detector-based coordinate systems, such as focal plane and pupil
 */
class NonDetectorSys : public CameraSys {
public:
    std::string getDetectorName() const { return ""; }
    bool isDetectorBased() const { return false; }
};

/**
 * Virtual base class for detector-based coordinate systems, such as pixels
 */
class DetectorSys : public CameraSys {
public:
    explicit DetectorSys(std::string const &detectorName)
    :
        _detectorName(detectorName), _name(_makeName()
    {}
    ~DetectorSys() {}

    std::string getDetectorName() const { return _detectorName; }
    bool isDetectorBased() const { return true; }
private:
    /** return the class name; used by _makeName; subclasses must override */
    std::string _getClassName() const = 0;

    /** construct the unique name */
    std::string _makeName() const {
        std::ostringstream os;
        os << getClassName() << "(" << getDetectorName() << ")";
        return os.str();
    }
    std::string _detectorName;  ///< detector name
};

/**
 * Pupil coordinates
 */
class PupilSys : public NonDetectorSys {
public:
    explicit PupilSys() : geom::CameraSys("PupilSys()") {}
    ~PupilSys() {}
    CONST_PTR(CameraSys) clone() const { return boost::make_shared<PupilSys>(); }
};

/**
 * Focal plane coordinates
 */
class FocalPlaneSys : public NonDetectorSys {
public:
    explicit FocalPlaneSys() : geom::CameraSys("FocalPlaneSys()") {}
    ~FocalPlaneSys() {}
    CONST_PTR(CameraSys) clone() const { return boost::make_shared<FocalPlaneSys>(); }
};

/**
 * Nominal pixels in a detector (not counting imperfections, "tree rings", etc.)
 */
class PixelSys : public DetectorSys {
public:
    explicit DetectorSys(std::string _detectorName) : DetectorSys(detectorName) {}
    ~DetectorSys() {}
    CONST_PTR(CameraSys) clone() const { return boost::make_shared<PixelSys>(_detectorName); }
private:
    std::string _getClassName() const { return "PixelSys"; }
};
